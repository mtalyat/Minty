#include "Bitmap.h"
#include "Minty/Render/BitmapInfo.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Library/STB.h"

using namespace Minty;

Minty::Bitmap::Bitmap(BitmapInfo const& info)
    : Asset(info.id)
    , m_width(info.width)
    , m_height(info.height)
    , m_channels(info.channels)
    , mp_data(nullptr)
{
    Size const dataSize = info.width * info.height * info.channels;
    if (dataSize == 0)
    {
        m_width = 0;
        m_height = 0;
        m_channels = 0;
        return;
    }
    
    mp_data = new Byte[dataSize];
    std::memcpy(mp_data, info.data, dataSize * sizeof(Byte));
}

Minty::Bitmap::Bitmap(Bitmap const &other)
    : Asset(other.get_id())
    , m_width(other.m_width)
    , m_height(other.m_height)
    , m_channels(other.m_channels)
    , mp_data(nullptr)
{
    Size const dataSize = other.get_size();
    if (dataSize == 0)
    {
        m_width = 0;
        m_height = 0;
        m_channels = 0;
        return;
    }

    mp_data = new Byte[dataSize];
    std::memcpy(mp_data, other.mp_data, dataSize * sizeof(Byte));
}

Minty::Bitmap::Bitmap(Bitmap &&other) noexcept
    : Asset(other.get_id())
    , m_width(other.m_width)
    , m_height(other.m_height)
    , m_channels(other.m_channels)
    , mp_data(other.mp_data)
{
    other.m_width = 0;
    other.m_height = 0;
    other.m_channels = 0;
    other.mp_data = nullptr;
}

Minty::Bitmap::~Bitmap()
{
    delete[] mp_data;
}

Bitmap &Minty::Bitmap::operator=(Bitmap const &other)
{
    if(this != &other)
    {
        delete[] mp_data;

        m_width = other.m_width;
        m_height = other.m_height;
        m_channels = other.m_channels;

        Size const dataSize = other.get_size();
        if (dataSize == 0)
        {
            m_width = 0;
            m_height = 0;
            m_channels = 0;
            mp_data = nullptr;
            return *this;
        }

        mp_data = new Byte[dataSize];
        std::memcpy(mp_data, other.mp_data, dataSize * sizeof(Byte));
    }
    return *this;
}

Bitmap &Minty::Bitmap::operator=(Bitmap &&other) noexcept
{
    if(this != &other)
    {
        delete[] mp_data;

        m_width = other.m_width;
        m_height = other.m_height;
        m_channels = other.m_channels;
        mp_data = other.mp_data;

        other.m_width = 0;
        other.m_height = 0;
        other.m_channels = 0;
        other.mp_data = nullptr;
    }
    return *this;
}

Color Minty::Bitmap::get_pixel(UInt const x, UInt const y) const
{
    MINTY_ASSERT(mp_data != nullptr, ErrorCode::Object_InvalidState);

    if (x >= m_width || y >= m_height)
    {
        MINTY_ERROR(ErrorCode::Argument_OutOfRange);
        return Color(0, 0, 0, 0); // Out of bounds, return transparent black
    }

    UInt index = (y * m_width + x) * m_channels;
    Byte r = 0, g = 0, b = 0, a = 255;

    if (m_channels >= 1)
    {
        r = mp_data[index + 0];
    }
    if (m_channels >= 2)
    {
        g = mp_data[index + 1];
    }
    if (m_channels >= 3)
    {
        b = mp_data[index + 2];
    }
    if (m_channels >= 4)
    {
        a = mp_data[index + 3];
    }

    return Color(r, g, b, a);
}

void Minty::Bitmap::set_pixel(UInt const x, UInt const y, Color const &color)
{
    MINTY_ASSERT(mp_data != nullptr, ErrorCode::Object_InvalidState);

    if (x >= m_width || y >= m_height)
    {
        MINTY_ERROR(ErrorCode::Argument_OutOfRange);
        return; // Out of bounds
    }

    UInt index = (y * m_width + x) * m_channels;

    if (m_channels >= 1)
    {
        mp_data[index + 0] = color.r;
    }
    if (m_channels >= 2)
    {
        mp_data[index + 1] = color.g;
    }
    if (m_channels >= 3)
    {
        mp_data[index + 2] = color.b;
    }
    if (m_channels >= 4)
    {
        mp_data[index + 3] = color.a;
    }
}

Byte *Minty::Bitmap::load(Path const &path, UInt &width, UInt &height, UInt &channels)
{
    // load the image using stb_image
    Int temp_width, temp_height, temp_channels;
    Byte* data = stbi_load(path.get_string().get_data(), &temp_width, &temp_height, &temp_channels, 0);
    if (!data)
    {
        MINTY_ERROR(ErrorCode::Render_FailedToLoadImage);
        return nullptr;
    }

    // replace with new data
    width = static_cast<UInt>(temp_width);
    height = static_cast<UInt>(temp_height);
    channels = static_cast<UInt>(temp_channels);
    return data;
}

Shared<Bitmap> Minty::Bitmap::create(BitmapInfo const &info)
{
    return Shared<Bitmap>::create(info);
}

Shared<Bitmap> Minty::Bitmap::create()
{
    return Shared<Bitmap>::create(BitmapInfo{});
}
