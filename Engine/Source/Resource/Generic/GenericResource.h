#pragma once

/**
 * @file GenericResourceInfo.h
 * @brief Header file defining the GenericResourceInfo struct.
 * @author Mitchell Talyat
 */

#include "Core/Serialize/Serializer.h"
#include "Core/Data/ConstantContainer.h"

namespace Minty
{
	struct GenericResourceInfo;

	/**
	 * @brief A generic Resource. It could be anything!
	 */
	class GenericResource
	{
		friend struct Serializer<GenericResource>;

#pragma region Constructors

	public:
		/**
		 * @brief Creates a new GenericResource.
		 * @param info The info.
		 */
		GenericResource();

		/**
		 * @brief Creates a new GenericResource.
		 * @param info The info.
		 */
		GenericResource(GenericResourceInfo && info);

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the data of this Resource.
		 * @return The ConstantContainer with the data for this Resource.
		 */
		ConstantContainer const& get_data() const { return *m_container; }

		/**
		 * @brief Gets the data of this Resource as a String.
		 * @return A String of the data.
		 */
		String get_text() const;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Opens a Reader for this Resource's data.
		 * @return A Reader Unique pointer.
		 */
		Unique<Reader> open_reader() const;

#pragma endregion

#pragma region Variables

	private:
		Shared<ConstantContainer> m_container;

#pragma endregion
	};

	template<>
	struct Serializer<GenericResource>
	{
		static Bool serialize(Writer& writer, GenericResource const& value);
		static Bool deserialize(Reader& reader, GenericResource& value);
	};
}
