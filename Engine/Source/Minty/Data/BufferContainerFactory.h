#pragma once
#include "Minty/Data/BufferContainer.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/UUID.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
	/// <summary>
	/// Handles groups of BufferContainers. Used for batch rendering.
	/// </summary>
	class BufferContainerFactory
	{
#pragma region Variables

	private:
		Size m_initialCapacity;
		BufferUsage m_usage;
		Vector<Vector<Tuple<Bool, BufferContainer>>> m_containers;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new BufferContainerFactory with the given BufferContainer capacity and usage.
		/// </summary>
		/// <param name="initialCapacity">The capacity for each new BufferContainer.</param>
		/// <param name="usage">The usage for each new BufferContainer.</param>
		BufferContainerFactory(Size const initialCapacity, BufferUsage const usage)
			: m_initialCapacity(initialCapacity)
			, m_usage(usage)
			, m_containers()
		{
		}

		~BufferContainerFactory() = default;

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the BufferContainer that corresponds to the given group ID and index.
		/// </summary>
		/// <param name="size">The size the BufferContainer must be able to hold.</param>
		/// <returns>The BufferContainer.</returns>
		BufferContainer& get_container(Size const size);

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Marks all BufferContainers as unused, so they can be reused.
		/// </summary>
		void reset();

#pragma endregion
	};
}