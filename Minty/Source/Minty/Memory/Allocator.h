#pragma once

namespace Minty
{
	/// <summary>
	/// Defines how a given resource is allocated in memory.
	/// </summary>
	enum class Allocator
	{
		/// <summary>
		/// This resource will be allocated using the system's default allocator.
		/// </summary>
		Default,

		/// <summary>
		/// This resource will be allocated for the current frame, then deallocated.
		/// </summary>
		Temporary,

		/// <summary>
		/// This resource will be allocated for a few frames, then deallocated.
		/// </summary>
		Task,

		/// <summary>
		/// This resource will be allocated, and must be manually de-allocated.
		/// </summary>
		Persistent,
	};
}