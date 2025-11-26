#include "pch.h"
#include "AssetManager.h"
#include "Minty/Animation/Animation.h"
#include "Minty/Animation/Animator.h"
#include "Minty/Core/Format.h"
#include "Minty/Context/Context.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Entity/Prefab.h"
#include "Minty/Library/STB.h"
#include "Minty/Render/Font.h"
#include "Minty/Render/FontVariant.h"
#include "Minty/Render/Image.h"
#include "Minty/Render/ImagePixelFormat.h"
#include "Minty/Render/Material.h"
#include "Minty/Render/MaterialTemplate.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Render/RenderAttachment.h"
#include "Minty/Render/RenderPass.h"
#include "Minty/Render/Shader.h"
#include "Minty/Render/ShaderModule.h"
#include "Minty/Render/Sprite.h"
#include "Minty/Render/SpriteAtlas.h"
#include "Minty/Render/Surface.h"
#include "Minty/Render/Texture.h"
#include "Minty/Render/Viewport.h"
#include "Minty/Event/WindowResizeEvent.h"
#include "Minty/Time/Timestep.h"

using namespace Minty;

Minty::AssetManager::AssetManager(AssetManagerInfo const& info)
	: m_savePaths(info.savePaths)
	, m_assets()
	, m_assetTypes()
	, m_handles()
	, m_assetsMutex()
	, m_wrapper()
{
	for (Path const& path : info.wraps)
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
	if (!exists(path))
	{
		// return invalid if no file
		return INVALID_ID;
	}

	Path metaPath = Asset::get_meta_path(path);

	if (!exists(metaPath))
	{
		// return invalid if no meta file
		return INVALID_ID;
	}

	Vector<String> lines = read_lines(metaPath);

	if (lines.is_empty())
	{
		// return invalid if empty meta file
		return INVALID_ID;
	}

	// get ID from first line
	String const& line = lines.front();
	MINTY_ASSERT(line.starts_with(": ") && line.get_size() == 18, ErrorCode::Asset_InvalidFormat, metaPath.to_string());

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

void Minty::AssetManager::run_completion_jobs()
{
	{
		std::unique_lock lock(m_onCompletionsMutex);
		while (!m_onCompletions.is_empty())
		{
			// get the ID and the Job
			auto tuple = m_onCompletions.pop();
			UUID const id = tuple.get_first();
			AssetJob const& job = tuple.get_second();

			// run the Job
			job(*this, id);
		}
	}
}

Ref<Asset> Minty::AssetManager::load_asset(Path const& path, AssetType const type, UUID const id)
{
	switch (type)
	{
	case AssetType::Generic:
		return load_generic(path, id);
	case AssetType::Image:
		return load_image(path, id);
	case AssetType::Material:
		return load_material(path, id);
	case AssetType::MaterialTemplate:
		return load_material_template(path, id);
	case AssetType::Mesh:
		return load_mesh(path, id);
	case AssetType::RenderPass:
		return load_render_pass(path, id);
	case AssetType::RenderTarget:
		return load_render_target(path, id);
	case AssetType::Camera:
		return load_camera(path, id);
	case AssetType::Shader:
		return load_shader(path, id);
	case AssetType::ShaderModule:
		return load_shader_module(path, id);
	case AssetType::Font:
		return load_font(path, id);
	case AssetType::FontVariant:
		return load_font_variant(path, id);
	case AssetType::Sprite:
		return load_sprite(path, id);
	case AssetType::SpriteAtlas:
		return load_sprite_atlas(path, id);
	case AssetType::Texture:
		return load_texture(path, id);
	case AssetType::Animation:
		return load_animation(path, id);
	case AssetType::Animator:
		return load_animator(path, id);
	case AssetType::AudioClip:
		return load_audio_clip(path, id);
	case AssetType::Prefab:
		return load_prefab(path, id);
	default:
		MINTY_ABORT(ErrorCode::Asset_UnknownType, type);
		return Ref<Asset>();
	}
}

void Minty::AssetManager::dispose()
{
	// sync to finish loading/unloading
	sync();

	// unload the rest
	unload_all();

	Manager::dispose();
}

void Minty::AssetManager::frame_update(Timestep const& time)
{
	MINTY_TRACE_SCOPE();

	// run all of the onCompletion jobs
	run_completion_jobs();
}

void Minty::AssetManager::sync()
{
	MINTY_TRACE_SCOPE();

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
	run_completion_jobs();
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
		MINTY_LOG_ERROR(F("Cannot load Wrap file. Path does not exist: {}", path));
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

	// import any existing includes
	String includePath;
	if (reader->read("import", includePath))
	{
		Reader* includeReader = nullptr;
		if (open_reader(Path(includePath), includeReader))
		{
			// merge the include into this reader and replace with the included reader
			includeReader->merge(*reader);
			close_reader(reader);
			reader = includeReader;
		}
	}

	return true;
}

void Minty::AssetManager::close_reader(Reader*& reader) const
{
	MINTY_ASSERT(reader != nullptr, ErrorCode::Argument_ExpectedNonNull);

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
	MINTY_ASSERT(writer != nullptr, ErrorCode::Argument_ExpectedNonNull);

	// close the file
	File* file = static_cast<File*>(writer->get_source());
	close(file);

	// delete the writer
	delete writer;
	writer = nullptr;
}

UUID Minty::AssetManager::schedule_load(Path const& path, AssetJob const& onCompletion)
{
	MINTY_ASSERT(exists(path), ErrorCode::File_NotFound, path);
	Path metaPath = Asset::get_meta_path(path);
	MINTY_ASSERT(exists(metaPath), ErrorCode::Asset_MissingMeta, metaPath);

	JobManager& jobManager = JobManager::get_singleton();

	// get UUID for reference
	UUID id = read_id(path);

	// ensure not already loading
	MINTY_ASSERT(!m_handles.contains(id), ErrorCode::Asset_Busy, id, path);

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
				m_onCompletions.push({ id, onCompletion });
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
	MINTY_ASSERT(exists(path), ErrorCode::File_NotFound, path);
	Path metaPath = Asset::get_meta_path(path);
	MINTY_ASSERT(exists(metaPath), ErrorCode::Asset_MissingMeta, metaPath);
#endif // MINTY_DEBUG  

	AssetType type = Asset::get_asset_type(path);
	return load_asset(path, type);
}

void Minty::AssetManager::schedule_unload(UUID const id, AssetJob const& onCompletion)
{
	MINTY_ASSERT(contains(id), ErrorCode::Asset_NotLoaded, id);
	MINTY_ASSERT(!m_handles.contains(id), ErrorCode::Asset_Busy, id);

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
				m_onCompletions.push({ id, onCompletion });
			}
		}, handle);

	{
		std::unique_lock lock(m_handlesMutex);
		m_handles.add(id, handle);
	}
}

