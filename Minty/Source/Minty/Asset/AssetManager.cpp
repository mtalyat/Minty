#include "pch.h"
#include "AssetManager.h"
#include "Minty/Core/Format.h"
#include "Minty/Context/Context.h"

using namespace Minty;

Minty::AssetManager::AssetManager(AssetManagerBuilder const& builder)
	: m_savePaths(builder.savePaths)
	, m_assets()
	, m_assetTypes()
	, m_handles()
	, m_assetsMutex()
	, m_wrapper()
{
	for (Path const& path : builder.wraps)
	{
		load_wrap(path);
	}
}

Minty::AssetManager::~AssetManager()
{
	// sync to finish loading/unloading
	sync();

	// unload the rest
	unload_all();
}

AssetManager::Location Minty::AssetManager::get_location(Path const& path) const
{
	if (m_wrapper.contains(path))
	{
		return Location::Wrapper;
	}

	if (Path::exists(path))
	{
		return Location::FileSystem;
	}

	return Location::Undefined;
}

ID Minty::AssetManager::read_id(Path const& path) const
{
	MINTY_ASSERT(exists(path), "Cannot read ID from file that does not exist.");

	Path metaPath = Asset::get_meta_path(path);

	MINTY_ASSERT(Path::exists(metaPath), "Cannot read ID from file that does not have a meta file.");

	File* file = open(metaPath);

	MINTY_ASSERT(file != nullptr, "Failed to open meta file for reading.");

	// read the first line
	String line;
	Bool result = file->read_line(line);
	MINTY_ASSERT(result && line.starts_with(": ") && line.get_size() == 18, "Failed to read ID from meta file: meta file not in correct format.");

	// get the ID
	String idString = line.sub(2, 16);
	UUID id = parse_to<UUID>(idString);

	close(file);

	return id;
}

File* Minty::AssetManager::open(Path const& path) const
{
	File* file = nullptr;

	switch (get_location(path))
	{
	case Location::FileSystem:
		file = new PhysicalFile(path, File::Flags::Read | File::Flags::Binary);
		break;
	case Location::Wrapper:
		file = new VirtualFile();
		m_wrapper.open(path, *static_cast<VirtualFile*>(file));
		break;
	}

	return file;
}

void Minty::AssetManager::close(File* file) const
{
	file->close();
	delete file;
}

Bool Minty::AssetManager::load_wrap(Path const& path)
{
	if (!Path::exists(path))
	{
		MINTY_ERROR(F("Cannot load Wrap file. Path does not exist: {}", path));
		return false;
	}

	m_wrapper.add(path);

	return true;
}

Bool Minty::AssetManager::exists(Path const& path) const
{
	return m_wrapper.contains(path) || Path::exists(path);
}

Bool Minty::AssetManager::open_reader(Path const& path, Reader*& reader) const
{
	// open file
	File* file = open(path);

	// if no file open, failed
	if (file == nullptr)
	{
		reader = nullptr;
		return false;
	}

	// create reader
	reader = new TextFileReader(file);

	return true;
}

void Minty::AssetManager::close_reader(Reader*& reader) const
{
	MINTY_ASSERT(reader != nullptr, "Reader is null.");

	// close the file
	File* file = static_cast<File*>(reader->get_source());
	close(file);

	// delete the reader
	delete reader;
	reader = nullptr;
}

Bool Minty::AssetManager::open_writer(Path const& path, Writer*& writer) const
{
	if (!Path::exists(path.get_parent()))
	{
		return false;
	}

	File* file = new PhysicalFile(path, File::Flags::Write);
	writer = new TextFileWriter(file);

	return true;
}

void Minty::AssetManager::close_writer(Writer*& writer) const
{
	MINTY_ASSERT(writer != nullptr, "Writer is null.");

	// close the file
	File* file = static_cast<File*>(writer->get_source());
	close(file);

	// delete the writer
	delete writer;
	writer = nullptr;
}

UUID Minty::AssetManager::schedule_load(Path const& path)
{
	MINTY_ASSERT(exists(path), "Cannot load Asset. The file does not exist.");
	Path metaPath = Asset::get_meta_path(path);
	MINTY_ASSERT(exists(metaPath), "Cannot load Asset. The meta file does not exist.");

	JobManager& jobManager = JobManager::get_singleton();

	// get UUID for reference
	UUID id = read_id(path);

	MINTY_ASSERT(!m_handles.contains(id), "Asset with the given ID is already being operated on.");

	// use a job to load the asset in the background
	Handle handle = jobManager.schedule([this, path, id]()
		{
			load_asset(path);
			{
				std::unique_lock lock(m_assetsMutex);
				m_handles.remove(id);
			}
		});

	{
		std::unique_lock lock(m_assetsMutex);
		m_handles.add(id, handle);
	}

	// return the ID
	return id;
}

