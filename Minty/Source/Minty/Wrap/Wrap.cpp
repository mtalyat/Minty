#include "pch.h"
#include "Wrap.h"
#include "Minty/Core/Format.h"
#include "Minty/Core/Math.h"

using namespace Minty;

Minty::Wrap::Wrap(Path const& path, String const& name, uint32_t const entryCount, Path const& base, uint32_t const contentVersion)
    : m_path(path.get_absolute())
    , m_header()
    , m_entries()
    , m_indexed()
{
    // set header data
    m_header.type = Type::File;
    m_header.wrapVersion = WRAP_VERSION;
    m_header.contentVersion = contentVersion;
    set_name(name);
    set_base_path(base);
    m_header.entryCount = entryCount;

    m_entries.resize(entryCount, Entry());
    for (uint32_t i = 0; i < entryCount; i++)
    {
        m_empties.add(i);
    }

    // open file, open with truncate to override any existing file
    PhysicalFile file(m_path, File::Flags::Write | File::Flags::Binary | File::Flags::Truncate);

    // write header
    write_header(file);

    // write entries
    for (uint32_t i = 0; i < entryCount; i++)
    {
        write_entry(file, i);
    }

    file.close();
}

void Minty::Wrap::load(Path const& path)
{
    Path absolutePath = path.get_absolute();

    MINTY_ASSERT(Path::exists(absolutePath), "Cannot load Wrap file. The file does not exist at the given path.");
	MINTY_ASSERT(Path::is_file(absolutePath), "Cannot load Wrap file. The path is not a file.");
	MINTY_ASSERT(absolutePath.get_extension() == EXTENSION_WRAP, "Cannot load Wrap file. The file does not have the correct extension.");

    m_path = absolutePath;

    // open the file
    PhysicalFile file(m_path, File::Flags::Read | File::Flags::Binary);

    // read header data
    file.read(&m_header, sizeof(Header));

    // ensure it is a valid wrap file by checking the magic data
    if (memcmp(m_header.id, WRAP_MAGIC, WRAP_MAGIC_SIZE))
    {
        // does not have the correct "WRAP" id magic
        MINTY_ERROR(F("Cannot emplace \"{}\" into Wrap file: invalid data.", m_path.get_string()));
        m_header = Header();
        return;
    }

    // read entries
    Path basePath(m_header.basePath);
    m_entries.resize(m_header.entryCount, Entry());
    m_indexed.reserve(m_header.entryCount);
    for (uint32_t i = 0; i < m_header.entryCount; i++)
    {
        // read entry
        Entry& entry = m_entries.at(i);
        file.read(&entry, sizeof(Entry));
        // add path and index
        m_indexed.add(fix_path(entry.path), i);
        // add to empties if empty
        if (entry.is_empty())
        {
            m_empties.add(i);
        }
    }

    file.close();
}

void Minty::Wrap::flush()
{
	// open file, open with truncate to override any existing file
	PhysicalFile file(m_path, File::Flags::Write | File::Flags::Binary | File::Flags::Truncate);

	// write header
	write_header(file);
	
    // write entries
	for (uint32_t i = 0; i < m_header.entryCount; i++)
	{
		write_entry(file, i);
	}
	
    file.close();
}

void Minty::Wrap::write_header(PhysicalFile& wrapFile) const
{
    wrapFile.seek_write(0);
    wrapFile.write(&m_header, sizeof(Header));
}

void Minty::Wrap::write_entry(PhysicalFile& wrapFile, Size const index) const
{
    wrapFile.seek_write(sizeof(Header) + sizeof(Entry) * index);
    wrapFile.write(&m_entries.at(index), sizeof(Entry));
}

