#include "pch.h"
#include "AssetManager.h"
#include "Minty/Animation/Animation.h"
#include "Minty/Animation/Animator.h"
#include "Minty/Core/Evaluate.h"
#include "Minty/Core/Format.h"
#include "Minty/Application/Application.h"
#include "Minty/Asset/Asset.h"
#include "Minty/Asset/AssetManagerInfo.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Entity/Prefab.h"
#include "Minty/Library/STB.h"
#include "Minty/Render/BitmapInfo.h"
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
#include "Minty/Job/JobManager.h"
#include "Minty/Animation/AnimationInfo.h"
#include "Minty/Animation/AnimatorInfo.h"
#include "Minty/Tool/Path.h"
#include "Minty/Tool/String.h"
#include "Minty/FSM/FSM.h"
#include "Minty/Audio/AudioClip.h"
#include "Minty/Render/ImageInfo.h"
#include "Minty/File/PhysicalFile.h"
#include "Minty/File/VirtualFile.h"
#include "Minty/Audio/AudioClipInfo.h"
#include "Minty/Render/FontInfo.h"
#include "Minty/Render/FontVariantInfo.h"
#include "Minty/Render/MaterialInfo.h"
#include "Minty/Render/MaterialTemplateInfo.h"
#include "Minty/Render/MeshInfo.h"
#include "Minty/Render/RenderPassInfo.h"
#include "Minty/Render/RenderTargetInfo.h"
#include "Minty/Render/ShaderInfo.h"
#include "Minty/Render/ShaderModuleInfo.h"
#include "Minty/Render/SpriteAtlasInfo.h"
#include "Minty/Render/SpriteInfo.h"
#include "Minty/Render/TextureInfo.h"
#include "Minty/Entity/PrefabInfo.h"
#include "Minty/Asset/GenericAssetInfo.h"
#include "Minty/Render/CameraInfo.h"
#include "Minty/Render/RenderManager.h"
#include "Minty/Render/Camera.h"
#include "Minty/Stream/MemoryStream.h"
#include "Minty/Serialization/TextReader.h"
#include "Minty/Serialization/TextWriter.h"
#include "Minty/Stream/FileStream.h"
#include "Minty/Serialization/EvaluatedTypes.h"

using namespace Minty;

Minty::AssetManager::AssetManager(AssetManagerInfo const &info)
	: m_savePaths(info.savePaths), m_assets(), m_assetTypes(), m_handles(), m_assetsMutex(), m_wrapper()
{
	for (Path const &path : info.wraps)
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

AssetManager::Location Minty::AssetManager::get_location(Path const &path) const
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

UUID Minty::AssetManager::read_id(Path const &path) const
{
	if (!exists(path))
	{
		// return invalid if no file
		MINTY_ERROR(ErrorCode::File_NotFound);
		return UUID();
	}

	Path metaPath = Asset::get_meta_path(path);

	if (!exists(metaPath))
	{
		// return invalid if no meta file
		MINTY_ERROR(ErrorCode::File_NotFound);
		return UUID();
	}

	Vector<String> lines = read_lines(metaPath);

	if (lines.is_empty())
	{
		// return invalid if empty meta file
		MINTY_ERROR(ErrorCode::File_Empty);
		return UUID();
	}

	// get UUID from first line
	String const &line = lines.front();
	MINTY_ASSERT_F(line.starts_with(": "), ErrorCode::Asset_InvalidFormat, metaPath.get_string());

	// get the UUID
	String const idString = line.sub(2, UUID_HEX_SIZE_FULL);
	UUID id;
	if (!Parser<UUID>::parse(idString, id))
	{
		MINTY_ERROR(ErrorCode::Serialization_InvalidFormat);
		return UUID();
	}
	return id;
}

Unique<File> Minty::AssetManager::open(Path const &path) const
{
	switch (get_location(path))
	{
	case Location::FileSystem:
	{
		Unique<PhysicalFile> file = Unique<PhysicalFile>::create();
		if (!file->open(path, FileFlags::Read))
		{
			return Unique<File>();
		}
		return file;
	}
	case Location::Wrapper:
	{
		Unique<VirtualFile> file = Unique<VirtualFile>::create();
		if (!m_wrapper.open(path, *file))
		{
			return Unique<File>();
		}
		return file;
	}
	}

	MINTY_NOT_IMPLEMENTED();
	return Unique<File>();
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
			AssetJob const &job = tuple.get_second();

			// run the Job
			job(*this, id);
		}
	}
}

Shared<Asset> Minty::AssetManager::load_asset(Path const &path, AssetType const type, UUID const id)
{
	switch (type)
	{
	case AssetType::Generic:
		return load_generic(path, id);
	case AssetType::Bitmap:
		return load_bitmap(path, id);
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
		MINTY_ABORT_F(ErrorCode::Asset_UnknownType, type);
		return nullptr;
	}
}

String Minty::AssetManager::read_type(Path const &path) const
{
	if (!exists(path))
	{
		// return invalid if no file
		return "";
	}

	Path metaPath = Asset::get_meta_path(path);
	if (!exists(metaPath))
	{
		// return invalid if no meta file
		return "";
	}

	Vector<String> lines = read_lines(metaPath);
	if (lines.is_empty())
	{
		// return invalid if empty meta file
		return "";
	}

	// get type from first line with "Type: "
	for (String const &line : lines)
	{
		if (line.starts_with("Type: "))
		{
			return line.sub(6);
		}
	}

	return "";
}

void Minty::AssetManager::frame_update(Timestep const time)
{
	MINTY_TRACE_SCOPE();

	// run all of the onCompletion jobs
	run_completion_jobs();
}

