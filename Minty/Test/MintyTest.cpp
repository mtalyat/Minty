// MintyTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Minty.h>
#include <unordered_map>

using namespace Minty;

struct Results
{
	int category;
	int passes;
	int fails;
};

class DualStreamBuffer : public std::streambuf {
public:
	DualStreamBuffer(std::streambuf* originalBuffer, std::ostream& secondStream)
		: originalBuffer(originalBuffer), secondStream(secondStream.rdbuf()) {}

protected:
	virtual int overflow(int ch) override {
		if (ch != EOF) {
			originalBuffer->sputc(ch); // Write to original stdout
			secondStream->sputc(ch);   // Write to additional stream
		}
		return ch;
	}

private:
	std::streambuf* originalBuffer;
	std::streambuf* secondStream;
};

// runs all of the tests
static void run_tests()
{
#pragma region Test Setup

	// keep track of results
	std::unordered_map<std::string, int> categories;
	std::unordered_map<int, Results> results;

	// variables used for tests
	char const* currentName = nullptr;
	char const* currentCategoryName = nullptr;
	int currentCategoryIndex = 0;
	Results* currentResults = nullptr;

	// catch stdout and stderr
	std::streambuf* coutBuf = std::cout.rdbuf();
	std::streambuf* cerrBuf = std::cerr.rdbuf();
	std::ostringstream coutStream;
	std::ostringstream cerrStream;

	//#define PRINT_OUTPUT

#ifdef PRINT_OUTPUT
#define CAPTURE_OUTPUT()
#define RESTORE_OUTPUT()
#else
#define CAPTURE_OUTPUT() std::cout.rdbuf(coutStream.rdbuf()); std::cerr.rdbuf(cerrStream.rdbuf())
#define RESTORE_OUTPUT() std::cout.rdbuf(coutBuf); std::cerr.rdbuf(cerrBuf)
#endif // PRINT_OUTPUT

	// category start macro
#define CATEGORY(categoryName) { \
currentCategoryName = #categoryName; \
auto found = categories.find(currentCategoryName); \
RESTORE_OUTPUT(); if(found == categories.end()) { currentCategoryIndex = static_cast<int>(categories.size()); categories.emplace(currentCategoryName, currentCategoryIndex); std::cout << "\t" << currentCategoryName << std::endl; } else { currentCategoryIndex = found->second; } CAPTURE_OUTPUT(); \
}

	// test start macro
#define TEST(testName) { \
currentName = testName; \
auto found2 = results.find(currentCategoryIndex); \
if(found2 == results.end()) { results.emplace(currentCategoryIndex, Results()); currentResults = &results[currentCategoryIndex]; } else { currentResults = &found2->second; } \
}

	// evaluation macros
#define PASS(condition) { RESTORE_OUTPUT(); currentResults->passes++; std::cout << "\r[\033[92mPASS\033[0m] " << currentName << " (" << #condition << ")" << std::endl; CAPTURE_OUTPUT(); }
#define FAIL(condition) { RESTORE_OUTPUT(); currentResults->fails++; std::cout << "\r[\033[91mPASS\033[0m] " << currentName << " (" << #condition << ")" << std::endl; CAPTURE_OUTPUT(); }
#define EXPECT_TRUE(condition) if(condition) { PASS(condition); } else { FAIL(condition); }
#define EXPECT_FAIL(operation) try { operation; FAIL(operation); } catch(...) { PASS(operation); }
#define PRINT(message) { RESTORE_OUTPUT(); std::cout << message << std::endl; CAPTURE_OUTPUT(); }

	// start capturing the output
	CAPTURE_OUTPUT();

#pragma endregion