uint32_t Minty::Wrap::emplace_entry(Entry& newEntry)
{
    int64_t bestIndex = -1;

    // search through empty entries to find best fit
    for (uint32_t const index : m_empties)
    {
        Entry& entry = m_entries.at(index);

        if (entry.reservedSize && entry.reservedSize < newEntry.reservedSize)
        {
            // not big enough
            continue;
        }

        // big enough

        // replace best index if no index yet, or this is a closer reserved size
        if (bestIndex == -1)
        {
            // no best index yet, so place the index unconditionally
            bestIndex = index;
            continue;
        }

        Entry const& bestEntry = m_entries.at(bestIndex);
        if ((entry.reservedSize && !bestEntry.reservedSize) || (entry.reservedSize && bestEntry.reservedSize && entry.reservedSize < bestEntry.reservedSize))
        {
            // place if best has no reserved size and this does, OR
            // if both have a size and this one is smaller
            bestIndex = index;
        }
    }

    // if index, replace that entry and return that index
    if (bestIndex >= 0)
    {
        // TODO: if not an exact size match, then split the entry
        uint32_t index = static_cast<uint32_t>(bestIndex);

        // remove index from empties
        m_empties.remove(index);

        // replace old indexed path
        m_indexed.remove(fix_path(m_entries[index].path));

        // move some data to new entry (pos, size, etc.)
        Entry const& oldEntry = m_entries.at(index);

        // if there already was a size and offset reserved, use those, otherwise accept the incoming size and offset
        if (oldEntry.reservedSize)
        {
            newEntry.offset = oldEntry.offset;
            newEntry.reservedSize = oldEntry.reservedSize;
        }

        // officially replace it
        m_entries[index] = newEntry;
        m_indexed[Path(m_header.basePath) / newEntry.path] = index;

        // return that index
        return static_cast<uint32_t>(index);
    }

    // cannot fit
    MINTY_ERROR(F("Cannot emplace entry to Wrap file. Entry count surpassed ({}).", m_entries.get_size()));

    return -1;
}

Path Minty::Wrap::fix_path(Path const& path) const
{
    if (path.is_empty() || m_header.basePath[0] == '\0' || path.begin()->get_string() == m_header.basePath)
    {
        // all good
        return path;
    }
    else
    {
        // missing base path
        return Path(m_header.basePath) / path;
    }
}

Path Minty::Wrap::relative_path(Path const& path) const
{
    if (path.is_empty() || m_header.basePath[0] == '\0' || path.begin()->get_string() != m_header.basePath)
    {
        // all good
        return path;
    }
    else
    {
        // remove base path
        return path.get_relative_to(m_header.basePath);
    }
}

Char const* Minty::Wrap::get_base_path() const
{
    return m_header.basePath;
}

void Minty::Wrap::set_base_path(Path const& path)
{
    // set the base path
    memcpy(m_header.basePath, path.get_string().get_data(), WRAP_HEADER_PATH_SIZE);
    m_header.basePath[WRAP_HEADER_PATH_SIZE - 1] = '\0';

    // replace indexed
    m_indexed.clear();
    Path basePath(m_header.basePath);
    for (Size i = 0; i < m_header.entryCount; i++)
    {
        Entry const& entry = m_entries.at(i);
        m_indexed.add(basePath / entry.path, i);
    }
}

Path const& Minty::Wrap::get_path() const
{
    return m_path;
}

Char const* Minty::Wrap::get_name() const
{
    return m_header.name;
}

void Minty::Wrap::set_name(String const& name)
{
    // set name
    memcpy(m_header.name, name.get_data(), WRAP_HEADER_NAME_SIZE);
    m_header.name[WRAP_HEADER_NAME_SIZE - 1] = '\0';
}

uint16_t Minty::Wrap::get_wrap_version() const
{
    return m_header.wrapVersion;
}

uint32_t Minty::Wrap::get_content_version() const
{
    return m_header.contentVersion;
}