void Minty::AssetManager::unload(UUID const id)
{
	MINTY_ASSERT(contains(id), ErrorCode::Asset_NotLoaded, id);

	// get the asset
	Owner<Asset> asset = m_assets.at(id).asset;

	// unload
	asset->on_unload();

	// remove from the lists
	remove(id);
}

void Minty::AssetManager::reload(UUID const id)
{
	MINTY_ASSERT(contains(id), ErrorCode::Asset_NotLoaded, id);
	MINTY_ASSERT(m_savePaths, ErrorCode::Asset_SavePathsNotEnabled);

	// get the path to the asset
	Path path = get_asset_path(id);

	// get the asset
	Ref<Asset> asset = get_asset(id);

	// open the file
	Reader* reader = nullptr;
	if (!open_reader(path, reader))
	{
		MINTY_LOG_ERROR(F("Failed to reload asset: {}. Could not open file.", path));
		return;
	}

	// deserialize the asset again
	if (!asset->deserialize(*reader))
	{
		MINTY_LOG_ERROR(F("Failed to deserialize asset: {}. Failed to deserialize the data.", path));
		close_reader(reader);
		return;
	}

	// close the reader
	close_reader(reader);
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
	MINTY_ASSERT(id.is_valid(), ErrorCode::UUID_Invalid);
	MINTY_ASSERT(!m_assets.contains(id), ErrorCode::Asset_AlreadyLoaded, id, path);
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
		MINTY_LOG_ERROR(F("Asset with the given ID does not exist: {}", id));
		return Ref<Asset>();
	}

	// return the asset
	return it->get_second().asset.create_ref();
}

Ref<Asset> Minty::AssetManager::at_asset(UUID const id) const
{
	std::unique_lock lock(m_assetsMutex);
	MINTY_ASSERT(contains(id), ErrorCode::Asset_NotLoaded, id);
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

	MINTY_ASSERT(contains(id), ErrorCode::Asset_NotLoaded, id);

	// get path
	std::unique_lock lock(m_assetsMutex);
	Path const& path = m_assets.at(id).path;

	// get name
	return path.get_name().get_string();
}

