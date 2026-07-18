#include "pch.hpp"
#include "MeshResource.hpp"
#include "Core/Data/Path.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"
#include "Resource/Manager/ResourceManager.hpp"
#include "Core/Tool/String.hpp"
#include "Core/Serialize/ParsedTypes.hpp"
#include "Core/Constant/File.hpp"

using namespace Minty;

static Bool deserialize_obj(Vector<Byte> const& data, ListContainer& vertexContainer, ListContainer& indexContainer)
{
    // Get the data as a string
    StringView const text(static_cast<Char const*>(static_cast<void const*>(data.get_data())), data.get_size());

    // Split into lines
    Vector<StringView> lines = Tool::split_lines(text);

    // Parse each line
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

	// Set strides of individual types
	vertexContainer.set_stride(sizeof(Float));
	indexContainer.set_stride(sizeof(UInt16));

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
					vertexContainer.append(&position.x);
					vertexContainer.append(&position.y);
					vertexContainer.append(&position.z);
					vertexContainer.append(&normal.x);
					vertexContainer.append(&normal.y);
					vertexContainer.append(&normal.z);
					vertexContainer.append(&coord.x);
					vertexContainer.append(&coord.y);
					indexContainer.append(&index);

					// add for reference
					faces.add(faceIndices, index);

					// increment count
					vertexCount += 1;
				}
				else
				{
					// vertex already exists
					UInt16 index = found->get_second();
					indexContainer.append(&index);
				}
			}
		}
	}

	// update strides to match the total size of the vertex and index respectively
	vertexContainer.set_stride(sizeof(Float) * 8);
	indexContainer.set_stride(sizeof(UInt16));

	return true;
}

Bool Minty::Serializer<MeshResource>::serialize(Writer &writer, MeshResource const &value)
{
    MINTY_NOT_IMPLEMENTED();
    return Bool();
}

Bool Minty::Serializer<MeshResource>::deserialize(Reader &reader, MeshResource &value)
{
    // Data to read
    Path path;
    ListContainer vertexContainer{};
    ListContainer indexContainer{};

    // Read path
    if (!reader.read("Path", path))
    {
        MINTY_ABORT(ErrorCodeEnum::Serialization_MissingKey);
        return false;
    }

    // Read based on the extension
    Path const extension = path.get_extension();
    ResourceManager &resourceManager = ResourceManager::get_instance();
    Vector<Byte> const fileData = resourceManager.read_file(path);

    if (extension == Minty::EXTENSION_OBJ)
    {
        if (!deserialize_obj(fileData, vertexContainer, indexContainer))
        {
            MINTY_ERROR_A(ErrorCodeEnum::Resource_InvalidFormat, path.get_string().get_data());
            return false;
        }
    } else
    {
        MINTY_ERROR_A(ErrorCodeEnum::Resource_InvalidFormat, extension.get_string().get_data());
        return false;
    }

    // Set the output value
    value.vertexContainer = std::move(vertexContainer);
    value.indexContainer = std::move(indexContainer);

    return true;
}
