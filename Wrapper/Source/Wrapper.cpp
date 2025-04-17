#include <Minty.h>

using namespace Minty;

enum class Action
{
	/// <summary>
	/// Create a new Wrap file, based on the given path to a directory.
	/// </summary>
	Wrap,

	/// <summary>
	/// Creates a new directory from the given Wrap file, populated with the files within it.
	/// </summary>
	Unwrap,

	/// <summary>
	/// Creates a new Wrap file, based on the given path to a directory, using the previous Wrap file's data.
	/// </summary>
	Update,

	/// <summary>
	/// Opens an existing Wrap file and prints out the contents.
	/// </summary>
	Info,
};

int main(Int argc, Char const* argv[])
{
	// Initialize the parser
	ArgumentParser parser;
	parser.add_parameter("file", 1); // file name
	parser.add_parameter("action", 1); // action to perform
	parser.add_parameter("path", 1); // path to directory or file to operate on
	parser.add_parameter("path2", -1); // second path to use for certain actions (optional)
	parser.add_parameter("output", "o"); // custom output directory or file
	parser.add_parameter("name", "n"); // name of the wrap file
	parser.add_parameter("base", "b"); // virtual base path for the assets within the wrap file
	parser.add_parameter("version", "v"); // the version of the wrap file
	parser.add_parameter("type", "t"); // the type of the wrap file
	parser.add_parameter("compression", "c"); // compression level for the wrap file

	// Parse the arguments
	parser.parse(argc, argv);

	// get action
	Action action;
	if (!parser.has_argument("action"))
	{
		Debug::write_error("No action argument provided.");
		return 1;
	}
	String actionStr = parser.get_argument("action").front();
	if (actionStr == "wrap")
	{
		action = Action::Wrap;
	}
	else if (actionStr == "unwrap")
	{
		action = Action::Unwrap;
	}
	else if (actionStr == "update")
	{
		action = Action::Update;
	}
	else if (actionStr == "info")
	{
		action = Action::Info;
	}
	else
	{
		Debug::write_error(F("Invalid action argument provided: {}", actionStr));
		return 1;
	}

	// get path
	if (!parser.has_argument("path"))
	{
		Debug::write_error("No path argument provided.");
		return 1;
	}
	Path path = parser.get_argument("path").front();

	// validate path
	if (!Path::exists(path))
	{
		Debug::write_error(F("Path does not exist: {}", path));
		return 1;
	}
	switch (action)
	{
	case Action::Wrap:
	case Action::Update:
		if (!Path::is_directory(path))
		{
			Debug::write_error(F("Path is not a directory: {}", path));
			return 1;
		}
		break;
	case Action::Unwrap:
	case Action::Info:
		if (!Wrap::exists(path))
		{
			Debug::write_error(F("Path is not a Wrap file: {}", path));
			return 1;
		}
		break;
	}

	// get path2, if needed
	Path path2 = "";
	if (parser.has_argument("path2"))
	{
		path2 = parser.get_argument("path2").front();
	}

	// if info, load the wrap and print the contents
	Wrap* wrap = nullptr;
	if (action == Action::Info)
	{
		wrap = new Wrap(path);

		// if path2 is provided, check if it exists in the wrap
		if (!path2.is_empty())
		{
			// check if the path2 exists in the wrap
			if (!wrap->contains(path2))
			{
				Debug::write_error(F("Path does not exist in the Wrap file: {}", path2));
				return 1;
			}

			// print info for just that entry at the path
			auto const& entry = wrap->get_entry(path2);

			std::cout
				<< "Wrap Info for \"" << path << "\":\n"
				<< "  " << entry.path << "\n"
				<< "    Compression Level: " << entry.compressionLevel << "\n"
				<< "    Reserved Size: " << entry.reservedSize << "\n"
				<< "    Compressed Size: " << entry.compressedSize << "\n"
				<< "    Uncompressed Size: " << entry.uncompressedSize << "\n"
				<< "    Offset: " << entry.offset << "\n";
		}
		else
		{
			// print all info
			uint32_t entryCount = static_cast<uint32_t>(wrap->get_entry_count());

			std::cout
				<< "Wrap Info at \"" << path << "\":\n"
				<< "  Name: " << wrap->get_name() << "\n"
				<< "  Type: " << (wrap->get_type() == Wrap::Type::File ? "File" : "Update") << "\n"
				<< "  Content Version: " << wrap->get_content_version() << "\n"
				<< "  Wrap Version: " << wrap->get_wrap_version() << "\n"
				<< "  Base Path: " << wrap->get_base_path() << "\n"
				<< "  Entry Count: " << entryCount << "\n"
				<< "  Entries:\n";

			for (uint32_t i = 0; i < entryCount; i++)
			{
				auto const& entry = wrap->get_entry(i);

				std::cout << "    " << entry.path << "\n";
			}
		}

		delete wrap;

		return 0;
	}

	// get output path
	Path output;
	if (parser.has_argument("output"))
	{
		output = parser.get_argument("output").front();
	}
	else
	{
		switch (action)
		{
		case Action::Wrap:
		case Action::Update:
			// Default: output to the same directory as the input path
			output = F("{}{}", path.get_parent() / path.get_name(), EXTENSION_WRAP);
			break;
		case Action::Unwrap:
			// Default: output to the same directory as the input path
			output = F("{}{}", path.get_parent(), path.get_name());
			break;
		}
	}

	Vector<Path> files;
	if (action == Action::Wrap || action == Action::Update)
	{
		// get all files in the directory
		files = Path::get_files(path, true);
	}

	// get compression
	CompressionLevel compression = CompressionLevel::Default;
	if (parser.has_argument("compression"))
	{
		String compressionStr = String::to_lower(parser.get_argument("compression").front());
		Int compressionInt;
		if (compressionStr == "none")
		{
			compression = CompressionLevel::None;
		}
		else if (compressionStr == "fast" || compressionStr == "low")
		{
			compression = CompressionLevel::Fast;
		}
		else if (compressionStr == "default")
		{
			compression = CompressionLevel::Default;
		}
		else if (compressionStr == "best" || compressionStr == "high")
		{
			compression = CompressionLevel::High;
		}
		else if (try_int(compressionStr, compressionInt))
		{
			compression = static_cast<CompressionLevel>(compressionInt);
		}
		else
		{
			Debug::write_error(F("Invalid compression argument provided: {}", compressionStr));
			return 1;
		}
	}

	// if updating, use the existing wrap file, and output path to do the work
	if (action == Action::Update)
	{
		// if no path, assume the output path
		if (path2.is_empty())
		{
			path2 = output;
		}

		// validate path2
		if (!Wrap::exists(path2))
		{
			Debug::write_error(F("Wrap file does not exist at: {}. Cannot perform an update.", path2));
			return 1;
		}

		// open the old wrap
		Wrap* oldWrap = new Wrap(path2);

		uint32_t oldVersion = oldWrap->get_content_version();
		uint32_t newVersion = oldVersion + 1;

		std::cout << "Updating \"" << path2 << "\" from v" << oldVersion << " -> v" << newVersion << ":\n";

		// use new entry count
		uint32_t entryCount = static_cast<uint32_t>(files.get_size());

		// use data from old wrap to create new wrap
		Path const TEMP_PATH = F("{}.tmp", path2);
		wrap = new Wrap(TEMP_PATH, oldWrap->get_name(), entryCount, oldWrap->get_base_path(), newVersion, oldWrap->get_type());

		// add files to the new wrap
		Set<Path> allFiles;
		Size updates = 0;
		Size additions = 0;
		Size removals = 0;
		for (auto const& file : files)
		{
			// add the file to the wrap
			Path relativePath = file.get_relative_to(path);
			wrap->add(file, relativePath, compression);

			// get old wrap entry, if any
			if (oldWrap->contains(relativePath))
			{
				auto const& oldEntry = oldWrap->get_entry(relativePath);
				auto const& newEntry = wrap->get_entry(relativePath);

				// identify changes
				if (oldEntry.compressedSize != newEntry.compressedSize || oldEntry.uncompressedSize != newEntry.uncompressedSize)
				{
					std::cout << "  Updated: " << relativePath << "\n";
					updates++;
				}
			}
			else
			{
				// addition
				std::cout << "  Added: " << relativePath << "\n";
				additions++;
			}

			allFiles.add(relativePath);
		}

		// identify removals
		for (uint32_t i = 0; i < oldWrap->get_entry_count(); i++)
		{
			auto const& entry = oldWrap->get_entry(i);
			if (!allFiles.contains(entry.path))
			{
				std::cout << "  Removed: " << entry.path << "\n";
				removals++;
			}
		}

		// print summary
		if (updates == 0 && additions == 0 && removals == 0)
		{
			// do not update
			std::cout << "\nNo changes detected. Update aborted.\n";

			// delete the new wrap
			File::destroy(TEMP_PATH);
		}
		else
		{
			// print summary
			std::cout << "\nSummary:\n"
				<< "  Updates: " << updates << "\n"
				<< "  Additions: " << additions << "\n"
				<< "  Removals: " << removals << "\n";

			// move from temp to path2 (output) name
			File::move(TEMP_PATH, path2);
		}

		// all done
		delete oldWrap;
		delete wrap;

		return 0;
	}

	// get name
	String name;
	if (parser.has_argument("name"))
	{
		name = parser.get_argument("name").front();
	}
	else
	{
		// Default: Make name the name of the directory
		name = path.get_name().get_string();
	}
	
	// get base path
	Path base;
	if (parser.has_argument("base"))
	{
		base = parser.get_argument("base").front();
	}
	else
	{
		// Default: base path is empty
		base = "";
	}

	// get version
	uint32_t version;
	if (!parser.has_argument("version") || !try_uint(parser.get_argument("version").front(), version))
	{
		// Default: version is 0
		version = 0;
	}

	// get type
	Wrap::Type type;
	if (parser.has_argument("type"))
	{
		String typeStr = String::to_lower(parser.get_argument("type").front());
		if (typeStr == "file")
		{
			type = Wrap::Type::File;
		}
		else if (typeStr == "update")
		{
			type = Wrap::Type::Update;
		}
		else
		{
			Debug::write_error(F("Invalid type argument provided: {}", typeStr));
			return 1;
		}
	}
	else
	{
		// Default: file type
		type = Wrap::Type::File;
	}

	if (action == Action::Wrap)
	{
		if (path2.is_empty())
		{
			// Default: output directory
			path2 = output;
		}
		if (path2.is_empty())
		{
			Debug::write_error(F("No output path provided for wrapping: {}. Cannot perform an unwrap.", path));
			delete wrap;
			return 1;
		}

		std::cout << "Wrapping \"" << path << "\" to \"" << path2 << "\":\n";

		// create new wrap
		wrap = new Wrap(path2, name, static_cast<uint32_t>(files.get_size()), base, version, type);
		for (auto const& file : files)
		{
			// add the file to the wrap
			Path relativePath = file.get_relative_to(path);
			std::cout << "  " << relativePath << "\n";
			wrap->add(file, relativePath, compression);
		}
		
		// all done
		delete wrap;

		return 0;
	}

	if (action == Action::Unwrap)
	{
		if (path2.is_empty())
		{
			// Default: output directory
			path2 = output;
		}
		if (path2.is_empty())
		{
			Debug::write_error(F("No output path provided for unwrapping: {}. Cannot perform an unwrap.", path));
			delete wrap;
			return 1;
		}

		std::cout << "Unwrapping \"" << path << "\" to \"" << path2 << "\":\n";

		// open the wrap
		wrap = new Wrap(path);

		// create the output directory
		Path::create(path2);

		// for each entry, extract the file into the output directory
		for (uint32_t i = 0; i < wrap->get_entry_count(); i++)
		{
			auto const& entry = wrap->get_entry(i);

			std::cout << "  " << entry.path << "\n";

			// get the path to extract to
			Path extractPath = path2 / entry.path;

			// create the directory if it doesn't exist
			Path extractParent = extractPath.get_parent();
			if (!extractParent.is_empty())
			{
				Path::create(extractParent);
			}

			// extract the file
			Vector<Byte> data = wrap->read_bytes(entry.path);

			// write to a file
			File::write_bytes(extractPath, data);
		}

		// all done
		delete wrap;

		return 0;
	}

	// if we get here, something went wrong
	Debug::write_error("Invalid action specified.");
	return 1;
}
