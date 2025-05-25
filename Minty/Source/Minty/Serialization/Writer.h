#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Core/Math.h"
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"
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
#include "Minty/File/File.h"
#include "Minty/Serialization/IsSerializable.h"
#include "Minty/Serialization/Node.h"

namespace Minty
{
#pragma region Base

	class Writer
	{
#pragma region Variables

	private:
		Allocator m_allocator;
		List<void const*> m_dataStack;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Writer.
		/// </summary>
		/// <param name="allocator">The Allocator to use.</param>
		Writer(Allocator const allocator = Allocator::Default)
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
		void const* get_user_data() const;

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

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Adds data to the top of the data stack.
		/// </summary>
		/// <param name="data">The pointer to the data to add.</param>
		void push_user_data(void const* const data);

		/// <summary>
		/// Removes the top of the data stack.
		/// </summary>
		void pop_user_data();

		/// <summary>
		/// Steps into the next child Node.
		/// </summary>
		virtual void indent() = 0;

		/// <summary>
		/// Steps into the child Node with the given name.
		/// </summary>
		/// <param name="name">The name of the child to indent into.</param>
		/// <returns>True on success.</returns>
		virtual void indent(String const& name) = 0;

		/// <summary>
		/// Steps out of the current Node, back to its parent.
		/// </summary>
		virtual void outdent() = 0;

#pragma region Writing

	protected:
		virtual void write_empty(String const& name) = 0;
		virtual void write_bool(String const& name, Bool const& obj) = 0;
		virtual void write_bool2(String const& name, Bool2 const& obj) = 0;
		virtual void write_bool3(String const& name, Bool3 const& obj) = 0;
		virtual void write_bool4(String const& name, Bool4 const& obj) = 0;
		virtual void write_char(String const& name, Char const& obj) = 0;
		virtual void write_byte(String const& name, Byte const& obj) = 0;
		virtual void write_short(String const& name, Short const& obj) = 0;
		virtual void write_ushort(String const& name, UShort const& obj) = 0;
		virtual void write_int(String const& name, Int const& obj) = 0;
		virtual void write_int2(String const& name, Int2 const& obj) = 0;
		virtual void write_int3(String const& name, Int3 const& obj) = 0;
		virtual void write_int4(String const& name, Int4 const& obj) = 0;
		virtual void write_uint(String const& name, UInt const& obj) = 0;
		virtual void write_uint2(String const& name, UInt2 const& obj) = 0;
		virtual void write_uint3(String const& name, UInt3 const& obj) = 0;
		virtual void write_uint4(String const& name, UInt4 const& obj) = 0;
		virtual void write_long(String const& name, Long const& obj) = 0;
		virtual void write_ulong(String const& name, ULong const& obj) = 0;
		virtual void write_size(String const& name, Size const& obj) = 0;
		virtual void write_float(String const& name, Float const& obj) = 0;
		virtual void write_float2(String const& name, Float2 const& obj) = 0;
		virtual void write_float3(String const& name, Float3 const& obj) = 0;
		virtual void write_float4(String const& name, Float4 const& obj) = 0;
		virtual void write_double(String const& name, Double const& obj) = 0;
		virtual void write_string(String const& name, String const& obj) = 0;
		virtual void write_type(String const& name, Type const& obj) = 0;

	public:
		/// <summary>
		/// Writes a Node with no value.
		/// </summary>
		/// <param name="name"></param>
		void write(String const& name) { write_empty(name); }

		template<typename T, typename std::enable_if<!is_asset<T>::value && !is_serializable<T>::value && !is_serializable_object<T>::value, int>::type = 0>
		void write(String const& name, T const& data)
		{
			// default: write as string
			write_string(name, to_string(data));
		}

		template<typename T, typename std::enable_if<!is_asset<T>::value && !is_serializable<T>::value&& is_serializable_object<T>::value, int>::type = 0>
		void write(String const& name, T const& data)
		{
			indent(name);
			data.serialize(*this);
			outdent();
		}

		template<typename T, typename std::enable_if<!is_asset<T>::value && is_serializable<T>::value, int>::type = 0>
		void write(String const& name, T const& data)
		{
			data.serialize(*this, name);
		}

