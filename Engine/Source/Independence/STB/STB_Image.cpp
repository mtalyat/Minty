#include "STB_Image.h"

using namespace Minty;

Byte *Minty::load_image_data_from_memory(Byte const *const buffer, Int const bufferSize, Int &width, Int &height, Int &channels)
{
    return stbi_load_from_memory(buffer, bufferSize, &width, &height, &channels, channels);
}

void Minty::free_image_data(Byte *const data)
{
    stbi_image_free(data);
}
