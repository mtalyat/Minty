#include "pch.hpp"
#include "ResourceManager.hpp"
#include "ResourceManagerInfo.hpp"
#include "Core/Debug/Debug.hpp"
#include "Core/Stream/FileStream.hpp"
#include "Core/File/PhysicalFile.hpp"
#include "Core/File/VirtualFile.hpp"
#include "Core/Data/StringBuilder.hpp"
#include "Core/Serialize/TextReader.hpp"
#include "Core/Constant/File.hpp"

using namespace Minty;

ResourceManager *Minty::ResourceManager::s_instance = nullptr;

Minty::ResourceManager::ResourceManager(ResourceManagerInfo const &info)
    : m_wrapper(),
      m_assets_generic(),
      m_assets_clips()
{
    MINTY_ASSERT(s_instance == nullptr, ErrorCodeEnum::Singleton_AlreadyExists);
    s_instance = this;

    for (Path const &wrapPath : info.wraps)
    {
        load_wrap(wrapPath);
    }
}

Minty::ResourceManager::~ResourceManager()
{
    MINTY_ASSERT(s_instance == this, ErrorCodeEnum::Singleton_DifferentObject);
    s_instance = nullptr;
}

Bool Minty::ResourceManager::load_wrap(Path const &path)
{
    MINTY_ASSERT_A(Path::exists(path), ErrorCodeEnum::File_NotFound, path.get_string().get_data());

    m_wrapper.add(path);

    return true;
}

Unique<File> Minty::ResourceManager::open_file(Path const &path, FileFlags const flags) const
{
    Location const location = find_location(path);
    switch (location)
    {
    case Location::FileSystem:
    {
        Unique<PhysicalFile> file = Unique<PhysicalFile>::create();
        if (!file->open(path, flags))
        {
            MINTY_ERROR_A(ErrorCodeEnum::File_FailedToOpen, path.get_string().get_data());
            return nullptr;
        }
        return file;
    }
    case Location::Wrapper:
    {
        Unique<VirtualFile> file = Unique<VirtualFile>::create();
        if (!m_wrapper.open(path, *file))
        {
            MINTY_ERROR_A(ErrorCodeEnum::File_FailedToOpen, path.get_string().get_data());
            return nullptr;
        }
        return file;
    }
    }

    MINTY_ERROR_A(ErrorCodeEnum::File_NotFound, path.get_absolute().get_string().get_data());
    return nullptr;
}

Unique<Stream> Minty::ResourceManager::open_stream(Path const &path, FileFlags const flags) const
{
    Unique<File> file = open_file(path, flags);
    if (!file)
    {
        return nullptr;
    }
    return Unique<FileStream>::create(std::move(file));
}

Unique<Reader> Minty::ResourceManager::open_reader(Path const &path) const
{
    Unique<Stream> stream = open_stream(path, FileFlagsEnum::Read | FileFlagsEnum::Binary);
    if (!stream)
    {
        return nullptr;
    }
    return Unique<TextReader>::create(std::move(stream));
}

Unique<Writer> Minty::ResourceManager::open_writer(Path const &path) const
{
    MINTY_NOT_IMPLEMENTED();
    return Unique<Writer>();
}

Vector<Byte> Minty::ResourceManager::read_file(Path const &path) const
{
    Unique<File> file = open_file(path);
    if (!file)
    {
        MINTY_ERROR_A(ErrorCodeEnum::File_FailedToOpen, path.get_string().get_data());
        return {};
    }

    Size const size = file->get_size();
    Vector<Byte> container;
    container.resize(size);
    if (!file->read(container.get_data(), size))
    {
        MINTY_ERROR_A(ErrorCodeEnum::File_ReadFailed, path.get_string().get_data());
        return {};
    }
    return container;
}

ResourceManager &Minty::ResourceManager::get_instance()
{
    MINTY_ASSERT(s_instance != nullptr, ErrorCodeEnum::Singleton_DoesNotExist);
    return *s_instance;
}

ResourceManager::Location Minty::ResourceManager::find_location(Path const &path) const
{
    if (m_wrapper.contains(path))
    {
        return Location::Wrapper;
    }
    else if (Path::exists(path))
    {
        return Location::FileSystem;
    }
    else
    {
        return Location::Undefined;
    }
}

UUID Minty::ResourceManager::load_id(Unique<Reader> const &metaReader)
{
    Stream &stream = metaReader->get_stream();
    Char ch;

    // Return an empty UUID if the format is invalid (expected ": <UUID>")
    if (!stream.read(&ch, sizeof(Char)) || ch != ':')
    {
        MINTY_WARNING(ErrorCodeEnum::Resource_InvalidFormat);
        return UUID();
    }
    if (!stream.read(&ch, sizeof(Char)) || ch != ' ')
    {
        MINTY_WARNING(ErrorCodeEnum::Resource_InvalidFormat);
        return UUID();
    }

    // Read the UUID from the stream
    StringBuilder uuidBuilder;
    while (stream.read(&ch, sizeof(Char)) && ch != '\r' && ch != '\n')
    {
        uuidBuilder.append(ch);
    }

    ch = stream.peek();
    while (ch == '\r' || ch == '\n')
    {
        stream.read(&ch, sizeof(Char));
        ch = stream.peek();
    }

    UUID id;
    if (!Parser<UUID>::parse(uuidBuilder.get_view(), id))
    {
        MINTY_WARNING_A(ErrorCodeEnum::Resource_InvalidFormat, uuidBuilder.get_data());
        return UUID();
    }

    return id;
}

Path Minty::ResourceManager::get_meta_path(Path const &path)
{
    MINTY_ASSERT(!path.is_empty(), ErrorCodeEnum::Argument_ExpectedNonEmpty);

    return Path(path.get_string() + EXTENSION_META);
}