Ref<Asset> Minty::AssetManager::load_asset(Path const& path)
{
#ifdef MINTY_DEBUG
	MINTY_ASSERT(exists(path), "Cannot load Asset. The file does not exist.");
	Path metaPath = Asset::get_meta_path(path);
	MINTY_ASSERT(exists(metaPath), "Cannot load Asset. The meta file does not exist.");
#endif // MINTY_DEBUG

	AssetType type = Asset::get_asset_type(path);

	switch (type)
	{
	case AssetType::Generic:
		return load_generic(path);
	default:
		MINTY_ABORT("Not implemented.");
		return Ref<Asset>();
	}
}

void Minty::AssetManager::schedule_unload(UUID const id)
{
	MINTY_ASSERT(contains(id), "Asset with the given ID does not exist.");
	MINTY_ASSERT(!m_handles.contains(id), "Asset with the given ID is already being operated on.");

	JobManager& jobManager = JobManager::get_singleton();

	// use a job to unload the asset in the background
	Handle handle = jobManager.schedule([this, id]()
		{
			unload(id);
			{
				std::unique_lock lock(m_assetsMutex);
				m_handles.remove(id);
			}
		});

	{
		std::unique_lock lock(m_assetsMutex);
		m_handles.add(id, handle);
	}
}

void Minty::AssetManager::unload(UUID const id)
{
	MINTY_ASSERT(contains(id), "Asset with the given ID does not exist.");

	// get the asset
	Owner<Asset> asset = m_assets.at(id).asset;

	// unload
	asset->on_unload();

	// remove from the lists
	remove(id);
}

void Minty::AssetManager::unload_all()
{
	// unload all assets
	for (auto const& pair : m_assets)
	{
		pair.second.asset->on_unload();
	}

	// clear the lists
	m_assets.clear();
	m_assetTypes.clear();
}

void Minty::AssetManager::sync()
{
	// get list of handles
	Vector<Handle> handles(m_handles.get_size());
	{
		std::unique_lock lock(m_assetsMutex);
		for (auto const& pair : m_handles)
		{
			handles.add(pair.second);
		}
	}

	// wait for them all
	JobManager& jobManager = JobManager::get_singleton();
	jobManager.wait(handles);

	// clear the handles
	{
		std::unique_lock lock(m_assetsMutex);
		m_handles.clear();
	}
}

Bool Minty::AssetManager::is_syncing() const
{
	// if any handles saved, the manager is syncing asset files
	return m_handles.get_size() > 0;
}

void Minty::AssetManager::add(Path const& path, Owner<Asset> const& asset)
{
	// create asset data
	AssetData data;
	data.asset = asset;
	if (m_savePaths)
	{
		data.path = path;
	}
	else
	{
		data.path = Path();
	}

	// add to lists
	UUID id = asset->get_id();
	MINTY_ASSERT(id.is_valid(), "Asset ID is invalid.");
	MINTY_ASSERT(!m_assets.contains(id), "Asset with the given ID already exists.");
	AssetType assetType = asset->get_asset_type();
	{
		std::unique_lock lock(m_assetsMutex);
		m_assets.add(id, data);
		auto it = m_assetTypes.find(assetType);
		if (it == m_assetTypes.end())
		{
			Set<UUID> set;
			set.add(id);
			m_assetTypes.add(assetType, std::move(set));
		}
		else
		{
			it->second.add(id);
		}
	}
}

Bool Minty::AssetManager::contains(UUID const id) const
{
	return m_assets.contains(id);
}

Ref<Asset> Minty::AssetManager::get_asset(UUID const id) const
{
	std::unique_lock lock(m_assetsMutex);

	// find the asset
	auto it = m_assets.find(id);

	// if not found, return null
	if (it == m_assets.end())
	{
		return Ref<Asset>();
	}

	// return the asset
	return it->second.asset.create_ref();
}

Ref<Asset> Minty::AssetManager::at_asset(UUID const id) const
{
	std::unique_lock lock(m_assetsMutex);
	MINTY_ASSERT(contains(id), "Asset with the given ID does not exist.");
	return m_assets.at(id).asset.create_ref();
}

Path Minty::AssetManager::get_asset_path(UUID const id) const
{
	// return empty if no paths
	if (!m_savePaths)
	{
		return Path();
	}

	std::unique_lock lock(m_assetsMutex);

	// find asset
	auto it = m_assets.find(id);
	
	// ignore if not found
	if (it == m_assets.end())
	{
		return Path();
	}

	// return path
	return it->second.path;
}

