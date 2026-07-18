#pragma once

/**
 * @file Wrapper.h
 * @brief Header file defining the Wrapper class.
 * @author Mitchell Talyat
 */

#include "Wrap.hpp"
#include "Platform/Type/Primitive.hpp"
#include "Core/Data/Vector.hpp"

namespace Minty
{
	class Path;
	class VirtualFile;

	/**
	 * @brief Handles a collection of Wrap files.
	 */
	class Wrapper
	{
#pragma region Variables

	private:
		// all wraps
		Vector<Wrap> m_wraps;

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Wrapper.
		 */
		Wrapper() = default;

#pragma endregion

#pragma region Iterators

	public:
		/**
		 * @brief Gets an Iterator to the beginning of the Wrap list.
		 * @return An Iterator pointing to the first element.
		 */
		Vector<Wrap>::Iterator begin() { return m_wraps.begin(); }

		/**
		 * @brief Gets an Iterator to the end of the Wrap list.
		 * @return An Iterator pointing to the last element + 1.
		 */
		Vector<Wrap>::Iterator end() { return m_wraps.end(); }

		/**
		 * @brief Gets a ConstIterator to the beginning of the Wrap list.
		 * @return A ConstIterator pointing to the first element.
		 */
		Vector<Wrap>::ConstIterator begin() const { return m_wraps.begin(); }

		/**
		 * @brief Gets a ConstIterator to the end of the Wrap list.
		 * @return A ConstIterator pointing to the last element + 1.
		 */
		Vector<Wrap>::ConstIterator end() const { return m_wraps.end(); }

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the number of Wraps within this Wrapper.
		 */
		Size get_wrap_count() const;

#pragma endregion

	public:
		/**
		 * @brief Adds the given Wrap to this Wrapper.
		 * @param wrap The Wrap at add.
		 */
		void add(Wrap const& wrap);

		/**
		 * @brief Adds the Wrap file at the given path to this Wrapper.
		 * @param path The Path of the Wrap file.
		 */
		void add(Path const& path);

		/**
		 * @brief Gets the Wrap at the given index.
		 * @return The Wrap at the given index.
		 */
		Wrap& get_wrap(Size const index);

		/**
		 * @brief Gets the Wrap at the given index.
		 * @return The Wrap at the given index.
		 */
		Wrap const& get_wrap(Size const index) const;

		/**
		 * @brief Finds the Wrap file that contains the given Path.
		 * @param path A path that the target Wrap file contains.
		 * @return A pointer to the found Wrap file, or nullptr if no file was found.
		 */
		Wrap* find_by_path(Path const& path);

		/**
		 * @brief Finds the Wrap file that contains the given Path.
		 * @param path A path that the target Wrap file contains.
		 * @return A pointer to the found Wrap file, or nullptr if no file was found.
		 */
		Wrap const* find_by_path(Path const& path) const;

		/**
		 * @brief Finds the Wrap file with the given name.
		 * @param name The name of the Wrap file.
		 * @return A pointer to the found Wrap file, or nullptr if no file was found.
		 */
		Wrap* find_by_name(String const& name);

		/**
		 * @brief Finds the Wrap file with the given name.
		 * @param name The name of the Wrap file.
		 * @return A pointer to the found Wrap file, or nullptr if no file was found.
		 */
		Wrap const* find_by_name(String const& name) const;

		/**
		 * @brief Checks if any of the Wrap files in this Wrapper contain a file with the given path.
		 * @param path The Path to the File.
		 * @return True, if the Path exists.
		 */
		Bool contains(Path const& path) const;

		/**
		 * @brief Opens the file at the given path.
		 * @param path The path to the file within the Wrapper.
		 * @param file The file object to use to open the file at the given path.
		 * @return True if the file was opened, otherwise false.
		 */
		Bool open(Path const& path, VirtualFile& file) const;

		/**
		 * @brief Read the contents of the file at the given path.
		 * @param path The virtual Path to the file.
		 * @return The contents of the file.
		 */
		Vector<Byte> read_bytes(Path const& path) const;
	};
}