void Minty::AssetManager::sync()
{
	MINTY_TRACE_SCOPE();

	auto const &jobManager = JobManager::get_instance();

	// if no job manager, nothing to wait for, because no jobs can run
	if (!jobManager)
	{
		return;
	}

	// get list of handles
	Vector<Handle> handles(m_handles.get_size());
	{
		std::unique_lock lock(m_assetsMutex);
		for (auto const &pair : m_handles)
		{
			handles.add(pair.get_second());
		}
	}

	// wait for them all
	jobManager->wait(handles);

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

Bool Minty::AssetManager::load_wrap(Path const &path)
{
	MINTY_ASSERT_F(Path::exists(path), ErrorCode::File_NotFound, path);

	m_wrapper.add(path);

	return true;
}

Bool Minty::AssetManager::exists(Path const &path) const
{
	return m_wrapper.contains(path) || Path::exists(path);
}

Bool Minty::AssetManager::exists(UUID const id) const
{
	std::unique_lock lock(m_assetsMutex);
	return m_assets.contains(id);
}

Unique<Reader> Minty::AssetManager::open_reader(Path const &path) const
{
	// if no file, fail
	if (!exists(path))
	{
		return Unique<Reader>();
	}

	// get the file data
	Vector<Byte> bytes = read_bytes(path);

	// if no bytes, fail
	if (bytes.is_empty())
	{
		return Unique<Reader>();
	}

	// create container and reader
	Shared<ConstantContainer> const container = Shared<ConstantContainer>::create(bytes.get_data(), bytes.get_size());
	Shared<Stream> const stream = Shared<MemoryStream>::create(container);
	Unique<Reader> reader = Unique<TextReader>::create(stream);
	return std::move(reader);
}

Unique<Writer> Minty::AssetManager::open_writer(Path const &path) const
{
	if (!Path::exists(path.get_parent()))
	{
		return Unique<Writer>();
	}

	Shared<File> const file = Shared<PhysicalFile>::create();
	if (!file->open(path, FileFlags::Write | FileFlags::Truncate))
	{
		return Unique<Writer>();
	}
	Shared<Stream> const stream = Shared<FileStream>::create(file);
	Unique<Writer> writer = Unique<TextWriter>::create(stream);
	return std::move(writer);
}

UUID Minty::AssetManager::schedule_load(Path const &path, AssetJob const &onCompletion)
{
	MINTY_ASSERT_F(exists(path), ErrorCode::File_NotFound, path);
	Path metaPath = Asset::get_meta_path(path);
	MINTY_ASSERT_F(exists(metaPath), ErrorCode::Asset_MissingMeta, metaPath);

	JobManager &jobManager = JobManager::get_singleton();

	// get UUID for reference
	UUID id = read_id(path);

	// ensure not already loading
	MINTY_ASSERT_F(!m_handles.contains(id), ErrorCode::Asset_Busy, id, path);

	// use a job to load the asset in the background
	Handle handle = jobManager.schedule([this, path, id]()
										{ load_asset(path); });
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
			} }, handle);

	// add final handle to the list
	{
		std::unique_lock lock(m_handlesMutex);
		m_handles.add(id, handle);
	}

	// return the ID of the Asset
	return id;
}

Shared<Asset> Minty::AssetManager::load_asset(Path const &path)
{
#ifdef MINTY_DEBUG
	MINTY_ASSERT_F(exists(path), ErrorCode::File_NotFound, path);
	Path const metaPath = Asset::get_meta_path(path);
	MINTY_ASSERT_F(exists(metaPath), ErrorCode::Asset_MissingMeta, metaPath);
#endif // MINTY_DEBUG

	AssetType type = Asset::get_asset_type(path);
	// if the asset type is image, get the type from the meta file
	if (type == AssetType::Image)
	{
		String const typeString = read_type(path);
		if (!typeString.is_empty())
		{
			if (!Parser<AssetType>::parse(typeString, type))
			{
				MINTY_ERROR(ErrorCode::Serialization_InvalidValue);
				type = AssetType::Texture;
			}
		}
		else
		{
			// default to texture
			type = AssetType::Texture;
		}
	}

	Shared<Asset> const asset = load_asset(path, type);

	if(asset == nullptr)
	{
		MINTY_ERROR_F(ErrorCode::Asset_LoadFailed, path);
		return nullptr;
	}

	MINTY_LOG_DEBUG_F("Loaded Asset: ID={}, Type={}, Path={}", asset->get_id(), type, path);
	return asset;
}

void Minty::AssetManager::schedule_unload(UUID const id, AssetJob const &onCompletion)
{
	MINTY_ASSERT_F(contains(id), ErrorCode::Asset_NotLoaded, id);
	MINTY_ASSERT_F(!m_handles.contains(id), ErrorCode::Asset_Busy, id);

	JobManager &jobManager = JobManager::get_singleton();

	// use a job to unload the asset in the background
	Handle handle = jobManager.schedule([this, id]()
										{ unload(id); });
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
			} }, handle);

	{
		std::unique_lock lock(m_handlesMutex);
		m_handles.add(id, handle);
	}
}

void Minty::AssetManager::unload(UUID const id)
{
	MINTY_ASSERT_F(contains(id), ErrorCode::Asset_NotLoaded, id);

	// get the asset
	Shared<Asset> asset = m_assets.at(id).asset;

	// unload
	asset->on_unload();

	// remove from the lists
	remove(id);

	MINTY_LOG_DEBUG_F("Unloaded Asset: ID={}", id);
}

