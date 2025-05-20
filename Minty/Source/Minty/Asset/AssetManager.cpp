#include "pch.h"
#include "AssetManager.h"
#include "Minty/Core/Format.h"
#include "Minty/Context/Context.h"
#include "Minty/Library/STB.h"
#include "Minty/Render/Image.h"
#include "Minty/Render/ImagePixelFormat.h"
#include "Minty/Render/Material.h"
#include "Minty/Render/MaterialTemplate.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Render/RenderAttachment.h"
#include "Minty/Render/RenderPass.h"
#include "Minty/Render/Shader.h"
#include "Minty/Render/ShaderModule.h"
#include "Minty/Render/Texture.h"
#include "Minty/Render/Viewport.h"
//#include "Minty/Render/Sprite.h"

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

	MINTY_ASSERT(exists(metaPath), "Cannot read_bytes ID from file that does not have a meta file.");

	Vector<String> lines = read_lines(metaPath);

	// ignore if empty
	if (lines.is_empty())
	{
		return INVALID_ID;
	}

	// get ID from first line
	String const& line = lines.front();
	MINTY_ASSERT(line.starts_with(": ") && line.get_size() == 18, "Failed to read_bytes ID from meta file: meta file not in correct format.");

	// get the ID
	String idString = line.sub(2, 16);
	UUID id = parse_to<UUID>(idString);

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

void Minty::AssetManager::dispose()
{
	// sync to finish loading/unloading
	sync();

	// unload the rest
	unload_all();

	Manager::dispose();
}

void Minty::AssetManager::update(Time const& time)
{
	// run all of the onCompletion jobs
	{
		std::unique_lock lock(m_onCompletionsMutex);
		while (!m_onCompletions.is_empty())
		{
			Job job = m_onCompletions.pop();
			job();
		}
	}
}

void Minty::AssetManager::sync()
{
	// get list of handles
	Vector<Handle> handles(m_handles.get_size());
	{
		std::unique_lock lock(m_assetsMutex);
		for (auto const& pair : m_handles)
		{
			handles.add(pair.get_second());
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

	// run all of the onCompletion jobs
	{
		std::unique_lock lock(m_onCompletionsMutex);
		while (!m_onCompletions.is_empty())
		{
			Job job = m_onCompletions.pop();
			job();
		}
	}
}

Bool Minty::AssetManager::is_syncing() const
{
	// if any handles saved, the manager is syncing asset files
	return m_handles.get_size() > 0;
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
	// if no file, fail
	if (!exists(path))
	{
		return false;
	}

	// get the file data
	Vector<Byte> bytes = read_bytes(path);

	// if no bytes, fail
	if (bytes.is_empty())
	{
		return false;
	}

	// create container
	ConstantContainer* container = new ConstantContainer(bytes.get_data(), bytes.get_size());

	// create reader
	reader = new TextMemoryReader(container);

	return true;
}

void Minty::AssetManager::close_reader(Reader*& reader) const
{
	MINTY_ASSERT(reader != nullptr, "Reader is null.");

	// delete the container
	ConstantContainer* container = static_cast<ConstantContainer*>(reader->get_source());
	delete container;

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

UUID Minty::AssetManager::schedule_load(Path const& path, Job const& onCompletion)
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
		});
	handle = jobManager.schedule([this, id, onCompletion]()
		{
			// remove handle
			{
				std::unique_lock lock(m_handlesMutex);
				m_handles.remove(id);
			}
			// add to completion queue
			{
				std::unique_lock lock(m_onCompletionsMutex);
				m_onCompletions.push(onCompletion);
			}
		}, handle);

	// add final handle to the list
	{
		std::unique_lock lock(m_handlesMutex);
		m_handles.add(id, handle);
	}

	// return the ID of the Asset
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
	case AssetType::Image:
		return load_image(path);
	case AssetType::Material:
		return load_material(path);
	case AssetType::MaterialTemplate:
		return load_material_template(path);
	//case AssetType::Mesh:
	//	return load_mesh(path);
	case AssetType::RenderPass:
		return load_render_pass(path);
	case AssetType::Shader:
		return load_shader(path);
	case AssetType::ShaderModule:
		return load_shader_module(path);
	//case AssetType::Scene:
	//	return load_scene(path);
	//case AssetType::Sprite:
	//	return load_sprite(path);
	case AssetType::Texture:
		return load_texture(path);
	default:
		MINTY_ABORT("Not implemented.");
		return Ref<Asset>();
	}
}