		template<>
		void write(String const& name, Bool const& data)
		{
			write_bool(name, data);
		}
		template<>
		void write(String const& name, Bool2 const& data)
		{
			write_bool2(name, data);
		}
		template<>
		void write(String const& name, Bool3 const& data)
		{
			write_bool3(name, data);
		}
		template<>
		void write(String const& name, Bool4 const& data)
		{
			write_bool4(name, data);
		}
		template<>
		void write(String const& name, Char const& data)
		{
			write_char(name, data);
		}
		template<>
		void write(String const& name, Byte const& data)
		{
			write_byte(name, data);
		}
		template<>
		void write(String const& name, Short const& data)
		{
			write_short(name, data);
		}
		template<>
		void write(String const& name, UShort const& data)
		{
			write_ushort(name, data);
		}
		template<>
		void write(String const& name, Int const& data)
		{
			write_int(name, data);
		}
		template<>
		void write(String const& name, Int2 const& data)
		{
			write_int2(name, data);
		}
		template<>
		void write(String const& name, Int3 const& data)
		{
			write_int3(name, data);
		}
		template<>
		void write(String const& name, Int4 const& data)
		{
			write_int4(name, data);
		}
		template<>
		void write(String const& name, UInt const& data)
		{
			write_uint(name, data);
		}
		template<>
		void write(String const& name, UInt2 const& data)
		{
			write_uint2(name, data);
		}
		template<>
		void write(String const& name, UInt3 const& data)
		{
			write_uint3(name, data);
		}
		template<>
		void write(String const& name, UInt4 const& data)
		{
			write_uint4(name, data);
		}
		template<>
		void write(String const& name, Long const& data)
		{
			write_long(name, data);
		}
		template<>
		void write(String const& name, ULong const& data)
		{
			write_ulong(name, data);
		}
		template<>
		void write(String const& name, Float const& data)
		{
			write_float(name, data);
		}
		template<>
		void write(String const& name, Float2 const& data)
		{
			write_float2(name, data);
		}
		template<>
		void write(String const& name, Float3 const& data)
		{
			write_float3(name, data);
		}
		template<>
		void write(String const& name, Float4 const& data)
		{
			write_float4(name, data);
		}
		template<>
		void write(String const& name, Double const& data)
		{
			write_double(name, data);
		}
		template<>
		void write(String const& name, String const& data)
		{
			write_string(name, data);
		}
		template<>
		void write(String const& name, Type const& data)
		{
			write_type(name, data);
		}

		template<typename T, Size S>
		void write(String const& name, Array<T, S> const& data)
		{
			indent(name);
			for (Size i = 0; i < S; i++)
			{
				write("", data[i]);
			}
			outdent();
		}

		template<typename T>
		void write(String const& name, List<T> const& data)
		{
			indent(name);
			for (Size i = 0; i < data.size(); i++)
			{
				write("", data[i]);
			}
			outdent();
		}

		template<typename T>
		void write(String const& name, Vector<T> const& data)
		{
			indent(name);
			for (Size i = 0; i < data.get_size(); i++)
			{
				write("", data[i]);
			}
			outdent();
		}

		template<typename T>
		void write(String const& name, Set<T> const& data)
		{
			indent(name);
			for (Size i = 0; i < data.get_size(); i++)
			{
				write("", data[i]);
			}
			outdent();
		}

		template<typename T>
		void write(String const& name, Map<String, T> const& data)
		{
			indent(name);
			for (auto const& [key, value] : data)
			{
				write(key, value);
			}
			outdent();
		}

		/// <summary>
		/// Writes the data with the given Type.
		/// </summary>
		/// <param name="name">The name.</param>
		/// <param name="data">A pointer to the byte data.</param>
		/// <param name="type">The Type.</param>
		virtual void write_typed(String const& name, void const* const data, Type const type) = 0;

		/// <summary>
		/// Writes the given Asset's ID. If null, writes INVALID_ID.
		/// </summary>
		/// <param name="name">The name of the Asset.</param>
		/// <param name="asset">The Asset.</param>
		void write_asset(String const& name, Ref<Asset> const& asset);