void Minty::AssetManager::unload_all()
{
	// unload all assets
	for (auto const &pair : m_assets)
	{
		pair.get_second().asset->on_unload();
	}

	// clear the lists
	m_assets.clear();
	m_assetTypes.clear();
}

void Minty::AssetManager::add(Path const &path, Shared<Asset> const &asset)
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
	MINTY_ASSERT_F(!m_assets.contains(id), ErrorCode::Asset_AlreadyLoaded, id, path);
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

Ref<Asset> Minty::AssetManager::get_asset_ref(UUID const id) const
{
	return get_asset(id).to_ref();
}

Shared<Asset> Minty::AssetManager::get_asset(UUID const id) const
{
	std::unique_lock lock(m_assetsMutex);

	// find the asset
	auto it = m_assets.find(id);

	// if not found, return null
	if (it == m_assets.end())
	{
		MINTY_ERROR_F(ErrorCode::Asset_NotLoaded, id);
		return nullptr;
	}

	// return the asset
	return it->get_second().asset;
}

Ref<Asset> Minty::AssetManager::at_asset_ref(UUID const id) const
{
	return at_asset(id).to_ref();
}

Shared<Asset> const &Minty::AssetManager::at_asset(UUID const id) const
{
	std::unique_lock lock(m_assetsMutex);
	MINTY_ASSERT_F(contains(id), ErrorCode::Asset_NotLoaded, id);
	return m_assets.at(id).asset;
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

	MINTY_ASSERT_F(contains(id), ErrorCode::Asset_NotLoaded, id);

	// get path
	std::unique_lock lock(m_assetsMutex);
	Path const &path = m_assets.at(id).path;

	// get name
	return path.get_name().get_string();
}

Shared<Asset> Minty::AssetManager::remove(UUID const id)
{
	MINTY_ASSERT_F(contains(id), ErrorCode::Asset_NotLoaded, id);

	// get asset
	Shared<Asset> asset;
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
	Ref<Asset> asset = get_asset_ref(id);

	// get type
	AssetType type = asset->get_asset_type();

	// check based on type
	// some types inherently have no dependents, some do
	MINTY_NOT_IMPLEMENTED();

	// switch (type)
	//{
	// case AssetType::Shader:
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
	// case AssetType::MaterialTemplate:
	//	// Materials use MaterialTemplates
	//	for (auto const material : get_by_type<Material>())
	//	{
	//		if (material->get_template() == asset)
	//		{
	//			result.add(material);
	//		}
	//	}
	//	break;
	// case AssetType::Material:
	//	// TODO: models depend on materials?
	//	break;
	// case AssetType::Texture:
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
	// case AssetType::FontVariant:
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
	// }

	return result;
}

Vector<Byte> Minty::AssetManager::read_bytes(Path const &path) const
{
	Location const location = get_location(path);
	MINTY_ASSERT_F(location != Location::Undefined, ErrorCode::File_NotFound, path);

	switch (location)
	{
	case Location::FileSystem:
		return File::read_bytes(path);
	case Location::Wrapper:
		return m_wrapper.read_bytes(path);
	}

	return Vector<Byte>();
}

String Minty::AssetManager::read_text(Path const &path) const
{
	Vector<Byte> bytes = read_bytes(path);

	if (bytes.is_empty())
	{
		return String();
	}

	// create string from bytes
	return String(StringView(reinterpret_cast<Char const *>(bytes.get_data()), bytes.get_size()));
}

Vector<String> Minty::AssetManager::read_lines(Path const &path) const
{
	String const text = read_text(path);
	return Tool::split_lines(text);
}

Bool Minty::AssetManager::deserialize_asset_raw(Reader &reader, StringView const name, Shared<Asset> &asset)
{
	UUID id;
	if (!reader.read(name, id))
	{
		return false;
	}

	asset = get_asset(id);
	return asset != nullptr;
}

Bool Minty::AssetManager::deserialize_asset_ref_raw(Reader &reader, StringView const name, Ref<Asset> &assetRef)
{
	UUID id;
	if (!reader.read(name, id))
	{
		return false;
	}

	assetRef = get_asset_ref(id);
	return assetRef != nullptr;
}

Int Minty::AssetManager::check_dependency(UUID const id, Path const &path, String const &name, Bool const required) const
{
	// if invalid id (0), set to null
	if (!id.is_valid())
	{
		if (required)
		{
			MINTY_ERROR_F(ErrorCode::UUID_Invalid, path, name);
		}

		return 2;
	}

	// if asset id is valid but asset with id DNE, set to null
	if (!id.is_valid() || !contains(id))
	{
		MINTY_ERROR_F(ErrorCode::Asset_MissingDependency, path, name, id);
		return -1;
	}

	return 0;
}

Int Minty::AssetManager::read_attachment(Path const &path, Reader &reader, String const &name, RenderAttachment &attachment, Bool const required) const
{
	if (!reader.indent(name))
	{
		if (required)
		{
			MINTY_ERROR_F(ErrorCode::Asset_InvalidFormat, path, name);
		}
		return 1;
	}

	// read the attachment data
	if (!reader.read("Load", attachment.loadOperation))
	{
		attachment.loadOperation = LoadOperation::DontCare;
	}
	if (!reader.read("Store", attachment.storeOperation))
	{
		attachment.storeOperation = StoreOperation::DontCare;
	}
	if (!reader.read("Initial", attachment.initialLayout))
	{
		attachment.initialLayout = ImageLayout::Undefined;
	}
	if (!reader.read("Final", attachment.finalLayout))
	{
		attachment.finalLayout = ImageLayout::Undefined;
	}
	reader.outdent();

	return 0;
}