Owner<Asset> Minty::AssetManager::remove(UUID const id)
{
	MINTY_ASSERT(contains(id), ErrorCode::Asset_NotLoaded, id);

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
	MINTY_NOT_IMPLEMENTED();

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
	Location const location = get_location(path);
	MINTY_ASSERT(location != Location::Undefined, ErrorCode::File_NotFound, path);

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
	return text.split_lines();
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

Ref<GenericAsset> Minty::AssetManager::load_generic(Path const& path, UUID const id)
{
	Vector<Byte> bytes = read_bytes(path);

	GenericAssetInfo info
	{
		.id = id,
		.data = ConstantContainer(bytes.get_data(), bytes.get_size())
	};

	return create_from_loaded<GenericAsset>(path, info);
}

Owner<Image> Minty::AssetManager::create_image(Path const& path, UUID const id)
{
	// get image data
	Vector<Byte> bytes = read_bytes(path);

	// get pixel data
	int width, height, channels;
	stbi_uc* data = stbi_load_from_memory(static_cast<stbi_uc*>(bytes.get_data()), static_cast<int>(bytes.get_size()), &width, &height, &channels, static_cast<int>(ImagePixelFormat::RedGreenBlueAlpha));
	char const* reason = stbi_failure_reason();
	MINTY_ASSERT(data != nullptr, ErrorCode::Asset_LoadFailed, path, reason ? String(reason) : F("Unknown error"));

	// create the image
	ImageInfo info{};
	info.id = id;
	info.size = UInt2(width, height);
	info.pixelData = data;
	info.pixelDataSize = static_cast<Size>(width) * static_cast<Size>(height) * 4 * sizeof(Byte);

	Reader* reader;
	Path metaPath = Asset::get_meta_path(path);
	if (open_reader(metaPath, reader))
	{
		if (!reader->read("Format", info.format))
		{
			info.format = Format::Default;
		}
		if (!reader->read("Type", info.type))
		{
			info.type = ImageType::D2;
		}
		if (!reader->read("Tiling", info.tiling))
		{
			info.tiling = ImageTiling::Optimal;
		}
		if (!reader->read("Aspect", info.aspect))
		{
			info.aspect = ImageAspect::Color;
		}
		if (!reader->read("Usage", info.usage))
		{
			info.usage = ImageUsage::Sampled;
		}
		close_reader(reader);
	}

	// create the image
	Owner<Image> image = Image::create(info);

	// free the pixel data
	stbi_image_free(data);

	return image;
}

Ref<Animation> Minty::AssetManager::load_animation(Path const& path, UUID const id)
{
	// create info
	AnimationInfo info{};
	info.id = id;

	// read values from the file
	Reader* reader;
	if (open_reader(path, reader))
	{
		// read values
		reader->read("Duration", info.duration);
		MINTY_ASSERT(info.duration >= 0.0f, ErrorCode::Animation_NegativeTime, path);
		// of duration is 0, adjust it to a small value so it will still play
		if (info.duration < Math::EPSILON)
		{
			info.duration = Math::EPSILON;
		}
		reader->read("Loop", info.loop);
		reader->read("Entities", info.entities);
		reader->read("Components", info.components);
		MINTY_ASSERT(!info.components.is_empty(), ErrorCode::Animation_NotEnoughComponents, path);
		if (reader->indent("Variables"))
		{
			reader->read("Rigid", info.rigidVariables);
			reader->read("Smooth", info.smoothVariables);

			reader->outdent();
		}
		reader->read("Values", info.values);
		reader->read("Actions", info.actions);
		MINTY_ASSERT(!info.actions.is_empty(), ErrorCode::Animation_NotEnoughActions, path);

#ifdef MINTY_DEBUG

		// ensure all action indices are valid
		for (Size i = 0; i < info.actions.get_size(); i++)
		{
			AnimationAction const& action = info.actions.at(i);
			MINTY_ASSERT(
				(info.entities.get_size() == 0 && action.entityIndex == 0) ||
				(action.entityIndex < info.entities.get_size()), 
				ErrorCode::Animation_InvalidEntityIndex, path);
			MINTY_ASSERT(action.componentIndex < info.components.get_size(), ErrorCode::Animation_InvalidComponentIndex, path);
			for (Size j = 0; j < action.values.get_size(); j++)
			{
				auto const [variableIndex, valueIndex] = action.values.at(j);
				MINTY_ASSERT(variableIndex < info.rigidVariables.get_size() + info.smoothVariables.get_size(), ErrorCode::Animation_InvalidVariableIndex, path);
				MINTY_ASSERT(valueIndex < info.values.get_size(), ErrorCode::Animation_InvalidValueIndex, path);
			}
		}

#endif // MINTY_DEBUG

		// read steps
		if (reader->indent("Steps"))
		{
			// read each time
			String timeString;
			Float time;
			for (Size i = 0; i < reader->get_size(); i++)
			{
				// read the time
				if (!reader->read_name(i, timeString))
				{
					MINTY_LOG_ERROR(F("Failed to read time from animation step: {}.", path));
					continue;
				}
				if (!try_float(timeString, time))
				{
					MINTY_LOG_ERROR(F("Failed to convert time string to float: {}.", timeString));
					continue;
				}

				// read the action indices
				String actionIndicesString;
				if (!reader->read(i, actionIndicesString))
				{
					MINTY_LOG_ERROR(F("Failed to read action indices from animation step: {}.", path));
					continue;
				}
				actionIndicesString = actionIndicesString.strip();
				Vector<String> actionIndicesParts = actionIndicesString.split(ANIMATION_ACTION_GROUP);
				Vector<Size> actionIndices;
				actionIndices.reserve(actionIndicesParts.get_size());
				for (String const& part : actionIndicesParts)
				{
					// convert to size
					Size index;
					if (try_size(part, index))
					{
						actionIndices.add(index);
					}
					else
					{
						MINTY_LOG_ERROR(F("Failed to convert action index string to size: {}.", part));
					}
				}

				// add to the info
				info.steps.add({ time, std::move(actionIndices) });
			}

			reader->outdent();
		}
		MINTY_ASSERT(!info.steps.is_empty(), ErrorCode::Animation_NotEnoughSteps, path);

		// read reset steps
		String resetStepsString;
		if (reader->read("Reset", resetStepsString))
		{
			// split each step by comma
			Vector<String> resetStepsParts = resetStepsString.split(ANIMATION_ACTION_GROUP);

			// read each step
			for (String const& part : resetStepsParts)
			{
				// convert to size
				Size index;
				if (try_size(part, index))
				{
					info.resetSteps.add(index);
				}
				else
				{
					MINTY_LOG_ERROR(F("Failed to convert reset step string to size: {}.", part));
				}
			}
		}

		close_reader(reader);
	}

	// create the animation
	return create_from_loaded<Animation>(path, info);
}

Ref<Animator> Minty::AssetManager::load_animator(Path const& path, UUID const id)
{
	// create info
	AnimatorInfo info{};
	info.id = id;
	
	// read values from the file
	Reader* reader;
	if (open_reader(path, reader))
	{
		// read value, directly as an FSM
		info.fsm.deserialize(*reader);
		info.fsm.reset();

		// read other values
		reader->read("Force", info.force);

#ifdef MINTY_DEBUG

		// check each state value
		// each one should be a valid UUID, or empty
		for (auto const& [name, stateId, state] : info.fsm.get_states())
		{
			Variable const& variable = state.get_value();

			// if empty, skip
			if(variable.is_empty())
			{
				continue;
			}

			// check type
			MINTY_ASSERT(variable.get_type() == Type::Object, ErrorCode::Asset_InvalidFormat, name, variable.get_type());

			// check value
			UUID const id = variable.get<UUID>();
			MINTY_ASSERT(contains(id), ErrorCode::Asset_MissingDependency, path, id);
			MINTY_ASSERT(get_asset(id)->get_asset_type() == AssetType::Animation, ErrorCode::Asset_InvalidDependencyType, name, id);
		}

#endif // MINTY_DEBUG

		close_reader(reader);
	}

	// create the animator
	return create_from_loaded<Animator>(path, info);
}

Ref<AudioClip> Minty::AssetManager::load_audio_clip(Path const& path, UUID const id)
{
	// create info
	AudioClipInfo info{};

	// read audio bytes
	info.data = read_bytes(path);
	if (info.data.is_empty())
	{
		return Ref<AudioClip>();
	}

	// read ID
	info.id = id;

	// read values from meta
	Path metaPath = Asset::get_meta_path(path);
	Reader* reader;
	if (open_reader(metaPath, reader))
	{
		// read values
		reader->read("Volume", info.volume);
		reader->read("Loop", info.loop);
		reader->read("LoopPoint", info.loopPoint);
		reader->read("Exclusive", info.exclusive);

		close_reader(reader);
	}

	return create_from_loaded<AudioClip>(path, info);
}

Ref<Camera> Minty::AssetManager::load_camera(Path const& path, UUID const id)
{
	// create the info
	CameraInfo info{};
	info.id = id;

	// read values from the file
	Reader* reader;
	if (open_reader(path, reader))
	{
		// read values
		reader->read("Perspective", info.perspective);
		reader->read("FOV", info.fov);
		reader->read("Near", info.nearPlane);
		reader->read("Far", info.farPlane);
		reader->read("Color", info.color);
		reader->read("AspectRatio", info.aspectRatio);
		reader->read("Size", info.size);
		reader->read("Layer", info.layer);
		reader->read("RenderTarget", info.renderTarget);

		close_reader(reader);
	}

	return create_from_loaded<Camera>(path, info);
}

Ref<Font> Minty::AssetManager::load_font(Path const& path, UUID const id)
{
	// create info
	FontInfo info{};
	info.id = id;

	// read the font data
	Reader* reader;
	if (open_reader(path, reader))
	{
		// read values
		reader->read("Name", info.name);
		Vector<UUID> variantIds;
		if (reader->read("Variants", variantIds))
		{
			// get the variants
			for (UUID const& variantId : variantIds)
			{
				Ref<FontVariant> variant = get<FontVariant>(variantId);
				MINTY_ASSERT(variant != nullptr, ErrorCode::Asset_MissingDependency, path, variantId);
				info.variants.add(variant);
			}
		}

		close_reader(reader);
	}

	// create the font
	return create_from_loaded<Font>(path, info);
}

Ref<FontVariant> Minty::AssetManager::load_font_variant(Path const& path, UUID const id)
{
	// create the info
	FontVariantInfo info{};
	info.id = id;

	// read the font variant data
	// this is a different, standard format (TTF)

	Vector<String> lines = read_lines(path);
	Float widthScale = 1.0f;
	Float heightScale = 1.0f;
	for (String const& line : lines)
	{
		// split by tabs
		Vector<String> parts = line.split();

		// determine what to do based on first word in line
		if (line.starts_with("char "))
		{
			FontChar fontChar{};

			for (String const& part : parts)
			{
				if (part.is_empty())
				{
					continue; // skip empty parts
				}

				if (part.starts_with("id="))
				{
					fontChar.id = to_char(part.sub(3, part.get_size() - 3));
				}
				else if (part.starts_with("x="))
				{
					fontChar.x = to_int(part.sub(2, part.get_size() - 2)) * widthScale;
				}
				else if (part.starts_with("y="))
				{
					fontChar.y = to_int(part.sub(2, part.get_size() - 2)) * heightScale;
				}
				else if (part.starts_with("width="))
				{
					fontChar.width = to_int(part.sub(6, part.get_size() - 6)) * widthScale;
				}
				else if (part.starts_with("height="))
				{
					fontChar.height = to_int(part.sub(7, part.get_size() - 7)) * heightScale;
				}
				else if (part.starts_with("xoffset="))
				{
					fontChar.xOffset = to_int(part.sub(8, part.get_size() - 8)) * widthScale;
				}
				else if (part.starts_with("yoffset="))
				{
					fontChar.yOffset = to_int(part.sub(8, part.get_size() - 8)) * heightScale;
				}
				else if (part.starts_with("xadvance="))
				{
					fontChar.xAdvance = to_int(part.sub(9, part.get_size() - 9)) * widthScale;
				}
			}

			info.characters.add(fontChar);
		}
		else if (line.starts_with("kerning "))
		{
			char first = 0;
			char second = 0;
			float amount = 0;
			for (String const& part : parts)
			{
				if (part.is_empty())
				{
					continue; // skip empty parts
				}

				if (part.starts_with("first="))
				{
					first = static_cast<Char>(to_int(part.sub(6, part.get_size() - 6)));
				}
				else if (part.starts_with("second="))
				{
					second = static_cast<Char>(to_int(part.sub(7, part.get_size() - 7)));
				}
				else if (part.starts_with("amount="))
				{
					amount = static_cast<Char>(to_int(part.sub(7, part.get_size() - 7)) * widthScale);
				}
			}

			// pack kerning into info
			info.kernings.add({ first, second, amount });
		}
		else if (line.starts_with("info "))
		{
			for (String const& part : parts)
			{
				if (part.is_empty())
				{
					continue; // skip empty parts
				}

				if (part.starts_with("size="))
				{
					info.size = to_uint(part.sub(5, part.get_size() - 5));
				}
				else if (part.starts_with("bold="))
				{
					Bool isBold = static_cast<Bool>(to_int(part.sub(5, part.get_size() - 5)));
					if (isBold)
					{
						info.flags |= FontFlags::Bold;
					}
				}
				else if (part.starts_with("italic="))
				{
					Bool isItalic = static_cast<Bool>(to_int(part.sub(7, part.get_size() - 7)));
					if (isItalic)
					{
						info.flags |= FontFlags::Italic;
					}
				}
			}
		}
		else if (line.starts_with("common "))
		{
			for (String const& part : parts)
			{
				if (part.is_empty())
				{
					continue; // skip empty parts
				}

				if (part.starts_with("lineHeight="))
				{
					info.lineHeight = static_cast<float>(to_int(part.sub(11, part.get_size() - 11)));
				}
			}
		}
		else if (line.starts_with("page "))
		{
			// textures to load
			Path directoryPath = path.get_parent();

			for (String const& part : parts)
			{
				if (part.is_empty())
				{
					continue; // skip empty parts
				}

				if (part.starts_with("file="))
				{
					// ignore " "
					String name = part.sub(6, part.get_size() - 7);
					UUID textureId = read_id(directoryPath / name);
					info.texture = get<Texture>(textureId);
				}
			}

			// stop if no texture
			if (info.texture == nullptr)
			{
				break;
			}
			
			// get size
			UInt2 textureSize = info.texture->get_size();

			// stop if no texture size
			MINTY_ASSERT(textureSize.x > 0 && textureSize.y > 0, ErrorCode::Asset_InvalidConfiguration, path);

			// get scale
			widthScale = 1.0f / textureSize.x;
			heightScale = 1.0f / textureSize.y;
		}
	}

	return create_from_loaded<FontVariant>(path, info);
}

Ref<Image> Minty::AssetManager::load_image(Path const& path, UUID const id)
{
	// create the image using the path and ID
	Owner<Image> image = create_image(path, id);

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

Ref<Material> Minty::AssetManager::load_material(Path const& path, UUID const id)
{
	// create info
	MaterialInfo info{};
	info.id = id;

	// read values
	Reader* reader;
	if (open_reader(path, reader))
	{
		// get template
		if (find_dependency<MaterialTemplate>(path, *reader, "Template", info.materialTemplate, true))
		{
			close_reader(reader);
			return Ref<Material>();
		}

		// read values
		if (reader->indent("Values"))
		{
			read_values(*reader, info.values);
			reader->outdent();
		}

		close_reader(reader);
	}

	return create_from_loaded<Material>(path, info);
}

Ref<MaterialTemplate> Minty::AssetManager::load_material_template(Path const& path, UUID const id)
{
	// create info
	MaterialTemplateInfo info{};
	info.id = id;

	// read values
	Reader* reader;
	if (open_reader(path, reader))
	{
		if (find_dependency<Shader>(path, *reader, "Shader", info.shader, true))
		{
			close_reader(reader);
			return Ref<MaterialTemplate>();
		}

		// read values
		if (reader->indent("Values"))
		{
			read_values(*reader, info.values);
			reader->outdent();
		}

		close_reader(reader);
	}

	return create_from_loaded<MaterialTemplate>(path, info);
}

Ref<Mesh> Minty::AssetManager::load_mesh_obj(Path const& path, UUID const id)
{
	MeshInfo info{};
	info.id = id;
	info.type = MeshType::Custom;
	info.vertices = ListContainer(sizeof(Float));
	info.indices = ListContainer(sizeof(UShort));

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
			positions.add(position);
		}
		else if (token == "vt")
		{
			// coord
			ss >> coord.x >> coord.y;
			coord.y = 1.0f - coord.y; // invert Y so it works with Vulkan
			coords.add(coord);
		}
		else if (token == "vn")
		{
			// normal
			ss >> normal.x >> normal.y >> normal.z;
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
					info.vertices.append(&position.x);
					info.vertices.append(&position.y);
					info.vertices.append(&position.z);
					info.vertices.append(&normal.x);
					info.vertices.append(&normal.y);
					info.vertices.append(&normal.z);
					info.vertices.append(&coord.x);
					info.vertices.append(&coord.y);
					info.indices.append(&index);

					// add for reference
					faces.add(faceIndices, index);

					// increment count
					vertexCount += 1;
				}
				else
				{
					// vertex already exists
					UShort index = found->get_second();
					info.indices.append(&index);
				}
			}
		}
	}

	// update vertex stride to match the vertex size
	info.vertices.set_stride(sizeof(Float) * 8);

	// create the mesh
	return create_from_loaded<Mesh>(path, info);
}

