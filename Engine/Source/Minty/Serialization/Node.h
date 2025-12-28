#ifndef MINTY_SERIALIZATION_NODE_H
#define MINTY_SERIALIZATION_NODE_H

/**
 * @file Node.h
 * @brief Header file defining the Node class for serialization.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/DynamicContainer.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Vector.h"
#include "Minty/Serialization/Parser.h"
#include "Minty/Serialization/Serializer.h"

namespace Minty
{
	/**
	 * @brief Represents an object that contains data, and a list of children nodes.
	 */
	class Node
	{
#pragma region Constructors

	public:
		/**
		 * @brief Create an empty Node.
		 */
		Node()
			: m_name()
			, m_data()
			, m_children()
			, m_lookup()
		{
		}

		/**
		 * @brief Creates a Node with the given name and data.
		 * @param name The name of this Node.
		 * @param data The data of this Node.
		 * @param size The size of the data in bytes.
		 */
		Node(String const& name, AnyConst const data, Size const size)
			: m_name(name)
			, m_data()
			, m_children()
			, m_lookup()
		{
			if (data && size)
			{
				m_data.set(data, size);
			}
		}

		/**
		 * @brief Creates a Node with the given name and data.
		 * @param name The name of this Node.
		 * @param value The string data of this Node.
		 */
		Node(String const& name, String const& value)
			: Node(name, value.get_data(), value.get_size())
		{
		}

		/**
		 * @brief Creates a Node with the given name.
		 * @param name The name of this Node.
		 */
		Node(String const& name)
			: Node(name, nullptr, 0)
		{
		}

		/**
		 * @brief Copies the given Node.
		 * @param other The Node to copy.
		 */
		Node(Node const& other)
			: m_name(other.m_name)
			, m_data(other.m_data)
			, m_children(other.m_children)
			, m_lookup(other.m_lookup)
		{
		}

		/**
		 * @brief Moves the given Node.
		 * @param other The Node to move.
		 */
		Node(Node&& other) noexcept
			: m_name(std::move(other.m_name))
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

#pragma region Accessors

	public:
		/**
		 * @brief Gets the name of this Node.
		 * @return The name of this Node.
		 */
		inline String const& get_name() const { return m_name; }

		/**
		 * @brief Sets the name of this Node.
		 * @param name The new name of this Node.
		 */
		inline void set_name(String const& name) { m_name = name; }

		/**
		 * @brief Gets the data of this Node.
		 * @return The data container.
		 */
		inline DynamicContainer const& get_data() const { return m_data; }

		/**
		 * @brief Gets the data as a String.
		 * @return The Node's data, but as a String.
		 */
		String get_data_string() const;

		/**
		 * @brief Sets the data of this Node.
		 * @param data The data in bytes.
		 * @param size The number of bytes.
		 */
		inline void set_data(AnyConst const data, Size const size)
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

		/**
		 * @brief Sets the data of this Node.
		 * @param text The String containing the data for this Node.
		 */
		inline void set_data(String const& text)
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

		/**
		 * @brief Gets the number of children in this Node.
		 * @return The number of child Nodes.
		 */
		inline Size get_children_size() const { return m_children.get_size(); }

		/**
		 * @brief Gets the Vector of children Nodes.
		 * @return The child Nodes.
		 */
		inline Vector<Node>& get_children() { return m_children; }

		/**
		 * @brief Gets the Vector of children Nodes.
		 * @return The child Nodes.
		 */
		inline Vector<Node> const& get_children() const { return m_children; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Checks if a child Node with the given index exists.
		 * @param index The index of the child Node.
		 * @return True, if a child Node with the given index exists.
		 */
		inline Bool has_child(Size const index) const
		{
			return index < m_children.get_size();
		}

		/**
		 * @brief Checks if a child Node with the given name exists.
		 * @param name The name of the child Node.
		 * @return True, if a child Node with the given name exists.
		 */
		inline Bool has_child(String const& name) const
		{
			return m_lookup.contains(name);
		}

		/**
		 * @brief Gets the child Node at the given index.
		 * @param index The index of the child Node.
		 * @return The Node at the given index.
		 */
		Node const& get_child(Size const index) const;

		/**
		 * @brief Gets the child Node with the given name.
		 * @param name The name of the child Node.
		 * @return The Node with the given name.
		 */
		Node const& get_child(String const& name) const;

		/**
		 * @brief Gets the index of the child Node with the given name.
		 * @param name The name of the child.
		 * @return The index to the child, or -1 if the child does not exist.
		 */
		inline Int get_child_index(String const& name) const
		{
			auto found = m_lookup.find(name);
			return found != m_lookup.end() ? found->get_second() : -1;
		}

		/**
		 * @brief Adds a Node as a child. Will not add if the name already exists, or if the name is empty.
		 * @param name The name of the Node.
		 * @param data The data of the Node.
		 * @param size The size of the data in bytes.
		 * @return The added Node.
		 */
		Node& add_child(String const& name, AnyConst const data, Size const size);

		/**
		 * @brief Adds a Node as a child. Will not add if the name already exists, or if the name is empty.
		 * @param name The name of the Node.
		 * @param value The String data of the Node.
		 * @return The added Node.
		 */
		inline Node& add_child(String const& name, String const& value)
		{
			return add_child(name, value.get_data(), value.get_size());
		}

		/**
		 * @brief Adds a Node as a child. Will not add if the name already exists, or if the name is empty.
		 * @param name The name of the Node to add.
		 * @return The added Node.
		 */
		inline Node& add_child(String const& name)
		{
			return add_child(name, nullptr, 0);
		}

		/**
		 * @brief Adds a Node as a child. Will not add if the name already exists, or if the name is empty.
		 * @param node The Node to add a copy of.
		 * @return The child Node.
		 */
		Node& add_child(Node const& node);

		/**
		 * @brief Adds a Node as a child. Will not add if the name already exists, or if the name is empty.
		 * @param node The Node to add.
		 * @return The child Node.
		 */
		Node& add_child(Node&& node);

		/**
		 * @brief Merge the contents or state of another Node into this Node.
		 * @param other The node to merge into this one.
		 * @return True on success.
		 */
		Bool merge(Node const& other);

#pragma endregion

#pragma region Variables

	private:
		String m_name;
		DynamicContainer m_data;
		Vector<Node> m_children;
		Map<String, Int> m_lookup;

#pragma endregion
	};
	
	template<>
	struct Parser<Node>
	{
		static Bool parse(StringView const str, Node& value);
		static String to_string(Node const& obj);
	};

    template<>
    struct Serializer<Node>
    {
        static void serialize(Writer& writer, Node const& value);
        static void deserialize(Reader& reader, Node& value);
    };
}

#endif // MINTY_SERIALIZATION_NODE_H