Shared<GenericAsset> Minty::AssetManager::load_generic(Path const &path, UUID const id)
{
	Vector<Byte> const bytes = read_bytes(path);
	Shared<ConstantContainer> const data = Shared<ConstantContainer>::create(bytes.get_data(), bytes.get_size());
	GenericAssetInfo info{
		.id = id,
		.data = std::move(data)};

	return create_from_loaded<GenericAsset>(path, info);
}

Shared<Image> Minty::AssetManager::create_image(Path const &path, UUID const id)
{
	// get image data
	Vector<Byte> bytes = read_bytes(path);

	// get pixel data
	int width, height, channels;
	stbi_uc *data = stbi_load_from_memory(static_cast<stbi_uc *>(bytes.get_data()), static_cast<int>(bytes.get_size()), &width, &height, &channels, static_cast<int>(ImagePixelFormat::RedGreenBlueAlpha));
	char const *reason = stbi_failure_reason();
	MINTY_ASSERT_F(data != nullptr, ErrorCode::Asset_LoadFailed, path, reason ? String(reason) : F("Unknown error"));

	// create the image
	ImageInfo info{};
	info.id = id;
	info.size = UInt2(width, height);
	info.pixelData = data;
	info.pixelDataSize = static_cast<Size>(width) * static_cast<Size>(height) * 4 * sizeof(Byte);

	Path metaPath = Asset::get_meta_path(path);
	if (Unique<Reader> const reader = open_reader(metaPath))
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

		// ignore texture values
		reader->ignore("Filter");
		reader->ignore("AddressMode");
	}

	// create the image
	Shared<Image> image = Image::create(info);

	// free the pixel data
	stbi_image_free(data);

	return image;
}

Shared<Animation> Minty::AssetManager::load_animation(Path const &path, UUID const id)
{
	// create info
	AnimationInfo info{};
	info.id = id;

	// read values from the file
	if (Unique<Reader> const reader = open_reader(path))
	{
		// read values
		reader->read("Duration", info.duration);
		MINTY_ASSERT_F(info.duration >= 0.0f, ErrorCode::Animation_NegativeTime, path);
		// of duration is 0, adjust it to a small value so it will still play
		if (info.duration < Math::EPSILON)
		{
			info.duration = Math::EPSILON;
		}
		reader->read("Loop", info.loop);
		reader->read("Entities", info.entities);
		reader->read("Components", info.components);
		if (reader->indent("Variables"))
		{
			String modeString; // key
			String name; // value
			Char mode;
			while(reader->read_next(modeString, name))
			{
				// get the mode from the string, or default
				if(modeString.is_empty())
				{
					// default to rigid
					mode = 'R';
				} else
				{
					mode = modeString.front();
				}

				// add to the appropriate list
				switch(mode)
				{
				case 'R':
					info.rigidVariables.add(name);
					break;
				case 'S':
					info.smoothVariables.add(name);
					break;
				default:
					MINTY_ERROR_F(ErrorCode::Animation_InvalidVariableMode, path, name, mode);
					break;
				}
			}

			reader->outdent();
		}
		reader->read("Values", info.values);
		reader->read("Actions", info.actions);

#ifdef MINTY_DEBUG

		// ensure all action indices are valid
		for (Size i = 0; i < info.actions.get_size(); i++)
		{
			AnimationAction const &action = info.actions.at(i);
			MINTY_ASSERT_F(
				(info.entities.get_size() == 0 && action.entityIndex == 0) ||
					(action.entityIndex < info.entities.get_size()),
				ErrorCode::Animation_InvalidEntityIndex, path);
			MINTY_ASSERT_F(action.componentIndex < info.components.get_size(), ErrorCode::Animation_InvalidComponentIndex, path);
			for (Size j = 0; j < action.values.get_size(); j++)
			{
				auto const [variableIndex, valueIndex] = action.values.at(j);
				MINTY_ASSERT_F(variableIndex < info.rigidVariables.get_size() + info.smoothVariables.get_size(), ErrorCode::Animation_InvalidVariableIndex, path);
				MINTY_ASSERT_F(valueIndex < info.values.get_size(), ErrorCode::Animation_InvalidValueIndex, path);
			}
		}

#endif // MINTY_DEBUG

		// read steps
		if (reader->indent("Steps"))
		{
			// read each time
			String timeString; // key
			Float time;
			String actionIndicesString; // value
			while (reader->read_next(timeString, actionIndicesString))
			{
				// convert to time float
				time = Math::evaluate<Float>(timeString);

				// read the action indices
				StringBuilder builder(actionIndicesString);
				builder.strip();
				Vector<String> actionIndicesParts = Tool::split(builder.get_string(), ANIMATION_ACTION_GROUP);
				Vector<Size> actionIndices;
				actionIndices.reserve(actionIndicesParts.get_size());
				for (String const &part : actionIndicesParts)
				{
					// convert to size
					Size const index = Math::evaluate<Size>(part);
					actionIndices.add(index);
				}

				// add to the info
				info.steps.add({time, std::move(actionIndices)});
			}

			reader->outdent();
		}

		// read reset steps
		String resetStepsString;
		if (reader->read("Reset", resetStepsString))
		{
			// split each step by comma
			Vector<String> resetStepsParts = Tool::split(resetStepsString, ANIMATION_ACTION_GROUP);

			// read each step
			for (String const &part : resetStepsParts)
			{
				// convert to size
				Size const index = Math::evaluate<Size>(part);
				info.resetSteps.add(index);
			}
		}
	}

	// create the animation
	return create_from_loaded<Animation>(path, info);
}