Ref<Mesh> Minty::AssetManager::load_mesh(Path const& path, UUID const id)
{
	String extension = path.get_extension().get_string();

	if (extension == ".obj")
	{
		return load_mesh_obj(path, id);
	}
	else
	{
		MINTY_LOG_ERROR(F("Cannot load mesh. Unsupported file type: {}", extension));
		return Ref<Mesh>();
	}
}

Ref<Prefab> Minty::AssetManager::load_prefab(Path const& path, UUID const id)
{
	// create info
	PrefabInfo info{};
	info.id = id;

	// read values
	Reader* reader;
	if (open_reader(path, reader))
	{
		// just save the values
		info.source = reader->get_node();

		close_reader(reader);
	}

	return create_from_loaded<Prefab>(path, info);
}

Ref<RenderPass> Minty::AssetManager::load_render_pass(Path const& path, UUID const id)
{
	// create info
	RenderPassInfo info{};
	info.id = id;

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
				info.colorAttachment = &colorAttachment;
			}
			if (!read_attachment(path, *reader, "Depth", depthAttachment, false))
			{
				depthAttachment.type = RenderAttachment::Type::Depth;
				info.depthAttachment = &depthAttachment;
			}
			
			reader->outdent();
		}
	}

	return create_from_loaded<RenderPass>(path, info);
}