		/// <summary>
		/// Writes the given Asset's ID. If null, writes INVALID_ID.
		/// </summary>
		/// <typeparam name="T">The type of Asset.</typeparam>
		/// <param name="name">The name of the Asset.</param>
		/// <param name="asset">The Asset.</param>
		template<typename T, typename std::enable_if<is_asset<T>::value, int>::type = 0>
		void write(String const& name, Ref<T> const& asset)
		{
			write_asset(name, asset);
		}

#pragma endregion

#pragma endregion
	};

#pragma endregion

#pragma region Behavior Base

	/// <summary>
	/// The base class for Writer behaviors that handle the formatting of the data.
	/// </summary>
	class WriterFormatBehavior
	{
#pragma region Methods

	protected:
		virtual void write_indent_to_buffer(Size const indent, Vector<Byte>& buffer) = 0;
		virtual Bool write_name_to_buffer(String const& data, Vector<Byte>& buffer) = 0;
		virtual void write_separator_to_buffer(Vector<Byte>& buffer) = 0;
		virtual void write_space_to_buffer(Vector<Byte>& buffer) = 0;
		virtual void write_end_to_buffer(Vector<Byte>& buffer) = 0;

		virtual void write_bool_to_buffer(Bool const data, Vector<Byte>& buffer) = 0;
		virtual void write_bool2_to_buffer(Bool2 const data, Vector<Byte>& buffer) = 0;
		virtual void write_bool3_to_buffer(Bool3 const data, Vector<Byte>& buffer) = 0;
		virtual void write_bool4_to_buffer(Bool4 const data, Vector<Byte>& buffer) = 0;
		virtual void write_char_to_buffer(Char const data, Vector<Byte>& buffer) = 0;
		virtual void write_byte_to_buffer(Byte const data, Vector<Byte>& buffer) = 0;
		virtual void write_short_to_buffer(Short const data, Vector<Byte>& buffer) = 0;
		virtual void write_ushort_to_buffer(UShort const data, Vector<Byte>& buffer) = 0;
		virtual void write_int_to_buffer(Int const data, Vector<Byte>& buffer) = 0;
		virtual void write_int2_to_buffer(Int2 const data, Vector<Byte>& buffer) = 0;
		virtual void write_int3_to_buffer(Int3 const data, Vector<Byte>& buffer) = 0;
		virtual void write_int4_to_buffer(Int4 const data, Vector<Byte>& buffer) = 0;
		virtual void write_uint_to_buffer(UInt const data, Vector<Byte>& buffer) = 0;
		virtual void write_uint2_to_buffer(UInt2 const data, Vector<Byte>& buffer) = 0;
		virtual void write_uint3_to_buffer(UInt3 const data, Vector<Byte>& buffer) = 0;
		virtual void write_uint4_to_buffer(UInt4 const data, Vector<Byte>& buffer) = 0;
		virtual void write_long_to_buffer(Long const data, Vector<Byte>& buffer) = 0;
		virtual void write_ulong_to_buffer(ULong const data, Vector<Byte>& buffer) = 0;
		virtual void write_size_to_buffer(Size const data, Vector<Byte>& buffer) = 0;
		virtual void write_float_to_buffer(Float const data, Vector<Byte>& buffer) = 0;
		virtual void write_float2_to_buffer(Float2 const data, Vector<Byte>& buffer) = 0;
		virtual void write_float3_to_buffer(Float3 const data, Vector<Byte>& buffer) = 0;
		virtual void write_float4_to_buffer(Float4 const data, Vector<Byte>& buffer) = 0;
		virtual void write_double_to_buffer(Double const data, Vector<Byte>& buffer) = 0;
		virtual void write_string_to_buffer(String const& data, Vector<Byte>& buffer) = 0;
		virtual void write_uuid_to_buffer(UUID const data, Vector<Byte>& buffer) = 0;
		virtual void write_type_to_buffer(Type const data, Vector<Byte>& buffer) = 0;
		virtual void write_typed_to_buffer(void const* const data, Vector<Byte>& buffer, Type const type) = 0;

#pragma endregion
	};