#pragma region Tests

	CATEGORY(String)
	{
		TEST("Default Constructor")
		{
			String test;
			EXPECT_TRUE(test.get_capacity() == 0);
			EXPECT_TRUE(test.get_size() == 0);
			EXPECT_TRUE(test.get_data() == nullptr);
		}

		TEST("Capacity Constructor")
		{
			String test(10);
			EXPECT_TRUE(test.get_capacity() == 10);
			EXPECT_TRUE(test.get_size() == 0);
			EXPECT_TRUE(test.get_data() != nullptr);
		}

		TEST("C String Constructor")
		{
			String test("Hello world!\n");

			EXPECT_TRUE(test.get_capacity() == 13);
			EXPECT_TRUE(test.get_size() == 13);
			EXPECT_TRUE(test.get_data() != nullptr);
			EXPECT_TRUE(test.get_data()[test.get_size()] == '\0');
		}

		TEST("Copy Constructor")
		{
			String test("Hello world!\n");
			String copy(test);
			EXPECT_TRUE(copy.get_capacity() == test.get_capacity());
			EXPECT_TRUE(copy.get_size() == test.get_size());
			EXPECT_TRUE(copy.get_data() != nullptr);
		}

		TEST("Move Constructor")
		{
			String test("Hello world!\n");
			String copy(std::move(test));
			EXPECT_TRUE(test.get_capacity() == 0);
			EXPECT_TRUE(test.get_size() == 0);
			EXPECT_TRUE(test.get_data() == nullptr);
			EXPECT_TRUE(copy.get_capacity() == 13);
			EXPECT_TRUE(copy.get_size() == 13);
			EXPECT_TRUE(copy.get_data() != nullptr);
		}

		TEST("Copy Operator")
		{
			String test("Hello world!\n");
			String copy = test;
			EXPECT_TRUE(copy.get_capacity() == test.get_capacity());
			EXPECT_TRUE(copy.get_size() == test.get_size());
			EXPECT_TRUE(copy.get_data() != nullptr);
		}

		TEST("Move Operator")
		{
			String test("Hello world!\n");
			String copy = std::move(test);
			EXPECT_TRUE(test.get_capacity() == 0);
			EXPECT_TRUE(test.get_size() == 0);
			EXPECT_TRUE(test.get_data() == nullptr);
			EXPECT_TRUE(copy.get_capacity() == 13);
			EXPECT_TRUE(copy.get_size() == 13);
			EXPECT_TRUE(copy.get_data() != nullptr);
		}

		TEST("Index Operator")
		{
			String test("Hello world!\n");
			EXPECT_TRUE(test[0] == 'H');
			EXPECT_TRUE(test[1] == 'e');
			EXPECT_TRUE(test[2] == 'l');
			EXPECT_TRUE(test[3] == 'l');
			EXPECT_TRUE(test[4] == 'o');
			EXPECT_TRUE(test[5] == ' ');
			EXPECT_TRUE(test[6] == 'w');
			EXPECT_TRUE(test[7] == 'o');
			EXPECT_TRUE(test[8] == 'r');
			EXPECT_TRUE(test[9] == 'l');
			EXPECT_TRUE(test[10] == 'd');
			EXPECT_TRUE(test[11] == '!');
			EXPECT_TRUE(test[12] == '\n');
			EXPECT_FAIL(test[13]);
		}

		TEST("Equal Operator")
		{
			String test("aaa");
			String copy("aaa");
			EXPECT_TRUE(test == copy);

			copy = "bbbbbb";
			EXPECT_TRUE(!(test == copy));

			copy = "aaa";
			EXPECT_TRUE(test == copy);

			copy = "aaaa";
			EXPECT_TRUE(!(test == copy));
		}

		TEST("Not Equal Operator")
		{
			String test("aaa");
			String copy("aaa");
			EXPECT_TRUE(!(test != copy));

			copy = "bbbbbb";
			EXPECT_TRUE(test != copy);

			copy = "aaa";
			EXPECT_TRUE(!(test != copy));

			copy = "aaaa";
			EXPECT_TRUE(test != copy);
		}

		TEST("Less Than Operator")
		{
			String test("aaa");
			String copy("aaa");
			EXPECT_TRUE(!(test < copy));

			copy = "bbb";
			EXPECT_TRUE(test < copy);

			copy = "aaa";
			EXPECT_TRUE(!(test < copy));

			copy = "aaaa";
			EXPECT_TRUE(test < copy);

			copy = "aa";
			EXPECT_TRUE(!(test < copy));
		}

		TEST("Less Than Or Equal Operator")
		{
			String test("aaa");
			String copy("aaa");
			EXPECT_TRUE(test <= copy);

			copy = "bbb";
			EXPECT_TRUE(test <= copy);

			copy = "aaa";
			EXPECT_TRUE(test <= copy);

			copy = "aaaa";
			EXPECT_TRUE(test <= copy);

			copy = "aa";
			EXPECT_TRUE(!(test <= copy));
		}

		TEST("Greater Than Operator")
		{
			String test("aaa");
			String copy("aaa");
			EXPECT_TRUE(!(test > copy));

			copy = "bbb";
			EXPECT_TRUE(!(test > copy));

			copy = "aaa";
			EXPECT_TRUE(!(test > copy));

			copy = "ccc";
			EXPECT_TRUE(!(test > copy));

			copy = "aa";
			EXPECT_TRUE(test > copy);

			copy = "aaaa";
			EXPECT_TRUE(!(test > copy));
		}

		TEST("Greater Than Or Equal Operator")
		{
			String test("aaa\n");
			String copy("aaa\n");
			EXPECT_TRUE(test >= copy);

			copy = "bbb";
			EXPECT_TRUE(!(test >= copy));

			copy = "aaa";
			EXPECT_TRUE(test >= copy);

			copy = "ccc";
			EXPECT_TRUE(!(test >= copy));

			copy = "aa";
			EXPECT_TRUE(test >= copy);

			copy = "aaaa";
			EXPECT_TRUE(!(test >= copy));
		}

		TEST("Get Capacity")
		{
			String test(100);

			EXPECT_TRUE(test.get_capacity() == 100);
		}

		TEST("Get Size")
		{
			String test("Hello world!\n");

			EXPECT_TRUE(test.get_size() == 13);
		}

		TEST("Get Data")
		{
			String test("Hello world!\n");

			EXPECT_TRUE(test.get_data() != nullptr);
		}

		TEST("Reserve")
		{
			String test;

			test.reserve(0);
			EXPECT_TRUE(test.get_capacity() == 0);

			test.reserve(100);
			EXPECT_TRUE(test.get_capacity() == 100);

			test.reserve(10);
			EXPECT_TRUE(test.get_capacity() == 10);
		}

		TEST("Resize")
		{
			String test;

			test.resize(0);
			EXPECT_TRUE(test.get_size() == 0);
			EXPECT_TRUE(test.get_capacity() == 0);

			test.resize(100);
			EXPECT_TRUE(test.get_size() == 100);
			EXPECT_TRUE(test.get_capacity() == 100);

			test.resize(10);
			EXPECT_TRUE(test.get_size() == 10);
			EXPECT_TRUE(test.get_capacity() == 100);
		}

		TEST("Is Empty")
		{
			String test;
			EXPECT_TRUE(test.is_empty());

			test = "Hello world!\n";
			EXPECT_TRUE(!test.is_empty());
		}

		TEST("At")
		{
			String test("Hello world!\n");
			EXPECT_TRUE(test.at(0) == 'H');
			EXPECT_TRUE(test.at(1) == 'e');
			EXPECT_TRUE(test.at(2) == 'l');
			EXPECT_TRUE(test.at(3) == 'l');
			EXPECT_TRUE(test.at(4) == 'o');
			EXPECT_TRUE(test.at(5) == ' ');
			EXPECT_TRUE(test.at(6) == 'w');
			EXPECT_TRUE(test.at(7) == 'o');
			EXPECT_TRUE(test.at(8) == 'r');
			EXPECT_TRUE(test.at(9) == 'l');
			EXPECT_TRUE(test.at(10) == 'd');
			EXPECT_TRUE(test.at(11) == '!');
			EXPECT_TRUE(test.at(12) == '\n');
			EXPECT_FAIL(test.at(13));
		}

		TEST("Sub")
		{
			String test("Hello world!\n");
			EXPECT_TRUE(test.sub(0, 5) == "Hello");
			EXPECT_TRUE(test.sub(6, 5) == "world");
			EXPECT_TRUE(test.sub(12, 1) == "\n");
			EXPECT_FAIL(test.sub(13, 1));
		}

		TEST("Find")
		{
			String test("Hello world!\n");
			EXPECT_TRUE(test.find("Hello") == 0);
			EXPECT_TRUE(test.find("world") == 6);
			EXPECT_TRUE(test.find("\n") == 12);
			EXPECT_TRUE(test.find("Hello world!\n") == 0);
			EXPECT_TRUE(test.find("aaa") == INVALID_INDEX);
			EXPECT_TRUE(test.find("") == INVALID_INDEX);

			test = "";
			EXPECT_TRUE(test.find("aaa") == INVALID_INDEX);
		}

		TEST("Contains")
		{
			String test("Hello world!\n");
			EXPECT_TRUE(test.contains("Hello"));
			EXPECT_TRUE(test.contains("world"));
			EXPECT_TRUE(test.contains("\n"));
			EXPECT_TRUE(test.contains("Hello world!\n"));
			EXPECT_TRUE(!test.contains("aaa"));
			EXPECT_TRUE(!test.contains(""));

			test = "";
			EXPECT_TRUE(!test.contains("aaa"));
		}
	}

#pragma endregion

#pragma region Test Teardown

	// restore stdout and stderr
	RESTORE_OUTPUT();

	// print results
	std::cout << "\nFinal Results:\n";
	for (auto const& [categoryName, categoryIndex] : categories)
	{
		Results const& result = results[categoryIndex];

		std::cout << categoryName << ": ";

		if (result.fails == 0)
		{
			// green
			std::cout << "\033[92m";
		}
		else
		{
			// red
			std::cout << "\033[91m";
		}

		std::cout << "(" << result.passes << "/" << (result.passes + result.fails) << ")\033[0m" << std::endl;
	}

#pragma endregion
}

int main()
{
	run_tests();
}