Shared<Animator> Minty::AssetManager::load_animator(Path const &path, UUID const id)
{
	// create info
	FSM fsm;
	AnimatorInfo info{};
	info.id = id;

	// read values from the file
	if (Unique<Reader> const reader = open_reader(path))
	{
		// read value, directly as an FSM
		Serializer<FSM>::deserialize(*reader, fsm);
		fsm.restart();
		info.fsm = &fsm;

		// read other values
		reader->read("Force", info.force);

#ifdef MINTY_DEBUG

		// check each state value
		// each one should be a valid UUID, or empty
		for (auto const &[name, stateId, state] : fsm.get_states())
		{
			Variable const &variable = state.get_value();

			// if empty, skip
			if (variable.is_empty())
			{
				continue;
			}

			// check type
			MINTY_ASSERT_F(variable.get_type() == Type::Object, ErrorCode::Asset_InvalidFormat, name, variable.get_type());

			// check value, if any
			UUID const id = variable.get<UUID>();
			if (!id.is_valid())
			{
				continue; // skip invalid IDs
			}
			MINTY_ASSERT_F(contains(id), ErrorCode::Asset_MissingDependency, path, id);
			MINTY_ASSERT_F(get_asset_ref(id)->get_asset_type() == AssetType::Animation, ErrorCode::Asset_InvalidDependencyType, name, id);
		}

#endif // MINTY_DEBUG
	}

	// create the animator
	return create_from_loaded<Animator>(path, info);
}

Shared<AudioClip> Minty::AssetManager::load_audio_clip(Path const &path, UUID const id)
{
	// create info
	AudioClipInfo info{};

	// read audio bytes
	Vector<Byte> bytes = read_bytes(path);
	if (bytes.is_empty())
	{
		return nullptr;
	}
	info.data = bytes.get_data();
	info.dataSize = bytes.get_size();

	// read ID
	info.id = id;

	// read values from meta
	Path metaPath = Asset::get_meta_path(path);
	if (Unique<Reader> const reader = open_reader(metaPath))
	{
		// read values
		reader->read("Volume", info.volume);
		reader->read("Loop", info.loop);
		reader->read("LoopPoint", info.loopPoint);
		reader->read("Exclusive", info.exclusive);
	}

	return create_from_loaded<AudioClip>(path, info);
}

Shared<Bitmap> Minty::AssetManager::load_bitmap(Path const &path, UUID const id)
{
	// create info
	BitmapInfo info{};
	info.id = id;

	// read values from the file
	info.data = Bitmap::load(path, info.width, info.height, info.channels);

	return create_from_loaded<Bitmap>(path, info);
}

Shared<Camera> Minty::AssetManager::load_camera(Path const &path, UUID const id)
{
	// create the info
	CameraInfo info{};
	info.id = id;

	// read values from the file
	if (Unique<Reader> const reader = open_reader(path))
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
		deserialize_asset_ref(*reader, "RenderTarget", info.renderTarget);
	}

	return create_from_loaded<Camera>(path, info);
}

Shared<Font> Minty::AssetManager::load_font(Path const &path, UUID const id)
{
	// create info
	FontInfo info{};
	info.id = id;

	// read the font data
	if (Unique<Reader> const reader = open_reader(path))
	{
		// read values
		reader->read("Name", info.name);
		Vector<UUID> variantIds;
		if (reader->read("Variants", variantIds))
		{
			// get the variants
			for (UUID const &variantId : variantIds)
			{
				Shared<FontVariant> variant = get<FontVariant>(variantId);
				MINTY_ASSERT_F(variant != nullptr, ErrorCode::Asset_MissingDependency, path, variantId);
				info.variants.add(variant);
			}
		}
	}

	// create the font
	return create_from_loaded<Font>(path, info);
}