void Minty::Wrap::emplace(Path const& physicalPath, Path const& virtualPath, CompressionLevel const compressionLevel, uint32_t const reservedSize)
{
	MINTY_ASSERT(Path::exists(physicalPath), "Cannot emplace into Wrap file: file does not exist.");
	MINTY_ASSERT(Path::is_file(physicalPath), "Cannot emplace into Wrap file: not a regular file.");

    // open wrap file
    PhysicalFile wrapFile(m_path, File::Flags::ReadWrite | File::Flags::Binary);

    // open file
    PhysicalFile file(physicalPath, File::Flags::Read | File::Flags::Binary);

    // read the data from the file
    File::Size_t fileSize = file.get_size();
    Byte* fileData = new Byte[fileSize];
    file.read(fileData, fileSize);

    // done with that file
    file.close();

    // create an entry for the new file
    String source = relative_path(virtualPath).get_string();
    MINTY_ASSERT(source.get_size() < WRAP_ENTRY_PATH_SIZE, "The given virtual Path is too long.");
    Entry entry;
    memcpy(entry.path, source.get_data(), Math::min(static_cast<Size>(WRAP_ENTRY_PATH_SIZE - 1), source.get_size()));
    entry.path[WRAP_ENTRY_PATH_SIZE - 1] = '\0';
    entry.compressionLevel = static_cast<Byte>(compressionLevel);
    entry.uncompressedSize = static_cast<uint32_t>(fileSize);

    // compress the data, if needed
    if (static_cast<Bool>(compressionLevel))
    {
        // calculate sizes
        ULong sourceSize = static_cast<ULong>(fileSize);
        ULong destSize = compress_bound(sourceSize);

        // create dest buffer
        Byte* compressedData = new Byte[destSize];

        // compress it
        if (!compress(compressedData, destSize, fileData, sourceSize, compressionLevel))
        {
            MINTY_ERROR(F("Cannot emplace \"{}\" into Wrap file: failed to compress file with compression level {}.", physicalPath.get_string(), static_cast<Int>(compressionLevel)));
            return;
        }

        // replace source
        delete[] fileData;
        fileData = compressedData;
        fileSize = static_cast<File::Size_t>(destSize);

        //MINTY_LOG_FORMAT("Compressed{} from{} bytes to{} bytes.", physicalPath.string(), std::to_string(sourceSize), std::to_string(destSize));
    }

    // set size and offset
    entry.offset = static_cast<uint32_t>(wrapFile.get_size());
    entry.compressedSize = static_cast<uint32_t>(fileSize);
    if (reservedSize)
    {
        entry.reservedSize = reservedSize;
    }
    else
    {
        entry.reservedSize = entry.compressedSize;
    }

    // add entry
    Size index = emplace_entry(entry);

    // write to file
    write_entry(wrapFile, index);
    wrapFile.seek_write(entry.offset, File::Direction::Begin);
    wrapFile.write(fileData, fileSize);

    // cleanup
    delete[] fileData;
    wrapFile.close();
}

Bool Minty::Wrap::contains(Path const& path) const
{
    return m_indexed.contains(path);
}

Bool Minty::Wrap::open(Path const& path, VirtualFile& file) const
{
    if (!contains(path))
    {
        return false;
    }

    // get entry
    Entry const& entry = get_entry(path);

    // open file in the given virtual file
    file.open(m_path, File::Flags::Read | File::Flags::Binary, entry.offset, entry.uncompressedSize);

    return true;
}

Vector<Char> Minty::Wrap::read(Path const& path) const
{
    VirtualFile file;

    if (!open(path, file))
    {
        // could not open
        return Vector<Char>();
    }

    // read all data from file
    Entry const& entry = get_entry(path);
    File::Size_t fileSize = static_cast<File::Size_t>(entry.compressedSize);
    Byte* fileData = new Byte[fileSize];
    file.read(fileData, fileSize);

    // uncompress it
    ULong sourceSize = static_cast<ULong>(entry.compressedSize);
    ULong size = static_cast<ULong>(entry.uncompressedSize);
    Byte* data = nullptr;
	// uncompress it, if it is compressed
	if (entry.compressedSize == entry.uncompressedSize)
	{
        data = fileData;
		fileData = nullptr;
	}
	else
	{
		data = new Byte[size];
		if (!uncompress(data, size, fileData, sourceSize))
		{
			MINTY_ERROR(F("Failed to uncompress file \"{}\" in Wrap file.", path.get_string()));
			return Vector<Char>();
		}
        delete[] fileData;
	}

    // add to vector
    Vector<Char> result;
    result.resize(size, ' ');
    memcpy(result.get_data(), data, size);

    // done with data
    delete[] data;

    return result;
}

