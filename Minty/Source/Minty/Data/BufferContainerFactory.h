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
		Map<UUID, Vector<BufferContainer>> m_groups;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new BufferContainerFactory with the given BufferContainer usage.
		/// </summary>
		/// <param name="usage">The usage for each new BufferContainer.</param>
		BufferContainerFactory(BufferUsage const usage)
			: m_initialCapacity(0)
			, m_usage(usage)
			, m_groups()
		{
		}

		/// <summary>
		/// Creates a new BufferContainerFactory with the given BufferContainer capacity and usage.
		/// </summary>
		/// <param name="initialCapacity">The capacity for each new BufferContainer.</param>
		/// <param name="usage">The usage for each new BufferContainer.</param>
		BufferContainerFactory(Size const initialCapacity, BufferUsage const usage)
			: m_initialCapacity(initialCapacity)
			, m_usage(usage)
			, m_groups()
		{
		}

		~BufferContainerFactory() = default;

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the BufferContainer that corresponds to the given group ID and index.
		/// </summary>
		/// <param name="groupId">The ID of the group to get the BufferContainer from.</param>
		/// <param name="index">The index of the BufferContainer within the group.</param>
		/// <returns>The BufferContainer.</returns>
		BufferContainer& get_container(UUID const groupId, Size const index);

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Creates a new group of BufferContainers and returns its ID.
		/// </summary>
		/// <returns>The ID of the new group.</returns>
		UUID create_group();

#pragma endregion
	};
}