void Minty::AssetManager::schedule_unload(UUID const id, Job const& onCompletion)
{
	MINTY_ASSERT(contains(id), "Asset with the given ID does not exist.");
	MINTY_ASSERT(!m_handles.contains(id), "Asset with the given ID is already being operated on.");

	JobManager& jobManager = JobManager::get_singleton();

	// use a job to unload the asset in the background
	Handle handle = jobManager.schedule([this, id]()
		{
			unload(id);
		});
	handle = jobManager.schedule([this, id, onCompletion]()
		{
			// remove handle
			{
				std::unique_lock lock(m_handlesMutex);
				m_handles.remove(id);
			}
			// add to completion queue
			{
				std::unique_lock lock(m_onCompletionsMutex);
				m_onCompletions.push(onCompletion);
			}
		}, handle);

	{
		std::unique_lock lock(m_handlesMutex);
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
		pair.get_second().asset->on_unload();
	}

	// clear the lists
	m_assets.clear();
	m_assetTypes.clear();
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
			it->get_second().add(id);
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
	return it->get_second().asset.create_ref();
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
	return it->get_second().path;
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

Vector<Byte> Minty::AssetManager::read_bytes(Path const& path) const
{
	Location location = get_location(path);

	MINTY_ASSERT(location != Location::Undefined, "Cannot read bytes from file that does not exist.");

	switch (location)
	{
	case Location::FileSystem:
		return File::read_bytes(path);
	case Location::Wrapper:
		return m_wrapper.read_bytes(path);
	}

	return Vector<Byte>();
}

String Minty::AssetManager::read_text(Path const& path) const
{
	Vector<Byte> bytes = read_bytes(path);

	if (bytes.is_empty())
	{
		return String();
	}

	// create string from bytes
	return String::from_bytes(bytes.get_data(), bytes.get_size());
}

Vector<String> Minty::AssetManager::read_lines(Path const& path) const
{
	String text = read_text(path);

	// split into lines
	return String::split(text);
}

Int Minty::AssetManager::check_dependency(UUID const id, Path const& path, String const& name, Bool const required) const
{
	// if invalid id (0), set to null
	if (!id.is_valid())
	{
		if (required)
		{
			Debug::write_error(F("Cannot load \"{}\". \"{}\"'s ID was invalid.", path, name));
		}

		return 2;
	}

	// if asset id is valid but asset with id DNE, set to null
	if (!id.is_valid() || !contains(id))
	{
		Debug::write_error(F("Cannot load \"{}\": requires a dependency \"{}\" with ID {} that has not been loaded yet.", path, name, id));
		return -1;
	}

	return 0;
}

Int Minty::AssetManager::read_attachment(Path const& path, Reader& reader, String const& name, RenderAttachment& attachment, Bool const required) const
{
	if (!reader.indent(name))
	{
		if (required)
		{
			Debug::write_error(F("Cannot load \"{}\". Missing \"{}\".", path, name));
		}
		return 1;
	}

	// read the attachment data
	reader.read("Load", attachment.loadOperation, LoadOperation::DontCare);
	reader.read("Store", attachment.storeOperation, StoreOperation::DontCare);
	reader.read("Initial", attachment.initialLayout, ImageLayout::Undefined);
	reader.read("Final", attachment.finalLayout, ImageLayout::Undefined);

	reader.outdent();

	return 0;
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

Owner<Image> Minty::AssetManager::create_image(Path const& path, UUID const id)
{
	// get image data
	Vector<Byte> bytes = read_bytes(path);

	// get pixel data
	int width, height, channels;
	stbi_uc* data = stbi_load_from_memory(static_cast<stbi_uc*>(bytes.get_data()), static_cast<int>(bytes.get_size()), &width, &height, &channels, static_cast<int>(ImagePixelFormat::RedGreenBlueAlpha));
	char const* reason = stbi_failure_reason();
	MINTY_ASSERT(data != nullptr, F("Failed to load image pixel data: {}", reason));

	// create the image
	ImageBuilder builder{};
	builder.id = id;
	builder.size = UInt2(width, height);
	builder.pixelData = data;
	builder.pixelDataSize = static_cast<Size>(width * height * 4 * sizeof(Byte));

	Reader* reader;
	Path metaPath = Asset::get_meta_path(path);
	if (open_reader(metaPath, reader))
	{
		if (!reader->read("Format", builder.format))
		{
			builder.format = Format::Default;
		}
		if (!reader->read("Type", builder.type))
		{
			builder.type = ImageType::D2;
		}
		if (!reader->read("Tiling", builder.tiling))
		{
			builder.tiling = ImageTiling::Optimal;
		}
		if (!reader->read("Aspect", builder.aspect))
		{
			builder.aspect = ImageAspect::Color;
		}
		if (!reader->read("Usage", builder.usage))
		{
			builder.usage = ImageUsage::Sampled;
		}
		close_reader(reader);
	}

	// create the image
	Owner<Image> image = Image::create(builder);

	// free the pixel data
	stbi_image_free(data);

	return image;
}

Ref<Image> Minty::AssetManager::load_image(Path const& path)
{
	// create the image using the path and ID
	Owner<Image> image = create_image(path, read_id(path));

	// add to the asset manager
	add(path, image);

	// done
	return image.create_ref();
}

static void read_values(Reader& reader, Cargo& values)
{
	String objectName;
	String valueName;
	Variable valueVariable;

	for (Size i = 0; i < reader.get_size(); i++)
	{
		// read the name of the object
		if (!reader.read_name(i, objectName))
		{
			continue;
		}

		// enter object
		reader.indent(i);

		// read names and variables for each value
		Object object(reader.get_size() * 2);
		for (Size j = 0; j < reader.get_size(); j++)
		{
			// read the name of the variable
			if (!reader.read_name(j, valueName))
			{
				continue;
			}

			// read the variable
			if (!reader.read(j, valueVariable))
			{
				continue;
			}

			// add to the object values
			object.add(valueName, valueVariable);
		}

		// add values to the object
		values.add(objectName, object);

		// outdent
		reader.outdent();
	}
}

Ref<Material> Minty::AssetManager::load_material(Path const& path)
{
	// create builder
	MaterialBuilder builder{};
	builder.id = read_id(path);

	// read values
	Reader* reader;
	if (open_reader(path, reader))
	{
		// get template
		if (find_dependency<MaterialTemplate>(path, *reader, "Template", builder.materialTemplate, true))
		{
			close_reader(reader);
			return Ref<Material>();
		}

		// read values
		if (reader->indent("Values"))
		{
			read_values(*reader, builder.values);
			reader->outdent();
		}

		close_reader(reader);
	}

	return create_from_loaded<Material>(path, builder);
}

Ref<MaterialTemplate> Minty::AssetManager::load_material_template(Path const& path)
{
	// create builder
	MaterialTemplateBuilder builder{};
	builder.id = read_id(path);

	// read values
	Reader* reader;
	if (open_reader(path, reader))
	{
		if (find_dependency<Shader>(path, *reader, "Shader", builder.shader, true))
		{
			close_reader(reader);
			return Ref<MaterialTemplate>();
		}

		// read values
		if (reader->indent("Values"))
		{
			read_values(*reader, builder.values);
			reader->outdent();
		}

		close_reader(reader);
	}

	return create_from_loaded<MaterialTemplate>(path, builder);
}

Ref<Mesh> Minty::AssetManager::load_mesh_obj(Path const& path)
{
	MeshBuilder builder{};
	builder.id = read_id(path);
	builder.type = MeshType::Custom;

	Vector<String> lines = read_lines(path);

	Vector<Float3> positions;
	Vector<Float2> coords;
	Vector<Float3> normals;

	Map<Int3, UShort> faces;
	UShort vertexCount = 0;

	std::istringstream ss;
	std::string token;

	Float3 position;
	Float2 coord;
	Float3 normal;

	for (auto const& line : lines)
	{
		ss = std::istringstream(line.get_data());
		ss >> token;
		if (token == "v")
		{
			// position
			ss >> position.x >> position.y >> position.z;
			position.y = -position.y; // flip Y
			positions.add(position);
		}
		else if (token == "vt")
		{
			// coord
			ss >> coord.x >> coord.y;
			coord.y = -coord.y; // flip y
			coords.add(coord);
		}
		else if (token == "vn")
		{
			// normal
			ss >> normal.x >> normal.y >> normal.z;
			normal.y = -normal.y;
			normals.add(normal);
		}
		else if (token == "f")
		{
			// face
			// get pairs
			for (size_t i = 0; i < 3; i++)
			{
				std::string set;
				ss >> set;

				std::istringstream setss(set);
				Int3 faceIndices = Int3();

				// subtract 1, since all indices are 1 indexed apparently
				if (std::getline(setss, token, '/'))
				{
					faceIndices.x = to_int(token.c_str()) - 1;

					if (std::getline(setss, token, '/'))
					{
						faceIndices.y = to_int(token.c_str()) - 1;

						if (std::getline(setss, token, '/'))
						{
							faceIndices.z = to_int(token.c_str()) - 1;
						}
					}
				}

				// if combo exists, add that index
				auto found = faces.find(faceIndices);
				if (found == faces.end())
				{
					// vertex does not exist yet
					UShort index = vertexCount;
					position = positions.at(faceIndices.x);
					coord = coords.at(faceIndices.y);
					normal = normals.at(faceIndices.z);

					// create vertex
					builder.vertices.append(&position.x);
					builder.vertices.append(&position.y);
					builder.vertices.append(&position.z);
					builder.vertices.append(&normal.x);
					builder.vertices.append(&normal.y);
					builder.vertices.append(&normal.z);
					builder.vertices.append(&coord.x);
					builder.vertices.append(&coord.y);
					builder.indices.append(&index);

					// add for reference
					faces.add(faceIndices, index);

					// increment count
					vertexCount += 1;
				}
				else
				{
					// vertex already exists
					UShort index = found->get_second();
					builder.indices.append(&index);
				}
			}
		}
	}

	// create the mesh
	return create_from_loaded<Mesh>(path, builder);
}

Ref<Mesh> Minty::AssetManager::load_mesh(Path const& path)
{
	String extension = path.get_extension().get_string();

	if (extension == "obj")
	{
		return load_mesh_obj(path);
	}
	else
	{
		MINTY_ERROR(F("Cannot load mesh. Unsupported file type: {}", extension));
		return Ref<Mesh>();
	}
}

Ref<RenderPass> Minty::AssetManager::load_render_pass(Path const& path)
{
	// create builder
	RenderPassBuilder builder{};
	builder.id = read_id(path);

	// read values
	RenderAttachment colorAttachment{};
	RenderAttachment depthAttachment{};
	Reader* reader;
	if (open_reader(path, reader))
	{
		// read color attachment
		if (reader->indent("Attachments"))
		{
			if(!read_attachment(path, *reader, "Color", colorAttachment, true))
			{
				colorAttachment.type = RenderAttachment::Type::Color;
				builder.colorAttachment = &colorAttachment;
			}
			if (!read_attachment(path, *reader, "Depth", depthAttachment, false))
			{
				depthAttachment.type = RenderAttachment::Type::Depth;
				builder.depthAttachment = &depthAttachment;
			}
			
			reader->outdent();
		}
	}

	return create_from_loaded<RenderPass>(path, builder);
}

Ref<Scene> Minty::AssetManager::load_scene(Path const& path)
{
	// get scene details
	SceneBuilder builder{};
	builder.id = read_id(path);
	builder.name = path.get_name().get_string();

	// create empty scene
	Ref<Scene> scene = create_from_loaded<Scene>(path, builder);

	// deserialize the Scene
	Reader* reader;
	if (open_reader(path, reader))
	{
		scene->deserialize(*reader);
		close_reader(reader);
	}

	return scene;
}

Ref<Shader> Minty::AssetManager::load_shader(Path const& path)
{
	// create builder
	ShaderBuilder builder{};
	builder.id = read_id(path);

	// read values
	Reader* reader;
	if (open_reader(path, reader))
	{
		// render pass
		if (find_dependency<RenderPass>(path, *reader, "RenderPass", builder.renderPass, true))
		{
			close_reader(reader);
			return Ref<Shader>();
		}

		// config
		reader->read("PrimitiveTopology", builder.primitiveTopology);
		reader->read("PolygonMode", builder.polygonMode);
		reader->read("CullMode", builder.cullMode);
		reader->read("FrontFace", builder.frontFace);
		reader->read("LineWidth", builder.lineWidth);

		// inputs (uniform, push, etc.)
		if (reader->indent("Inputs"))
		{
			// offset for push constants
			Size offset = 0;

			builder.inputs.resize(reader->get_size(), ShaderInput{});
			for (Size i = 0; i < reader->get_size(); i++)
			{
				// get the input
				ShaderInput& input = builder.inputs[i];

				// get the name
				if (!reader->read_name(i, input.name))
				{
					continue;
				}

				// step in to read values
				if (reader->indent(i))
				{
					// get basic data
					reader->read("Binding", input.binding);
					reader->read("Stage", input.stage);
					reader->read("Type", input.type);
					reader->read("Count", input.count);
					reader->read("Frequent", input.frequent);

					// set offset if push constant
					if (input.type == ShaderInputType::PushConstant)
					{
						MINTY_ASSERT(input.stage == ShaderStage::Vertex, "Push constants can only be used in the vertex stage.");

						input.offset = offset;
					}

					// read structure
					if (reader->indent("Structure"))
					{
						String name = "";
						Type type = Type::Undefined;
						for (Size j = 0; j < reader->get_size(); j++)
						{
							// get name
							if (!reader->read_name(j, name))
							{
								continue;
							}

							// get type
							if (!reader->read(j, type))
							{
								continue;
							}

							// add to the input
							input.data.add({ name, Variable(type) });

							// add to total size
							UInt typeSize = static_cast<UInt>(sizeof_type(type));
							input.size += typeSize;
						}

						reader->outdent();
					}

					// adjust offset if push constant, so next push const is aligned
					if (input.type == ShaderInputType::PushConstant)
					{
						offset += input.size;
					}

					reader->outdent();
				}
			}

			reader->outdent();
		}

		// bindings
		if (reader->indent("Bindings"))
		{
			// allot space for bindings
			builder.vertexInput.bindings.resize(reader->get_size(), ShaderBinding{});

			String name;
			UInt binding = UINT_MAX;
			UInt location;
			for (Size i = 0; i < reader->get_size(); i++)
			{
				ShaderBinding& shaderBinding = builder.vertexInput.bindings[i];

				// read the binding
				if (!reader->read_name(i, name) || !try_uint(name, binding))
				{
					binding += 1;
				}
				shaderBinding.binding = binding;

				// read rate
				if (!reader->read(i, shaderBinding.inputRate))
				{
					continue;
				}

				// read attributes
				if (reader->indent(i))
				{
					// allot space for attributes
					shaderBinding.attributes.resize(reader->get_size(), ShaderAttribute{});
					
					// read each attribute
					location = UINT_MAX;
					for (Size j = 0; j < reader->get_size(); j++)
					{
						ShaderAttribute& shaderAttribute = shaderBinding.attributes[j];

						// get attribute location
						if (!reader->read_name(j, name) || !try_uint(name, location))
						{
							// set location to last location + 1
							location += 1;
						}
						shaderAttribute.location = location;

						// get attribute type
						if (!reader->read(j, shaderAttribute.type))
						{
							continue;
						}
					}

					reader->outdent();
				}
			}

			reader->outdent();
		}

		// modules
		if (reader->indent("Stages"))
		{
			if (find_dependency<ShaderModule>(path, *reader, "Vertex", builder.vertexShaderModule, true))
			{
				close_reader(reader);
				return Ref<Shader>();
			}

			if (find_dependency<ShaderModule>(path, *reader, "Fragment", builder.fragmentShaderModule, true))
			{
				close_reader(reader);
				return Ref<Shader>();
			}

			reader->outdent();
		}

		// viewport
		if (find_dependency<Viewport>(path, *reader, "Viewport", builder.viewport, false))
		{
			// if no viewport given, use default viewport
			builder.viewport = RenderManager::get_singleton().get_default_viewport();
		}

		close_reader(reader);
	}

	// create the shader
	return create_from_loaded<Shader>(path, builder);
}

Ref<ShaderModule> Minty::AssetManager::load_shader_module(Path const& path)
{
	// create builder
	ShaderModuleBuilder builder{};
	builder.id = read_id(path);

	// read data
	Vector<Byte> bytes = read_bytes(path);
	builder.data = bytes.get_data();
	builder.size = bytes.get_size();

	return create_from_loaded<ShaderModule>(path, builder);
}

Ref<Texture> Minty::AssetManager::load_texture(Path const& path)
{
	// create builder
	TextureBuilder builder{};
	builder.id = read_id(path);
	
	// read meta file
	Path metaPath = Asset::get_meta_path(path);
	Reader* reader;
	if (open_reader(metaPath, reader))
	{
		// create image
		UUID imageId = UUID::create();
		Owner<Image> image = create_image(path, imageId);

		// add image to asset manager
		add(path, image);

		// set builder values
		builder.image = image.create_ref();
		reader->read("Filter", builder.filter);
		reader->read("AddressMode", builder.addressMode);

		close_reader(reader);
	}

	return create_from_loaded<Texture>(path, builder);
}

Owner<AssetManager> Minty::AssetManager::create(AssetManagerBuilder const& builder)
{
	return Owner<AssetManager>(builder);
}

AssetManager& Minty::AssetManager::get_singleton()
{
	return Context::get_singleton().get_asset_manager();
}