Shared<FontVariant> Minty::AssetManager::load_font_variant(Path const &path, UUID const id)
{
	// create the info
	FontVariantInfo info{};
	info.id = id;

	// read the font variant data
	// this is a different, standard format (TTF)

	Vector<String> lines = read_lines(path);
	Float widthScale = 1.0f;
	Float heightScale = 1.0f;
	for (String const &line : lines)
	{
		// split by tabs
		Vector<String> parts = Tool::split(line, '\t');

		// determine what to do based on first word in line
		if (line.starts_with("char "))
		{
			FontChar fontChar{};

			for (String const &part : parts)
			{
				if (part.is_empty())
				{
					continue; // skip empty parts
				}

				if (part.starts_with("id="))
				{
					String idString;
					Parser<String>::parse(part.peek(3, part.get_size() - 3), idString);
					if (!idString.is_empty())
					{
						fontChar.id = idString.front();
					}
				}
				else if (part.starts_with("x="))
				{
					Parser<Float>::parse(part.peek(2, part.get_size() - 2), fontChar.x);
				}
				else if (part.starts_with("y="))
				{
					Parser<Float>::parse(part.peek(2, part.get_size() - 2), fontChar.y);
				}
				else if (part.starts_with("width="))
				{
					Parser<Float>::parse(part.peek(6, part.get_size() - 6), fontChar.width);
				}
				else if (part.starts_with("height="))
				{
					Parser<Float>::parse(part.peek(7, part.get_size() - 7), fontChar.height);
				}
				else if (part.starts_with("xoffset="))
				{
					Parser<Float>::parse(part.peek(8, part.get_size() - 8), fontChar.xOffset);
				}
				else if (part.starts_with("yoffset="))
				{
					Parser<Float>::parse(part.peek(8, part.get_size() - 8), fontChar.yOffset);
				}
				else if (part.starts_with("xadvance="))
				{
					Parser<Float>::parse(part.peek(9, part.get_size() - 9), fontChar.xAdvance);
				}
			}

			info.characters.add(fontChar);
		}
		else if (line.starts_with("kerning "))
		{
			char first = 0;
			char second = 0;
			float amount = 0;
			for (String const &part : parts)
			{
				if (part.is_empty())
				{
					continue; // skip empty parts
				}

				if (part.starts_with("first="))
				{
					Parser<Char>::parse(part.peek(6, part.get_size() - 6), first);
				}
				else if (part.starts_with("second="))
				{
					Parser<Char>::parse(part.peek(7, part.get_size() - 7), second);
				}
				else if (part.starts_with("amount="))
				{
					Parser<Float>::parse(part.peek(7, part.get_size() - 7), amount);
				}
			}

			// pack kerning into info
			info.kernings.add({first, second, amount});
		}
		else if (line.starts_with("info "))
		{
			for (String const &part : parts)
			{
				if (part.is_empty())
				{
					continue; // skip empty parts
				}

				if (part.starts_with("size="))
				{
					Parser<UInt>::parse(part.sub(5, part.get_size() - 5), info.size);
				}
				else if (part.starts_with("bold="))
				{
					Int isBold;
					Parser<Int>::parse(part.sub(5, part.get_size() - 5), isBold);
					if (isBold != 0)
					{
						info.flags |= FontFlags::Bold;
					}
				}
				else if (part.starts_with("italic="))
				{
					Int isItalic;
					Parser<Int>::parse(part.sub(7, part.get_size() - 7), isItalic);
					if (isItalic != 0)
					{
						info.flags |= FontFlags::Italic;
					}
				}
			}
		}
		else if (line.starts_with("common "))
		{
			for (String const &part : parts)
			{
				if (part.is_empty())
				{
					continue; // skip empty parts
				}

				if (part.starts_with("lineHeight="))
				{
					Parser<Float>::parse(part.sub(11, part.get_size() - 11), info.lineHeight);
				}
			}
		}
		else if (line.starts_with("page "))
		{
			// textures to load
			Path directoryPath = path.get_parent();

			for (String const &part : parts)
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
					info.texture = get_ref<Texture>(textureId);
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
			MINTY_ASSERT_F(textureSize.x > 0 && textureSize.y > 0, ErrorCode::Asset_InvalidConfiguration, path);

			// get scale
			widthScale = 1.0f / textureSize.x;
			heightScale = 1.0f / textureSize.y;
		}
	}

	return create_from_loaded<FontVariant>(path, info);
}

Shared<Image> Minty::AssetManager::load_image(Path const &path, UUID const id)
{
	// create the image using the path and ID
	Shared<Image> image = create_image(path, id);

	// add to the asset manager
	add(path, image);

	// done
	return image;
}

static void read_values(Reader &reader, Cargo &values)
{
	String objectName;
	String valueName;
	Type type;
	Byte buffer[64];
	Variable valueVariable;

	// read each object
	while (reader.indent_next(objectName))
	{
		// read names and variables for each value
		Object object;
		while (reader.read_next(valueName, type, buffer))
		{
			// add to the object values
			object.add(valueName, Variable(type, buffer));
		}

		// add to the cargo values
		values.add(objectName, object);

		reader.outdent();
	}
}

Shared<Material> Minty::AssetManager::load_material(Path const &path, UUID const id)
{
	// create info
	MaterialInfo info{};
	info.id = id;

	// read values
	if (Unique<Reader> const reader = open_reader(path))
	{
		// get template
		if (find_dependency<MaterialTemplate>(path, *reader, "Template", info.materialTemplate, true))
		{
			return nullptr;
		}

		// read values
		if (reader->indent("Values"))
		{
			read_values(*reader, info.values);
			reader->outdent();
		}
	}

	return create_from_loaded<Material>(path, info);
}

Shared<MaterialTemplate> Minty::AssetManager::load_material_template(Path const &path, UUID const id)
{
	// create info
	MaterialTemplateInfo info{};
	info.id = id;

	// read values
	if (Unique<Reader> const reader = open_reader(path))
	{
		if (find_dependency<Shader>(path, *reader, "Shader", info.shader, true))
		{
			return nullptr;
		}

		// read values
		if (reader->indent("Values"))
		{
			read_values(*reader, info.values);
			reader->outdent();
		}
	}

	return create_from_loaded<MaterialTemplate>(path, info);
}

Shared<Mesh> Minty::AssetManager::load_mesh_obj(Path const &path, UUID const id)
{
	MeshInfo info{};
	info.id = id;
	info.type = MeshType::Custom;
	ListContainer vertices(sizeof(Float32));
	ListContainer indices(sizeof(UInt16));

	Vector<String> lines = read_lines(path);

	Vector<Float3> positions;
	Vector<Float2> coords;
	Vector<Float3> normals;

	Map<Int3, UInt16> faces;
	UInt16 vertexCount = 0;

	std::istringstream ss;
	std::string token;

	Float3 position;
	Float2 coord;
	Float3 normal;

	for (auto const &line : lines)
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
					Parser<Int>::parse(token.c_str(), faceIndices.x);
					faceIndices.x -= 1;

					if (std::getline(setss, token, '/'))
					{
						Parser<Int>::parse(token.c_str(), faceIndices.y);
						faceIndices.y -= 1;

						if (std::getline(setss, token, '/'))
						{
							Parser<Int>::parse(token.c_str(), faceIndices.z);
							faceIndices.z -= 1;
						}
					}
				}

				// if combo exists, add that index
				auto found = faces.find(faceIndices);
				if (found == faces.end())
				{
					// vertex does not exist yet
					UInt16 index = vertexCount;
					position = positions.at(faceIndices.x);
					coord = coords.at(faceIndices.y);
					normal = normals.at(faceIndices.z);

					// create vertex
					vertices.append(&position.x);
					vertices.append(&position.y);
					vertices.append(&position.z);
					vertices.append(&normal.x);
					vertices.append(&normal.y);
					vertices.append(&normal.z);
					vertices.append(&coord.x);
					vertices.append(&coord.y);
					indices.append(&index);

					// add for reference
					faces.add(faceIndices, index);

					// increment count
					vertexCount += 1;
				}
				else
				{
					// vertex already exists
					UInt16 index = found->get_second();
					indices.append(&index);
				}
			}
		}
	}

	// update vertex stride to match the vertex size
	vertices.set_stride(sizeof(Float) * 8);

	// set vertex and index data
	info.vertexData = vertices.get_data();
	info.vertexCount = vertices.get_count();
	info.vertexStride = vertices.get_stride();
	info.indexData = indices.get_data();
	info.indexCount = indices.get_count();
	info.indexStride = indices.get_stride();

	// create the mesh
	return create_from_loaded<Mesh>(path, info);
}

