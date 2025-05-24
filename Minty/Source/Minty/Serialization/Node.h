#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/DynamicContainer.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
	/// <summary>
	/// Represents an object that contains data, and a list of children nodes.
	/// </summary>
	class Node
	{
#pragma region Variables

	private:
		Allocator m_allocator;

		// the name of this node
		String m_name;

		// the data in this node
		DynamicContainer m_data;
		
		// list of children
		Vector<Node> m_children;

		// lookup of children
		Map<String, Int> m_lookup;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Create an empty Node.
		/// </summary>
		/// <param name="allocator">The Allocator to use.</param>
		Node(Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_name(allocator)
			, m_data(allocator)
			, m_children(allocator)
			, m_lookup(allocator)
		{
		}

		/// <summary>
		/// Creates a Node with the given name and data.
		/// </summary>
		/// <param name="name">The name of this Node.</param>
		/// <param name="data">The data of this Node.</param>
		/// <param name="size">The size of the data in bytes.</param>
		/// <param name="allocator">The Allocator to use.</param>
		Node(String const& name, void const* const data, Size const size, Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_name(name)
			, m_data(allocator)
			, m_children(allocator)
			, m_lookup(allocator)
		{
			if (data && size)
			{
				m_data.set(data, size);
			}
		}

		/// <summary>
		/// Creates a Node with the given name and data.
		/// </summary>
		/// <param name="name">The name of this Node.</param>
		/// <param name="value">The string data of this Node.</param>
		/// <param name="allocator">The Allocator to use.</param>
		Node(String const& name, String const& value, Allocator const allocator = Allocator::Default)
			: Node(name, value.get_data(), value.get_size(), allocator)
		{
		}

		/// <summary>
		/// Creates a Node with the given name.
		/// </summary>
		/// <param name="name">The name of this Node.</param>
		/// <param name="allocator">The Allocator to use.</param>
		Node(String const& name, Allocator const allocator = Allocator::Default)
			: Node(name, nullptr, 0, allocator)
		{
		}

		/// <summary>
		/// Copies the given Node.
		/// </summary>
		/// <param name="other">The Node to copy.</param>
		Node(Node const& other)
			: m_allocator(other.m_allocator)
			, m_name(other.m_name)
			, m_data(other.m_data)
			, m_children(other.m_children)
			, m_lookup(other.m_lookup)
		{
		}

		/// <summary>
		/// Moves the given Node.
		/// </summary>
		/// <param name="other">The Node to move.</param>
		Node(Node&& other) noexcept
			: m_allocator(other.m_allocator)
			, m_name(std::move(other.m_name))
			, m_data(std::move(other.m_data))
			, m_children(std::move(other.m_children))
			, m_lookup(std::move(other.m_lookup))
		{
		}

		~Node()
		{
		}

#pragma endregion

#pragma region Operators

	public:
		Node& operator=(Node const& other)
		{
			if (this != &other)
			{
				m_name = other.m_name;
				m_data = other.m_data;
				m_children = other.m_children;
				m_lookup = other.m_lookup;
			}
			return *this;
		}

		Node& operator=(Node&& other) noexcept
		{
			if (this != &other)
			{
				m_name = std::move(other.m_name);
				m_data = std::move(other.m_data);
				m_children = std::move(other.m_children);
				m_lookup = std::move(other.m_lookup);
			}
			return *this;
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the name of this Node.
		/// </summary>
		/// <returns>The name of this Node.</returns>
		String const& get_name() const { return m_name; }

		/// <summary>
		/// Sets the name of this Node.
		/// </summary>
		/// <param name="name">The new name of this Node.</param>
		void set_name(String const& name) { m_name = name; }

		/// <summary>
		/// Gets the data of this Node.
		/// </summary>
		/// <returns>The data container.</returns>
		DynamicContainer const& get_data() const { return m_data; }

		/// <summary>
		/// Gets the data as a String.
		/// </summary>
		/// <returns>The Node's data, but as a String.</returns>
		String get_data_string() const;

		/// <summary>
		/// Sets the data of this Node.
		/// </summary>
		/// <param name="data">The data in bytes.</param>
		/// <param name="size">The number of bytes.</param>
		void set_data(void const* const data, Size const size)
		{
			if (data && size)
			{
				m_data.set(data, size);
			}
			else
			{
				m_data.clear();
			}
		}

		/// <summary>
		/// Sets the data of this Node.
		/// </summary>
		/// <param name="text">The String containing the data for this Node.</param>
		void set_data(String const& text)
		{
			if (!text.is_empty())
			{
				m_data.set(text.get_data(), text.get_size());
			}
			else
			{
				m_data.clear();
			}
		}

		/// <summary>
		/// Gets the number of children in this Node.
		/// </summary>
		/// <returns>The number of child Nodes.</returns>
		Size get_children_size() const { return m_children.get_size(); }

		/// <summary>
		/// Gets the Vector of children Nodes.
		/// </summary>
		/// <returns>The child Nodes.</returns>
		Vector<Node>& get_children() { return m_children; }

		/// <summary>
		/// Gets the Vector of children Nodes.
		/// </summary>
		/// <returns>The child Nodes.</returns>
		Vector<Node> const& get_children() const { return m_children; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Checks if a child Node with the given index exists.
		/// </summary>
		/// <param name="index">The index of the child Node.</param>
		/// <returns>True, if a child Node with the given index exists.</returns>
		Bool has_child(Size const index) const
		{
			return index < m_children.get_size();
		}

		/// <summary>
		/// Checks if a child Node with the given name exists.
		/// </summary>
		/// <param name="name">The name of the child Node.</param>
		/// <returns>True, if a child Node with the given name exists.</returns>
		Bool has_child(String const& name) const
		{
			return m_lookup.contains(name);
		}

		/// <summary>
		/// Gets the child Node at the given index.
		/// </summary>
		/// <param name="index">The index of the child Node.</param>
		/// <returns>The Node at the given index.</returns>
		Node const& get_child(Size const index) const
		{
			MINTY_ASSERT(index < m_children.get_size(), "The given index is out of range.");
			return m_children[index];
		}

		/// <summary>
		/// Gets the child Node with the given name.
		/// </summary>
		/// <param name="name">The name of the child Node.</param>
		/// <returns>The Node with the given name.</returns>
		Node const& get_child(String const& name) const
		{
			MINTY_ASSERT(m_lookup.contains(name), "The given name does not exist.");
			return m_children[m_lookup[name]];
		}

		/// <summary>
		/// Gets the index of the child Node with the given name.
		/// </summary>
		/// <param name="name">The name of the child.</param>
		/// <returns>The index to the child, or -1 if the child does not exist.</returns>
		Int get_child_index(String const& name) const
		{
			auto found = m_lookup.find(name);
			return found != m_lookup.end() ? found->get_second() : -1;
		}

		/// <summary>
		/// Adds a Node as a child. Will not add if the name already exists, or if the name is empty.
		/// </summary>
		/// <param name="name">The name of the Node.</param>
		/// <param name="data">The data of the Node.</param>
		/// <param name="size">The size of the data in bytes.</param>
		/// <returns>The added Node.</returns>
		Node& add_child(String const& name, void const* const data, Size const size);

		/// <summary>
		/// Adds a Node as a child. Will not add if the name already exists, or if the name is empty.
		/// </summary>
		/// <param name="name">The name of the Node.</param>
		/// <param name="value">The String data of the Node.</param>
		/// <returns>The added Node.</returns>
		Node& add_child(String const& name, String const& value)
		{
			return add_child(name, value.get_data(), value.get_size());
		}

		/// <summary>
		/// Adds a Node as a child. Will not add if the name already exists, or if the name is empty.
		/// </summary>
		/// <param name="name">The name of the Node to add.</param>
		/// <returns>The added Node.</returns>
		Node& add_child(String const& name)
		{
			return add_child(name, nullptr, 0);
		}

		/// <summary>
		/// Adds a Node as a child. Will not add if the name already exists, or if the name is empty.
		/// </summary>
		/// <param name="node">The Node to add a copy of.</param>
		/// <returns>The child Node.</returns>
		Node& add_child(Node const& node);

		/// <summary>
		/// Adds a Node as a child. Will not add if the name already exists, or if the name is empty.
		/// </summary>
		/// <param name="node">The Node to add.</param>
		/// <returns>The child Node.</returns>
		Node& add_child(Node&& node);

#pragma endregion
	};
}