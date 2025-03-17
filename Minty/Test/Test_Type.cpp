#include "Test_Type.h"
#include "Minty.h"

void test_Type(Test& _test)
{
	CATEGORY(Type)
	{
		Vector<TypeID> const TYPE_IDS =
		{
			typeid(nullptr),
			typeid(Bool),
			typeid(Bool2),
			typeid(Bool3),
			typeid(Bool4),
			typeid(Char),
			typeid(Byte),
			typeid(Short),
			typeid(UShort),
			typeid(Int),
			typeid(Int2),
			typeid(Int3),
			typeid(Int4),
			typeid(UInt),
			typeid(UInt2),
			typeid(UInt3),
			typeid(UInt4),
			typeid(Long),
			typeid(ULong),
			typeid(Size),
			typeid(Float),
			typeid(Float2),
			typeid(Float3),
			typeid(Float4),
			typeid(Double),
			typeid(Matrix2),
			typeid(Matrix3),
			typeid(Matrix4),
			typeid(Quaternion),
			typeid(Color),
			typeid(UUID),
			typeid(void*),
			typeid(String),
			typeid(String),
		};

		Vector<Size> const TYPE_SIZES =
		{
			0,
			sizeof(Bool),
			sizeof(Bool2),
			sizeof(Bool3),
			sizeof(Bool4),
			sizeof(Char),
			sizeof(Byte),
			sizeof(Short),
			sizeof(UShort),
			sizeof(Int),
			sizeof(Int2),
			sizeof(Int3),
			sizeof(Int4),
			sizeof(UInt),
			sizeof(UInt2),
			sizeof(UInt3),
			sizeof(UInt4),
			sizeof(Long),
			sizeof(ULong),
			sizeof(Size),
			sizeof(Float),
			sizeof(Float2),
			sizeof(Float3),
			sizeof(Float4),
			sizeof(Double),
			sizeof(Matrix2),
			sizeof(Matrix3),
			sizeof(Matrix4),
			sizeof(Quaternion),
			sizeof(Color),
			sizeof(UUID),
			sizeof(void*),
			sizeof(String),
			sizeof(String),
		};

		SETUP()
		{
			EXPECT_EQUAL(static_cast<Size>(Type::Count), TYPE_IDS.get_size());
			EXPECT_EQUAL(static_cast<Size>(Type::Count), TYPE_SIZES.get_size());
		}

		TEST("Type TypeID")
		{
			for (Size i = 0; i < TYPE_IDS.get_size(); ++i)
			{
				TypeID typeID = TYPE_IDS[i];
				Type expected = static_cast<Type>(i);
				// special cases
				if (expected == Type::Size)
				{
					expected = type_typeid(typeid_type(Type::Size));
				}
				else if (expected == Type::MultilineString)
				{
					expected = Type::String;
				}
				Type actual = type_typeid(typeID);

				EXPECT_EQUAL(actual, expected);
			}
		}

		TEST("TypeID Type")
		{
			for (Size i = 0; i < TYPE_IDS.get_size(); ++i)
			{
				TypeID expected = TYPE_IDS[i];
				TypeID actual = typeid_type(static_cast<Type>(i));

				EXPECT_EQUAL(actual, expected);
			}
		}

		TEST("SizeOf Type")
		{
			for (Size i = 0; i < TYPE_SIZES.get_size(); ++i)
			{
				Type type = static_cast<Type>(i);
				Size expected = TYPE_SIZES.at(i);
				Size actual = sizeof_type(type);
				EXPECT_EQUAL(actual, expected);
			}
		}
	}
}
