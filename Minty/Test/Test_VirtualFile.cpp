#include "Test_VirtualFile.h"
#include "Minty.h"

void test_VirtualFile(Test& _test)
{
	CATEGORY(VirtualFile)
	{
		Path const TEST_FILE_PATH = "Assets/test.txt";
		char const* const TEST_TEXT = "This is part of file 1. This is part of file 2.";
		size_t const TEST_TEXT_LENGTH = strlen(TEST_TEXT);
		size_t const TEST_TEXT_SIZE = sizeof(Char) * TEST_TEXT_LENGTH;
		char const* const TEST_TEXT_1 = "This is part of file 1. ";
		size_t const TEST_TEXT_1_LENGTH = 24;
		size_t const TEST_TEXT_1_SIZE = sizeof(Char) * TEST_TEXT_1_LENGTH;
		char const* const TEST_TEXT_2 = "This is part of file 2.";
		size_t const TEST_TEXT_2_LENGTH = 23;
		size_t const TEST_TEXT_2_SIZE = sizeof(Char) * TEST_TEXT_2_LENGTH;

#define RESET_FILE() { PhysicalFile _file(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate); _file.write(TEST_TEXT, TEST_TEXT_SIZE); _file.close(); }

		RESET_FILE();

		TEST("Default Constructor")
		{
			VirtualFile file;
			EXPECT_TRUE(file.get_path().is_empty());
			EXPECT_TRUE(file.get_flags() == File::Flags::None);
			EXPECT_TRUE(file.is_open() == false);
		}

		TEST("Open Constructor")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			EXPECT_TRUE(file.get_path().is_empty() == false);
			EXPECT_TRUE(file.get_flags() == File::Flags::Read);
			EXPECT_TRUE(file.is_open() == true);
			EXPECT_TRUE(file.get_virtual_offset() == 0);
			EXPECT_TRUE(file.get_virtual_size() == TEST_TEXT_1_LENGTH);
			file = VirtualFile(TEST_FILE_PATH, File::Flags::Read, TEST_TEXT_1_LENGTH, TEST_TEXT_2_LENGTH);
			EXPECT_TRUE(file.get_path().is_empty() == false);
			EXPECT_TRUE(file.get_flags() == File::Flags::Read);
			EXPECT_TRUE(file.is_open() == true);
			EXPECT_TRUE(file.get_virtual_offset() == TEST_TEXT_1_LENGTH);
			EXPECT_TRUE(file.get_virtual_size() == TEST_TEXT_2_LENGTH);
		}

		TEST("Get Path")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			EXPECT_TRUE(file.get_path() == TEST_FILE_PATH);
		}

		TEST("Get Flags")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			EXPECT_TRUE(file.get_flags() == File::Flags::Read);
		}

		TEST("Get Size")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			EXPECT_TRUE(file.get_size() == TEST_TEXT_1_LENGTH);
			file.open(TEST_FILE_PATH, File::Flags::Read, TEST_TEXT_1_LENGTH, TEST_TEXT_2_LENGTH);
			EXPECT_TRUE(file.get_size() == TEST_TEXT_2_LENGTH);
		}

		TEST("Get Virtual Offset")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			EXPECT_TRUE(file.get_virtual_offset() == 0);
			file.open(TEST_FILE_PATH, File::Flags::Read, TEST_TEXT_1_LENGTH, TEST_TEXT_2_LENGTH);
			EXPECT_TRUE(file.get_virtual_offset() == TEST_TEXT_1_LENGTH);
		}

		TEST("Get Virtual Size")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			EXPECT_TRUE(file.get_virtual_size() == TEST_TEXT_1_LENGTH);
			file.open(TEST_FILE_PATH, File::Flags::Read, TEST_TEXT_1_LENGTH, TEST_TEXT_2_LENGTH);
			EXPECT_TRUE(file.get_virtual_size() == TEST_TEXT_2_LENGTH);
		}

		TEST("Is Open")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			EXPECT_TRUE(file.is_open() == true);
			file.close();
			EXPECT_TRUE(file.is_open() == false);
		}

		TEST("Open")
		{
			VirtualFile file;
			EXPECT_SUCCESS(file.open(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH));
			EXPECT_TRUE(file.get_path() == TEST_FILE_PATH);
			EXPECT_TRUE(file.get_flags() == File::Flags::Read);
			EXPECT_TRUE(file.is_open() == true);
			EXPECT_TRUE(file.get_virtual_offset() == 0);
			EXPECT_TRUE(file.get_virtual_size() == TEST_TEXT_1_LENGTH);
			EXPECT_SUCCESS(file.open(TEST_FILE_PATH, File::Flags::ReadWrite, TEST_TEXT_1_LENGTH, TEST_TEXT_2_LENGTH));
			EXPECT_TRUE(file.get_path() == TEST_FILE_PATH);
			EXPECT_TRUE(file.get_flags() == File::Flags::ReadWrite);
			EXPECT_TRUE(file.is_open() == true);
			EXPECT_TRUE(file.get_virtual_offset() == TEST_TEXT_1_LENGTH);
			EXPECT_TRUE(file.get_virtual_size() == TEST_TEXT_2_LENGTH);

			EXPECT_FAIL(file.open(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate, 0, TEST_TEXT_1_LENGTH));
			EXPECT_FAIL(file.open(TEST_FILE_PATH, File::Flags::Append, 0, TEST_TEXT_1_LENGTH));
			EXPECT_FAIL(file.open(TEST_FILE_PATH, File::Flags::Write, 0, TEST_TEXT_1_LENGTH));
		}

		TEST("Flush")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::ReadWrite, 0, TEST_TEXT_1_LENGTH);
			String test('X', TEST_TEXT_1_LENGTH);
			file.write(test.get_data(), TEST_TEXT_1_LENGTH);
			file.flush();
			VirtualFile file2(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			String read;
			read.resize(TEST_TEXT_1_LENGTH);
			file2.read(read.get_data(), TEST_TEXT_1_LENGTH);
			EXPECT_TRUE(read == test);

			file.close();
			file2.close();

			RESET_FILE();
		}

		TEST("Close")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			file.close();
			EXPECT_TRUE(file.is_open() == false);
		}

		TEST("Seek")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			file.seek(0);
			EXPECT_TRUE(file.tell() == 0);
			file.seek(1);
			EXPECT_TRUE(file.tell() == 1);
			file.seek(0, File::Direction::End);
			EXPECT_TRUE(file.tell() == TEST_TEXT_1_LENGTH);
			file.seek(-1, File::Direction::End);
			EXPECT_TRUE(file.tell() == TEST_TEXT_1_LENGTH - 1);
		}

		TEST("Seek Read")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			file.seek_read(0);
			EXPECT_TRUE(file.tell_read() == 0);
			file.seek_read(1);
			EXPECT_TRUE(file.tell_read() == 1);
			file.seek_read(0, File::Direction::End);
			EXPECT_TRUE(file.tell_read() == TEST_TEXT_1_LENGTH);
			file.seek_read(-1, File::Direction::End);
			EXPECT_TRUE(file.tell_read() == TEST_TEXT_1_LENGTH - 1);
		}

		TEST("Seek Write")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::ReadWrite, 0, TEST_TEXT_1_LENGTH);
			file.seek_write(0);
			EXPECT_TRUE(file.tell_write() == 0);
			file.seek_write(1);
			EXPECT_TRUE(file.tell_write() == 1);
			file.seek_write(0, File::Direction::End);
			EXPECT_TRUE(file.tell_write() == TEST_TEXT_1_LENGTH);
			file.seek_write(-1, File::Direction::End);
			EXPECT_TRUE(file.tell_write() == TEST_TEXT_1_LENGTH - 1);

			RESET_FILE();
		}

		TEST("End Of File")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			EXPECT_TRUE(file.end_of_file() == false);
			String line;
			while (file.read_line(line)) { }
			EXPECT_TRUE(file.end_of_file() == true);
		}

		TEST("Tell")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			EXPECT_TRUE(file.tell() == 0);
			file.seek(1);
			EXPECT_TRUE(file.tell() == 1);
			file.seek(0, File::Direction::End);
			EXPECT_TRUE(file.tell() == TEST_TEXT_1_LENGTH);
			file.seek(-1, File::Direction::End);
			EXPECT_TRUE(file.tell() == TEST_TEXT_1_LENGTH - 1);
		}

		TEST("Tell Read")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			EXPECT_TRUE(file.tell_read() == 0);
			file.seek_read(1);
			EXPECT_TRUE(file.tell_read() == 1);
			file.seek_read(0, File::Direction::End);
			EXPECT_TRUE(file.tell_read() == TEST_TEXT_1_LENGTH);
			file.seek_read(-1, File::Direction::End);
			EXPECT_TRUE(file.tell_read() == TEST_TEXT_1_LENGTH - 1);
		}

		TEST("Tell Write")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::ReadWrite, 0, TEST_TEXT_1_LENGTH);
			EXPECT_TRUE(file.tell_write() == 0);
			file.seek_write(1);
			EXPECT_TRUE(file.tell_write() == 1);
			file.seek_write(0, File::Direction::End);
			EXPECT_TRUE(file.tell_write() == TEST_TEXT_1_LENGTH);
			file.seek_write(-1, File::Direction::End);
			EXPECT_TRUE(file.tell_write() == TEST_TEXT_1_LENGTH - 1);

			RESET_FILE();
		}

		TEST("Peek")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			EXPECT_TRUE(file.peek() == TEST_TEXT[0]);
			file.seek(1);
			EXPECT_TRUE(file.peek() == TEST_TEXT[1]);
			file.seek(0, File::Direction::End);
			EXPECT_TRUE(file.peek() == '\0');
			file.seek(-1, File::Direction::End);
			EXPECT_TRUE(file.peek() == TEST_TEXT[TEST_TEXT_1_LENGTH - 1]);
		}

		TEST("Read")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			EXPECT_TRUE(file.read() == TEST_TEXT[0]);
			EXPECT_TRUE(file.read() == TEST_TEXT[1]);
			file.seek(-1, File::Direction::End);
			EXPECT_TRUE(file.read() == TEST_TEXT[TEST_TEXT_1_LENGTH - 1]);
			EXPECT_TRUE(file.read() == '\0');
		}

		TEST("Read Buffer")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			char buffer[TEST_TEXT_1_SIZE];
			file.read(buffer, TEST_TEXT_1_SIZE);
			EXPECT_TRUE(memcmp(buffer, TEST_TEXT_1, TEST_TEXT_1_SIZE) == 0);
		}

		TEST("Read Line")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH);
			String line;
			file.read_line(line);
			EXPECT_TRUE(line == TEST_TEXT_1);
		}

		TEST("Write")
		{
			VirtualFile file(TEST_FILE_PATH, File::Flags::ReadWrite, 0, TEST_TEXT_1_LENGTH);
			file.write(TEST_TEXT_1, TEST_TEXT_1_SIZE);
			file.flush();
			file.seek(0);
			char buffer[TEST_TEXT_1_SIZE];
			file.read(buffer, TEST_TEXT_1_SIZE);
			EXPECT_TRUE(memcmp(buffer, TEST_TEXT_1, TEST_TEXT_1_SIZE) == 0);

			RESET_FILE();
		}

#undef RESET_FILE
	}
}