Ref<RenderTarget> Minty::AssetManager::load_render_target(Path const& path, UUID const id)
{
	// create info
	RenderTargetInfo info{};
	info.id = id;

	// read values
	Reader* reader;
	if (open_reader(path, reader))
	{
		reader->read("RenderPass", info.renderPass);
		String images;
		if (reader->read("Images", images) && !images.is_empty())
		{
			// if "Surface", automatically grab the images from the surface
			if (images != "Surface")
			{
				MINTY_LOG_ERROR(F("Failed to load render target. Invalid image name: \"{}\". Must provide a valid name (Surface), or a list of Image IDs to use.", images));
				return Ref<RenderTarget>();
			}
			
			// get the surface images
			RenderManager& renderManager = RenderManager::get_singleton();
			Ref<Surface> surface = renderManager.get_surface();
			MINTY_ASSERT(surface != nullptr, ErrorCode::Asset_MissingDependency, path);
			info.surfaceBound = true;
			info.images = surface->get_images();
		}
		else
		{
			info.surfaceBound = false;

			// manually providing the images
			// read the images
			if (reader->indent("Images"))
			{
				// read each image
				UUID id;
				Ref<Image> image;
				Ref<Texture> texture;
				for (Size i = 0; i < reader->get_size(); i++)
				{
					// read the ID
					if (!reader->read(i, id))
					{
						continue;
					}

					// get the image, either from the texture with the given ID, or the image with the given ID
					texture = get<Texture>(id);
					if (texture != nullptr)
					{
						image = texture->get_image();
					}
					else
					{
						image = get<Image>(id);
					}

					// add to the list
					info.images.add(image);
				}

				reader->outdent();
			}
		}
		close_reader(reader);
	}

	return create_from_loaded<RenderTarget>(path, info);
}