Wrap::Entry const& Minty::Wrap::get_entry(Size const index) const
{
    return m_entries.at(index);
}

Size Minty::Wrap::get_entry_count() const
{
    return m_entries.get_size();
}

Wrap::Entry const& Minty::Wrap::get_entry(Path const& path) const
{
    return m_entries.at(m_indexed.at(path));
}

Wrap::Type Minty::Wrap::get_type() const
{
    return m_header.type;
}

void Minty::Wrap::set_type(Type const type)
{
    m_header.type = type;
}

Size Minty::Wrap::get_size() const
{
    return Path::get_file_size(m_path);
}

Wrap Minty::Wrap::load_or_create(Path const& path, String const& name, uint32_t const entryCount, Path const& base, uint32_t const contentVersion)
{
    if (Path::exists(path))
    {
        return Wrap(path);
    }
    else
    {
        return Wrap(path, name, entryCount, base, contentVersion);
    }
}

Minty::Wrap::Header::Header(Header const& other)
    : id("")
    , type(other.type)
    , wrapVersion(other.wrapVersion)
    , contentVersion(other.contentVersion)
    , basePath("")
    , name("")
    , entryCount(other.entryCount)
{
    memcpy(id, other.id, WRAP_MAGIC_SIZE);
    memcpy(basePath, other.basePath, WRAP_HEADER_PATH_SIZE);
    basePath[WRAP_HEADER_PATH_SIZE - 1] = '\0';
    memcpy(name, other.name, WRAP_HEADER_NAME_SIZE);
    name[WRAP_HEADER_NAME_SIZE - 1] = '\0';
}

Wrap::Header& Minty::Wrap::Header::operator=(Header const& other)
{
    if (&other != this)
    {
        memcpy(id, other.id, WRAP_MAGIC_SIZE);
        type = other.type;
        wrapVersion = other.wrapVersion;
        contentVersion = other.contentVersion;
        memcpy(basePath, other.basePath, WRAP_HEADER_PATH_SIZE);
        basePath[WRAP_HEADER_PATH_SIZE - 1] = '\0';
        memcpy(name, other.name, WRAP_HEADER_NAME_SIZE);
        name[WRAP_HEADER_NAME_SIZE - 1] = '\0';
        entryCount = other.entryCount;
    }

    return *this;
}

Minty::Wrap::Entry::Entry(Entry const& other)
    : path("")
    , compressionLevel(other.compressionLevel)
    , reservedSize(other.reservedSize)
    , compressedSize(other.compressedSize)
    , uncompressedSize(other.uncompressedSize)
    , offset(other.offset)
{
    memcpy(path, other.path, WRAP_ENTRY_PATH_SIZE);
    path[WRAP_ENTRY_PATH_SIZE - 1] = '\0';
}

Wrap::Entry& Minty::Wrap::Entry::operator=(Entry const& other)
{
    if (&other != this)
    {
        memcpy(path, other.path, WRAP_ENTRY_PATH_SIZE);
        path[WRAP_ENTRY_PATH_SIZE - 1] = '\0';
        compressionLevel = other.compressionLevel;
        reservedSize = other.reservedSize;
        compressedSize = other.compressedSize;
        uncompressedSize = other.uncompressedSize;
        offset = other.offset;
    }

    return *this;
}