	/// <summary>
	/// The base class for Reader behaviors that handle the storage of the data.
	/// </summary>
	class WriterStorageBehavior
	{
#pragma region Get Set

	public:
		virtual void* get_source() const = 0;

#pragma endregion

#pragma region Methods

	protected:
		virtual void write_data(void const* const data, Size const size) = 0;

#pragma endregion
	};

#pragma endregion

#pragma region Behaviors

	/// <summary>
	/// Writes data to a File.
	/// </summary>
	class FileWriterBehavior
		: private WriterStorageBehavior
	{
#pragma region Variables

	private:
		File* mp_file;

#pragma endregion

#pragma region Constructors

	public:
		FileWriterBehavior(void* const file)
			: mp_file(static_cast<File*>(file))
		{
		}

		virtual ~FileWriterBehavior()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		void* get_source() const override { return mp_file; }

#pragma endregion

#pragma region Methods

	protected:
		void write_data(void const* const data, Size const size) override;

#pragma endregion
	};

	class MemoryWriterBehavior
		: private WriterStorageBehavior
	{
#pragma region Variables

	private:
		Container* mp_data;

#pragma endregion

#pragma region Constructors

	public:
		MemoryWriterBehavior(void* const container)
			: mp_data(static_cast<Container*>(container))
		{
		}

		virtual ~MemoryWriterBehavior()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		void* get_source() const override { return mp_data; }

#pragma endregion

#pragma region Methods

	protected:
		void write_data(void const* const data, Size const size) override;

#pragma endregion
	};

	/// <summary>
	/// Writes data as plain text.
	/// </summary>
	class TextWriterBehavior
		: private WriterFormatBehavior
	{
#pragma region Methods

	protected:
		void write_indent_to_buffer(Size const indent, Vector<Byte>& buffer) override;
		Bool write_name_to_buffer(String const& data, Vector<Byte>& buffer) override;
		void write_separator_to_buffer(Vector<Byte>& buffer) override;
		void write_space_to_buffer(Vector<Byte>& buffer) override;
		void write_end_to_buffer(Vector<Byte>& buffer) override;

		void write_bool_to_buffer(Bool const data, Vector<Byte>& buffer) override;
		void write_bool2_to_buffer(Bool2 const data, Vector<Byte>& buffer) override;
		void write_bool3_to_buffer(Bool3 const data, Vector<Byte>& buffer) override;
		void write_bool4_to_buffer(Bool4 const data, Vector<Byte>& buffer) override;
		void write_char_to_buffer(Char const data, Vector<Byte>& buffer) override;
		void write_byte_to_buffer(Byte const data, Vector<Byte>& buffer) override;
		void write_short_to_buffer(Short const data, Vector<Byte>& buffer) override;
		void write_ushort_to_buffer(UShort const data, Vector<Byte>& buffer) override;
		void write_int_to_buffer(Int const data, Vector<Byte>& buffer) override;
		void write_int2_to_buffer(Int2 const data, Vector<Byte>& buffer) override;
		void write_int3_to_buffer(Int3 const data, Vector<Byte>& buffer) override;
		void write_int4_to_buffer(Int4 const data, Vector<Byte>& buffer) override;
		void write_uint_to_buffer(UInt const data, Vector<Byte>& buffer) override;
		void write_uint2_to_buffer(UInt2 const data, Vector<Byte>& buffer) override;
		void write_uint3_to_buffer(UInt3 const data, Vector<Byte>& buffer) override;
		void write_uint4_to_buffer(UInt4 const data, Vector<Byte>& buffer) override;
		void write_long_to_buffer(Long const data, Vector<Byte>& buffer) override;
		void write_ulong_to_buffer(ULong const data, Vector<Byte>& buffer) override;
		void write_size_to_buffer(Size const data, Vector<Byte>& buffer) override;
		void write_float_to_buffer(Float const data, Vector<Byte>& buffer) override;
		void write_float2_to_buffer(Float2 const data, Vector<Byte>& buffer) override;
		void write_float3_to_buffer(Float3 const data, Vector<Byte>& buffer) override;
		void write_float4_to_buffer(Float4 const data, Vector<Byte>& buffer) override;
		void write_double_to_buffer(Double const data, Vector<Byte>& buffer) override;
		void write_string_to_buffer(String const& data, Vector<Byte>& buffer) override;
		void write_uuid_to_buffer(UUID const data, Vector<Byte>& buffer) override;
		void write_type_to_buffer(Type const data, Vector<Byte>& buffer) override;
		void write_typed_to_buffer(void const* const data, Vector<Byte>& buffer, Type const type) override;

#pragma endregion
	};

#pragma endregion

#pragma region Implementation

