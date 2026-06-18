#ifndef MINTY_DATA_DICTIONARY_H
#define MINTY_DATA_DICTIONARY_H

/**
 * @file Dictionary.h
 * @brief Header file for the Dictionary class.
 * @author Mitchell Talyat
 */

#include "Minty/Debug/Debug.h"
#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/Vector.h"
#include "Minty/Memory/DefaultAllocator.h"

namespace Minty
{
	/**
	 * @class Dictionary
	 * @brief A key-value pair collection implemented as a balanced binary search tree (AVL Tree).
	 * @tparam Key The type of keys in the dictionary.
	 * @tparam Value The type of values in the dictionary.
	 * @tparam Compare The comparison functor for ordering keys.
	 * @tparam Allocator The allocator type to use for memory management.
	 */
	template<typename Key, typename Value, typename Compare = std::less<Key>, typename Allocator = DefaultAllocator>
	class Dictionary
	{
#pragma region Types

	private:
		struct Node
		{
			Tuple<Key, Value> data;
			Node* left;
			Node* right;
			Int height;
			Node(Key const& key, Value const& value)
				: data(key, value)
				, left(nullptr)
				, right(nullptr)
				, height(1)
			{
			}
			Node(Key const& key, Value&& value)
				: data(key, std::move(value))
				, left(nullptr)
				, right(nullptr)
				, height(1)
			{
			}
		};

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Dictionary.
		 */
		Dictionary()
			: mp_root(nullptr)
			, m_size(0)
			, m_compare()
			, m_allocator()
		{
		}

		~Dictionary()
		{
			clear(mp_root);
		}

#pragma endregion

#pragma region Iterators

	public:
		class Iterator
		{
		private:
			Node* m_current;
			Vector<Node*> m_stack;

		public:
			using value_type = Tuple<Key, Value>;
			using pointer = value_type*;
			using reference = value_type&;

			Iterator()
				: m_current(nullptr)
				, m_stack()
			{
			}

			Iterator(Node* root)
				: m_current(root)
				, m_stack()
			{
				push_left(root);
				advance();
			}

			Iterator(Node* const root, Vector<Node*>&& stack)
				: m_current(root)
				, m_stack(std::move(stack))
			{
			}

			reference operator*() const { return m_current->data; }
			pointer operator->() const { return &(m_current->data); }

			Iterator& operator++() {
				advance();
				return *this;
			}

			Iterator operator++(int) {
				Iterator tmp = *this;
				advance();
				return tmp;
			}

			bool operator==(const Iterator& other) const
			{
				if (m_current != other.m_current || m_stack.get_size() != other.m_stack.get_size())
				{
					return false;
				}

				for (Size i = 0; i < m_stack.get_size(); ++i)
				{
					if (m_stack.at(i) != other.m_stack.at(i))
					{
						return false;
					}
				}

				return true;
			}
			bool operator!=(const Iterator& other) const { return !(*this == other); }

		private:
			void push_left(Node* node) {
				while (node) {
					m_stack.add(node);
					node = node->left;
				}
			}

			void advance() {
				if (m_stack.is_empty()) {
					m_current = nullptr;
					return;
				}
				m_current = m_stack.back();
				m_stack.remove(m_stack.get_size() - 1);
				if (m_current->right) {
					push_left(m_current->right);
				}
			}
		};

		class ConstIterator
		{
		private:
			Node const* m_current;
			Vector<Node const*> m_stack;

		public:
			using value_type = Tuple<Key, Value> const;
			using pointer = value_type*;
			using reference = value_type&;

			ConstIterator()
				: m_current(nullptr)
				, m_stack()
			{
			}

			ConstIterator(Node const* root)
				: m_current(root)
				, m_stack()
			{
				push_left(root);
				advance();
			}

			ConstIterator(Node const* const root, Vector<Node const*>&& stack)
				: m_current(root)
				, m_stack(std::move(stack))
			{
			}

			reference operator*() const { return m_current->data; }
			pointer operator->() const { return &(m_current->data); }

			ConstIterator& operator++() {
				advance();
				return *this;
			}

			ConstIterator operator++(int) {
				ConstIterator tmp = *this;
				advance();
				return tmp;
			}

			bool operator==(const ConstIterator& other) const
			{
				if (m_current != other.m_current || m_stack.get_size() != other.m_stack.get_size())
				{
					return false;
				}

				for (Size i = 0; i < m_stack.get_size(); ++i)
				{
					if (m_stack.at(i) != other.m_stack.at(i))
					{
						return false;
					}
				}

				return true;
			}
			bool operator!=(const ConstIterator& other) const { return !(*this == other); }

