#include "Test_Writer.h"
#include "Minty.h"

void test_Writer(Test& _test)
{
	CATEGORY(TextFileWriter)
	{
		constexpr Char const* TEST_PATH = "test.txt";

		TEST("Constructor")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);

			EXPECT_EQUAL(writer.get_source(), &file);
			EXPECT_EQUAL(writer.get_depth(), 0);

			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Get User Data")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			EXPECT_EQUAL(writer.get_user_data(), nullptr);
			Size data = 45;
			writer.push_user_data(&data);
			EXPECT_EQUAL(*static_cast<Size*>(writer.get_user_data()), data);

			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Get Source")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			EXPECT_EQUAL(writer.get_source(), &file);

			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Get Depth")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			EXPECT_EQUAL(writer.get_depth(), 0);
			writer.indent();
			EXPECT_EQUAL(writer.get_depth(), 1);
			writer.indent();
			EXPECT_EQUAL(writer.get_depth(), 2);
			writer.outdent();
			EXPECT_EQUAL(writer.get_depth(), 1);
			writer.outdent();
			EXPECT_EQUAL(writer.get_depth(), 0);

			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Push User Data")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			Size data = 45;
			writer.push_user_data(&data);
			EXPECT_EQUAL(*static_cast<Size*>(writer.get_user_data()), data);
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Pop User Data")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			Size data = 45;
			writer.push_user_data(&data);
			EXPECT_EQUAL(*static_cast<Size*>(writer.get_user_data()), data);
			writer.pop_user_data();
			EXPECT_EQUAL(writer.get_user_data(), nullptr);
			EXPECT_FAILURE(writer.pop_user_data());
			file.close();
			File::destroy(TEST_PATH);
		}

		TEST("Indent")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", "Two");
			writer.indent();
			writer.write("Three", "Four");
			writer.outdent();
			file.close();

			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: Two\n\tThree: Four\n");

			File::destroy(TEST_PATH);
		}

		TEST("Indent Name")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", "Two");
			writer.indent("Three");
			writer.write("Four", "Five");
			writer.outdent();
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: Two\nThree\n\tFour: Five\n");
			File::destroy(TEST_PATH);
		}

		TEST("Outdent")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", "Two");
			writer.indent();
			writer.write("Three", "Four");
			writer.outdent();
			writer.write("Five", "Six");
			EXPECT_FAILURE(writer.outdent());
			file.close();

			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: Two\n\tThree: Four\nFive: Six\n");

			File::destroy(TEST_PATH);
		}

		TEST("Write Name")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One");
			writer.write("Two");
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One\nTwo\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Bool")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", true);
			writer.write("Two", false);
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: T\nTwo: F\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Bool2")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", Bool2(true, false));
			writer.write("Two", Bool2(false, true));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: (T, F)\nTwo: (F, T)\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Bool3")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", Bool3(true, false, true));
			writer.write("Two", Bool3(false, true, false));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: (T, F, T)\nTwo: (F, T, F)\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Bool4")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", Bool4(true, false, true, false));
			writer.write("Two", Bool4(false, true, false, true));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: (T, F, T, F)\nTwo: (F, T, F, T)\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Char")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", 'A');
			writer.write("Two", 'B');
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: A\nTwo: B\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Byte")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", Byte(1));
			writer.write("Two", Byte(2));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: 1\nTwo: 2\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Short")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", Short(1));
			writer.write("Two", Short(2));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: 1\nTwo: 2\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write UShort")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", UShort(1));
			writer.write("Two", UShort(2));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: 1\nTwo: 2\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Int")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", 1);
			writer.write("Two", 2);
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: 1\nTwo: 2\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Int2")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", Int2(1, 2));
			writer.write("Two", Int2(3, 4));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: (1, 2)\nTwo: (3, 4)\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Int3")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", Int3(1, 2, 3));
			writer.write("Two", Int3(4, 5, 6));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: (1, 2, 3)\nTwo: (4, 5, 6)\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Int4")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", Int4(1, 2, 3, 4));
			writer.write("Two", Int4(5, 6, 7, 8));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: (1, 2, 3, 4)\nTwo: (5, 6, 7, 8)\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write UInt")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", UInt(1));
			writer.write("Two", UInt(2));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: 1\nTwo: 2\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write UInt2")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", UInt2(1, 2));
			writer.write("Two", UInt2(3, 4));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: (1, 2)\nTwo: (3, 4)\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write UInt3")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", UInt3(1, 2, 3));
			writer.write("Two", UInt3(4, 5, 6));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: (1, 2, 3)\nTwo: (4, 5, 6)\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write UInt4")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", UInt4(1, 2, 3, 4));
			writer.write("Two", UInt4(5, 6, 7, 8));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: (1, 2, 3, 4)\nTwo: (5, 6, 7, 8)\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Long")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", Long(1));
			writer.write("Two", Long(2));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: 1\nTwo: 2\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write ULong")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", ULong(1));
			writer.write("Two", ULong(2));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: 1\nTwo: 2\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Float")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", 1.0f);
			writer.write("Two", 2.0f);
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: 1\nTwo: 2\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Float2")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", Float2(1.0f, 2.0f));
			writer.write("Two", Float2(3.0f, 4.0f));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: (1, 2)\nTwo: (3, 4)\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Float3")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", Float3(1.0f, 2.0f, 3.0f));
			writer.write("Two", Float3(4.0f, 5.0f, 6.0f));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: (1, 2, 3)\nTwo: (4, 5, 6)\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Float4")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", Float4(1.0f, 2.0f, 3.0f, 4.0f));
			writer.write("Two", Float4(5.0f, 6.0f, 7.0f, 8.0f));
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: (1, 2, 3, 4)\nTwo: (5, 6, 7, 8)\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Double")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", 1.0);
			writer.write("Two", 2.0);
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: 1\nTwo: 2\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write String")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", "Two");
			writer.write("Three", "Four");
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: Two\nThree: Four\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Type")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			writer.write("One", Type::Bool);
			writer.write("Two", Type::Char);
			file.close();
			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "One: Bool\nTwo: Char\n");
			File::destroy(TEST_PATH);
		}

		TEST("Write Serializable")
		{
			PhysicalFile file(TEST_PATH, File::Flags::Write);
			TextFileWriter writer(&file);
			UUID one = UUID::create();
			UUID two = UUID::create();
			writer.write("One", one);
			writer.write("Two", two);
			file.close();
			String text = File::read_text(TEST_PATH);
			String expected = String("One: ").append(to_string(one)).append("\nTwo: ").append(to_string(two)).append("\n");
			EXPECT_EQUAL(text, expected);
			File::destroy(TEST_PATH);
		}

		TEST("Write Serializable Object")
		{

		}
	}
}
