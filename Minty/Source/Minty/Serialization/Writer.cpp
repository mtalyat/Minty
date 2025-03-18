#include "pch.h"
#include "Writer.h"
#include "Minty/Core/Format.h"
#include "Minty/Serialization/Serializable.h"
#include "Minty/Serialization/SerializableObject.h"

using namespace Minty;

void* Minty::Writer::get_user_data() const
{
	if (m_dataStack.get_size() == 0)
	{
		return nullptr;
	}

	return m_dataStack.peek();
}

void Minty::Writer::push_user_data(void* const data)
{
	m_dataStack.push(data);
}

void Minty::Writer::pop_user_data()
{
	MINTY_ASSERT(m_dataStack.get_size() > 0, "Data stack is empty.");

	m_dataStack.pop();
}

void Minty::Writer::write(String const& name, const void* const data, Type const type)
{
	switch (type)
	{
	case Type::Bool:
		return write_bool(name, *static_cast<Bool const* const>(data));
	case Type::Bool2:
		return write_bool2(name, *static_cast<Bool2 const* const>(data));
	case Type::Bool3:
		return write_bool3(name, *static_cast<Bool3 const* const>(data));
	case Type::Bool4:
		return write_bool4(name, *static_cast<Bool4 const* const>(data));
	case Type::Char:
		return write_char(name, *static_cast<Char const* const>(data));
	case Type::Byte:
		return write_byte(name, *static_cast<Byte const* const>(data));
	case Type::Short:
		return write_short(name, *static_cast<Short const* const>(data));
	case Type::UShort:
		return write_ushort(name, *static_cast<UShort const* const>(data));
	case Type::Int:
		return write_int(name, *static_cast<Int const* const>(data));
	case Type::Int2:
		return write_int2(name, *static_cast<Int2 const* const>(data));
	case Type::Int3:
		return write_int3(name, *static_cast<Int3 const* const>(data));
	case Type::Int4:
		return write_int4(name, *static_cast<Int4 const* const>(data));
	case Type::UInt:
		return write_uint(name, *static_cast<UInt const* const>(data));
	case Type::UInt2:
		return write_uint2(name, *static_cast<UInt2 const* const>(data));
	case Type::UInt3:
		return write_uint3(name, *static_cast<UInt3 const* const>(data));
	case Type::UInt4:
		return write_uint4(name, *static_cast<UInt4 const* const>(data));
	case Type::Long:
		return write_long(name, *static_cast<Long const* const>(data));
	case Type::ULong:
		return write_ulong(name, *static_cast<ULong const* const>(data));
	case Type::Size:
		return write_size(name, *static_cast<Size const* const>(data));
	case Type::Float:
		return write_float(name, *static_cast<Float const* const>(data));
	case Type::Float2:
		return write_float2(name, *static_cast<Float2 const* const>(data));
	case Type::Float3:
		return write_float3(name, *static_cast<Float3 const* const>(data));
	case Type::Float4:
		return write_float4(name, *static_cast<Float4 const* const>(data));
	case Type::Double:
		return write_double(name, *static_cast<Double const* const>(data));
	case Type::String:
		return write_string(name, *static_cast<String const* const>(data));
	default:
		MINTY_ABORT(F("Cannot write type \"{}\".", to_string(type)).get_data());
	}
}

void Minty::FileWriterBehavior::write_data(void const* const data, Size const size)
{
	mp_file->write(data, size);
}

void Minty::MemoryWriterBehavior::write_data(void const* const data, Size const size)
{
	mp_data->append(data, size);
}

void Minty::TextWriterBehavior::write_indent_to_buffer(Size const indent, Vector<Byte>& buffer)
{
	write_string_to_buffer(String('\t', indent), buffer);
}

Bool Minty::TextWriterBehavior::write_name_to_buffer(String const& data, Vector<Byte>& buffer)
{
	MINTY_ASSERT(data.get_size() < 256, "A name cannot be longer than 255 bytes.");

	if (data.is_empty())
	{
		// no name: do bullet point
		write_string_to_buffer("- ", buffer);
		return false;
	}
	else
	{
		// yes name: write name
		write_string_to_buffer(data, buffer);
		return true;
	}
}

void Minty::TextWriterBehavior::write_separator_to_buffer(Vector<Byte>& buffer)
{
	write_string_to_buffer(": ", buffer);
}

void Minty::TextWriterBehavior::write_space_to_buffer(Vector<Byte>& buffer)
{
	write_string_to_buffer(" ", buffer);
}

void Minty::TextWriterBehavior::write_end_to_buffer(Vector<Byte>& buffer)
{
	write_string_to_buffer("\n", buffer);
}

