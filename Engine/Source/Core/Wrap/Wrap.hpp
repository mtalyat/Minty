#pragma once

/**
 * @file Wrap.h
 * @brief Header file defining the Wrap class.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Platform/Macro/Keyword.hpp"
#include "Core/Data/Map.hpp"
#include "Core/Data/Path.hpp"
#include "Core/Data/Set.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Compression/CompressionLevel.hpp"
#include "Core/Constant/Convert.hpp"

namespace Minty
{
	class PhysicalFile;
	class VirtualFile;

	/**
	 * @brief Simulates a file system within a single file. This is useful for packaging multiple files into a single file.
	 */
	class Wrap
	{

#pragma region Constant

	public:
		/**
		 * @brief The first bytes in any Wrap file.
		 */
		static constexpr Char const *WRAP_MAGIC = "WRAP";

		/**
		 * @brief The number of magic bytes in a Wrap file.
		 */
		static constexpr Size WRAP_MAGIC_SIZE = 4;

		/**
		 * @brief The maximum size of a Wrap header path.
		 */
		static constexpr Size WRAP_HEADER_PATH_SIZE = 100;

		/**
		 * @brief The maximum size of a Wrap header name.
		 */
		static constexpr Size WRAP_HEADER_NAME_SIZE = 50;

		/**
		 * @brief The maximum size of a Wrap entry path.
		 */
		static constexpr Size WRAP_ENTRY_PATH_SIZE = 255;

		/**
		 * @brief The current Wrap version.
		 */
		static constexpr UInt16 WRAP_VERSION = 0;

#pragma endregion

#pragma region Types

	public:
		/**
		 * @brief The type of the Wrap file.
		 */
		enum class WrapTypeEnum : UInt16
		{
			/**
			 * @brief This file has no type. Ignore it.
			 */
			None = 0,
			/**
			 * @brief This file is a base file.
			 */
			File = 1,
			/**
			 * @brief This file should override some data.
			 */
			Update = 2,
		};

		/**
		 * @brief The header information for a .wrap file. Holds meta data about the file itself.
		 */
		struct Header
		{
			/**
			 * @brief The ID to ensure that this is in fact a Wrap file.
			 */
			Char id[WRAP_MAGIC_SIZE] = {'W', 'R', 'A', 'P'};

			/**
			 * @brief The type of Wrap file.
			 */
			WrapTypeEnum type = WrapTypeEnum::None;

			/**
			 * @brief The Wrap version.
			 */
			uint16_t wrapVersion = 0;

			/**
			 * @brief The content version.
			 */
			uint32_t contentVersion = 0;

			/**
			 * @brief The base path of every virtual file Entry within this Wrap.
			 */
			Char basePath[WRAP_HEADER_PATH_SIZE] = "";

			/**
			 * @brief The name of this Wrap.
			 */
			Char name[WRAP_HEADER_NAME_SIZE] = "";

			/**
			 * @brief The number of Entries within this Wrap.
			 */
			uint32_t entryCount = 0;

			Header()
			{
				memset(basePath, 0, WRAP_HEADER_PATH_SIZE * sizeof(Char));
				memset(name, 0, WRAP_HEADER_NAME_SIZE * sizeof(Char));
			}

			Header(Header const &other);

			Header &operator=(Header const &other);
		};

		/**
		 * @brief The entry information for a virtual file that is stored within the .wrap file.
		 */
		struct Entry
		{
			/**
			 * @brief The path to this Entry within the Wrap file.
			 */
			Char path[WRAP_ENTRY_PATH_SIZE] = "";

			/**
			 * @brief The compression level of this data in the Wrap file.
			 */
			Byte compressionLevel = 0;

			/**
			 * @brief The reserved size of the data within the Wrap file.
			 */
			uint32_t reservedSize = 0;

			/**
			 * @brief The size of the data after compression, if any.
			 */
			uint32_t compressedSize = 0;

			/**
			 * @brief The size of the data before compression, if any.
			 */
			uint32_t uncompressedSize = 0;

			/**
			 * @brief The offset to the data within the Wrap file.
			 */
			uint32_t offset = 0;

			Entry()
			{
				memset(path, 0, WRAP_ENTRY_PATH_SIZE * sizeof(Char));
			}

			Entry(Entry const &other);

			Entry &operator=(Entry const &other);

			Bool is_empty() const { return uncompressedSize == 0; }
		};

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Wrap.
		 */
		Wrap()
			: m_path(), m_compressionThreshold(KB), m_header(), m_entries(), m_empties(), m_indexed()
		{
		}

		/**
		 * @brief Creates and loads a Wrap file at the given path.
		 * @param path The path to the Wrap file on the disk.
		 */
		Wrap(Path const &path)
			: m_path(), m_compressionThreshold(KB), m_header(), m_entries(), m_indexed()
		{
			load(path);
		}

		/**
		 * @brief Creates a new Wrap file with the given name, base path, and content version.
		 * @param path The path to the Wrap file on the disk.
		 * @param name The name of the Wrap file.
		 * @param entryCount The number of entries in the Wrap file.
		 * @param base The base path all files within the Wrap file.
		 * @param contentVersion The version of the content within the Wrap file.
		 * @param type The type of the Wrap file.
		 * @param compressionThreshold The threshold at which to start compressing files. Anything below this value will not be compressed.
		 */
		Wrap(Path const &path, String const &name, uint32_t const entryCount, Path const &base = "", uint32_t const contentVersion = 0, WrapTypeEnum const type = WrapTypeEnum::File, Size const compressionThreshold = KB);

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the base path of each file within this Wrap.
		 * @return
		 */
		Char const *get_base_path() const;

		/**
		 * @brief Sets the base path of each file within this Wrap.
		 * @param path
		 */
		void set_base_path(Path const &path);

		/**
		 * @brief Gets the Path that this Wrap file is located at.
		 * @return
		 */
		Path const &get_path() const;

		/**
		 * @brief Gets the name of this Wrap file.
		 * @return
		 */
		Char const *get_name() const;

		/**
		 * @brief Sets the name of this Wrap file.
		 * @param name
		 */
		void set_name(String const &name);

		/**
		 * @brief Gets the Wrap version of this Wrap file.
		 * @return
		 */
		uint16_t get_wrap_version() const;

		/**
		 * @brief Gets the content version of this Wrap file.
		 * @return
		 */
		uint32_t get_content_version() const;

		/**
		 * @brief Gets the type of this Wrap file.
		 * @return
		 */
		WrapTypeEnum get_type() const;

		/**
		 * @brief Sets the Type for this Wrap file.
		 * @param type
		 */
		void set_type(WrapTypeEnum const type);

		/**
		 * @brief Gets the size of the Wrap file.
		 * @return
		 */
		Size get_size() const;

		/**
		 * @brief Gets the number of entries in this Wrap.
		 * @return
		 */
		Size get_entry_count() const;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Loads the Wrap file at the given path.
		 * @param path The Path of the Wrap file.
		 */
		void load(Path const &path);

		/**
		 * @brief Flushes all changes within this Wrap to the disk.
		 */
		void flush();

	private:
		// writes the header to the file
		void write_header(PhysicalFile &wrapFile) const;

		// writes the entry at the given index to the file
		void write_entry(PhysicalFile &wrapFile, Size const index) const;

		// adds the given entry to m_wraps, then returns the index of it
		uint32_t add_entry(Entry &entry);

#pragma region Files

	private:
		// forces the given path to include the base path if it doesn't already
		Path fix_path(Path const &path) const;

		// forces the given path to be relative to the base path
		Path relative_path(Path const &path) const;

	public:
		/**
		 * @brief Adds the file at the given physicalPath to the Wrap at the given virtualPath.
		 * @param physicalPath The path to the file to read and add to the Wrap file.
		 * @param virtualPath The path of the file within the Wrap file.
		 * @param compression The level of compression for the given file.
		 * @param reservedSize The reserved size of the chunk to store the file within. If the reservedSize is 0, it will default to the size of the file at the physicalPath.
		 */
		void add(Path const &physicalPath, Path const &virtualPath, CompressionLevelEnum const compression = CompressionLevelEnum::Default, uint32_t const reservedSize = 0);

		/**
		 * @brief Checks if the Wrap contains a file with the given path.
		 * @param path The path to check.
		 * @return
		 */
		Bool contains(Path const &path) const;

		/**
		 * @brief Opens a file at the given path using the given VirtualFile.
		 * @param path The path at which to open a file.
		 * @param file The file object to use to open with.
		 * @return
		 */
		Bool open(Path const &path, VirtualFile &file) const;

		/**
		 * @brief Opens, reads, uncompresses (if needed) and returns the data from the file at the given path.
		 * @param path The path at which to open a file.
		 * @return The uncompressed data from the file, or an empty vector if no file found.
		 */
		Vector<Byte> read_bytes(Path const &path) const;

		/**
		 * @brief Gets the Entry at the given index.
		 * @param index
		 * @return
		 */
		Entry const &get_entry(Size const index) const;

		/**
		 * @brief Gets the Entry at the given path.
		 * @param index
		 * @return
		 */
		Entry const &get_entry(Path const &path) const;

#pragma endregion

#pragma endregion

#pragma region Statics

	public:
		/**
		 * @brief Checks if there is a valid Wrap file at the given path.
		 * @param path The Path to a file.
		 * @return True if the file exists, and is a Wrap file.
		 */
		static Bool exists(Path const &path);

		/**
		 * @brief Loads or creates a new Wrap if none exists.
		 * @param path
		 * @param name
		 * @param entryCount
		 * @param base
		 * @param contentVersion
		 * @return
		 */
		static Wrap load_or_create(Path const &path, String const &name, uint32_t const entryCount, Path const &base = "", uint32_t const contentVersion = 0, WrapTypeEnum const type = WrapTypeEnum::File);

#pragma endregion

#pragma region Variables

	private:
		// path to the wrap file on the disk
		Path m_path;

		// the threshold at which to compress files
		Size m_compressionThreshold; // 1 KB

		// header in the wrap file
		Header m_header;

		// list of entries in the wrap file
		Vector<Entry> m_entries;
		// list of empty gaps in the wrap file, where files used to be
		Set<uint32_t> m_empties;
		// virtual paths indexed to entry indices
		Map<Path, Size> m_indexed;

#pragma endregion
	};
}
