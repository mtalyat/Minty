#ifndef MINTY_MEMORY_ALLOCATORTYPE_H
#define MINTY_MEMORY_ALLOCATORTYPE_H

/**
 * @file AllocatorType.h
 * @brief Header file defining the AllocatorType enumeration.
 * @author Mitchell Talyat
 */

namespace Minty
{
	/**
	 * @enum AllocatorType
	 * @brief Enumeration of different types of memory allocators.
	 */
	enum class AllocatorType
	{
		/**
		 * @brief This resource will be allocated and de-allocated using the default allocator.
		 */
		Default,

		/**
		 * @brief This resource will be allocated for the current frame, then deallocated.
		 */
		Temporary,

		/**
		 * @brief This resource will be allocated for a few frames, then deallocated.
		 */
		Task,

		/**
		 * @brief This resource will be allocated, and must be manually de-allocated.
		 */
		Persistent,
	};
}

#endif // MINTY_MEMORY_ALLOCATORTYPE_H