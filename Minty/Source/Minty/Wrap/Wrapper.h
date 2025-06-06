#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Core/Types.h"
#include "Minty/Wrap/Wrap.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
	/// <summary>
	/// Handles a collection of Wrap files.
	/// </summary>
	class Wrapper
	{
#pragma region Variables

	private:
		// all wraps
		Vector<Wrap> m_wraps;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Wrapper.
		/// </summary>
		Wrapper() = default;

#pragma endregion

#pragma region Iterators

	public:
		/// <summary>
		/// Gets an Iterator to the beginning of the Wrap list.
		/// </summary>
		/// <returns>An Iterator pointing to the first element.</returns>
		Vector<Wrap>::Iterator begin() { return m_wraps.begin(); }

		/// <summary>
		/// Gets an Iterator to the end of the Wrap list.
		/// </summary>
		/// <returns>An Iterator pointing to the last element + 1.</returns>
		Vector<Wrap>::Iterator end() { return m_wraps.end(); }

		/// <summary>
		/// Gets a ConstIterator to the beginning of the Wrap list.
		/// </summary>
		/// <returns>A ConstIterator pointing to the first element.</returns>
		Vector<Wrap>::ConstIterator begin() const { return m_wraps.begin(); }

		/// <summary>
		/// Gets a ConstIterator to the end of the Wrap list.
		/// </summary>
		/// <returns>A ConstIterator pointing to the last element + 1.</returns>
		Vector<Wrap>::ConstIterator end() const { return m_wraps.end(); }

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the number of Wraps within this Wrapper.
		/// </summary>
		Size get_wrap_count() const;

#pragma endregion

	public:
		/// <summary>
		/// Adds the given Wrap to this Wrapper.
		/// </summary>
		/// <param name="wrap">The Wrap at add.</param>
		void add(Wrap const& wrap);

		/// <summary>
		/// Adds the Wrap file at the given path to this Wrapper.
		/// </summary>
		/// <param name="path">The Path of the Wrap file.</param>
		void add(Path const& path);

		/// <summary>
		/// Gets the Wrap at the given index.
		/// </summary>
		/// <returns>The Wrap at the given index.</returns>
		Wrap& get_wrap(Size const index);

		/// <summary>
		/// Gets the Wrap at the given index.
		/// </summary>
		/// <returns>The Wrap at the given index.</returns>
		Wrap const& get_wrap(Size const index) const;

		/// <summary>
		/// Finds the Wrap file that contains the given Path.
		/// </summary>
		/// <param name="path">A path that the target Wrap file contains.</param>
		/// <returns>A pointer to the found Wrap file, or nullptr if no file was found.</returns>
		Wrap* find_by_path(Path const& path);

		/// <summary>
		/// Finds the Wrap file that contains the given Path.
		/// </summary>
		/// <param name="path">A path that the target Wrap file contains.</param>
		/// <returns>A pointer to the found Wrap file, or nullptr if no file was found.</returns>
		Wrap const* find_by_path(Path const& path) const;

		/// <summary>
		/// Finds the Wrap file with the given name.
		/// </summary>
		/// <param name="name">The name of the Wrap file.</param>
		/// <returns>A pointer to the found Wrap file, or nullptr if no file was found.</returns>
		Wrap* find_by_name(String const& name);

		/// <summary>
		/// Finds the Wrap file with the given name.
		/// </summary>
		/// <param name="name">The name of the Wrap file.</param>
		/// <returns>A pointer to the found Wrap file, or nullptr if no file was found.</returns>
		Wrap const* find_by_name(String const& name) const;

		/// <summary>
		/// Checks if any of the Wrap files in this Wrapper contain a file with the given path.
		/// </summary>
		/// <param name="path">The Path to the File.</param>
		/// <returns>True, if the Path exists.</returns>
		Bool contains(Path const& path) const;

		/// <summary>
		/// Opens the file at the given path.
		/// </summary>
		/// <param name="path">The path to the file within the Wrapper.</param>
		/// <param name="file">The file object to use to open the file at the given path.</param>
		/// <returns>True if the file was opened, otherwise false.</returns>
		Bool open(Path const& path, VirtualFile& file) const;

		/// <summary>
		/// Read the contents of the file at the given path.
		/// </summary>
		/// <param name="path">The virtual Path to the file.</param>
		/// <returns>The contents of the file.</returns>
		Vector<Byte> read_bytes(Path const& path) const;
	};
}