	template<typename FormatBehavior, typename StorageBehavior>
	class WriterImplementation
		: public Writer, private FormatBehavior, private StorageBehavior
	{
#pragma region Variables

	private:
		Size m_depth;

#pragma endregion

#pragma region Constructors

	public:
		WriterImplementation(void* const source)
			: FormatBehavior()
			, StorageBehavior(source)
			, m_depth(0)
		{
		}
		virtual ~WriterImplementation()
		{
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

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Steps into the next child Node.
		/// </summary>
		void indent() override
		{
			m_depth++;
		}

		/// <summary>
		/// Steps into the child Node with the given name.
		/// </summary>
		/// <param name="name">The name of the child to indent into.</param>
		/// <returns>True on success.</returns>
		void indent(String const& name) override
		{
			Writer::write(name);
			indent();
		}

		/// <summary>
		/// Steps out of the current Node, back to its parent.
		/// </summary>
		void outdent() override
		{
			MINTY_ASSERT(m_depth > 0, "Cannot outdent from the root.");
			m_depth--;
		}

#pragma region Write

	protected:
		void write_empty(String const& name) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			this->write_name_to_buffer(name, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_bool(String const& name, Bool const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_bool_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_bool2(String const& name, Bool2 const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_bool2_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_bool3(String const& name, Bool3 const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_bool3_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_bool4(String const& name, Bool4 const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_bool4_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_char(String const& name, Char const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_char_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_byte(String const& name, Byte const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_byte_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_short(String const& name, Short const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_short_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_ushort(String const& name, UShort const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_ushort_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_int(String const& name, Int const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_int_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_int2(String const& name, Int2 const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_int2_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_int3(String const& name, Int3 const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_int3_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_int4(String const& name, Int4 const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_int4_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_uint(String const& name, UInt const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_uint_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_uint2(String const& name, UInt2 const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_uint2_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_uint3(String const& name, UInt3 const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_uint3_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_uint4(String const& name, UInt4 const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_uint4_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_long(String const& name, Long const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_long_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_ulong(String const& name, ULong const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_ulong_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_size(String const& name, Size const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_size_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_float(String const& name, Float const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_float_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_float2(String const& name, Float2 const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_float2_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_float3(String const& name, Float3 const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_float3_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_float4(String const& name, Float4 const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_float4_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_double(String const& name, Double const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_double_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_string(String const& name, String const& obj) override
		{
			if (obj.is_empty())
			{
				write_empty(name);
				return;
			}

			String fixedObj = String::replace(obj, "\n", "\\n");

			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_string_to_buffer(fixedObj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

		void write_type(String const& name, Type const& obj) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_type_to_buffer(obj, buffer);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

	public:
		void write_typed(String const& name, void const* const data, Type const type) override
		{
			// write to memory buffer
			Vector<Byte> buffer;
			buffer.reserve(256);
			this->write_indent_to_buffer(m_depth, buffer);
			if (this->write_name_to_buffer(name, buffer))
			{
				this->write_separator_to_buffer(buffer);
			}
			this->write_type_to_buffer(type, buffer);
			this->write_separator_to_buffer(buffer);
			this->write_typed_to_buffer(data, buffer, type);
			this->write_end_to_buffer(buffer);

			// write to stream
			this->write_data(buffer.get_data(), buffer.get_size());
		}

#pragma endregion

#pragma endregion
	};

#pragma endregion

#pragma region Writers

	using TextFileWriter = WriterImplementation<TextWriterBehavior, FileWriterBehavior>;
	using TextMemoryWriter = WriterImplementation<TextWriterBehavior, MemoryWriterBehavior>;

#pragma endregion
}