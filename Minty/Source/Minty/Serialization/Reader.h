#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Core/Format.h"
#include "Minty/Core/Math.h"
#include "Minty/Core/Type.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Array.h"
#include "Minty/Data/List.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Set.h"
#include "Minty/Data/Stack.h"
#include "Minty/Data/String.h"
#include "Minty/Data/UUID.h"
#include "Minty/Data/Vector.h"
#include "Minty/Debug/Debug.h"
#include "Minty/File/File.h"
#include "Minty/Serialization/IsSerializable.h"
#include "Minty/Serialization/Node.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
#pragma region Base

	/// <summary>
	/// Handles reading data from a source, formatted in a Minty Node structure.
	/// </summary>
	class Reader
	{
#pragma region Variables

	protected:
		Allocator m_allocator;

	private:
		List<void*> m_dataStack;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Reader.
		/// </summary>
		/// <param name="allocator">The Allocator to use.</param>
		Reader(Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_dataStack(allocator)
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the top of the data stack.
		/// </summary>
		/// <returns>A pointer to the data, or null if nothing in the data stack.</returns>
		void* get_user_data() const;

		/// <summary>
		/// Gets the data source for this Reader.
		/// </summary>
		/// <returns>A pointer to the data source.</returns>
		virtual void* get_source() const = 0;

		/// <summary>
		/// Gets the depth in the Node structure.
		/// </summary>
		/// <returns>The number of indents made from the root Node.</returns>
		virtual Size get_depth() const = 0;

		/// <summary>
		/// Gets the current Node this Reader is on.
		/// </summary>
		/// <returns>The active Node.</returns>
		virtual Node const& get_node() const = 0;

		/// <summary>
		/// Gets the number of child Nodes in the current Node.
		/// </summary>
		/// <returns>The number of children.</returns>
		Size get_size() const { return get_node().get_children_size(); }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Adds data to the top of the data stack.
		/// </summary>
		/// <param name="data">The pointer to the data to add.</param>
		void push_user_data(void* const data);

		/// <summary>
		/// Removes the top of the data stack.
		/// </summary>
		void pop_user_data();

		/// <summary>
		/// Steps into the child Node at the given index.
		/// </summary>
		/// <param name="index">The index of the child to indent into.</param>
		/// <returns>True on success.</returns>
		virtual Bool indent(Size const index) = 0;

		/// <summary>
		/// Steps into the child Node with the given name.
		/// </summary>
		/// <param name="name">The name of the child to indent into.</param>
		/// <returns>True on success.</returns>
		virtual Bool indent(String const& name) = 0;

		/// <summary>
		/// Steps out of the current Node, back to its parent.
		/// </summary>
		virtual void outdent() = 0;

		/// <summary>
		/// Checks if this Reader is valid.
		/// </summary>
		/// <returns>True when valid.</returns>
		virtual Bool is_valid() const = 0;

#pragma region Reading

	protected:
		inline Int get_index(String const& name) const
		{
			return get_node().get_child_index(name);
		}

		virtual Bool read_bool(Size const index, Bool& obj) const = 0;
		virtual Bool read_bool2(Size const index, Bool2& obj) const = 0;
		virtual Bool read_bool3(Size const index, Bool3& obj) const = 0;
		virtual Bool read_bool4(Size const index, Bool4& obj) const = 0;
		virtual Bool read_char(Size const index, Char& obj) const = 0;
		virtual Bool read_byte(Size const index, Byte& obj) const = 0;
		virtual Bool read_short(Size const index, Short& obj) const = 0;
		virtual Bool read_ushort(Size const index, UShort& obj) const = 0;
		virtual Bool read_int(Size const index, Int& obj) const = 0;
		virtual Bool read_int2(Size const index, Int2& obj) const = 0;
		virtual Bool read_int3(Size const index, Int3& obj) const = 0;
		virtual Bool read_int4(Size const index, Int4& obj) const = 0;
		virtual Bool read_uint(Size const index, UInt& obj) const = 0;
		virtual Bool read_uint2(Size const index, UInt2& obj) const = 0;
		virtual Bool read_uint3(Size const index, UInt3& obj) const = 0;
		virtual Bool read_uint4(Size const index, UInt4& obj) const = 0;
		virtual Bool read_long(Size const index, Long& obj) const = 0;
		virtual Bool read_ulong(Size const index, ULong& obj) const = 0;
		virtual Bool read_float(Size const index, Float& obj) const = 0;
		virtual Bool read_float2(Size const index, Float2& obj) const = 0;
		virtual Bool read_float3(Size const index, Float3& obj) const = 0;
		virtual Bool read_float4(Size const index, Float4& obj) const = 0;
		virtual Bool read_double(Size const index, Double& obj) const = 0;
		virtual Bool read_string(Size const index, String& obj) const = 0;
		virtual Bool read_type(Size const index, Type& obj) const = 0;

	private:
		Bool read_object(Size const index, SerializableObject& obj);

	public:
		/// <summary>
		/// Reads the name of the Node at the given index.
		/// </summary>
		/// <param name="index">The index of the child Node.</param>
		/// <param name="obj">The object to read the data into.</param>
		/// <returns>True on success.</returns>
		virtual Bool read_name(Size const index, String& obj) const = 0;

		/// <summary>
		/// Read the data from the Node at the given index.
		/// </summary>
		/// <typeparam name="T">The type of data to read.</typeparam>
		/// <typeparam name="type">A non-Serializable type.</typeparam>
		/// <param name="index">The index of the Node to read from.</param>
		/// <param name="obj">The object to read the data into.</param>
		/// <returns>True on success.</returns>
		template<typename T, typename std::enable_if<!is_asset<T>::value && !is_serializable<T>::value && !is_serializable_object<T>::value, int>::type = 0>
		Bool read(Size const index, T& obj)
		{
			// default: read as string
			String stringData;
			if (read_string(index, stringData))
			{
				obj = parse_to<T>(stringData);
				return true;
			}
			return false;
		}

		/// <summary>
		/// Read the data from the Node at the given index.
		/// </summary>
		/// <typeparam name="T">The type of data to read.</typeparam>
		/// <typeparam name="type">A Serializable type.</typeparam>
		/// <param name="index">The index of the Node to read from.</param>
		/// <param name="obj">The object to read the data into.</param>
		/// <returns>True on success.</returns>
		template<typename T, typename std::enable_if<!is_asset<T>::value && !is_serializable<T>::value && is_serializable_object<T>::value, int>::type = 0>
		Bool read(Size const index, T& obj)
		{
			return read_object(index, obj);
		}

		/// <summary>
		/// Reads the data from the Node at the given index.
		/// </summary>
		/// <typeparam name="T">The type of data to read.</typeparam>
		/// <typeparam name="type">A Serializable type.</typeparam>
		/// <param name="index">The index of the Node to read from.</param>
		/// <param name="obj">The object to read the data into.</param>
		/// <returns>True on success.</returns>
		template<typename T, typename std::enable_if<!is_asset<T>::value && is_serializable<T>::value, int>::type = 0>
		Bool read(Size const index, T& obj)
		{
			return obj.deserialize(*this, index);
		}

		/// <summary>
		/// Read the data from the Node at the given name.
		/// </summary>
		/// <typeparam name="T">The type of data to read.</typeparam>
		/// <param name="name">The name of the Node to read from.</param>
		/// <param name="obj">The object to read the data into.</param>
		/// <returns>True on success.</returns>
		template<typename T>
		Bool read(String const& name, T& obj)
		{
			return read(get_index(name), obj);
		}

		/// <summary>
		/// Reads the data from the Node at the given index.
		/// </summary>
		/// <typeparam name="T">The type of the data.</typeparam>
		/// <param name="index">The index to the data.</param>
		/// <param name="obj">The object to set.</param>
		/// <param name="defaultValue">The default value to set obj to, if no value found.</param>
		/// <returns>True if set using the found value, otherwise false if the default was used.</returns>
		template<typename T>
		Bool read(Size const index, T& obj, T const& defaultValue)
		{
			if (read(index, obj))
			{
				return true;
			}
			obj = defaultValue;
			return false;
		}

		/// <summary>
		/// Reads the data from the Node with the given name.
		/// </summary>
		/// <typeparam name="T">The type of the data.</typeparam>
		/// <param name="name">The name of the data.</param>
		/// <param name="obj">The object to set.</param>
		/// <param name="defaultValue">The default value to set obj to, if no value found.</param>
		/// <returns>True if set using the found value, otherwise false if the default was used.</returns>
		template<typename T>
		Bool read(String const& name, T& obj, T const& defaultValue)
		{
			return read(get_index(name), obj, defaultValue);
		}

		template<>
		Bool read(Size const index, Bool& data)
		{
			return read_bool(index, data);
		}
		template<>
		Bool read(Size const index, Bool2& data)
		{
			return read_bool2(index, data);
		}
		template<>
		Bool read(Size const index, Bool3& data)
		{
			return read_bool3(index, data);
		}
		template<>
		Bool read(Size const index, Bool4& data)
		{
			return read_bool4(index, data);
		}
		template<>
		Bool read(Size const index, Char& data)
		{
			return read_char(index, data);
		}
		template<>
		Bool read(Size const index, Byte& data)
		{
			return read_byte(index, data);
		}
		template<>
		Bool read(Size const index, Short& data)
		{
			return read_short(index, data);
		}
		template<>
		Bool read(Size const index, UShort& data)
		{
			return read_ushort(index, data);
		}
		template<>
		Bool read(Size const index, Int& data)
		{
			return read_int(index, data);
		}
		template<>
		Bool read(Size const index, Int2& data)
		{
			return read_int2(index, data);
		}
		template<>
		Bool read(Size const index, Int3& data)
		{
			return read_int3(index, data);
		}
		template<>
		Bool read(Size const index, Int4& data)
		{
			return read_int4(index, data);
		}
		template<>
		Bool read(Size const index, UInt& data)
		{
			return read_uint(index, data);
		}
		template<>
		Bool read(Size const index, UInt2& data)
		{
			return read_uint2(index, data);
		}
		template<>
		Bool read(Size const index, UInt3& data)
		{
			return read_uint3(index, data);
		}
		template<>
		Bool read(Size const index, UInt4& data)
		{
			return read_uint4(index, data);
		}
		template<>
		Bool read(Size const index, Long& data)
		{
			return read_long(index, data);
		}
		template<>
		Bool read(Size const index, ULong& data)
		{
			return read_ulong(index, data);
		}
		template<>
		Bool read(Size const index, Float& data)
		{
			return read_float(index, data);
		}
		template<>
		Bool read(Size const index, Float2& data)
		{
			return read_float2(index, data);
		}
		template<>
		Bool read(Size const index, Float3& data)
		{
			return read_float3(index, data);
		}
		template<>
		Bool read(Size const index, Float4& data)
		{
			return read_float4(index, data);
		}
		template<>
		Bool read(Size const index, Double& data)
		{
			return read_double(index, data);
		}
		template<>
		Bool read(Size const index, String& data)
		{
			return read_string(index, data);
		}
		template<>
		Bool read(Size const index, Type& data)
		{
			return read_type(index, data);
		}

		template<typename T, Size S>
		Bool read(Size const index, Array<T, S>& data)
		{
			if (indent(index))
			{
				// read each elements
				for (Size i = 0; i < S; i++)
				{
					if (!read<T>(i, data[i]))
					{
						// could not read element
						return false;
					}
				}
				outdent();
				return true;
			}
			return false;
		}

		template<typename T>
		Bool read(Size const index, List<T>& data)
		{
			if (indent(index))
			{
				// resize the list
				Size size = get_size();
				data.clear();

				// read each element
				T obj;
				for (Size i = 0; i < size; i++)
				{
					if (!read<T>(i, obj))
					{
						MINTY_ERROR(F("Reader failed to read element {}.", i));
						continue;
					}
					data.add(obj);
				}

				outdent();
				return true;
			}
			return false;
		}

		template<typename T>
		Bool read(Size const index, Vector<T>& data)
		{
			if (indent(index))
			{
				// resize the vector
				Size size = get_size();
				data.clear();
				data.reserve(size);

				// read each element
				T obj;
				for (Size i = 0; i < size; i++)
				{
					if (!read<T>(i, obj))
					{
						MINTY_ERROR(F("Reader failed to read element {}.", i));
						continue;
					}
					data.add(obj);
				}

				outdent();

				return true;
			}

			return false;
		}

		template<typename T>
		Bool read(Size const index, Set<T>& data)
		{
			if (indent(index))
			{
				// resize the set
				Size size = get_size();
				data.reserve(size);

				// read each element
				T obj;
				for (Size i = 0; i < size; i++)
				{
					if (!read<T>(i, obj))
					{
						MINTY_ERROR(F("Reader failed to read element {}.", i));
						continue;
					}
					data.add(obj);
				}

				outdent();
				return true;
			}
			return false;
		}

		template<typename T>
		Bool read(Size const index, Map<String, T>& data)
		{
			if (indent(index))
			{
				// resize the map
				Size size = get_size();
				data.reserve(size);

				// read each element
				String key;
				T value;
				for (Size i = 0; i < size; i++)
				{
					if (!read_name(i, key))
					{
						MINTY_ERROR(F("Reader failed to read key {}.", i));
						continue;
					}
					if (!read(i, value))
					{
						MINTY_ERROR(F("Reader failed to read value {}.", i));
						continue;
					}
					data.add(key, value);
				}

				outdent();
				return true;
			}
			return false;
		}

		/// <summary>
		/// Reads the data with the given Type.
		/// </summary>
		/// <param name="index">The index of the value.</param>
		/// <param name="data">The value. Expects data to point to a buffer equal to or greater in size than the Type size.</param>
		/// <param name="type">The Type.</param>
		/// <returns>True on success.</returns>
		virtual Bool read_typed(Size const index, void* const data, Type& type) = 0;

		/// <summary>
		/// Reads the data with the given Type.
		/// </summary>
		/// <param name="name">The name of the value.</param>
		/// <param name="data">The value. Expects data to point to a buffer equal to or greater in size than the Type size.</param>
		/// <param name="type">The Type.</param>
		/// <returns>True on success.</returns>
		Bool read_typed(String const& name, void* const data, Type& type)
		{
			return read_typed(get_index(name), data, type);
		}

		/// <summary>
		/// Reads the ID of the Asset and populates the given Asset if found.
		/// </summary>
		/// <param name="index">The index of the Node to read.</param>
		/// <param name="asset">The Asset.</param>
		/// <returns>True on success.</returns>
		Bool read_asset(Size const index, Ref<Asset>& asset);

		/// <summary>
		/// Reads the ID of the Asset and populates the given Asset if found.
		/// </summary>
		/// <param name="name">The name of the Node to read.</param>
		/// <param name="asset">The Asset.</param>
		/// <returns>True on success.</returns>
		Bool read_asset(String const& name, Ref<Asset>& asset)
		{
			return read_asset(get_index(name), asset);
		}

		/// <summary>
		/// Reads the ID of the Asset and populates the given Asset if found.
		/// </summary>
		/// <typeparam name="T">The type of Asset.</typeparam>
		/// <typeparam name="type">The type.</typeparam>
		/// <param name="index">The index of the Asset.</param>
		/// <param name="asset">The Asset.</param>
		/// <returns>True on success.</returns>
		template<typename T, typename std::enable_if<is_asset<T>::value, int>::type = 0>
		Bool read(Size const index, Ref<T>& asset)
		{
			Ref<Asset> assetRef = asset.cast_to<Asset>();
			Bool result = read_asset(index, assetRef);
			asset = assetRef.cast_to<T>();
			return result;
		}

#pragma endregion

#pragma endregion
	};

#pragma endregion

#pragma region Behavior Base

	/// <summary>
	/// The base class for Reader behaviors that handle the formatting of the data.
	/// </summary>
	class ReaderFormatBehavior
	{
#pragma region Methods

	protected:
		virtual Node read_node(const void* const data, Size const size) const = 0;
		virtual Bool read_bool_from_buffer(const void* const data, Size const size) const = 0;
		virtual Bool2 read_bool2_from_buffer(const void* const data, Size const size) const = 0;
		virtual Bool3 read_bool3_from_buffer(const void* const data, Size const size) const = 0;
		virtual Bool4 read_bool4_from_buffer(const void* const data, Size const size) const = 0;
		virtual Char read_char_from_buffer(const void* const data, Size const size) const = 0;
		virtual Byte read_byte_from_buffer(const void* const data, Size const size) const = 0;
		virtual Short read_short_from_buffer(const void* const data, Size const size) const = 0;
		virtual UShort read_ushort_from_buffer(const void* const data, Size const size) const = 0;
		virtual Int read_int_from_buffer(const void* const data, Size const size) const = 0;
		virtual Int2 read_int2_from_buffer(const void* const data, Size const size) const = 0;
		virtual Int3 read_int3_from_buffer(const void* const data, Size const size) const = 0;
		virtual Int4 read_int4_from_buffer(const void* const data, Size const size) const = 0;
		virtual UInt read_uint_from_buffer(const void* const data, Size const size) const = 0;
		virtual UInt2 read_uint2_from_buffer(const void* const data, Size const size) const = 0;
		virtual UInt3 read_uint3_from_buffer(const void* const data, Size const size) const = 0;
		virtual UInt4 read_uint4_from_buffer(const void* const data, Size const size) const = 0;
		virtual Long read_long_from_buffer(const void* const data, Size const size) const = 0;
		virtual ULong read_ulong_from_buffer(const void* const data, Size const size) const = 0;
		virtual Float read_float_from_buffer(const void* const data, Size const size) const = 0;
		virtual Float2 read_float2_from_buffer(const void* const data, Size const size) const = 0;
		virtual Float3 read_float3_from_buffer(const void* const data, Size const size) const = 0;
		virtual Float4 read_float4_from_buffer(const void* const data, Size const size) const = 0;
		virtual Double read_double_from_buffer(const void* const data, Size const size) const = 0;
		virtual String read_string_from_buffer(const void* const data, Size const size) const = 0;
		virtual UUID read_uuid_from_buffer(const void* const data, Size const size) const = 0;
		virtual Type read_type_from_buffer(const void* const data, Size const size) const = 0;
		virtual void* read_typed_from_buffer(const void* const data, Size const size, Type const type) const = 0;

#pragma endregion
	};

	/// <summary>
	/// The base class for Reader behaviors that handle the storage of the data.
	/// </summary>
	class ReaderStorageBehavior
	{
#pragma region Get Set

	public:
		/// <summary>
		/// Gets the pointer to the data source.
		/// </summary>
		/// <returns>A pointer to the data source.</returns>
		virtual void* get_source() const = 0;

#pragma endregion

#pragma region Methods

	protected:
		virtual void read_data(void* const data, Size const size) = 0;
		virtual Vector<Byte> read_all() = 0;

#pragma endregion
	};

#pragma endregion

#pragma region Behaviors

	/// <summary>
	/// Handles reading from a Node data source.
	/// </summary>
	class NodeReaderBehavior
		: private ReaderStorageBehavior
	{
#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new NodeReaderBehavior.
		/// </summary>
		/// <param name="ignore">This argument is ignored.</param>
		NodeReaderBehavior(void* const ignore)
		{
		}

		virtual ~NodeReaderBehavior()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Returns nullptr.
		/// </summary>
		/// <returns>Nullptr.</returns>
		void* get_source() const override { return nullptr; }

#pragma endregion

#pragma region Methods

	protected:
		void read_data(void* const data, Size const size) override {}
		Vector<Byte> read_all() override { return {}; }

#pragma endregion
	};

	/// <summary>
	/// Handles reading from a file data source.
	/// </summary>
	class FileReaderBehavior
		: private ReaderStorageBehavior
	{
#pragma region Variables

	private:
		File* mp_file;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new FileReaderBehavior.
		/// </summary>
		/// <param name="file">The File to read from.</param>
		FileReaderBehavior(void* const file)
			: mp_file(static_cast<File*>(file))
		{
		}

		virtual ~FileReaderBehavior()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the pointer to the File data source.
		/// </summary>
		/// <returns>A pointer to the File.</returns>
		void* get_source() const { return mp_file; }

#pragma endregion

#pragma region Methods

	protected:
		void read_data(void* const data, Size const size) override;
		Vector<Byte> read_all() override;

#pragma endregion
	};

	/// <summary>
	/// Handles reading from memory data source.
	/// </summary>
	class MemoryReaderBehavior
		: private ReaderStorageBehavior
	{
#pragma region Variables

	private:
		Container* mp_data;
		Size m_index;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new MemoryReaderBehavior.
		/// </summary>
		/// <param name="data">The data to read from.</param>
		MemoryReaderBehavior(void* const data)
			: mp_data(static_cast<Container*>(data))
			, m_index(0)
		{
		}

		virtual ~MemoryReaderBehavior()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the memory source.
		/// </summary>
		/// <returns>A pointer to the memory source.</returns>
		void* get_source() const override { return mp_data; }

#pragma endregion

#pragma region Methods

	protected:
		void read_data(void* const data, Size const size) override;
		Vector<Byte> read_all() override;

#pragma endregion
	};

	/// <summary>
	/// Reads plain text data.
	/// </summary>
	class TextReaderBehavior
		: private ReaderFormatBehavior
	{
#pragma region Methods

	protected:
		Node read_node(const void* const data, Size const size) const override;
		Bool read_bool_from_buffer(const void* const data, Size const size) const override;
		Bool2 read_bool2_from_buffer(const void* const data, Size const size) const override;
		Bool3 read_bool3_from_buffer(const void* const data, Size const size) const override;
		Bool4 read_bool4_from_buffer(const void* const data, Size const size) const override;
		Char read_char_from_buffer(const void* const data, Size const size) const override;
		Byte read_byte_from_buffer(const void* const data, Size const size) const override;
		Short read_short_from_buffer(const void* const data, Size const size) const override;
		UShort read_ushort_from_buffer(const void* const data, Size const size) const override;
		Int read_int_from_buffer(const void* const data, Size const size) const override;
		Int2 read_int2_from_buffer(const void* const data, Size const size) const override;
		Int3 read_int3_from_buffer(const void* const data, Size const size) const override;
		Int4 read_int4_from_buffer(const void* const data, Size const size) const override;
		UInt read_uint_from_buffer(const void* const data, Size const size) const override;
		UInt2 read_uint2_from_buffer(const void* const data, Size const size) const override;
		UInt3 read_uint3_from_buffer(const void* const data, Size const size) const override;
		UInt4 read_uint4_from_buffer(const void* const data, Size const size) const override;
		Long read_long_from_buffer(const void* const data, Size const size) const override;
		ULong read_ulong_from_buffer(const void* const data, Size const size) const override;
		Float read_float_from_buffer(const void* const data, Size const size) const override;
		Float2 read_float2_from_buffer(const void* const data, Size const size) const override;
		Float3 read_float3_from_buffer(const void* const data, Size const size) const override;
		Float4 read_float4_from_buffer(const void* const data, Size const size) const override;
		Double read_double_from_buffer(const void* const data, Size const size) const override;
		String read_string_from_buffer(const void* const data, Size const size) const override;
		UUID read_uuid_from_buffer(const void* const data, Size const size) const override;
		Type read_type_from_buffer(const void* const data, Size const size) const override;
		void* read_typed_from_buffer(const void* const data, Size const size, Type const type) const override;

#pragma endregion
	};

#pragma endregion

#pragma region Implementation

	/// <summary>
	/// Combines the Reader with the FormatBehavior and StorageBehavior.
	/// </summary>
	/// <typeparam name="FormatBehavior">The format behavior to use.</typeparam>
	/// <typeparam name="StorageBehavior">The storage behavior to use.</typeparam>
	template<typename FormatBehavior, typename StorageBehavior>
	class ReaderImplementation
		: public Reader, private FormatBehavior, private StorageBehavior
	{
#pragma region Variables

	private:
		Size m_depth;
		Node* mp_node;
		Stack<Node const*> m_nodeStack;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new ReaderImplementation using the given data source.
		/// </summary>
		/// <param name="source">A pointer to the appropriate data source for this Reader.</param>
		/// <param name="allocator">The Allocator to use.</param>
		ReaderImplementation(void* const source, Allocator const allocator = Allocator::Default)
			: Reader(allocator)
			, FormatBehavior()
			, StorageBehavior(source)
			, m_depth(0)
			, mp_node(construct<Node>(allocator))
			, m_nodeStack(allocator)
		{
			Vector<Byte> data = this->read_all();
			if (data.get_size() > 0)
			{
				Vector<Byte> temp(data.get_size());
				for (Byte b : data)
				{
					if (b != '\r')
					{
						temp.add(b);
					}
				}
				data = std::move(temp);
			}
			*mp_node = this->read_node(data.get_data(), data.get_size());
			m_nodeStack.push(mp_node);
		}

		/// <summary>
		/// Creates a new ReaderImplementation using the given data source.
		/// </summary>
		/// <param name="root">The root Node data source.</param>
		/// <param name="allocator">The Allocator to use.</param>
		ReaderImplementation(Node const& root, Allocator const allocator = Allocator::Default)
			: Reader(allocator)
			, FormatBehavior()
			, StorageBehavior(nullptr)
			, m_depth(0)
			, mp_node(construct<Node>(allocator))
			, m_nodeStack(allocator)
		{
			*mp_node = root;
			m_nodeStack.push(mp_node);
		}

		virtual ~ReaderImplementation()
		{
			destruct(mp_node, m_allocator);
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the data source for this Reader.
		/// </summary>
		/// <returns>A pointer to the data source.</returns>
		void* get_source() const override { return StorageBehavior::get_source(); }

		/// <summary>
		/// Gets the depth in the Node structure.
		/// </summary>
		/// <returns>The number of indents made from the root Node.</returns>
		Size get_depth() const override { return m_depth; }

		/// <summary>
		/// Gets the current Node this Reader is on.
		/// </summary>
		/// <returns>The active Node.</returns>
		Node const& get_node() const override { return *m_nodeStack.peek(); }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Steps into the child Node at the given index.
		/// </summary>
		/// <param name="index">The index of the child to indent into.</param>
		/// <returns>True on success.</returns>
		Bool indent(Size const index) override
		{
			Node const& node = get_node();
			if (is_valid() && index < node.get_children_size())
			{
				m_nodeStack.push(&node.get_child(index));
				m_depth++;
				return true;
			}
			return false;
		}

		/// <summary>
		/// Steps into the child Node with the given name.
		/// </summary>
		/// <param name="name">The name of the child to indent into.</param>
		/// <returns>True on success.</returns>
		Bool indent(String const& name) override
		{
			return indent(this->get_index(name));
		}

		/// <summary>
		/// Steps out of the current Node, back to its parent.
		/// </summary>
		void outdent() override
		{
			MINTY_ASSERT(m_depth > 0, "Cannot outdent from the root Node.");

			if (is_valid())
			{
				m_nodeStack.pop();
			}
			m_depth--;
		}

		/// <summary>
		/// Checks if this Reader is valid. The reader is valid when the depth is equal to the size of the node stack. 
		/// A Reader becomes invalid when it attempts to indent() into a child Node that does not exist.
		/// </summary>
		/// <returns>True when valid.</returns>
		Bool is_valid() const override { return m_depth + 1 == m_nodeStack.get_size(); }

		/// <summary>
		/// Reads the name of the Node at the given index.
		/// </summary>
		/// <param name="index">The index of the child Node.</param>
		/// <param name="obj">The object to read the data into.</param>
		/// <returns>True on success.</returns>
		Bool read_name(Size const index, String& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					obj = node.get_child(index).get_name();
					return true;
				}
			}
			return false;
		}

	protected:
		Bool read_bool(Size const index, Bool& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_bool_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_bool2(Size const index, Bool2& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_bool2_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_bool3(Size const index, Bool3& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_bool3_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_bool4(Size const index, Bool4& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_bool4_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_char(Size const index, Char& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_char_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_byte(Size const index, Byte& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_byte_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_short(Size const index, Short& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_short_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_ushort(Size const index, UShort& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_ushort_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_int(Size const index, Int& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_int_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_int2(Size const index, Int2& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_int2_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_int3(Size const index, Int3& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_int3_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_int4(Size const index, Int4& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_int4_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_uint(Size const index, UInt& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_uint_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_uint2(Size const index, UInt2& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_uint2_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_uint3(Size const index, UInt3& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_uint3_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_uint4(Size const index, UInt4& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_uint4_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_long(Size const index, Long& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_long_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_ulong(Size const index, ULong& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_ulong_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_float(Size const index, Float& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_float_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_float2(Size const index, Float2& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_float2_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_float3(Size const index, Float3& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_float3_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_float4(Size const index, Float4& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_float4_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_double(Size const index, Double& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_double_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_string(Size const index, String& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_string_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}
		Bool read_type(Size const index, Type& obj) const override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& data = node.get_child(index).get_data();
					obj = this->read_type_from_buffer(data.get_data(), data.get_size());
					return true;
				}
			}
			return false;
		}

		Bool read_typed(Size const index, void* const data, Type& type) override
		{
			if (is_valid())
			{
				Node const& node = get_node();
				if (node.has_child(index))
				{
					Container const& container = node.get_child(index).get_data();
					// find separator (: )
					Char* ch = static_cast<Char*>(container.get_data());
					Size i;
					for (i = 0; i < container.get_size(); ++i)
					{
						if (ch[i] == ':' && ch[i + 1] == ' ')
						{
							break;
						}
					}
					// read type
					type = this->read_type_from_buffer(container.get_data(), i);
					i += 2; // skip (: )
					// if i over the size, no value
					if (i >= container.get_size())
					{
						return false;
					}
					// value
					void* temp = this->read_typed_from_buffer(&ch[i], container.get_size() - i, type);
					if (!temp)
					{
						// failed to read typed data
						return false;
					}
					// copy data over
					memcpy(data, temp, sizeof_type(type));
					// delete the temp data
					delete temp;

					return true;
				}
			}
			return false;
		}

#pragma endregion
	};

#pragma endregion

#pragma region Readers

	using TextFileReader = ReaderImplementation<TextReaderBehavior, FileReaderBehavior>;
	using TextNodeReader = ReaderImplementation<TextReaderBehavior, NodeReaderBehavior>;
	using TextMemoryReader = ReaderImplementation<TextReaderBehavior, MemoryReaderBehavior>;

#pragma endregion
}