		private:
			void push_left(Node const* node) {
				while (node) {
					m_stack.add(node);
					node = node->left;
				}
			}

			void advance() {
				if (m_stack.is_empty()) {
					m_current = nullptr;
					return;
				}
				m_current = m_stack.back();
				m_stack.remove(m_stack.get_size() - 1);
				if (m_current->right) {
					push_left(m_current->right);
				}
			}
		};

		Iterator begin() { return Iterator(mp_root); }
		Iterator end() { return Iterator(); }
		ConstIterator begin() const { return ConstIterator(mp_root); }
		ConstIterator end() const { return ConstIterator(); }

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Checks if the Dictionary contains the given key.
		 * @param key The key to check for.
		 */
		inline Size get_size() const { return m_size; }

		/**
		 * @brief Checks if the Dictionary is empty.
		 * @returns True if the Dictionary contains no elements.
		 */
		inline Bool is_empty() const { return m_size == 0; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Inserts a Key-Value pair into the Dictionary.
		 * @param key The Key.
		 * @param value The Value.
		 * @returns True when a new pair was inserted, or false if the key already exists and its value was replaced.
		 */
		Bool insert(Key const& key, Value const& value)
		{
			Bool inserted = false;
			mp_root = insert(mp_root, key, value, inserted);
			return inserted;
		}

		/**
		 * @brief Inserts a Key-Value pair into the Dictionary.
		 * @param key The Key.
		 * @param value The Value.
		 * @returns True when a new pair was inserted, or false if the key already exists.
		 */
		Bool add(Key const& key, Value const& value)
		{
			if (contains(key))
			{
				return false;
			}

			insert(key, value);
			return true;
		}

		/**
		 * @brief Gets the Value for the given Key.
		 * @param key The key.
		 * @returns The value.
		 */
		Value const& at(Key const& key) const
		{
			Node const* node = mp_root;
			while (node)
			{
				if (m_compare(key, node->data.get_first()))
				{
					node = node->left;
				}
				else if (m_compare(node->data.get_first(), key))
				{
					node = node->right;
				}
				else
				{
					return node->data.get_second();
				}
			}

			// not found
			MINTY_ABORT(ErrorCode::Argument_KeyNotFound);
		}

		/**
		 * @brief Gets the Value for the given Key.
		 * @param key The key.
		 * @returns The value.
		 */
		Value& at(Key const& key)
		{
			Node* node = mp_root;
			while (node)
			{
				if (m_compare(key, node->data.get_first()))
				{
					node = node->left;
				}
				else if (m_compare(node->data.get_first(), key))
				{
					node = node->right;
				}
				else
				{
					return node->data.get_second();
				}
			}

			// not found
			MINTY_ABORT(ErrorCode::Argument_KeyNotFound);
		}

		/**
		 * @brief Finds the ConstIterator for the given Key.
		 * @param key The Key to find.
		 * @returns A ConstIterator to the found element, or end() if not found.
		 */
		ConstIterator find(Key const& key) const
		{
			Node const* node = mp_root;
			Vector<Node const*> stack;

			while (node)
			{
				if (m_compare(key, node->data.get_first()))
				{
					stack.add(node);
					node = node->left;
				}
				else if (m_compare(node->data.get_first(), key))
				{
					node = node->right;
				}
				else
				{
					// Found the node, stack is set for in-order traversal
					return ConstIterator(node, std::move(stack));
				}
			}

			// not found
			return end();
		}

		/**
		 * @brief Finds the Iterator for the given Key.
		 * @param key The Key to find.
		 * @returns An Iterator to the found element, or end() if not found.
		 */
		Iterator find(Key const& key)
		{
			Node* node = mp_root;
			Vector<Node*> stack;

			while (node)
			{
				if (m_compare(key, node->data.get_first()))
				{
					stack.add(node);
					node = node->left;
				}
				else if (m_compare(node->data.get_first(), key))
				{
					node = node->right;
				}
				else
				{
					// Found the node, stack is set for in-order traversal
					return Iterator(node, std::move(stack));
				}
			}

			// not found
			return end();
		}

		/**
		 * @brief Removes the Key-Value pair with the given Key.
		 * @param key The Key to remove.
		 * @returns True if the Key was found and removed, false otherwise.
		 */
		Bool remove(Key const& key)
		{
			Bool erased = false;
			mp_root = erase(mp_root, key, erased);
			if (erased)
			{
				m_size--;
			}
			return erased;
		}

		/**
		 * @brief Checks if the Dictionary contains the given key.
		 * @param key The key to check for.
		 * @returns True if the key exists in the Dictionary, false otherwise.
		 */
		Bool contains(Key const& key) const
		{
			Node* node = mp_root;
			while (node)
			{
				if (m_compare(key, node->data.get_first()))
				{
					node = node->left;
				}
				else if (m_compare(node->data.get_first(), key))
				{
					node = node->right;
				}
				else
				{
					return true;
				}
			}

			// not found
			return false;
		}

		/**
		 * @brief Clears all Key-Value pairs from the Dictionary.
		 */
		void clear()
		{
			clear(mp_root);
			mp_root = nullptr;
			m_size = 0;
		}
		
	private:
		inline Int get_height(Node const* const n) const { return n ? n->height : 0; }
		
		Int get_balance(Node const* const n) const { return n ? get_height(n->left) - get_height(n->right) : 0; }
		
		void update_height(Node* const n)
		{
			n->height = 1 + Math::max(get_height(n->left), get_height(n->right));
		}

		Node* rotate_right(Node* const y)
		{
			// swap the nodes
			auto x = std::move(y->left);
			y->left = std::move(x->right);
			x->right = std::move(y);

			// update heights
			update_height(x->right);
			update_height(x);

			return x;
		}

		Node* rotate_left(Node* const x)
		{
			// swap the nodes
			auto y = std::move(x->right);
			x->right = std::move(y->left);
			y->left = std::move(x);

			// update heights
			update_height(y->left);
			update_height(y);
			
			return y;
		}

		Node* balance(Node* const n)
		{
			update_height(n);
			Int b = get_balance(n);

			if (b > 1)
			{
				if (get_balance(n->left) < 0)
					n->left = rotate_left(std::move(n->left));
				return rotate_right(std::move(n));
			}
			if (b < -1)
			{
				if (get_balance(n->right) > 0)
					n->right = rotate_right(std::move(n->right));
				return rotate_left(std::move(n));
			}

			return n;
		}

		Node* insert(Node* const n, Key const& key, Value const& value, Bool& inserted)
		{
			if (!n)
			{
				inserted = true;
				m_size++;
				return m_allocator.construct<Node>(key, value);
			}

			if (m_compare(key, n->data.get_first()))
			{
				n->left = insert(n->left, key, value, inserted);
			}
			else if (m_compare(n->data.get_first(), key))
			{
				n->right = insert(n->right, key, value, inserted);
			}
			else
			{
				n->data.get_second() = value; // Update existing value
				return n;
			}
			return balance(n);
		}

		Node* min(Node* n) const
		{
			while (n && n->left) n = n->left;
			return n;
		}

		Node* erase(Node* n, const Key& key, bool& erased) {
			if (!n) return nullptr;
			if (m_compare(key, n->data.get_first()))
				n->left = erase(n->left, key, erased);
			else if (m_compare(n->data.get_first(), key))
				n->right = erase(n->right, key, erased);
			else {
				erased = true;
				if (!n->left) {
					Node* const right = n->right;
					MINTY_ASSERT(right != n, ErrorCode::Object_InvalidState);
					MINTY_ASSERT(right->left == nullptr, ErrorCode::Object_InvalidState);
					MINTY_ASSERT(right->right == nullptr, ErrorCode::Object_InvalidState);
					m_allocator.destruct(n);
					return right;
				}
				if (!n->right) {
					Node* const left = n->left;
					MINTY_ASSERT(left != n, ErrorCode::Object_InvalidState);
					MINTY_ASSERT(left->left == nullptr, ErrorCode::Object_InvalidState);
					MINTY_ASSERT(left->right == nullptr, ErrorCode::Object_InvalidState);
					m_allocator.destruct(n);
					return left;
				}
				Node* m = min(n->right);
				n->data = m->data;
				bool dummy = false;
				n->right = erase(n->right, m->data.get_first(), dummy);
			}
			return balance(n);
		}

		void clear(Node* const n) {
			if (!n) return;
			clear(n->left);
			clear(n->right);
			m_allocator.destruct(n);
		}

#pragma endregion

#pragma region Variables

	private:
		Node* mp_root;
		Size m_size;
		Compare m_compare;
		Allocator m_allocator;

#pragma endregion
	};
}

#endif // MINTY_DATA_DICTIONARY_H