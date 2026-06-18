#include "pch.h"
#include "ImageResource.h"
#include "ImageInfo.h"
#include "Core/Serialize/Reader.h"
#include "Core/Serialize/Writer.h"
#include "Core/Data/Path.h"
#include "Resource/Manager/ResourceManager.h"
#include "Independence/STB/STB_Image.h"
#include "Core/Tool/Copy.h"

using namespace Minty;

Bool Minty::Serializer<ImageResource>::serialize(Writer &writer, ImageResource const &value)
{
    MINTY_NOT_IMPLEMENTED();
    return Bool();
}

Bool Minty::Serializer<ImageResource>::deserialize(Reader &reader, ImageResource &value)
{
    // Data to load
    Path path;
    ImageFormat format = value.format;
    ImageType type = value.type;
    ImageTiling tiling = value.tiling;
    ImageUsageFlags usage = value.usage;
    Bool immutable = value.immutable;

    // Load the data from the reader
    if (!reader.read("Path", path))
    {
        MINTY_ERROR(ErrorCodeEnum::Serialization_MissingKey);
        return false;
    }
    reader.read("Format", format);
    reader.read("Type", type);
    reader.read("Tiling", tiling);
    reader.read("Usage", usage);
    reader.read("Immutable", immutable);

    // Validate the read data
    MINTY_ASSERT(type == ImageTypeEnum::D2, ErrorCodeEnum::NotSupported);

    // Read the image data from the file
    ResourceManager &resourceManager = ResourceManager::get_instance();
    Unique<Stream> stream = resourceManager.open_stream(path);
    if (!stream)
    {
        MINTY_ERROR_A(ErrorCodeEnum::File_FailedToOpen, path.get_string().get_data());
        return false;
    }
    Size const dataSize = static_cast<Size>(stream->get_size());
    ConstantContainer data(dataSize);
    if (!stream->read(data.get_data(), dataSize))
    {
        MINTY_ERROR_A(ErrorCodeEnum::File_ReadFailed, path.get_string().get_data());
        return false;
    }

    // Convert it into pixel data
    Int width, height;
    Int channels = static_cast<Int>(format.get_depth());
    Byte *const pixelData = load_image_data_from_memory(static_cast<Byte const *>(data.get_data()), static_cast<Int>(dataSize), width, height, channels);
    Size const pixelDataSize = static_cast<Size>(width) * static_cast<Size>(height) * static_cast<Size>(channels);
    Vector<Byte> pixelDataContainer;
    pixelDataContainer.resize(pixelDataSize);
    Tool::shallow_copy<Byte>(pixelData, static_cast<Byte *>(pixelDataContainer.get_data()), pixelDataSize);
    free_image_data(pixelData);
    if (channels != static_cast<Int>(format.get_depth()))
    {
        MINTY_ERROR_A(ErrorCodeEnum::Resource_InvalidFormat, path.get_string().get_data());
        return false;
    }

    // Set the resource data
    value.data = std::move(pixelDataContainer);
    value.size = {width, height};
    value.format = format;
    value.type = type;
    value.tiling = tiling;
    value.usage = usage;
    value.immutable = immutable;

    // Success
    return true;
}