String Minty::AssetManager::get_asset_name(UUID const id) const
{
	// return empty if no paths
	if (!m_savePaths)
	{
		return String();
	}

	MINTY_ASSERT(contains(id), "Asset with the given ID does not exist.");

	// get path
	std::unique_lock lock(m_assetsMutex);
	Path const& path = m_assets.at(id).path;

	// get name
	return path.get_name().get_string();
}

Owner<Asset> Minty::AssetManager::remove(UUID const id)
{
	MINTY_ASSERT(contains(id), "Asset with the given ID does not exist.");

	// get asset
	Owner<Asset> asset;
	{
		std::unique_lock lock(m_assetsMutex);
		asset = m_assets.at(id).asset;

		// remove from lists
		AssetType type = asset->get_asset_type();

		m_assets.remove(id);
		m_assetTypes.at(type).remove(id);
	}

	// return asset
	return asset;
}

Vector<Ref<Asset>> Minty::AssetManager::get_dependents(UUID const id) const
{
	Vector<Ref<Asset>> result;

	// get the asset
	Ref<Asset> asset = get_asset(id);

	// get type
	AssetType type = asset->get_asset_type();

	// check based on type
	// some types inherently have no dependents, some do
	MINTY_ABORT("Not implemented.");
	//switch (type)
	//{
	//case AssetType::Shader:
	//	// MaterialTemplates use Shaders
	//	for (auto const materialTemplate : get_by_type<MaterialTemplate>())
	//	{
	//		if (materialTemplate->get_shader() == asset)
	//		{
	//			// the materialTemplate uses this shader
	//			result.add(materialTemplate);
	//		}
	//	}
	//	break;
	//case AssetType::MaterialTemplate:
	//	// Materials use MaterialTemplates
	//	for (auto const material : get_by_type<Material>())
	//	{
	//		if (material->get_template() == asset)
	//		{
	//			result.add(material);
	//		}
	//	}
	//	break;
	//case AssetType::Material:
	//	// TODO: models depend on materials?
	//	break;
	//case AssetType::Texture:
	//	// Sprites use Textures
	//	for (auto const sprite : get_by_type<Sprite>())
	//	{
	//		if (sprite->get_texture() == asset)
	//		{
	//			result.add(sprite);
	//		}
	//	}
	//	// FontVariants use Textures and Material Templates
	//	for (auto const font : get_by_type<FontVariant>())
	//	{
	//		if (font->get_texture() == asset)
	//		{
	//			result.add(font->get_texture());
	//		}
	//		else if (font->get_material().get() && (font->get_material()->get_template() == asset))
	//		{
	//			result.add(font->get_material()->get_template());
	//		}
	//	}
	//	break;
	//case AssetType::FontVariant:
	//	// Fonts use FontVariants
	//	for (auto const font : get_by_type<Font>())
	//	{
	//		for (Ref<FontVariant> const variant : font->get_variants())
	//		{
	//			if (variant == asset)
	//			{
	//				result.add(variant);
	//			}
	//		}
	//	}
	//}

	return result;
}

String Minty::AssetManager::read_text(Path const& path) const
{
	MINTY_ASSERT(exists(path), "Cannot read text from file that does not exist.");

	File* file = open(path);

	MINTY_ASSERT(file != nullptr, "Failed to open file for reading.");

	String text = file->read_text();

	close(file);

	return text;
}

Vector<String> Minty::AssetManager::read_lines(Path const& path) const
{
	MINTY_ASSERT(exists(path), "Cannot read lines from file that does not exist.");

	File* file = open(path);

	MINTY_ASSERT(file != nullptr, "Failed to open file for reading.");

	Vector<String> lines = file->read_lines();

	close(file);

	return lines;
}

Vector<Byte> Minty::AssetManager::read_bytes(Path const& path) const
{
	MINTY_ASSERT(exists(path), "Cannot read bytes from file that does not exist.");

	File* file = open(path);

	MINTY_ASSERT(file != nullptr, "Failed to open file for reading.");
	
	Vector<Byte> bytes = file->read_bytes();

	close(file);

	return bytes;
}

Ref<GenericAsset> Minty::AssetManager::load_generic(Path const& path)
{
	Vector<Byte> bytes = read_bytes(path);

	GenericAssetBuilder builder
	{
		.id = read_id(path),
		.data = ConstantContainer(bytes.get_data(), bytes.get_size())
	};

	return create_from_loaded<GenericAsset>(path, builder);
}

Owner<AssetManager> Minty::AssetManager::create(AssetManagerBuilder const& builder)
{
	return Owner<AssetManager>(builder);
}

AssetManager& Minty::AssetManager::get_singleton()
{
	return Context::get_singleton().get_asset_manager();
}
