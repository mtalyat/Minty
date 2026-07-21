#pragma once

/**
 * @file CompressionLevel.hpp
 * @brief Defines the CompressionLevel enum for data compression levels.
 * @author Mitchell Talyat
 */

#include "Core/Type/Enum.hpp"

namespace Minty
{
    /**
     * @enum CompressionLevelEnum
     * @brief Represents the level of compression to apply to data.
     */
	enum class CompressionLevelEnum
	{
		Level0 = 0,
		Level1 = 1,
		Level2 = 2,
		Level3 = 3,
		Level4 = 4,
		Level5 = 5,
		Level6 = 6,
		Level7 = 7,
		Level8 = 8,
		Level9 = 9,

        Count,

        /**
         * @brief No compression.
         */
		None = Level0,

        /**
         * @brief Fast, low-quality compression.
         */
		Fast = Level1,
        
        /**
         * @brief Slow, high-quality compression.
         */
		Slow = Level9,

        /**
         * @brief Fast, low-quality compression.
         */
		Low = Level1,
        
        /**
         * @brief Slow, high-quality compression.
         */
		High = Level9,

        /**
         * @brief Default compression level.
         */
		Default = Level6,
	};

	MINTY_ENABLE_ENUM_OPERATORS(CompressionLevelEnum)
}