void Minty::TextWriterBehavior::write_string_to_buffer(String const& data, Vector<Byte>& buffer)
{
	// add string to buffer
	Size offset = buffer.get_size();
	buffer.resize(offset + data.get_size());
	memcpy(buffer.get_data() + offset, data.get_data(), data.get_size());
}

void Minty::TextWriterBehavior::write_bool_to_buffer(Bool const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_bool2_to_buffer(Bool2 const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_bool3_to_buffer(Bool3 const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_bool4_to_buffer(Bool4 const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_char_to_buffer(Char const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_byte_to_buffer(Byte const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_short_to_buffer(Short const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_ushort_to_buffer(UShort const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_int_to_buffer(Int const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_int2_to_buffer(Int2 const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_int3_to_buffer(Int3 const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_int4_to_buffer(Int4 const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_uint_to_buffer(UInt const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_uint2_to_buffer(UInt2 const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_uint3_to_buffer(UInt3 const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_uint4_to_buffer(UInt4 const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_long_to_buffer(Long const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_ulong_to_buffer(ULong const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_size_to_buffer(Size const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_float_to_buffer(Float const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_float2_to_buffer(Float2 const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_float3_to_buffer(Float3 const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_float4_to_buffer(Float4 const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_double_to_buffer(Double const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}
void Minty::TextWriterBehavior::write_type_to_buffer(Type const data, Vector<Byte>& buffer)
{
	write_string_to_buffer(Minty::to_string(data), buffer);
}

void Minty::TextWriterBehavior::write_typed_to_buffer(Type const type, void const* const data, Vector<Byte>& buffer)
{
	switch (type)
	{
	case Type::Bool:
		write_bool_to_buffer(*static_cast<Bool const* const>(data), buffer);
		break;
	case Type::Bool2:
		write_bool2_to_buffer(*static_cast<Bool2 const* const>(data), buffer);
		break;
	case Type::Bool3:
		write_bool3_to_buffer(*static_cast<Bool3 const* const>(data), buffer);
		break;
	case Type::Bool4:
		write_bool4_to_buffer(*static_cast<Bool4 const* const>(data), buffer);
		break;
	case Type::Char:
		write_char_to_buffer(*static_cast<Char const* const>(data), buffer);
		break;
	case Type::Byte:
		write_byte_to_buffer(*static_cast<Byte const* const>(data), buffer);
		break;
	case Type::Short:
		write_short_to_buffer(*static_cast<Short const* const>(data), buffer);
		break;
	case Type::UShort:
		write_ushort_to_buffer(*static_cast<UShort const* const>(data), buffer);
		break;
	case Type::Int:
		write_int_to_buffer(*static_cast<Int const* const>(data), buffer);
		break;
	case Type::Int2:
		write_int2_to_buffer(*static_cast<Int2 const* const>(data), buffer);
		break;
	case Type::Int3:
		write_int3_to_buffer(*static_cast<Int3 const* const>(data), buffer);
		break;
	case Type::Int4:
		write_int4_to_buffer(*static_cast<Int4 const* const>(data), buffer);
		break;
	case Type::UInt:
		write_uint_to_buffer(*static_cast<UInt const* const>(data), buffer);
		break;
	case Type::UInt2:
		write_uint2_to_buffer(*static_cast<UInt2 const* const>(data), buffer);
		break;
	case Type::UInt3:
		write_uint3_to_buffer(*static_cast<UInt3 const* const>(data), buffer);
		break;
	case Type::UInt4:
		write_uint4_to_buffer(*static_cast<UInt4 const* const>(data), buffer);
		break;
	case Type::Long:
		write_long_to_buffer(*static_cast<Long const* const>(data), buffer);
		break;
	case Type::ULong:
		write_ulong_to_buffer(*static_cast<ULong const* const>(data), buffer);
		break;
	case Type::Size:
		write_size_to_buffer(*static_cast<Size const* const>(data), buffer);
		break;
	case Type::Float:
		write_float_to_buffer(*static_cast<Float const* const>(data), buffer);
		break;
	case Type::Float2:
		write_float2_to_buffer(*static_cast<Float2 const* const>(data), buffer);
		break;
	case Type::Float3:
		write_float3_to_buffer(*static_cast<Float3 const* const>(data), buffer);
		break;
	case Type::Float4:
		write_float4_to_buffer(*static_cast<Float4 const* const>(data), buffer);
		break;
	case Type::Double:
		write_double_to_buffer(*static_cast<Double const* const>(data), buffer);
		break;
	case Type::String:
		write_string_to_buffer(*static_cast<String const* const>(data), buffer);
		break;
	default:
		MINTY_ABORT(F("Cannot write type \"{}\".", to_string(type)).get_data());
	}
}