Shared<Mesh> Minty::AssetManager::load_mesh(Path const &path, UUID const id)
{
	String extension = path.get_extension().get_string();

	if (extension == ".obj")
	{
		return load_mesh_obj(path, id);
	}

	MINTY_ABORT_F(ErrorCode::Asset_UnknownType, path);
}

Shared<Prefab> Minty::AssetManager::load_prefab(Path const &path, UUID const id)
{
	// create info
	PrefabInfo info{};
	info.id = id;

	// read values
	if (Unique<Reader> const reader = open_reader(path))
	{
		// just save the values
		Shared<Stream> const &stream = reader->get_stream();
		Size const size = static_cast<Size>(stream->get_size());
		info.source = Shared<ConstantContainer>::create(size);
		if (!stream->read(info.source->get_data(), size))
		{
			MINTY_ERROR_F(ErrorCode::Asset_LoadFailed, path);
			return nullptr;
		}
	}

	return create_from_loaded<Prefab>(path, info);
}

Shared<RenderPass> Minty::AssetManager::load_render_pass(Path const &path, UUID const id)
{
	// create info
	RenderPassInfo info{};
	info.id = id;

	// read values
	RenderAttachment colorAttachment{};
	RenderAttachment depthAttachment{};
	if (Unique<Reader> const reader = open_reader(path))
	{
		// read color attachment
		if (reader->indent("Attachments"))
		{
			if (!read_attachment(path, *reader, "Color", colorAttachment, true))
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

Shared<RenderTarget> Minty::AssetManager::load_render_target(Path const &path, UUID const id)
{
	// create info
	RenderTargetInfo info{};
	info.id = id;

	// read values
	if (Unique<Reader> const reader = open_reader(path))
	{
		AssetManager &assetManager = AssetManager::get_singleton();
		assetManager.deserialize_asset(*reader, "RenderPass", info.renderPass);
		String images;
		if (reader->read("Images", images) && !images.is_empty())
		{
			// if "Surface", automatically grab the images from the surface
			MINTY_ASSERT_F(images == "Surface", ErrorCode::Serialization_InvalidFormat, path, F("Invalid image name: \"{}\". Must provide a valid name (Surface), or a list of Image IDs to use.", images));

			// get the surface images
			RenderManager &renderManager = RenderManager::get_singleton();
			Shared<Surface> surface = renderManager.get_surface();
			MINTY_ASSERT_F(surface != nullptr, ErrorCode::Asset_MissingDependency, path);
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
				String dummy;
				UUID id;
				Shared<Image> image;
				Shared<Texture> texture;
				while (reader->read_next(dummy, id))
				{
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
	}

	return create_from_loaded<RenderTarget>(path, info);
}

Shared<Shader> Minty::AssetManager::load_shader(Path const &path, UUID const id)
{
	// create info
	ShaderInfo info{};
	info.id = id;

	// read values
	if (Unique<Reader> const reader = open_reader(path))
	{
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

		// render pass
		if (find_dependency<RenderPass>(path, *reader, "RenderPass", info.renderPass, true))
		{
			return nullptr;
		}

		// modules
		if (reader->indent("Stages"))
		{
			if (find_dependency<ShaderModule>(path, *reader, "Vertex", info.vertexShaderModule, true))
			{
				return nullptr;
			}

			if (find_dependency<ShaderModule>(path, *reader, "Fragment", info.fragmentShaderModule, true))
			{
				return nullptr;
			}

			reader->outdent();
		}

		// bindings
		if (reader->indent("Bindings"))
		{
			String name;			   // key str
			UInt binding = UINT_MAX;   // key
			ShaderInputRate inputRate; // value
			UInt location;
			Type type;
			while (reader->indent_next(name, inputRate))
			{
				ShaderBinding shaderBinding{};

				// read the binding
				if (!Parser<UInt>::parse(name.get_data(), binding))
				{
					// if the first binding, this += will make it wrap around to 0
					// otherwise, go to the next binding
					binding += 1;
				}
				shaderBinding.binding = binding;

				// set the input rate
				shaderBinding.inputRate = inputRate;

				// read attributes
				// read each attribute
				location = UINT_MAX;
				while (reader->read_next(name, type))
				{
					ShaderAttribute shaderAttribute{};

					// get attribute location
					if (!Parser<UInt>::parse(name.get_data(), location))
					{
						// set location to last location + 1
						location += 1;
					}
					shaderAttribute.location = location;

					// get attribute type
					shaderAttribute.type = type;

					// add to the binding
					shaderBinding.attributes.add(std::move(shaderAttribute));
				}

				// add to the info
				info.vertexInput.bindings.add(std::move(shaderBinding));

				reader->outdent();
			}

			reader->outdent();
		}

		// inputs (uniform, push, etc.)
		if (reader->indent("Inputs"))
		{
			// offset for push constants
			Size offset = 0;
			String name;
			Type type;

			while (reader->indent_next(name))
			{
				// get the input and set the name
				ShaderInput input{};
				input.name = std::move(name);

				// get basic data
				reader->read("Type", input.type);
				reader->read("Stage", input.stage);
				reader->read("Set", input.set);
				reader->read("Binding", input.binding);
				reader->read("Count", input.count);
				reader->read("Frequent", input.frequent);

				// set offset if push constant
				if (input.type == ShaderInputType::PushConstant)
				{
					MINTY_ASSERT_F(input.stage == ShaderStage::Vertex, ErrorCode::Asset_Shader_PushConstantLocation, path, input.name);
					input.offset = offset;
				}

				// read structure
				if (reader->indent("Structure"))
				{
					while (reader->read_next(name, type))
					{
						// add to the input
						input.data.add({name, Variable(type)});

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

				info.inputs.add(std::move(input));

				reader->outdent();
			}

			reader->outdent();
		}

		// viewport
		if (find_dependency<Viewport>(path, *reader, "Viewport", info.viewport, false))
		{
			// if no viewport given, use default viewport
			info.viewport = RenderManager::get_singleton().get_default_viewport();
		}
	}

	// create the shader
	return create_from_loaded<Shader>(path, info);
}

Shared<ShaderModule> Minty::AssetManager::load_shader_module(Path const &path, UUID const id)
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

static void read_sprite_slice(Reader &reader, SpriteSlice &slice, CoordinateMode const defaultCoordinateMode = CoordinateMode::Normalized)
{
	if (!reader.read("CoordinateMode", slice.coordinateMode))
	{
		slice.coordinateMode = defaultCoordinateMode;
	}
	reader.read("Offset", slice.offset);
	reader.read("Size", slice.size);
	reader.read("Pivot", slice.pivot);
	reader.read("PPU", slice.pixelsPerUnit);
}

Shared<Sprite> Minty::AssetManager::load_sprite(Path const &path, UUID const id)
{
	// create info
	SpriteInfo info{};
	info.id = id;

	// read values
	if (Unique<Reader> const reader = open_reader(path))
	{
		// read values
		AssetManager &assetManager = AssetManager::get_singleton();
		assetManager.deserialize_asset(*reader, "Texture", info.texture);
		read_sprite_slice(*reader, info.slice);
	}

	return create_from_loaded<Sprite>(path, info);
}

Shared<SpriteAtlas> Minty::AssetManager::load_sprite_atlas(Path const &path, UUID const id)
{
	// create info
	SpriteAtlasInfo info{};
	info.id = id;

	// read values
	if (Unique<Reader> const reader = open_reader(path))
	{
		// read values
		AssetManager &assetManager = AssetManager::get_singleton();
		assetManager.deserialize_asset(*reader, "Texture", info.texture);
		CoordinateMode defaultCoordinateMode;
		if (!reader->read("CoordinateMode", defaultCoordinateMode))
		{
			defaultCoordinateMode = CoordinateMode::Normalized;
		}

		// read the automatic slices
		if (reader->indent("Groups"))
		{
			String name;
			while (reader->indent_next(name))
			{
				SpriteSlice slice{};
				Int2 count{};

				// read data
				read_sprite_slice(*reader, slice, defaultCoordinateMode);
				reader->read("Count", count);

				// Sprites is overrides for specific slices, so they can have their own, static IDs.
				// The other Sprites within the Count range will have random IDs, generated every time the game is ran.
				Map<Int2, UUID> overrides;
				if (reader->indent("IDs"))
				{
					Int2 index; // key
					UUID id;	// value
					while (reader->read_next(name, id))
					{
						// read the index
						index = Evaluator<Int2>::evaluate(name);

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

			reader->outdent();
		}
	}

	return create_from_loaded<SpriteAtlas>(path, info);
}

Shared<Texture> Minty::AssetManager::load_texture(Path const &path, UUID const id)
{
	// create info
	TextureInfo info{};
	info.id = id;

	// read meta file
	Path metaPath = Asset::get_meta_path(path);
	if (Unique<Reader> const reader = open_reader(metaPath))
	{
		// create image
		UUID imageId = UUID::create();
		Shared<Image> image = create_image(path, imageId);

		// add image to asset manager
		add(path, image);

		// set info values
		info.image = image;
		if (!reader->read("Filter", info.filter))
		{
			info.filter = Filter::Linear;
		}
		if (!reader->read("AddressMode", info.addressMode))
		{
			info.addressMode = AddressMode::Repeat;
		}
	}

	return create_from_loaded<Texture>(path, info);
}

Unique<AssetManager> Minty::AssetManager::create(AssetManagerInfo const &info)
{
	return Unique<AssetManager>::create(info);
}

Unique<AssetManager> Minty::AssetManager::create()
{
	AssetManagerInfo info{};
	return create(info);
}

AssetManager &Minty::AssetManager::get_singleton()
{
	Unique<AssetManager> const &instance = Application::get_singleton().get_asset_manager();
	MINTY_ASSERT(instance, ErrorCode::Application_AssetManagerNotInitialized);
	return *instance;
}

Unique<AssetManager> const &Minty::AssetManager::get_instance()
{
	return Application::get_singleton().get_asset_manager();
}