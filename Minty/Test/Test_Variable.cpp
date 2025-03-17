#include "Test_Variable.h"
#include "Minty.h"

void test_Variable(Test& _test)
{
	CATEGORY(Variable)
	{
		TEST("Default Constructor")
		{
			Variable v;
			EXPECT_EQUAL(v.get_type(), Type::Undefined);
			EXPECT_EQUAL(v.get_data().get_capacity(), 0);
			EXPECT_EQUAL(v.get_data().get_size(), 0);
		}

		TEST("Type Constructor")
		{
			Variable v(Type::Int);
			EXPECT_EQUAL(v.get_type(), Type::Int);
			EXPECT_EQUAL(v.get_data().get_size(), 0);

			Variable v2(Type::Undefined);
			EXPECT_EQUAL(v2.get_type(), Type::Undefined);
			EXPECT_EQUAL(v2.get_data().get_size(), 0);

			EXPECT_FAIL(Variable v3(Type::Object));
		}

		TEST("Type Data Constructor")
		{
			Int const value = 42;
			Variable v(Type::Int, &value);
			EXPECT_EQUAL(v.get_type(), Type::Int);
			EXPECT_EQUAL(v.get_data().get_capacity(), sizeof_type(Type::Int));
			EXPECT_EQUAL(v.get_data().get_size(), sizeof_type(Type::Int));
			EXPECT_EQUAL(v, value);
		}

		TEST("Value Constructor")
		{
			Int const value = 42;
			Variable v(value);
			EXPECT_EQUAL(v.get_type(), Type::Int);
			EXPECT_EQUAL(v.get_data().get_capacity(), sizeof_type(Type::Int));
			EXPECT_EQUAL(v.get_data().get_size(), sizeof_type(Type::Int));
			EXPECT_EQUAL(v, value);

			String const string = "42";
			EXPECT_FAIL(Variable v2(string));
		}

		TEST("T Operator")
		{
			Variable v;
			v = Variable(Int(42));
			Int value = v;
			EXPECT_EQUAL(value, 42);
			v = Variable(Float(42.0f));
			Float value2 = v;
			EXPECT_EQUAL(value2, 42.0f);
		}

		TEST("T Assignment Operator")
		{
			Variable v;
			v = Int(42);
			EXPECT_EQUAL(v, 42);
			v = Float(42.0f);
			EXPECT_EQUAL(v, 42.0f);
		}

		TEST("Equal Operator")
		{
			Variable v1, v2;
			EXPECT_TRUE(v1 == v2);
			v1 = Int(42);
			EXPECT_FALSE(v1 == v2);
			v2 = Int(42);
			EXPECT_TRUE(v1 == v2);
			v2 = Float(42.0f);
			EXPECT_FALSE(v1 == v2);
			v2 = Int(42);
			EXPECT_TRUE(v1 == v2);
		}

		TEST("Not Equal Operator")
		{
			Variable v1, v2;
			EXPECT_FALSE(v1 != v2);
			v1 = Int(42);
			EXPECT_TRUE(v1 != v2);
			v2 = Int(42);
			EXPECT_FALSE(v1 != v2);
			v2 = Float(42.0f);
			EXPECT_TRUE(v1 != v2);
			v2 = Int(42);
			EXPECT_FALSE(v1 != v2);
		}

		TEST("Equal T Operator")
		{
			Variable v;
			v = Int(42);
			EXPECT_TRUE(v == 42);
			EXPECT_FALSE(v == 42.0f);
			EXPECT_FALSE(v == String("42"));
			v = Float(42.0f);
			EXPECT_FALSE(v == 42);
			EXPECT_TRUE(v == 42.0f);
			EXPECT_FALSE(v == String("42"));
		}

		TEST("Not Equal T Operator")
		{
			Variable v;
			v = Int(42);
			EXPECT_FALSE(v != 42);
			EXPECT_TRUE(v != 42.0f);
			EXPECT_TRUE(v != String("42"));
			v = Float(42.0f);
			EXPECT_TRUE(v != 42);
			EXPECT_FALSE(v != 42.0f);
			EXPECT_TRUE(v != String("42"));
		}

		TEST("Get Type")
		{
			Variable v;
			EXPECT_EQUAL(v.get_type(), Type::Undefined);
			v = Int(42);
			EXPECT_EQUAL(v.get_type(), Type::Int);
			v = Float(42.0f);
			EXPECT_EQUAL(v.get_type(), Type::Float);
			v = nullptr;
			EXPECT_EQUAL(v.get_type(), Type::Float);
			EXPECT_TRUE(v.is_empty());
		}

		TEST("Set Type")
		{
			Variable v;
			v.set_type(Type::Int);
			EXPECT_EQUAL(v.get_type(), Type::Int);
			EXPECT_EQUAL(v.get_data().get_size(), 0);
			v.set_type(Type::Float);
			EXPECT_EQUAL(v.get_type(), Type::Float);
			EXPECT_EQUAL(v.get_data().get_size(), 0);
			v.set_type(Type::Undefined);
			EXPECT_EQUAL(v.get_type(), Type::Undefined);
			EXPECT_EQUAL(v.get_data().get_size(), 0);
		}

		TEST("Get Data")
		{
			Variable v;
			EXPECT_EQUAL(v.get_data().get_capacity(), 0);
			EXPECT_EQUAL(v.get_data().get_size(), 0);
			v = Int(42);
			EXPECT_EQUAL(v.get_data().get_capacity(), sizeof_type(Type::Int));
			EXPECT_EQUAL(v.get_data().get_size(), sizeof_type(Type::Int));
			v = Float(42.0f);
			EXPECT_EQUAL(v.get_data().get_capacity(), sizeof_type(Type::Float));
			EXPECT_EQUAL(v.get_data().get_size(), sizeof_type(Type::Float));
		}

		TEST("Set Type and Data")
		{
			Variable v;
			Int const value = 42;
			v.set_data(Type::Int, &value);
			EXPECT_EQUAL(v.get_type(), Type::Int);
			EXPECT(v.get_data().get_capacity(), >=, sizeof_type(Type::Int));
			EXPECT_EQUAL(v.get_data().get_size(), sizeof_type(Type::Int));
			Float const value2 = 42.0f;
			v.set_data(Type::Float, &value2);
			EXPECT_EQUAL(v.get_type(), Type::Float);
			EXPECT(v.get_data().get_capacity(), >=, sizeof_type(Type::Float));
			EXPECT_EQUAL(v.get_data().get_size(), sizeof_type(Type::Float));
			v.set_data(Type::Undefined, nullptr);
			EXPECT_EQUAL(v.get_type(), Type::Undefined);
			EXPECT_EQUAL(v.get_data().get_size(), 0);
		}

		TEST("Set Data")
		{
			Variable v(Type::Int);
			Int const value = 42;
			v.set_data(&value);
			EXPECT_EQUAL(v.get_data().get_capacity(), sizeof_type(Type::Int));
			EXPECT_EQUAL(v.get_data().get_size(), sizeof_type(Type::Int));
			EXPECT_EQUAL(v, value);
			Float const value2 = 42.0f;
			v.set_type(Type::Float);
			v.set_data(&value2);
			EXPECT_EQUAL(v.get_data().get_capacity(), sizeof_type(Type::Float));
			EXPECT_EQUAL(v.get_data().get_size(), sizeof_type(Type::Float));
			EXPECT_EQUAL(v, value2);
			v.set_data(nullptr);
			EXPECT_EQUAL(v.get_type(), Type::Float);
			EXPECT_EQUAL(v.get_data().get_capacity(), sizeof_type(Type::Float));
			EXPECT_EQUAL(v.get_data().get_size(), 0);
		}

		TEST("Get")
		{
			Variable v;
			v = Int(42);
			EXPECT_EQUAL(*v.get<Int>(), 42);
			EXPECT_EQUAL(v.get<Float>(), nullptr);
			v.clear();
			EXPECT_EQUAL(v.get<Int>(), nullptr);
			v = Float(42.0f);
			EXPECT_EQUAL(*v.get<Float>(), 42.0f);

			v = Variable();
			EXPECT_EQUAL(v.get<Int>(), nullptr);
		}

		TEST("Set")
		{
			Variable v;
			Int value = 42;
			v.set(value);
			EXPECT_EQUAL(v.get_type(), Type::Int);
			EXPECT_EQUAL(v.get_data().get_capacity(), sizeof_type(Type::Int));
			EXPECT_EQUAL(v.get_data().get_size(), sizeof_type(Type::Int));
			EXPECT_EQUAL(v, value);
			Float value2 = 42.0f;
			v.set(value2);
			EXPECT_EQUAL(v.get_type(), Type::Float);
			EXPECT_EQUAL(v.get_data().get_capacity(), sizeof_type(Type::Float));
			EXPECT_EQUAL(v.get_data().get_size(), sizeof_type(Type::Float));
			EXPECT_EQUAL(v, value2);
		}

		TEST("Is Empty")
		{
			Variable v;
			EXPECT_TRUE(v.is_empty());
			v = Int(42);
			EXPECT_FALSE(v.is_empty());
			v.clear();
			EXPECT_TRUE(v.is_empty());
			v = Float(42.0f);
			EXPECT_FALSE(v.is_empty());
			v.clear();
			EXPECT_TRUE(v.is_empty());
		}

		TEST("Clear")
		{
			Variable v;
			v = Int(42);
			v.clear();
			EXPECT_EQUAL(v.get_type(), Type::Int);
			EXPECT_EQUAL(v.get_data().get_size(), 0);
			v = Float(42.0f);
			v.clear();
			EXPECT_EQUAL(v.get_type(), Type::Float);
			EXPECT_EQUAL(v.get_data().get_size(), 0);
		}
	}
}
