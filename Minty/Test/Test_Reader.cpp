#include "Test_Reader.h"
#include "Minty.h"

void test_Reader(Test& _test)
{
	CATEGORY(TextFileReader)
	{
		constexpr Char const* TEST_PATH = "test.txt";

		TEST("Constructor")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			
			EXPECT_EQUAL(reader.get_source(), &file);
			EXPECT_EQUAL(reader.get_depth(), 0);

			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Get User Data")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			EXPECT_EQUAL(reader.get_user_data(), nullptr);
			Size data = 45;
			reader.push_user_data(&data);
			EXPECT_EQUAL(*static_cast<Size*>(reader.get_user_data()), data);
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Get Source")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			EXPECT_EQUAL(reader.get_source(), &file);
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Get Depth")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.indent("One");
			writer.indent("Two");
			writer.write("Three", "Four");
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			EXPECT_EQUAL(reader.get_depth(), 0);
			reader.indent(0);
			EXPECT_EQUAL(reader.get_depth(), 1);
			reader.indent(0);
			EXPECT_EQUAL(reader.get_depth(), 2);
			reader.outdent();
			EXPECT_EQUAL(reader.get_depth(), 1);
			reader.outdent();
			EXPECT_EQUAL(reader.get_depth(), 0);
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Get Node")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Node const& node = reader.get_node();
			EXPECT_EQUAL(node.get_name(), "");
			EXPECT_EQUAL(node.get_data_string(), "");
			EXPECT_EQUAL(node.get_children_size(), 0);
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Get Size")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			EXPECT_EQUAL(reader.get_size(), 0);
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Push User Data")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Size data = 45;
			reader.push_user_data(&data);
			EXPECT_EQUAL(*static_cast<Size*>(reader.get_user_data()), data);
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Pop User Data")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Size data = 45;
			reader.push_user_data(&data);
			EXPECT_EQUAL(*static_cast<Size*>(reader.get_user_data()), data);
			reader.pop_user_data();
			EXPECT_EQUAL(reader.get_user_data(), nullptr);
			EXPECT_FAIL(reader.pop_user_data());
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Indent")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", 1);
			writer.indent();
			writer.write("Two", 2);
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			EXPECT_TRUE(reader.indent(0));
			EXPECT_TRUE(reader.indent(0));
			EXPECT_FALSE(reader.indent(0));
			reader.outdent();
			reader.outdent();
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Indent Name")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", "Two");
			writer.indent("Three");
			writer.write("Four", "Five");
			writer.outdent();
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			EXPECT_TRUE(reader.indent("Three"));
			EXPECT_TRUE(reader.indent("Four"));
			EXPECT_FALSE(reader.indent("Five"));
			EXPECT_SUCCESS(reader.outdent());
			EXPECT_SUCCESS(reader.outdent());
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Outdent")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", 1);
			writer.indent();
			writer.write("Two", 2);
			writer.outdent();
			writer.write("Three", 3);
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			EXPECT_FAIL(reader.outdent());
			reader.indent(0);
			EXPECT_SUCCESS(reader.outdent());
			EXPECT_FAIL(reader.outdent());
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Name")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One");
			writer.write("Two");
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			String name;
			EXPECT_TRUE(reader.read_name(0, name));
			EXPECT_EQUAL(name, "One");
			EXPECT_TRUE(reader.read_name(1, name));
			EXPECT_EQUAL(name, "Two");
			EXPECT_FALSE(reader.read_name(2, name));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Bool")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("True", true);
			writer.write("False", false);
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Bool value;
			EXPECT_TRUE(reader.read(0, value));
			EXPECT_TRUE(value);
			EXPECT_TRUE(reader.read(1, value));
			EXPECT_FALSE(value);
			EXPECT_FALSE(reader.read(2, value));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Bool2")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			Bool2 value(true, false);
			writer.write("One", value);
			writer.write("Two", Bool2(false, true));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Bool2 result;
			EXPECT_TRUE(reader.read(0, result));
			EXPECT_EQUAL(result, value);
			EXPECT_TRUE(reader.read(1, result));
			EXPECT_EQUAL(result, Bool2(false, true));
			EXPECT_FALSE(reader.read(2, result));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Bool3")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			Bool3 value(true, false, true);
			writer.write("One", value);
			writer.write("Two", Bool3(false, true, false));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Bool3 result;
			EXPECT_TRUE(reader.read(0, result));
			EXPECT_EQUAL(result, value);
			EXPECT_TRUE(reader.read(1, result));
			EXPECT_EQUAL(result, Bool3(false, true, false));
			EXPECT_FALSE(reader.read(2, result));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Bool4")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			Bool4 value(true, false, true, false);
			writer.write("One", value);
			writer.write("Two", Bool4(false, true, false, true));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Bool4 result;
			EXPECT_TRUE(reader.read(0, result));
			EXPECT_EQUAL(result, value);
			EXPECT_TRUE(reader.read(1, result));
			EXPECT_EQUAL(result, Bool4(false, true, false, true));
			EXPECT_FALSE(reader.read(2, result));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Char")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("A", 'A');
			writer.write("B", 'B');
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Char value;
			EXPECT_TRUE(reader.read(0, value));
			EXPECT_EQUAL(value, 'A');
			EXPECT_TRUE(reader.read(1, value));
			EXPECT_EQUAL(value, 'B');
			EXPECT_FALSE(reader.read(2, value));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Byte")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", Byte(1));
			writer.write("Two", Byte(2));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Byte value;
			EXPECT_TRUE(reader.read(0, value));
			EXPECT_EQUAL(value, Byte(1));
			EXPECT_TRUE(reader.read(1, value));
			EXPECT_EQUAL(value, Byte(2));
			EXPECT_FALSE(reader.read(2, value));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Short")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", Short(1));
			writer.write("Two", Short(2));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Short value;
			EXPECT_TRUE(reader.read(0, value));
			EXPECT_EQUAL(value, Short(1));
			EXPECT_TRUE(reader.read(1, value));
			EXPECT_EQUAL(value, Short(2));
			EXPECT_FALSE(reader.read(2, value));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read UShort")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", UShort(1));
			writer.write("Two", UShort(2));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			UShort value;
			EXPECT_TRUE(reader.read(0, value));
			EXPECT_EQUAL(value, UShort(1));
			EXPECT_TRUE(reader.read(1, value));
			EXPECT_EQUAL(value, UShort(2));
			EXPECT_FALSE(reader.read(2, value));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Int")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", 1);
			writer.write("Two", 2);
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Int value;
			EXPECT_TRUE(reader.read(0, value));
			EXPECT_EQUAL(value, 1);
			EXPECT_TRUE(reader.read(1, value));
			EXPECT_EQUAL(value, 2);
			EXPECT_FALSE(reader.read(2, value));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Int2")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			Int2 value(1, 2);
			writer.write("One", value);
			writer.write("Two", Int2(3, 4));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Int2 result;
			EXPECT_TRUE(reader.read(0, result));
			EXPECT_EQUAL(result, value);
			EXPECT_TRUE(reader.read(1, result));
			EXPECT_EQUAL(result, Int2(3, 4));
			EXPECT_FALSE(reader.read(2, result));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Int3")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			Int3 value(1, 2, 3);
			writer.write("One", value);
			writer.write("Two", Int3(4, 5, 6));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Int3 result;
			EXPECT_TRUE(reader.read(0, result));
			EXPECT_EQUAL(result, value);
			EXPECT_TRUE(reader.read(1, result));
			EXPECT_EQUAL(result, Int3(4, 5, 6));
			EXPECT_FALSE(reader.read(2, result));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Int4")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			Int4 value(1, 2, 3, 4);
			writer.write("One", value);
			writer.write("Two", Int4(5, 6, 7, 8));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Int4 result;
			EXPECT_TRUE(reader.read(0, result));
			EXPECT_EQUAL(result, value);
			EXPECT_TRUE(reader.read(1, result));
			EXPECT_EQUAL(result, Int4(5, 6, 7, 8));
			EXPECT_FALSE(reader.read(2, result));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read UInt")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", UInt(1));
			writer.write("Two", UInt(2));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			UInt value;
			EXPECT_TRUE(reader.read(0, value));
			EXPECT_EQUAL(value, UInt(1));
			EXPECT_TRUE(reader.read(1, value));
			EXPECT_EQUAL(value, UInt(2));
			EXPECT_FALSE(reader.read(2, value));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read UInt2")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			UInt2 value(1, 2);
			writer.write("One", value);
			writer.write("Two", UInt2(3, 4));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			UInt2 result;
			EXPECT_TRUE(reader.read(0, result));
			EXPECT_EQUAL(result, value);
			EXPECT_TRUE(reader.read(1, result));
			EXPECT_EQUAL(result, UInt2(3, 4));
			EXPECT_FALSE(reader.read(2, result));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read UInt3")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			UInt3 value(1, 2, 3);
			writer.write("One", value);
			writer.write("Two", UInt3(4, 5, 6));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			UInt3 result;
			EXPECT_TRUE(reader.read(0, result));
			EXPECT_EQUAL(result, value);
			EXPECT_TRUE(reader.read(1, result));
			EXPECT_EQUAL(result, UInt3(4, 5, 6));
			EXPECT_FALSE(reader.read(2, result));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read UInt4")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			UInt4 value(1, 2, 3, 4);
			writer.write("One", value);
			writer.write("Two", UInt4(5, 6, 7, 8));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			UInt4 result;
			EXPECT_TRUE(reader.read(0, result));
			EXPECT_EQUAL(result, value);
			EXPECT_TRUE(reader.read(1, result));
			EXPECT_EQUAL(result, UInt4(5, 6, 7, 8));
			EXPECT_FALSE(reader.read(2, result));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Long")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", Long(1));
			writer.write("Two", Long(2));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Long value;
			EXPECT_TRUE(reader.read(0, value));
			EXPECT_EQUAL(value, Long(1));
			EXPECT_TRUE(reader.read(1, value));
			EXPECT_EQUAL(value, Long(2));
			EXPECT_FALSE(reader.read(2, value));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read ULong")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", ULong(1));
			writer.write("Two", ULong(2));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			ULong value;
			EXPECT_TRUE(reader.read(0, value));
			EXPECT_EQUAL(value, ULong(1));
			EXPECT_TRUE(reader.read(1, value));
			EXPECT_EQUAL(value, ULong(2));
			EXPECT_FALSE(reader.read(2, value));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Float")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", 1.0f);
			writer.write("Two", 2.0f);
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Float value;
			EXPECT_TRUE(reader.read(0, value));
			EXPECT_EQUAL(value, 1.0f);
			EXPECT_TRUE(reader.read(1, value));
			EXPECT_EQUAL(value, 2.0f);
			EXPECT_FALSE(reader.read(2, value));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Float2")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			Float2 value(1.0f, 2.0f);
			writer.write("One", value);
			writer.write("Two", Float2(3.0f, 4.0f));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Float2 result;
			EXPECT_TRUE(reader.read(0, result));
			EXPECT_EQUAL(result, value);
			EXPECT_TRUE(reader.read(1, result));
			EXPECT_EQUAL(result, Float2(3.0f, 4.0f));
			EXPECT_FALSE(reader.read(2, result));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Float3")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			Float3 value(1.0f, 2.0f, 3.0f);
			writer.write("One", value);
			writer.write("Two", Float3(4.0f, 5.0f, 6.0f));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Float3 result;
			EXPECT_TRUE(reader.read(0, result));
			EXPECT_EQUAL(result, value);
			EXPECT_TRUE(reader.read(1, result));
			EXPECT_EQUAL(result, Float3(4.0f, 5.0f, 6.0f));
			EXPECT_FALSE(reader.read(2, result));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Float4")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			Float4 value(1.0f, 2.0f, 3.0f, 4.0f);
			writer.write("One", value);
			writer.write("Two", Float4(5.0f, 6.0f, 7.0f, 8.0f));
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Float4 result;
			EXPECT_TRUE(reader.read(0, result));
			EXPECT_EQUAL(result, value);
			EXPECT_TRUE(reader.read(1, result));
			EXPECT_EQUAL(result, Float4(5.0f, 6.0f, 7.0f, 8.0f));
			EXPECT_FALSE(reader.read(2, result));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Double")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", 1.0);
			writer.write("Two", 2.0);
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Double value;
			EXPECT_TRUE(reader.read(0, value));
			EXPECT_EQUAL(value, 1.0);
			EXPECT_TRUE(reader.read(1, value));
			EXPECT_EQUAL(value, 2.0);
			EXPECT_FALSE(reader.read(2, value));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read String")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", "Two");
			writer.write("Three", "Four");
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			String value;
			EXPECT_TRUE(reader.read(0, value));
			EXPECT_EQUAL(value, "Two");
			EXPECT_TRUE(reader.read(1, value));
			EXPECT_EQUAL(value, "Four");
			EXPECT_FALSE(reader.read(2, value));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Type")
		{
			File::create(TEST_PATH);
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", Type::Bool);
			writer.write("Two", Type::Char);
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			Type value;
			EXPECT_TRUE(reader.read(0, value));
			EXPECT_EQUAL(value, Type::Bool);
			EXPECT_TRUE(reader.read(1, value));
			EXPECT_EQUAL(value, Type::Char);
			EXPECT_FALSE(reader.read(2, value));
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Serializable")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			UUID one = UUID::create();
			UUID two = UUID::create();
			writer.write("One", one);
			writer.write("Two", two);
			file.close();
			file.open(TEST_PATH, File::Flags::Read);
			TextFileReader reader(&file);
			UUID value;
			EXPECT_TRUE(reader.read(0, value));
			EXPECT_EQUAL(value, one);
			EXPECT_TRUE(reader.read(1, value));
			EXPECT_EQUAL(value, two);
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Read Serializable Object")
		{

		}
	}
}
