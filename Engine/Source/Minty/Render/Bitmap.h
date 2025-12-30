#ifndef MINTY_RENDER_BITMAP_H
#define MINTY_RENDER_BITMAP_H

/**
 * @file Bitmap.h
 * @brief Header file defining the Bitmap class.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Color.h"
#include "Minty/Data/Path.h"

namespace Minty
{
    struct BitmapInfo;

    /**
     * @brief Represents a Bitmap.
     */
    class Bitmap
        : public Asset
    {
#pragma region Constructor

    public:
        /**
         * @brief Creates a new Bitmap.
         * @param info The Bitmap creation parameters.
         */
        Bitmap(BitmapInfo const& info);

        Bitmap(Bitmap const& other);

        Bitmap(Bitmap&& other) noexcept;

        ~Bitmap();

#pragma endregion

#pragma region Operators

    public:
        Bitmap& operator=(Bitmap const& other);

        Bitmap& operator=(Bitmap&& other) noexcept;

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Gets the width of the Bitmap.
         * @return The width of the Bitmap.
         */
        inline UInt get_width() const { return m_width; }

        /**
         * @brief Gets the height of the Bitmap.
         * @return The height of the Bitmap.
         */
        inline UInt get_height() const { return m_height; }

        /**
         * @brief Gets the number of channels in the Bitmap.
         * @return The number of channels in the Bitmap.
         */
        inline UInt get_channels() const { return m_channels; }

        /**
         * @brief Gets a pointer to the pixel data.
         * @return A pointer to the pixel data.
         */
        inline AnyConst get_data() const { return mp_data; }

        /**
         * @brief Gets a pointer to the pixel data.
         * @return A pointer to the pixel data.
         */
        inline Any get_data() { return mp_data; }

        /**
         * @brief Gets the size of the Bitmap data in bytes.
         * @return The size of the Bitmap data.
         */
        inline Size get_size() const { return static_cast<Size>(m_width) * static_cast<Size>(m_height) * static_cast<Size>(m_channels); }

        /**
         * @brief Gets the color of a pixel at the specified coordinates.
         * @param x The x-coordinate of the pixel.
         * @param y The y-coordinate of the pixel.
         * @return The color of the pixel.
         */
        Color get_pixel(UInt const x, UInt const y) const;

        /**
         * @brief Sets the color of a pixel at the specified coordinates.
         * @param x The x-coordinate of the pixel.
         * @param y The y-coordinate of the pixel.
         * @param color The color to set the pixel to.
         */
        void set_pixel(UInt const x, UInt const y, Color const& color);
        
        /**
         * @brief Returns AssetType::Image.
         * @return AssetType::Image.
         */
        inline AssetType get_asset_type() const override { return AssetType::Image; }

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Loads the Bitmap from the specified path.
         * @param path The path to load the Bitmap from.
         */
        static Byte* load(Path const& path, UInt& width, UInt& height, UInt& channels);

        /**
         * @brief Creates a new Bitmap.
         * @param info The Bitmap creation parameters.
         * @return A Bitmap Owner.
         */
        static Shared<Bitmap> create(BitmapInfo const& info);

        /**
         * @brief Creates a default Bitmap (1x1 size, 4 channels, black pixel).
         * @return A Bitmap Owner.
         */
        static Shared<Bitmap> create();

#pragma endregion

#pragma region Variables

    private:
        UInt m_width;
        UInt m_height;
        UInt m_channels;
        Byte* mp_data;

#pragma endregion
    };
}

#endif // MINTY_RENDER_BITMAP_H