Ref<Shader> Minty::AssetManager::load_shader(Path const& path, UUID const id)
{
	// create info
	ShaderInfo info{};
	info.id = id;

	// read values
	Reader* reader;
	if (open_reader(path, reader))
	{
		// render pass
		if (find_dependency<RenderPass>(path, *reader, "RenderPass", info.renderPass, true))
		{
			close_reader(reader);
			return Ref<Shader>();
		}

		// config
		reader->read("Priority", info.priority);
		reader->read("PrimitiveTopology", info.primitiveTopology);
		reader->read("PolygonMode", info.polygonMode);
		reader->read("CullMode", info.cullMode);
		reader->read("FrontFace", info.frontFace);
		reader->read("LineWidth", info.lineWidth);
		reader->read("Transparency", info.transparency);
		reader->read("DepthMode", info.depthMode);
		reader->read("DepthTestOp", info.depthTestOp);
		reader->read("StencilMode", info.stencilMode);
		reader->read("StencilTestOp", info.stencilTestOp);

		// inputs (uniform, push, etc.)
		if (reader->indent("Inputs"))
		{
			// offset for push constants
			Size offset = 0;

			info.inputs.resize(reader->get_size(), ShaderInput{});
			for (Size i = 0; i < reader->get_size(); i++)
			{
				// get the input
				ShaderInput& input = info.inputs[i];

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
						MINTY_ASSERT(input.stage == ShaderStage::Vertex, ErrorCode::Asset_Shader_PushConstantLocation, path, input.name);

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
			info.vertexInput.bindings.resize(reader->get_size(), ShaderBinding{});

			String name;
			UInt binding = UINT_MAX;
			UInt location;
			for (Size i = 0; i < reader->get_size(); i++)
			{
				ShaderBinding& shaderBinding = info.vertexInput.bindings[i];

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
			if (find_dependency<ShaderModule>(path, *reader, "Vertex", info.vertexShaderModule, true))
			{
				close_reader(reader);
				return Ref<Shader>();
			}

			if (find_dependency<ShaderModule>(path, *reader, "Fragment", info.fragmentShaderModule, true))
			{
				close_reader(reader);
				return Ref<Shader>();
			}

			reader->outdent();
		}

		// viewport
		if (find_dependency<Viewport>(path, *reader, "Viewport", info.viewport, false))
		{
			// if no viewport given, use default viewport
			info.viewport = RenderManager::get_singleton().get_default_viewport();
		}

		close_reader(reader);
	}

	// create the shader
	return create_from_loaded<Shader>(path, info);
}

Ref<ShaderModule> Minty::AssetManager::load_shader_module(Path const& path, UUID const id)
{
	// create info
	ShaderModuleInfo info{};
	info.id = id;

	// read data
	Vector<Byte> bytes = read_bytes(path);
	info.data = bytes.get_data();
	info.size = bytes.get_size();

	return create_from_loaded<ShaderModule>(path, info);
}

static void read_sprite_slice(Reader& reader, SpriteSlice& slice, CoordinateMode const defaultCoordinateMode = CoordinateMode::Normalized)
{
	reader.read("CoordinateMode", slice.coordinateMode, defaultCoordinateMode);
	reader.read("Offset", slice.offset);
	reader.read("Size", slice.size);
	reader.read("Pivot", slice.pivot);
	reader.read("PPU", slice.pixelsPerUnit);
}

Ref<Sprite> Minty::AssetManager::load_sprite(Path const& path, UUID const id)
{
	// create info
	SpriteInfo info{};
	info.id = id;

	// read values
	Reader* reader;
	if (open_reader(path, reader))
	{
		// read values
		reader->read("Texture", info.texture);
		read_sprite_slice(*reader, info.slice);

		close_reader(reader);
	}

	return create_from_loaded<Sprite>(path, info);
}

Ref<SpriteAtlas> Minty::AssetManager::load_sprite_atlas(Path const& path, UUID const id)
{
	// create info
	SpriteAtlasInfo info{};
	info.id = id;

	// read values
	Reader* reader;
	if (open_reader(path, reader))
	{
		// read values
		reader->read("Texture", info.texture);
		CoordinateMode defaultCoordinateMode;
		reader->read("CoordinateMode", defaultCoordinateMode, CoordinateMode::Normalized);

		// read the automatic slices
		if (reader->indent("Groups"))
		{
			for (Size i = 0; i < reader->get_size(); i++)
			{
				if (reader->indent(i))
				{
					SpriteSlice slice;
					Int2 count;

					// read data
					read_sprite_slice(*reader, slice, defaultCoordinateMode);
					reader->read("Count", count);

					// Sprites is overrides for specific slices, so they can have their own, static IDs.
					// The other Sprites within the Count range will have random IDs, generated every time the game is ran.
					Map<Int2, UUID> overrides;
					if (reader->indent("IDs"))
					{
						String name;
						Int2 index;
						UUID id;
						for (Size j = 0; j < reader->get_size(); j++)
						{
							// read the index
							if (!reader->read_name(j, name) || !try_int2(name, index))
							{
								continue;
							}
							// read the ID
							if (!reader->read(j, id))
							{
								continue;
							}
							// add to overrides
							overrides.add(index, id);
						}

						reader->outdent();
					}

					// turn the overrides into a vector, and fill any missing IDs with random UUIDs
					Vector<UUID> spriteIds(static_cast<Size>(count.y) * count.x);
					for (Int y = 0; y < count.y; y++)
					{
						for (Int x = 0; x < count.x; x++)
						{
							Int2 spriteIndex2D = Int2(x, y);
							UUID spriteId;
							auto it = overrides.find(spriteIndex2D);
							if (it != overrides.end())
							{
								// if override exists, use it
								spriteId = it->get_second();
							}
							else
							{
								// otherwise, generate a random ID
								spriteId = UUID::create();
							}

							spriteIds.add(std::move(spriteId));
						}
					}

					// create group
					SpriteGroup group(std::move(slice), count, std::move(spriteIds));

					// add to info
					info.groups.add(std::move(group));

					reader->outdent();
				}
			}

			reader->outdent();
		}
		
		close_reader(reader);
	}

	return create_from_loaded<SpriteAtlas>(path, info);
}

Ref<Texture> Minty::AssetManager::load_texture(Path const& path, UUID const id)
{
	// create info
	TextureInfo info{};
	info.id = id;
	
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

		// set info values
		info.image = image.create_ref();
		reader->read("Filter", info.filter, Filter::Linear);
		reader->read("AddressMode", info.addressMode, AddressMode::Repeat);

		close_reader(reader);
	}

	return create_from_loaded<Texture>(path, info);
}

Owner<AssetManager> Minty::AssetManager::create(AssetManagerInfo const& info)
{
	return Owner<AssetManager>(info);
}

AssetManager& Minty::AssetManager::get_singleton()
{
	return Context::get_singleton().get_asset_manager();
}
