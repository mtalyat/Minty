#include "Test_PhysicalFile.h"
#include "Minty.h"

void test_PhysicalFile(Test& _test)
{
	CATEGORY(PhysicalFile)
	{
		Path const TEST_FILE_PATH = "Assets/test.txt";
		char const* const TEST_TEXT = "Hello, World!";
		size_t const TEST_TEXT_LENGTH = strlen(TEST_TEXT);
		size_t const TEST_TEXT_SIZE = sizeof(Char) * TEST_TEXT_LENGTH;

		TEST("Default Constructor")
		{
			PhysicalFile file;
			EXPECT_TRUE(file.get_path().is_empty());
			EXPECT_TRUE(file.get_flags() == File::Flags::None);
			EXPECT_TRUE(file.is_open() == false);
		}

		TEST("Open Constructor")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Read);
			EXPECT_TRUE(file.get_path().is_empty() == false);
			EXPECT_TRUE(file.get_flags() == File::Flags::Read);
			EXPECT_TRUE(file.is_open() == true);
		}

		TEST("Get Path")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Read);
			EXPECT_TRUE(file.get_path() == TEST_FILE_PATH);
		}

		TEST("Get Flags")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Read);
			EXPECT_TRUE(file.get_flags() == File::Flags::Read);
			PhysicalFile file2;
			EXPECT_TRUE(file2.get_flags() == File::Flags::None);
		}

		TEST("Get Size")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate);
			file.close();
			PhysicalFile file2(TEST_FILE_PATH, File::Flags::Write);
			EXPECT_TRUE(file2.get_size() == 0);
			file2.write(TEST_TEXT, TEST_TEXT_SIZE);
			file2.flush();
			EXPECT_TRUE(file2.get_size() == TEST_TEXT_LENGTH);
			file2.close();
			PhysicalFile file3(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate);
			file3.close();
			PhysicalFile file4(TEST_FILE_PATH, File::Flags::Read);
			EXPECT_TRUE(file4.get_size() == 0);
			file4.close();
		}

		TEST("Is Open")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Read);
			EXPECT_TRUE(file.is_open() == true);
			file.close();
			EXPECT_TRUE(file.is_open() == false);
			PhysicalFile file2;
			EXPECT_TRUE(file2.is_open() == false);
			file.open(TEST_FILE_PATH, File::Flags::Read);
			EXPECT_TRUE(file.is_open() == true);
		}

		TEST("Open")
		{
			PhysicalFile file;
			file.open(TEST_FILE_PATH, File::Flags::Read);
			EXPECT_TRUE(file.get_path() == TEST_FILE_PATH);
			EXPECT_TRUE(file.get_flags() == File::Flags::Read);
			EXPECT_TRUE(file.is_open() == true);
			file.open(TEST_FILE_PATH, File::Flags::Read);
			EXPECT_TRUE(file.get_path() == TEST_FILE_PATH);
			EXPECT_TRUE(file.get_flags() == File::Flags::Read);
			EXPECT_TRUE(file.is_open() == true);
			file.close();
			EXPECT_TRUE(file.is_open() == false);
		}

		TEST("Flush")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate);
			file.write(TEST_TEXT, TEST_TEXT_SIZE);
			file.flush();
			file.close();
			PhysicalFile file2(TEST_FILE_PATH, File::Flags::Read);
			EXPECT_TRUE(file2.get_size() == TEST_TEXT_LENGTH);
			file2.close();
		}

		TEST("Close")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Read);
			file.close();
			EXPECT_TRUE(file.is_open() == false);
		}

		TEST("Seek")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate);
			file.write(TEST_TEXT, TEST_TEXT_SIZE);
			file.close();
			PhysicalFile file2(TEST_FILE_PATH, File::Flags::Read);
			file2.seek(0, File::Direction::End);
			EXPECT_TRUE(file2.tell() == TEST_TEXT_LENGTH);
			file2.seek(0, File::Direction::Begin);
			EXPECT_TRUE(file2.tell() == 0);
			file2.seek(0, File::Direction::Current);
			EXPECT_TRUE(file2.tell() == 0);
			file2.seek(0, File::Direction::End);
			EXPECT_TRUE(file2.tell() == TEST_TEXT_LENGTH);
			file2.close();
		}

		TEST("Seek Read")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate);
			file.write(TEST_TEXT, TEST_TEXT_SIZE);
			file.close();
			PhysicalFile file2(TEST_FILE_PATH, File::Flags::Read);
			file2.seek_read(0, File::Direction::End);
			EXPECT_TRUE(file2.tell_read() == TEST_TEXT_LENGTH);
			file2.seek_read(0, File::Direction::Begin);
			EXPECT_TRUE(file2.tell_read() == 0);
			file2.seek_read(0, File::Direction::Current);
			EXPECT_TRUE(file2.tell_read() == 0);
			file2.seek_read(0, File::Direction::End);
			EXPECT_TRUE(file2.tell_read() == TEST_TEXT_LENGTH);
			file2.close();
		}

		TEST("Seek Write")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate);
			file.write(TEST_TEXT, TEST_TEXT_SIZE);
			file.close();
			PhysicalFile file2(TEST_FILE_PATH, File::Flags::Write);
			file2.write(TEST_TEXT, TEST_TEXT_SIZE);
			file2.seek_write(0, File::Direction::End);
			EXPECT_TRUE(file2.tell_write() == TEST_TEXT_LENGTH);
			file2.seek_write(0, File::Direction::Begin);
			EXPECT_TRUE(file2.tell_write() == 0);
			file2.seek_write(0, File::Direction::Current);
			EXPECT_TRUE(file2.tell_write() == 0);
			file2.seek_write(0, File::Direction::End);
			EXPECT_TRUE(file2.tell_write() == TEST_TEXT_LENGTH);
			file2.close();
		}

		TEST("End Of File")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate);
			file.write(TEST_TEXT, TEST_TEXT_SIZE);
			file.close();
			PhysicalFile file2(TEST_FILE_PATH, File::Flags::Read);
			EXPECT_TRUE(file2.end_of_file() == false);
			String line;
			while (file2.read_line(line)) {}
			EXPECT_TRUE(file2.end_of_file() == true);
			file2.close();
		}

		TEST("Tell")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate);
			file.write(TEST_TEXT, TEST_TEXT_SIZE);
			file.close();
			PhysicalFile file2(TEST_FILE_PATH, File::Flags::Read);
			EXPECT_TRUE(file2.tell() == 0);
			file2.seek(0, File::Direction::End);
			EXPECT_TRUE(file2.tell() == TEST_TEXT_SIZE);
			file2.seek(0, File::Direction::Begin);
			EXPECT_TRUE(file2.tell() == 0);
			file2.seek(0, File::Direction::Current);
			EXPECT_TRUE(file2.tell() == 0);
			file2.seek(0, File::Direction::End);
			EXPECT_TRUE(file2.tell() == TEST_TEXT_SIZE);
			file2.close();
		}

		TEST("Tell Read")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate);
			file.write(TEST_TEXT, TEST_TEXT_SIZE);
			file.close();
			PhysicalFile file2(TEST_FILE_PATH, File::Flags::Read);
			EXPECT_TRUE(file2.tell_read() == 0);
			file2.seek_read(0, File::Direction::End);
			EXPECT_TRUE(file2.tell_read() == TEST_TEXT_SIZE);
			file2.seek_read(0, File::Direction::Begin);
			EXPECT_TRUE(file2.tell_read() == 0);
			file2.seek_read(0, File::Direction::Current);
			EXPECT_TRUE(file2.tell_read() == 0);
			file2.seek_read(0, File::Direction::End);
			EXPECT_TRUE(file2.tell_read() == TEST_TEXT_SIZE);
			file2.close();
		}

		TEST("Tell Write")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate);
			file.write(TEST_TEXT, TEST_TEXT_SIZE);
			file.close();
			PhysicalFile file2(TEST_FILE_PATH, File::Flags::Write);
			file2.write(TEST_TEXT, TEST_TEXT_SIZE);
			EXPECT_TRUE(file2.tell_write() == TEST_TEXT_SIZE);
			file2.seek_write(0, File::Direction::End);
			EXPECT_TRUE(file2.tell_write() == TEST_TEXT_SIZE);
			file2.seek_write(0, File::Direction::Begin);
			EXPECT_TRUE(file2.tell_write() == 0);
			file2.seek_write(0, File::Direction::Current);
			EXPECT_TRUE(file2.tell_write() == 0);
			file2.seek_write(0, File::Direction::End);
			EXPECT_TRUE(file2.tell_write() == TEST_TEXT_SIZE);
			file2.close();
		}

		TEST("Peek")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate);
			file.write(TEST_TEXT, TEST_TEXT_SIZE);
			file.close();
			PhysicalFile file2(TEST_FILE_PATH, File::Flags::Read);
			EXPECT_TRUE(file2.peek() == 'H');
			file2.seek(0, File::Direction::End);
			EXPECT_TRUE(file2.peek() == '\0');
			file2.close();
		}

		TEST("Read Char")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate);
			char const* const text = TEST_TEXT;
			size_t const textLength = strlen(text);
			size_t const textSize = sizeof(Char) * textLength;
			file.write(text, textSize);
			file.close();
			PhysicalFile file2(TEST_FILE_PATH, File::Flags::Read);
			for (size_t i = 0; i < textLength; ++i)
			{
				EXPECT_TRUE(file2.read() == text[i]);
			}
			file2.close();
		}

		TEST("Read Buffer")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate);
			char const* const text = TEST_TEXT;
			size_t const textLength = strlen(text);
			size_t const textSize = sizeof(Char) * textLength;
			file.write(text, textSize);
			file.close();
			PhysicalFile file2(TEST_FILE_PATH, File::Flags::Read);
			char buffer[256];
			file2.read(buffer, textSize);
			for (size_t i = 0; i < textLength; ++i)
			{
				EXPECT_TRUE(buffer[i] == text[i]);
			}
			file2.close();
		}

		TEST("Read Line")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate);
			file.write("Hello, World!\n", sizeof(Char) * 14);
			file.close();
			PhysicalFile file2(TEST_FILE_PATH, File::Flags::Read);
			String line;
			EXPECT_TRUE(file2.read_line(line) == true);
			EXPECT_TRUE(line == TEST_TEXT);
			file2.close();
			PhysicalFile file3(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate);
			file.close();
			PhysicalFile file4(TEST_FILE_PATH, File::Flags::Read);
			EXPECT_TRUE(file4.read_line(line) == false);
			file4.close();
		}

		TEST("Write")
		{
			PhysicalFile file(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate);
			file.write(TEST_TEXT, TEST_TEXT_SIZE);
			file.close();
			PhysicalFile file2(TEST_FILE_PATH, File::Flags::Read);
			char buffer[256];
			memset(buffer, 0, 256);
			file2.read(buffer, TEST_TEXT_LENGTH);
			EXPECT_TRUE(strcmp(buffer, TEST_TEXT) == 0);
			file2.close();
		}
	}
}
