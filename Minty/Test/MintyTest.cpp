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
		: originalBuffer(originalBuffer), secondStream(secondStream.rdbuf()) {
	}

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
	std::vector<std::string> categoryNames;
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
RESTORE_OUTPUT(); if(found == categories.end()) { currentCategoryIndex = static_cast<int>(categories.size()); categories.emplace(currentCategoryName, currentCategoryIndex); categoryNames.push_back(currentCategoryName); std::cout << "\n\t" << currentCategoryName << std::endl; } else { currentCategoryIndex = found->second; } CAPTURE_OUTPUT(); \
}

	// test start macro
#define TEST(testName) { \
currentName = testName; \
auto found2 = results.find(currentCategoryIndex); \
if(found2 == results.end()) { results.emplace(currentCategoryIndex, Results()); currentResults = &results[currentCategoryIndex]; } else { currentResults = &found2->second; } \
}

	// evaluation macros
#define PASS(condition) { currentResults->passes++; }
#define FAIL(condition) { RESTORE_OUTPUT(); currentResults->fails++; std::cout << "\r[\033[91mFAIL\033[0m] " << currentName << " (" << #condition << ") [Line " << __LINE__ <<  "]" << std::endl; CAPTURE_OUTPUT(); }
#define EXPECT_TRUE(condition) try { if(condition) { PASS(condition); } else { FAIL(condition); } } catch(...) { FAIL(condition); }
#define EXPECT_SUCCESS(operation) try { operation; PASS(operation); } catch(...) { FAIL(operation); }
#define EXPECT_FAIL(operation) try { operation; FAIL(operation); } catch(...) { PASS(operation); }
#define PRINT(message) { RESTORE_OUTPUT(); std::cout << message << std::endl; CAPTURE_OUTPUT(); }

	// start capturing the output
	CAPTURE_OUTPUT();

#pragma endregion

#pragma region Tests

	CATEGORY(Minty)
	{
		TEST("Allocate")
		{

		}
	}

	CATEGORY(String::Iterator)
	{
		TEST("Copy Constructor")
		{
			String test("abc");
			String::Iterator it = test.begin();
			String::Iterator copy(it);
			EXPECT_TRUE(*copy == 'a');
			EXPECT_TRUE(*(copy + 1) == 'b');
			EXPECT_TRUE(*(copy + 2) == 'c');
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 'b');
			EXPECT_TRUE(*++copy == 'c');
			EXPECT_TRUE(++copy == test.end());
			copy = it;
			EXPECT_TRUE(*copy++ == 'a');
			EXPECT_TRUE(*copy++ == 'b');
			EXPECT_TRUE(*copy++ == 'c');
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Move Constructor")
		{
			String test("abc");
			String::Iterator it = test.begin();
			String::Iterator copy(std::move(it));
			EXPECT_TRUE(*copy == 'a');
			EXPECT_TRUE(*(copy + 1) == 'b');
			EXPECT_TRUE(*(copy + 2) == 'c');
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 'b');
			EXPECT_TRUE(*++copy == 'c');
			EXPECT_TRUE(++copy == test.end());
			it = test.begin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 'a');
			EXPECT_TRUE(*copy++ == 'b');
			EXPECT_TRUE(*copy++ == 'c');
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Copy Operator")
		{
			String test("abc");
			String::Iterator it = test.begin();
			String::Iterator copy = it;
			EXPECT_TRUE(*copy == 'a');
			EXPECT_TRUE(*(copy + 1) == 'b');
			EXPECT_TRUE(*(copy + 2) == 'c');
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 'b');
			EXPECT_TRUE(*++copy == 'c');
			EXPECT_TRUE(++copy == test.end());
			copy = it;
			EXPECT_TRUE(*copy++ == 'a');
			EXPECT_TRUE(*copy++ == 'b');
			EXPECT_TRUE(*copy++ == 'c');
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Move Operator")
		{
			String test("abc");
			String::Iterator it = test.begin();
			String::Iterator copy = std::move(it);
			EXPECT_TRUE(*copy == 'a');
			EXPECT_TRUE(*(copy + 1) == 'b');
			EXPECT_TRUE(*(copy + 2) == 'c');
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 'b');
			EXPECT_TRUE(*++copy == 'c');
			EXPECT_TRUE(++copy == test.end());
			it = test.begin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 'a');
			EXPECT_TRUE(*copy++ == 'b');
			EXPECT_TRUE(*copy++ == 'c');
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Dereference Operator")
		{
			String test("abc");
			String::Iterator it = test.begin();
			EXPECT_TRUE(*it == 'a');
			EXPECT_TRUE(*(it + 1) == 'b');
			EXPECT_TRUE(*(it + 2) == 'c');
			EXPECT_TRUE(it + 3 == test.end());
			EXPECT_TRUE(*++it == 'b');
			EXPECT_TRUE(*++it == 'c');
			EXPECT_TRUE(++it == test.end());
			it = test.begin();
			EXPECT_TRUE(*it++ == 'a');
			EXPECT_TRUE(*it++ == 'b');
			EXPECT_TRUE(*it++ == 'c');
			EXPECT_TRUE(it == test.end());
		}

		TEST("Increment Operator")
		{
			String test("abc");
			String::Iterator it = test.begin();
			EXPECT_TRUE(*it == 'a');
			EXPECT_TRUE(*(it + 1) == 'b');
			EXPECT_TRUE(*(it + 2) == 'c');
			EXPECT_TRUE(it + 3 == test.end());
			EXPECT_TRUE(*++it == 'b');
			EXPECT_TRUE(*++it == 'c');
			EXPECT_TRUE(++it == test.end());
			it = test.begin();
			EXPECT_TRUE(*it++ == 'a');
			EXPECT_TRUE(*it++ == 'b');
			EXPECT_TRUE(*it++ == 'c');
			EXPECT_TRUE(it == test.end());
		}

		TEST("Addition Operator")
		{
			String test("abc");
			String::Iterator it = test.begin();
			EXPECT_TRUE(*it == 'a');
			EXPECT_TRUE(*(it + 1) == 'b');
			EXPECT_TRUE(*(it + 2) == 'c');
			EXPECT_TRUE(it + 3 == test.end());
			EXPECT_TRUE(*++it == 'b');
			EXPECT_TRUE(*++it == 'c');
			EXPECT_TRUE(++it == test.end());
			it = test.begin();
			EXPECT_TRUE(*it++ == 'a');
			EXPECT_TRUE(*it++ == 'b');
			EXPECT_TRUE(*it++ == 'c');
			EXPECT_TRUE(it == test.end());
		}

		TEST("Equal Operator")
		{
			String test("abc");
			String::Iterator it = test.begin();
			String::Iterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.begin());
			EXPECT_TRUE(test.begin() == it);
			EXPECT_TRUE(copy == test.begin());
			EXPECT_TRUE(test.begin() == copy);
		}

		TEST("Not Equal Operator")
		{
			String test("abc");
			String::Iterator it = test.begin();
			String::Iterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.begin()));
			EXPECT_TRUE(!(test.begin() != it));
			EXPECT_TRUE(!(copy != test.begin()));
			EXPECT_TRUE(!(test.begin() != copy));
		}
	}

	CATEGORY(String::ConstIterator)
	{
		TEST("Copy Constructor")
		{
			String test("abc");
			String::ConstIterator it = test.cbegin();
			String::ConstIterator copy(it);
			EXPECT_TRUE(*copy == 'a');
			EXPECT_TRUE(*(copy + 1) == 'b');
			EXPECT_TRUE(*(copy + 2) == 'c');
			EXPECT_TRUE(copy + 3 == test.cend());
			EXPECT_TRUE(*++copy == 'b');
			EXPECT_TRUE(*++copy == 'c');
			EXPECT_TRUE(++copy == test.cend());
			copy = it;
			EXPECT_TRUE(*copy++ == 'a');
			EXPECT_TRUE(*copy++ == 'b');
			EXPECT_TRUE(*copy++ == 'c');
			EXPECT_TRUE(copy == test.cend());
		}

		TEST("Move Constructor")
		{
			String test("abc");
			String::ConstIterator it = test.cbegin();
			String::ConstIterator copy(std::move(it));
			EXPECT_TRUE(*copy == 'a');
			EXPECT_TRUE(*(copy + 1) == 'b');
			EXPECT_TRUE(*(copy + 2) == 'c');
			EXPECT_TRUE(copy + 3 == test.cend());
			EXPECT_TRUE(*++copy == 'b');
			EXPECT_TRUE(*++copy == 'c');
			EXPECT_TRUE(++copy == test.cend());
			it = test.cbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 'a');
			EXPECT_TRUE(*copy++ == 'b');
			EXPECT_TRUE(*copy++ == 'c');
			EXPECT_TRUE(copy == test.cend());
		}

		TEST("Copy Operator")
		{
			String test("abc");
			String::ConstIterator it = test.cbegin();
			String::ConstIterator copy = it;
			EXPECT_TRUE(*copy == 'a');
			EXPECT_TRUE(*(copy + 1) == 'b');
			EXPECT_TRUE(*(copy + 2) == 'c');
			EXPECT_TRUE(copy + 3 == test.cend());
			EXPECT_TRUE(*++copy == 'b');
			EXPECT_TRUE(*++copy == 'c');
			EXPECT_TRUE(++copy == test.cend());
			copy = it;
			EXPECT_TRUE(*copy++ == 'a');
			EXPECT_TRUE(*copy++ == 'b');
			EXPECT_TRUE(*copy++ == 'c');
			EXPECT_TRUE(copy == test.cend());
		}

		TEST("Move Operator")
		{
			String test("abc");
			String::ConstIterator it = test.cbegin();
			String::ConstIterator copy = std::move(it);
			EXPECT_TRUE(*copy == 'a');
			EXPECT_TRUE(*(copy + 1) == 'b');
			EXPECT_TRUE(*(copy + 2) == 'c');
			EXPECT_TRUE(copy + 3 == test.cend());
			EXPECT_TRUE(*++copy == 'b');
			EXPECT_TRUE(*++copy == 'c');
			EXPECT_TRUE(++copy == test.cend());
			it = test.cbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 'a');
			EXPECT_TRUE(*copy++ == 'b');
			EXPECT_TRUE(*copy++ == 'c');
			EXPECT_TRUE(copy == test.cend());
		}

		TEST("Dereference Operator")
		{
			String test("abc");
			String::ConstIterator it = test.cbegin();
			EXPECT_TRUE(*it == 'a');
			EXPECT_TRUE(*(it + 1) == 'b');
			EXPECT_TRUE(*(it + 2) == 'c');
			EXPECT_TRUE(it + 3 == test.cend());
			EXPECT_TRUE(*++it == 'b');
			EXPECT_TRUE(*++it == 'c');
			EXPECT_TRUE(++it == test.cend());
			it = test.cbegin();
			EXPECT_TRUE(*it++ == 'a');
			EXPECT_TRUE(*it++ == 'b');
			EXPECT_TRUE(*it++ == 'c');
			EXPECT_TRUE(it == test.cend());
		}

		TEST("Increment Operator")
		{
			String test("abc");
			String::ConstIterator it = test.cbegin();
			EXPECT_TRUE(*it == 'a');
			EXPECT_TRUE(*(it + 1) == 'b');
			EXPECT_TRUE(*(it + 2) == 'c');
			EXPECT_TRUE(it + 3 == test.cend());
			EXPECT_TRUE(*++it == 'b');
			EXPECT_TRUE(*++it == 'c');
			EXPECT_TRUE(++it == test.cend());
			it = test.cbegin();
			EXPECT_TRUE(*it++ == 'a');
			EXPECT_TRUE(*it++ == 'b');
			EXPECT_TRUE(*it++ == 'c');
			EXPECT_TRUE(it == test.cend());
		}

		TEST("Addition Operator")
		{
			String test("abc");
			String::ConstIterator it = test.cbegin();
			EXPECT_TRUE(*it == 'a');
			EXPECT_TRUE(*(it + 1) == 'b');
			EXPECT_TRUE(*(it + 2) == 'c');
			EXPECT_TRUE(it + 3 == test.cend());
			EXPECT_TRUE(*++it == 'b');
			EXPECT_TRUE(*++it == 'c');
			EXPECT_TRUE(++it == test.cend());
			it = test.cbegin();
			EXPECT_TRUE(*it++ == 'a');
			EXPECT_TRUE(*it++ == 'b');
			EXPECT_TRUE(*it++ == 'c');
			EXPECT_TRUE(it == test.cend());
		}

		TEST("Equal Operator")
		{
			String test("abc");
			String::ConstIterator it = test.cbegin();
			String::ConstIterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.cbegin());
			EXPECT_TRUE(test.cbegin() == it);
			EXPECT_TRUE(copy == test.cbegin());
			EXPECT_TRUE(test.cbegin() == copy);
		}

		TEST("Not Equal Operator")
		{
			String test("abc");
			String::ConstIterator it = test.cbegin();
			String::ConstIterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.cbegin()));
			EXPECT_TRUE(!(test.cbegin() != it));
			EXPECT_TRUE(!(copy != test.cbegin()));
			EXPECT_TRUE(!(test.cbegin() != copy));
		}
	}

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

		TEST("Character Constructor")
		{
			String test('a', 3);

			EXPECT_TRUE(test.get_capacity() == 3);
			EXPECT_TRUE(test.get_size() == 3);
			EXPECT_TRUE(test.get_data() != nullptr);
			EXPECT_TRUE(test.get_data()[0] == 'a');
			EXPECT_TRUE(test.get_data()[1] == 'a');
			EXPECT_TRUE(test.get_data()[2] == 'a');
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

		TEST("Addition Operator")
		{
			String test("Hello ");
			String copy("world!\n");
			String result = test + copy;
			EXPECT_TRUE(result == "Hello world!\n");

			copy = "";
			result = test + copy;
			EXPECT_TRUE(result == "Hello ");

			test = "";
			result = test + copy;
			EXPECT_TRUE(result == "");
		}

		TEST("Stream Insertion Operator")
		{
			String test("Hello world!\n");
			{
				std::ostringstream stream;
				stream << test;
				EXPECT_TRUE(stream.str() == "Hello world!\n");
			}
			test = "";
			{
				std::ostringstream stream;
				stream << test;
				EXPECT_TRUE(stream.str() == "");
			}
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

		TEST("Iterator")
		{
			String test("abc");
			String::Iterator it = test.begin();
			EXPECT_TRUE(*it == 'a');
			EXPECT_TRUE(*(it + 1) == 'b');
			EXPECT_TRUE(*(it + 2) == 'c');
			EXPECT_TRUE(it + 3 == test.end());
			EXPECT_TRUE(*++it == 'b');
			EXPECT_TRUE(*++it == 'c');
			EXPECT_TRUE(++it == test.end());
			it = test.begin();
			EXPECT_TRUE(*it++ == 'a');
			EXPECT_TRUE(*it++ == 'b');
			EXPECT_TRUE(*it++ == 'c');
			EXPECT_TRUE(it == test.end());
		}

		TEST("ConstIterator")
		{
			String test("abc");
			String::ConstIterator it = test.cbegin();
			EXPECT_TRUE(*it == 'a');
			EXPECT_TRUE(*(it + 1) == 'b');
			EXPECT_TRUE(*(it + 2) == 'c');
			EXPECT_TRUE(it + 3 == test.cend());
			EXPECT_TRUE(*++it == 'b');
			EXPECT_TRUE(*++it == 'c');
			EXPECT_TRUE(++it == test.cend());
			it = test.cbegin();
			EXPECT_TRUE(*it++ == 'a');
			EXPECT_TRUE(*it++ == 'b');
			EXPECT_TRUE(*it++ == 'c');
			EXPECT_TRUE(it == test.cend());
		}
	}

	CATEGORY(Array::Iterator)
	{
		TEST("Copy Constructor")
		{
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
			Array<int, 3>::Iterator copy(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.end());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Move Constructor")
		{
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
			Array<int, 3>::Iterator copy(std::move(it));
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.end());
			it = test.begin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Copy Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
			Array<int, 3>::Iterator copy = it;
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.end());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Move Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
			Array<int, 3>::Iterator copy = std::move(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.end());
			it = test.begin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Dereference Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
			EXPECT_TRUE(it + 3 == test.end());
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(++it == test.end());
			it = test.begin();
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(it == test.end());
		}

		TEST("Decrement Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.end();
			EXPECT_TRUE(*(it - 1) == 5);
			EXPECT_TRUE(*(it - 2) == 5);
			EXPECT_TRUE(it - 3 == test.begin());
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(--it == test.begin());
			it = test.end();
			it--;
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(it == test.begin());
		}

		TEST("Addition Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.end();
			EXPECT_TRUE(it - 3 == test.begin());
			EXPECT_TRUE(it - 2 == test.begin() + 1);
			EXPECT_TRUE(it - 1 == test.begin() + 2);
		}

		TEST("Equal Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
			Array<int, 3>::Iterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.begin());
			EXPECT_TRUE(test.begin() == it);
			EXPECT_TRUE(copy == test.begin());
			EXPECT_TRUE(test.begin() == copy);
		}

		TEST("Not Equal Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
			Array<int, 3>::Iterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.begin()));
			EXPECT_TRUE(!(test.begin() != it));
			EXPECT_TRUE(!(copy != test.begin()));
			EXPECT_TRUE(!(test.begin() != copy));
		}
	}

	CATEGORY(Array::ConstIterator)
	{
		TEST("Copy Constructor")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
			Array<int, 3>::ConstIterator copy(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.cend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.cend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.cend());
		}

		TEST("Move Constructor")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
			Array<int, 3>::ConstIterator copy(std::move(it));
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.cend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.cend());
			it = test.cbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.cend());
		}

		TEST("Copy Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
			Array<int, 3>::ConstIterator copy = it;
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.cend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.cend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.cend());
		}

		TEST("Move Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
			Array<int, 3>::ConstIterator copy = std::move(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.cend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.cend());
			it = test.cbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.cend());
		}

		TEST("Dereference Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
			EXPECT_TRUE(it + 3 == test.cend());
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(++it == test.cend());
			it = test.cbegin();
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(it == test.cend());
		}

		TEST("Decrement Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cend();
			EXPECT_TRUE(*(it - 1) == 5);
			EXPECT_TRUE(*(it - 2) == 5);
			EXPECT_TRUE(it - 3 == test.cbegin());
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(--it == test.cbegin());
			it = test.cend();
			it--;
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(it == test.cbegin());
		}

		TEST("Addition Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cend();
			EXPECT_TRUE(it - 3 == test.cbegin());
			EXPECT_TRUE(it - 2 == test.cbegin() + 1);
			EXPECT_TRUE(it - 1 == test.cbegin() + 2);
		}

		TEST("Equal Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
			Array<int, 3>::ConstIterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.cbegin());
			EXPECT_TRUE(test.cbegin() == it);
			EXPECT_TRUE(copy == test.cbegin());
			EXPECT_TRUE(test.cbegin() == copy);
		}

		TEST("Not Equal Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
			Array<int, 3>::ConstIterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.cbegin()));
			EXPECT_TRUE(!(test.cbegin() != it));
			EXPECT_TRUE(!(copy != test.cbegin()));
			EXPECT_TRUE(!(test.cbegin() != copy));
		}
	}

	CATEGORY(Array::ReverseIterator)
	{
		TEST("Copy Constructor")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
			Array<int, 3>::ReverseIterator copy(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.rend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.rend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.rend());
		}

		TEST("Move Constructor")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
			Array<int, 3>::ReverseIterator copy(std::move(it));
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.rend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.rend());
			it = test.rbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.rend());
		}

		TEST("Copy Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
			Array<int, 3>::ReverseIterator copy = it;
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.rend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.rend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.rend());
		}

		TEST("Move Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
			Array<int, 3>::ReverseIterator copy = std::move(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.rend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.rend());
			it = test.rbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.rend());
		}

		TEST("Dereference Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
			EXPECT_TRUE(it + 3 == test.rend());
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(++it == test.rend());
			it = test.rbegin();
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(it == test.rend());
		}

		TEST("Decrement Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rend();
			EXPECT_TRUE(*(it - 1) == 5);
			EXPECT_TRUE(*(it - 2) == 5);
			EXPECT_TRUE(it - 3 == test.rbegin());
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(--it == test.rbegin());
			it = test.rend();
			it--;
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(it == test.rbegin());
		}

		TEST("Addition Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rend();
			EXPECT_TRUE(it - 3 == test.rbegin());
			EXPECT_TRUE(it - 2 == test.rbegin() + 1);
			EXPECT_TRUE(it - 1 == test.rbegin() + 2);
		}

		TEST("Equal Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
			Array<int, 3>::ReverseIterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.rbegin());
			EXPECT_TRUE(test.rbegin() == it);
			EXPECT_TRUE(copy == test.rbegin());
			EXPECT_TRUE(test.rbegin() == copy);
		}

		TEST("Not Equal Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
			Array<int, 3>::ReverseIterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.rbegin()));
			EXPECT_TRUE(!(test.rbegin() != it));
			EXPECT_TRUE(!(copy != test.rbegin()));
			EXPECT_TRUE(!(test.rbegin() != copy));
		}
	}

	CATEGORY(Array::ConstReverseIterator)
	{
		TEST("Copy Constructor")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
			Array<int, 3>::ConstReverseIterator copy(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.crend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.crend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.crend());
		}

		TEST("Move Constructor")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
			Array<int, 3>::ConstReverseIterator copy(std::move(it));
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.crend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.crend());
			it = test.crbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.crend());
		}

		TEST("Copy Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
			Array<int, 3>::ConstReverseIterator copy = it;
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.crend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.crend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.crend());
		}

		TEST("Move Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
			Array<int, 3>::ConstReverseIterator copy = std::move(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.crend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.crend());
			it = test.crbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.crend());
		}

		TEST("Dereference Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
			EXPECT_TRUE(it + 3 == test.crend());
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(++it == test.crend());
			it = test.crbegin();
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(it == test.crend());
		}

		TEST("Decrement Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crend();
			EXPECT_TRUE(*(it - 1) == 5);
			EXPECT_TRUE(*(it - 2) == 5);
			EXPECT_TRUE(it - 3 == test.crbegin());
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(--it == test.crbegin());
			it = test.crend();
			it--;
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(it == test.crbegin());
		}

		TEST("Addition Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crend();
			EXPECT_TRUE(it - 3 == test.crbegin());
			EXPECT_TRUE(it - 2 == test.crbegin() + 1);
			EXPECT_TRUE(it - 1 == test.crbegin() + 2);
		}

		TEST("Equal Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
			Array<int, 3>::ConstReverseIterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.crbegin());
			EXPECT_TRUE(test.crbegin() == it);
			EXPECT_TRUE(copy == test.crbegin());
			EXPECT_TRUE(test.crbegin() == copy);
		}

		TEST("Not Equal Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
			Array<int, 3>::ConstReverseIterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.crbegin()));
			EXPECT_TRUE(!(test.crbegin() != it));
			EXPECT_TRUE(!(copy != test.crbegin()));
			EXPECT_TRUE(!(test.crbegin() != copy));
		}
	}

	CATEGORY(Array)
	{
		TEST("Default Constructor")
		{
			Array<int, 3> test;
			EXPECT_TRUE(test.get_size() == 3);
		}

		TEST("Value Constructor")
		{
			Array<int, 3> test(5);
			EXPECT_TRUE(test.get_size() == 3);
			EXPECT_TRUE(test.at(0) == 5);
			EXPECT_TRUE(test.at(1) == 5);
			EXPECT_TRUE(test.at(2) == 5);
		}

		TEST("Initializer List Constructor")
		{
			Array<int, 3> test({ 0, 1, 2 });
			EXPECT_TRUE(test.get_size() == 3);
			EXPECT_TRUE(test.at(0) == 0);
			EXPECT_TRUE(test.at(1) == 1);
			EXPECT_TRUE(test.at(2) == 2);
		}

		TEST("Copy Constructor")
		{
			Array<int, 3> test(5);
			Array<int, 3> copy(test);
			EXPECT_TRUE(copy.get_size() == 3);
			EXPECT_TRUE(copy.at(0) == 5);
			EXPECT_TRUE(copy.at(1) == 5);
			EXPECT_TRUE(copy.at(2) == 5);
		}

		TEST("Move Constructor")
		{
			Array<int, 3> test(5);
			Array<int, 3> copy(std::move(test));
			EXPECT_TRUE(copy.get_size() == 3);
			EXPECT_TRUE(copy.at(0) == 5);
			EXPECT_TRUE(copy.at(1) == 5);
			EXPECT_TRUE(copy.at(2) == 5);
		}

		TEST("Copy Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3> copy = test;
			EXPECT_TRUE(copy.get_size() == 3);
			EXPECT_TRUE(copy.at(0) == 5);
			EXPECT_TRUE(copy.at(1) == 5);
			EXPECT_TRUE(copy.at(2) == 5);
		}

		TEST("Move Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3> copy = std::move(test);
			EXPECT_TRUE(copy.get_size() == 3);
			EXPECT_TRUE(copy.at(0) == 5);
			EXPECT_TRUE(copy.at(1) == 5);
			EXPECT_TRUE(copy.at(2) == 5);
		}

		TEST("Index Operator")
		{
			Array<int, 3> test(5);
			EXPECT_TRUE(test[0] == 5);
			EXPECT_TRUE(test[1] == 5);
			EXPECT_TRUE(test[2] == 5);
			EXPECT_FAIL(test[3]);
		}

		TEST("Const Index Operator")
		{
			Array<int, 3> const test(5);
			EXPECT_TRUE(test[0] == 5);
			EXPECT_TRUE(test[1] == 5);
			EXPECT_TRUE(test[2] == 5);
			EXPECT_FAIL(test[3]);
		}

		TEST("Get Size")
		{
			Array<int, 3> test(5);
			EXPECT_TRUE(test.get_size() == 3);
		}

		TEST("Get Data")
		{
			Array<int, 3> test(5);
			EXPECT_TRUE(test.get_data() != nullptr);
		}

		TEST("At")
		{
			Array<int, 3> test(5);
			EXPECT_TRUE(test.at(0) == 5);
			EXPECT_TRUE(test.at(1) == 5);
			EXPECT_TRUE(test.at(2) == 5);
			EXPECT_FAIL(test.at(3));
		}

		TEST("Const At")
		{
			Array<int, 3> const test(5);
			EXPECT_TRUE(test.at(0) == 5);
			EXPECT_TRUE(test.at(1) == 5);
			EXPECT_TRUE(test.at(2) == 5);
			EXPECT_FAIL(test.at(3));
		}

		TEST("Sub")
		{
			Array<int, 3> test(5);
			Array<int, 2> sub = test.sub<2>(0);
			EXPECT_TRUE(sub.get_size() == 2);
			EXPECT_TRUE(sub.at(0) == 5);
			EXPECT_TRUE(sub.at(1) == 5);
			EXPECT_FAIL(sub.at(2) == 5);
		}

		TEST("Find")
		{
			Array<int, 3> test({ 0, 1, 2 });
			EXPECT_TRUE(test.find(0) == test.begin());
			EXPECT_TRUE(test.find(1) == test.begin() + 1);
			EXPECT_TRUE(test.find(2) == test.begin() + 2);
			EXPECT_TRUE(test.find(3) == test.end());
		}

		TEST("Const Find")
		{
			Array<int, 3> const test({ 0, 1, 2 });
			EXPECT_TRUE(test.find(0) == test.cbegin());
			EXPECT_TRUE(test.find(1) == test.cbegin() + 1);
			EXPECT_TRUE(test.find(2) == test.cbegin() + 2);
			EXPECT_TRUE(test.find(3) == test.cend());
		}
	}

	CATEGORY(MemoryPool)
	{
		MemoryPoolBuilder builder
		{
			.blockSize = 1024,
			.blockCountCapacity = 10
		};

		TEST("Constructor")
		{
			EXPECT_FAIL(MemoryPool({ 0, 10 }));
			EXPECT_FAIL(MemoryPool({ 1024, 0 }));
			MemoryPool pool(builder);
			EXPECT_TRUE(pool.get_block_size() == 1024);
			EXPECT_TRUE(pool.get_capacity() == 10);
			EXPECT_TRUE(pool.get_count() == 0);
		}

		TEST("Move Constructor")
		{
			MemoryPool pool(builder);
			pool.allocate();
			MemoryPool copy(std::move(pool));
			EXPECT_TRUE(pool.get_block_size() == 0);
			EXPECT_TRUE(pool.get_capacity() == 0);
			EXPECT_TRUE(pool.get_count() == 0);
			EXPECT_TRUE(copy.get_block_size() == 1024);
			EXPECT_TRUE(copy.get_capacity() == 10);
			EXPECT_TRUE(copy.get_count() == 1);
		}

		TEST("Move Operator")
		{
			MemoryPool pool(builder);
			pool.allocate();
			MemoryPool copy = std::move(pool);
			EXPECT_TRUE(pool.get_block_size() == 0);
			EXPECT_TRUE(pool.get_capacity() == 0);
			EXPECT_TRUE(pool.get_count() == 0);
			EXPECT_TRUE(copy.get_block_size() == 1024);
			EXPECT_TRUE(copy.get_capacity() == 10);
			EXPECT_TRUE(copy.get_count() == 1);
		}

		TEST("Get Block Size")
		{
			MemoryPool pool(builder);
			EXPECT_TRUE(pool.get_block_size() == 1024);
		}

		TEST("Get Capacity")
		{
			MemoryPool pool(builder);
			EXPECT_TRUE(pool.get_capacity() == 10);
		}

		TEST("Get Count")
		{
			MemoryPool pool(builder);
			EXPECT_TRUE(pool.get_count() == 0);
			pool.allocate();
			EXPECT_TRUE(pool.get_count() == 1);
		}

		TEST("Get Data")
		{
			MemoryPool pool(builder);
			EXPECT_TRUE(pool.get_data() != nullptr);
			void* ptr = pool.allocate();
			EXPECT_TRUE(ptr == pool.get_data());
		}

		TEST("Is Full")
		{
			MemoryPool pool({ 1024, 1 });
			EXPECT_TRUE(!pool.is_full());
			pool.allocate();
			EXPECT_TRUE(pool.is_full());
		}

		TEST("Allocate")
		{
			MemoryPool pool(builder);
			void* ptr = pool.allocate();
			EXPECT_TRUE(ptr != nullptr);
			EXPECT_TRUE(pool.get_count() == 1);
			ptr = pool.allocate();
			EXPECT_TRUE(ptr != nullptr);
			EXPECT_TRUE(pool.get_count() == 2);
		}

		TEST("Deallocate")
		{
			MemoryPool pool(builder);
			void* ptr = pool.allocate();
			pool.deallocate(ptr);
			EXPECT_TRUE(pool.get_count() == 0);
		}

		TEST("Clear")
		{
			MemoryPool pool(builder);
			pool.allocate();
			pool.clear();
			EXPECT_TRUE(pool.get_count() == 0);
		}
	}

	CATEGORY(MemoryStack)
	{
		MemoryStackBuilder builder
		{
			.capacity = 1024
		};

		TEST("Constructor")
		{
			EXPECT_FAIL(MemoryStack({ 0 }));
			MemoryStack stack(builder);
			EXPECT_TRUE(stack.get_capacity() == 1024);
			EXPECT_TRUE(stack.get_size() == 0);
		}

		TEST("Move Constructor")
		{
			MemoryStack stack(builder);
			stack.allocate(512);
			MemoryStack copy(std::move(stack));
			EXPECT_TRUE(stack.get_capacity() == 0);
			EXPECT_TRUE(stack.get_size() == 0);
			EXPECT_TRUE(copy.get_capacity() == 1024);
			EXPECT_TRUE(copy.get_size() == 512);
		}

		TEST("Move Operator")
		{
			MemoryStack stack(builder);
			stack.allocate(512);
			MemoryStack copy = std::move(stack);
			EXPECT_TRUE(stack.get_capacity() == 0);
			EXPECT_TRUE(stack.get_size() == 0);
			EXPECT_TRUE(copy.get_capacity() == 1024);
			EXPECT_TRUE(copy.get_size() == 512);
		}

		TEST("Get Capacity")
		{
			MemoryStack stack(builder);
			EXPECT_TRUE(stack.get_capacity() == 1024);
		}

		TEST("Get Size")
		{
			MemoryStack stack(builder);
			EXPECT_TRUE(stack.get_size() == 0);
			stack.allocate(512);
			EXPECT_TRUE(stack.get_size() == 512);
			stack.allocate(512);
			EXPECT_TRUE(stack.get_size() == 1024);
		}

		TEST("Get Data")
		{
			MemoryStack stack(builder);
			EXPECT_TRUE(stack.get_data() != nullptr);
			void* ptr = stack.allocate(512);
			EXPECT_TRUE(ptr == stack.get_data());
		}

		TEST("Allocate")
		{
			MemoryStack stack(builder);
			void* ptr = stack.allocate(512);
			EXPECT_FAIL(stack.allocate(0));
			EXPECT_TRUE(ptr != nullptr);
			EXPECT_TRUE(stack.get_size() == 512);
			ptr = stack.allocate(512);
			EXPECT_TRUE(ptr != nullptr);
			EXPECT_TRUE(stack.get_size() == 1024);
			EXPECT_FAIL(stack.allocate(1));
		}

		TEST("Deallocate")
		{
			MemoryStack stack(builder);
			EXPECT_FAIL(stack.deallocate(0));
			EXPECT_FAIL(stack.deallocate(512));
			void* ptr = stack.allocate(512);
			stack.deallocate(512);
			EXPECT_TRUE(stack.get_size() == 0);
		}

		TEST("Clear")
		{
			MemoryStack stack(builder);
			stack.allocate(512);
			stack.clear();
			EXPECT_TRUE(stack.get_size() == 0);
		}
	}

	CATEGORY(MemoryManager)
	{
		MemoryManagerBuilder builder
		{
			.temporary = { 1024 },
			.task = { 1024 },
			.persistent = {
				{ 8, 10 },
				{ 16, 10 },
				{ 32, 10 },
				{ 64, 10 },
				{ 128, 10 },
				{ 256, 10 },
				{ 512, 10 },
				{ 1024, 10 }
			}
		};

		TEST("Constructor")
		{
			MemoryManager manager(builder);
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
			EXPECT_TRUE(manager.get_static_size() == 0);
		}

		TEST("Move Constructor")
		{
			MemoryManager manager(builder);
			void* temporary = manager.allocate(24, Allocator::Temporary);
			void* persistent = manager.allocate(24, Allocator::Persistent);
			void* def = manager.allocate(24, Allocator::Default);
			MemoryManager copy(std::move(manager));
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
			EXPECT_TRUE(manager.get_static_size() == 0);
			EXPECT_TRUE(copy.get_dynamic_size() == 24);
			EXPECT_TRUE(copy.get_static_size() == 48);
			EXPECT_SUCCESS(copy.deallocate(def, 24, Allocator::Default));
		}

		TEST("Move Operator")
		{
			MemoryManager manager(builder);
			void* temporary = manager.allocate(24, Allocator::Temporary);
			void* persistent = manager.allocate(24, Allocator::Persistent);
			void* def = manager.allocate(24, Allocator::Default);
			MemoryManager copy = std::move(manager);
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
			EXPECT_TRUE(manager.get_static_size() == 0);
			EXPECT_TRUE(copy.get_dynamic_size() == 24);
			EXPECT_TRUE(copy.get_static_size() == 48);
			EXPECT_SUCCESS(copy.deallocate(def, 24, Allocator::Default));
		}

		TEST("Get Size")
		{
			MemoryManager manager(builder);
			EXPECT_TRUE(manager.get_size() == 0);
			void* temporary = manager.allocate(24, Allocator::Temporary);
			EXPECT_TRUE(manager.get_size() == 24);
			void* persistent = manager.allocate(24, Allocator::Persistent);
			EXPECT_TRUE(manager.get_size() == 48);
			void* def = manager.allocate(24, Allocator::Default);
			EXPECT_TRUE(manager.get_size() == 72);
			manager.deallocate(def, 24, Allocator::Default);
			EXPECT_TRUE(manager.get_size() == 48);
			manager.deallocate(persistent, 24, Allocator::Persistent);
			EXPECT_TRUE(manager.get_size() == 24);
			manager.deallocate(temporary, 24, Allocator::Temporary);
			EXPECT_TRUE(manager.get_size() == 0);
		}

		TEST("Get Static Size")
		{
			MemoryManager manager(builder);
			EXPECT_TRUE(manager.get_static_size() == 0);
			void* temporary = manager.allocate(24, Allocator::Temporary);
			EXPECT_TRUE(manager.get_static_size() == 24);
			void* persistent = manager.allocate(24, Allocator::Persistent);
			EXPECT_TRUE(manager.get_static_size() == 48);
			void* def = manager.allocate(24, Allocator::Default);
			EXPECT_TRUE(manager.get_static_size() == 48);
			manager.deallocate(def, 24, Allocator::Default);
			EXPECT_TRUE(manager.get_static_size() == 48);
			manager.deallocate(persistent, 24, Allocator::Persistent);
			EXPECT_TRUE(manager.get_static_size() == 24);
			manager.deallocate(temporary, 24, Allocator::Temporary);
			EXPECT_TRUE(manager.get_static_size() == 0);
		}

		TEST("Get Dynamic Size")
		{
			MemoryManager manager(builder);
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
			void* temporary = manager.allocate(24, Allocator::Temporary);
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
			void* persistent = manager.allocate(24, Allocator::Persistent);
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
			void* def = manager.allocate(24, Allocator::Default);
			EXPECT_TRUE(manager.get_dynamic_size() == 24);
			manager.deallocate(def, 24, Allocator::Default);
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
			manager.deallocate(persistent, 24, Allocator::Persistent);
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
			manager.deallocate(temporary, 24, Allocator::Temporary);
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
		}

		TEST("Update")
		{
			MemoryManager manager(builder);

			for (Size i = 0; i < MemoryManager::TASK_MEMORY_COUNT + 1; i++)
			{
				EXPECT_SUCCESS(manager.allocate(1024, Allocator::Temporary));
				EXPECT_FAIL(manager.allocate(1024, Allocator::Temporary));

				EXPECT_SUCCESS(manager.allocate(1024, Allocator::Task));
				EXPECT_FAIL(manager.allocate(1024, Allocator::Task));

				manager.update();
			}
		}

		TEST("Allocate")
		{
			void* temporary = nullptr;
			void* task = nullptr;
			void* persistent = nullptr;
			void* def = nullptr;

			MemoryManager manager(builder);
			EXPECT_FAIL(manager.allocate(0, Allocator::Temporary));
			EXPECT_FAIL(manager.allocate(0, Allocator::Task));
			EXPECT_FAIL(manager.allocate(0, Allocator::Persistent));
			EXPECT_FAIL(manager.allocate(0, Allocator::Default));

			EXPECT_FAIL(manager.allocate(2048, Allocator::Temporary));
			EXPECT_FAIL(manager.allocate(2048, Allocator::Task));
			EXPECT_FAIL(manager.allocate(2048, Allocator::Persistent));
			EXPECT_SUCCESS(def = manager.allocate(2048, Allocator::Default));
			manager.deallocate(def, 2048, Allocator::Default);

			temporary = manager.allocate(1024, Allocator::Temporary);
			EXPECT_TRUE(temporary != nullptr);

			task = manager.allocate(1024, Allocator::Task);
			EXPECT_TRUE(task != nullptr);

			persistent = manager.allocate(1024, Allocator::Persistent);
			EXPECT_TRUE(persistent != nullptr);

			def = manager.allocate(1024, Allocator::Default);
			EXPECT_TRUE(def != nullptr);
			manager.deallocate(def, 1024, Allocator::Default);
		}

		TEST("Deallocate")
		{
			MemoryManager manager(builder);
			EXPECT_FAIL(manager.deallocate(nullptr, 24, Allocator::Temporary));
			EXPECT_FAIL(manager.deallocate(nullptr, 24, Allocator::Task));
			EXPECT_FAIL(manager.deallocate(nullptr, 24, Allocator::Persistent));
			EXPECT_FAIL(manager.deallocate(nullptr, 24, Allocator::Default));

			void* temporary = manager.allocate(24, Allocator::Temporary);
			EXPECT_FAIL(manager.deallocate(nullptr, 24, Allocator::Temporary));
			EXPECT_FAIL(manager.deallocate(temporary, 0, Allocator::Temporary));
			EXPECT_SUCCESS(manager.deallocate(temporary, 24, Allocator::Temporary));

			manager.allocate(24, Allocator::Temporary);
			manager.update();
			EXPECT_FAIL(manager.deallocate(temporary, 24, Allocator::Temporary));

			void* task = manager.allocate(24, Allocator::Task);
			EXPECT_FAIL(manager.deallocate(nullptr, 24, Allocator::Task));
			EXPECT_FAIL(manager.deallocate(task, 0, Allocator::Task));
			EXPECT_FAIL(manager.deallocate(task, 24, Allocator::Default));
			EXPECT_SUCCESS(manager.deallocate(task, 24, Allocator::Task));

			void* persistent = manager.allocate(24, Allocator::Persistent);
			EXPECT_FAIL(manager.deallocate(nullptr, 24, Allocator::Persistent));
			EXPECT_FAIL(manager.deallocate(persistent, 0, Allocator::Persistent));
			EXPECT_FAIL(manager.deallocate(persistent, 24, Allocator::Default));
			EXPECT_SUCCESS(manager.deallocate(persistent, 24, Allocator::Persistent));

			void* def = manager.allocate(24, Allocator::Default);
			EXPECT_FAIL(manager.deallocate(nullptr, 24, Allocator::Default));
			EXPECT_FAIL(manager.deallocate(def, 0, Allocator::Default));
			EXPECT_FAIL(manager.deallocate(def, 24, Allocator::Temporary));
			EXPECT_SUCCESS(manager.deallocate(def, 24, Allocator::Default));

			EXPECT_TRUE(manager.get_static_size() == 0);
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
		}
	}

	CATEGORY(Vector::Iterator)
	{
		TEST("Copy Constructor")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			Vector<int>::Iterator copy(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.end());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Move Constructor")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			Vector<int>::Iterator copy(std::move(it));
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.end());
			it = test.begin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Copy Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			Vector<int>::Iterator copy = it;
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.end());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Move Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			Vector<int>::Iterator copy = std::move(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.end());
			it = test.begin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Dereference Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
			EXPECT_TRUE(it + 3 == test.end());
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(++it == test.end());
			it = test.begin();
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(it == test.end());
		}

		TEST("Decrement Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.end();
			EXPECT_TRUE(*(it - 1) == 5);
			EXPECT_TRUE(*(it - 2) == 5);
			EXPECT_TRUE(it - 3 == test.begin());
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(--it == test.begin());
			it = test.end();
			it--;
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(it == test.begin());
		}

		TEST("Addition Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.end();
			EXPECT_TRUE(it - 3 == test.begin());
			EXPECT_TRUE(it - 2 == test.begin() + 1);
			EXPECT_TRUE(it - 1 == test.begin() + 2);
		}

		TEST("Equal Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			Vector<int>::Iterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.begin());
			EXPECT_TRUE(test.begin() == it);
			EXPECT_TRUE(copy == test.begin());
			EXPECT_TRUE(test.begin() == copy);
		}

		TEST("Not Equal Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			Vector<int>::Iterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.begin()));
			EXPECT_TRUE(!(test.begin() != it));
			EXPECT_TRUE(!(copy != test.begin()));
			EXPECT_TRUE(!(test.begin() != copy));
		}
	}

	CATEGORY(Vector::ConstIterator)
	{
		TEST("Copy Constructor")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			Vector<int>::ConstIterator copy(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.cend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.cend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.cend());
		}

		TEST("Move Constructor")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			Vector<int>::ConstIterator copy(std::move(it));
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.cend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.cend());
			it = test.cbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.cend());
		}

		TEST("Copy Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			Vector<int>::ConstIterator copy = it;
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.cend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.cend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.cend());
		}

		TEST("Move Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			Vector<int>::ConstIterator copy = std::move(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.cend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.cend());
			it = test.cbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.cend());
		}

		TEST("Dereference Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
			EXPECT_TRUE(it + 3 == test.cend());
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(++it == test.cend());
			it = test.cbegin();
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(it == test.cend());
		}

		TEST("Decrement Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cend();
			EXPECT_TRUE(*(it - 1) == 5);
			EXPECT_TRUE(*(it - 2) == 5);
			EXPECT_TRUE(it - 3 == test.cbegin());
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(--it == test.cbegin());
			it = test.cend();
			it--;
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(it == test.cbegin());
		}

		TEST("Addition Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cend();
			EXPECT_TRUE(it - 3 == test.cbegin());
			EXPECT_TRUE(it - 2 == test.cbegin() + 1);
			EXPECT_TRUE(it - 1 == test.cbegin() + 2);
		}

		TEST("Equal Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			Vector<int>::ConstIterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.cbegin());
			EXPECT_TRUE(test.cbegin() == it);
			EXPECT_TRUE(copy == test.cbegin());
			EXPECT_TRUE(test.cbegin() == copy);
		}

		TEST("Not Equal Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			Vector<int>::ConstIterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.cbegin()));
			EXPECT_TRUE(!(test.cbegin() != it));
			EXPECT_TRUE(!(copy != test.cbegin()));
			EXPECT_TRUE(!(test.cbegin() != copy));
		}
	}

	CATEGORY(Vector::ReverseIterator)
	{
		TEST("Copy Constructor")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			Vector<int>::ReverseIterator copy(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.rend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.rend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.rend());
		}

		TEST("Move Constructor")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			Vector<int>::ReverseIterator copy(std::move(it));
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.rend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.rend());
			it = test.rbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.rend());
		}

		TEST("Copy Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			Vector<int>::ReverseIterator copy = it;
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.rend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.rend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.rend());
		}

		TEST("Move Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			Vector<int>::ReverseIterator copy = std::move(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.rend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.rend());
			it = test.rbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.rend());
		}

		TEST("Dereference Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
			EXPECT_TRUE(it + 3 == test.rend());
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(++it == test.rend());
			it = test.rbegin();
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(it == test.rend());
		}

		TEST("Decrement Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rend();
			EXPECT_TRUE(*(it - 1) == 5);
			EXPECT_TRUE(*(it - 2) == 5);
			EXPECT_TRUE(it - 3 == test.rbegin());
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(--it == test.rbegin());
			it = test.rend();
			it--;
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(it == test.rbegin());
		}

		TEST("Addition Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rend();
			EXPECT_TRUE(it - 3 == test.rbegin());
			EXPECT_TRUE(it - 2 == test.rbegin() + 1);
			EXPECT_TRUE(it - 1 == test.rbegin() + 2);
		}

		TEST("Equal Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			Vector<int>::ReverseIterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.rbegin());
			EXPECT_TRUE(test.rbegin() == it);
			EXPECT_TRUE(copy == test.rbegin());
			EXPECT_TRUE(test.rbegin() == copy);
		}

		TEST("Not Equal Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			Vector<int>::ReverseIterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.rbegin()));
			EXPECT_TRUE(!(test.rbegin() != it));
			EXPECT_TRUE(!(copy != test.rbegin()));
			EXPECT_TRUE(!(test.rbegin() != copy));
		}
	}

	CATEGORY(Vector::ConstReverseIterator)
	{
		TEST("Copy Constructor")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			Vector<int>::ConstReverseIterator copy(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.crend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.crend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.crend());
		}

		TEST("Move Constructor")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			Vector<int>::ConstReverseIterator copy(std::move(it));
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.crend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.crend());
			it = test.crbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.crend());
		}

		TEST("Copy Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			Vector<int>::ConstReverseIterator copy = it;
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.crend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.crend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.crend());
		}

		TEST("Move Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			Vector<int>::ConstReverseIterator copy = std::move(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.crend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.crend());
			it = test.crbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.crend());
		}

		TEST("Dereference Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
			EXPECT_TRUE(it + 3 == test.crend());
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(++it == test.crend());
			it = test.crbegin();
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(it == test.crend());
		}

		TEST("Decrement Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crend();
			EXPECT_TRUE(*(it - 1) == 5);
			EXPECT_TRUE(*(it - 2) == 5);
			EXPECT_TRUE(it - 3 == test.crbegin());
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(--it == test.crbegin());
			it = test.crend();
			it--;
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(it == test.crbegin());
		}

		TEST("Addition Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crend();
			EXPECT_TRUE(it - 3 == test.crbegin());
			EXPECT_TRUE(it - 2 == test.crbegin() + 1);
			EXPECT_TRUE(it - 1 == test.crbegin() + 2);
		}

		TEST("Equal Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			Vector<int>::ConstReverseIterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.crbegin());
			EXPECT_TRUE(test.crbegin() == it);
			EXPECT_TRUE(copy == test.crbegin());
			EXPECT_TRUE(test.crbegin() == copy);
		}

		TEST("Not Equal Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			Vector<int>::ConstReverseIterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.crbegin()));
			EXPECT_TRUE(!(test.crbegin() != it));
			EXPECT_TRUE(!(copy != test.crbegin()));
			EXPECT_TRUE(!(test.crbegin() != copy));
		}
	}

	CATEGORY(Vector)
	{
		TEST("Default Constructor")
		{
			Vector<int> vec;
			EXPECT_TRUE(vec.get_size() == 0);
			EXPECT_TRUE(vec.get_capacity() == 0);
			EXPECT_TRUE(vec.get_data() == nullptr);
		}

		TEST("Capacity Constructor")
		{
			Vector<int> vec(10);
			EXPECT_TRUE(vec.get_size() == 0);
			EXPECT_TRUE(vec.get_capacity() == 10);
			EXPECT_TRUE(vec.get_data() != nullptr);

			Vector<int> vec2(0);
			EXPECT_TRUE(vec2.get_size() == 0);
			EXPECT_TRUE(vec2.get_capacity() == 0);
			EXPECT_TRUE(vec2.get_data() == nullptr);
		}

		TEST("Value Constructor")
		{
			Vector<int> vec(10, 5);
			EXPECT_TRUE(vec.get_size() == 10);
			EXPECT_TRUE(vec.get_capacity() == 10);
			EXPECT_TRUE(vec.get_data() != nullptr);
			for (Size i = 0; i < vec.get_size(); i++)
			{
				EXPECT_TRUE(vec[i] == 5);
			}

			Vector<int> vec2(0, 0);
			EXPECT_TRUE(vec2.get_size() == 0);
			EXPECT_TRUE(vec2.get_capacity() == 0);
			EXPECT_TRUE(vec2.get_data() == nullptr);
		}

		TEST("Initializer List Constructor")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.get_size() == 5);
			EXPECT_TRUE(vec.get_capacity() == 5);
			EXPECT_TRUE(vec.get_data() != nullptr);
			for (Size i = 0; i < vec.get_size(); i++)
			{
				EXPECT_TRUE(vec[i] == i);
			}

			Vector<int> vec2({});
			EXPECT_TRUE(vec2.get_size() == 0);
			EXPECT_TRUE(vec2.get_capacity() == 0);
			EXPECT_TRUE(vec2.get_data() == nullptr);
		}

		TEST("Copy Constructor")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			Vector<int> copy(vec);
			EXPECT_TRUE(copy.get_size() == 5);
			EXPECT_TRUE(copy.get_capacity() == 5);
			EXPECT_TRUE(copy.get_data() != nullptr);
			for (Size i = 0; i < copy.get_size(); i++)
			{
				EXPECT_TRUE(copy[i] == i);
			}
		}

		TEST("Move Constructor")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			Vector<int> copy(std::move(vec));
			EXPECT_TRUE(copy.get_size() == 5);
			EXPECT_TRUE(copy.get_capacity() == 5);
			EXPECT_TRUE(copy.get_data() != nullptr);
			for (Size i = 0; i < copy.get_size(); i++)
			{
				EXPECT_TRUE(copy[i] == i);
			}
		}

		TEST("Copy Operator")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			Vector<int> copy = vec;
			EXPECT_TRUE(copy.get_size() == 5);
			EXPECT_TRUE(copy.get_capacity() == 5);
			EXPECT_TRUE(copy.get_data() != nullptr);
			for (Size i = 0; i < copy.get_size(); i++)
			{
				EXPECT_TRUE(copy[i] == i);
			}
		}

		TEST("Move Operator")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			Vector<int> copy = std::move(vec);
			EXPECT_TRUE(copy.get_size() == 5);
			EXPECT_TRUE(copy.get_capacity() == 5);
			EXPECT_TRUE(copy.get_data() != nullptr);
			for (Size i = 0; i < copy.get_size(); i++)
			{
				EXPECT_TRUE(copy[i] == i);
			}
		}

		TEST("Index Operator")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 2);
			EXPECT_TRUE(vec[3] == 3);
			EXPECT_TRUE(vec[4] == 4);
			EXPECT_FAIL(vec[5]);
		}

		TEST("Const Index Operator")
		{
			Vector<int> const vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 2);
			EXPECT_TRUE(vec[3] == 3);
			EXPECT_TRUE(vec[4] == 4);
			EXPECT_FAIL(vec[5]);
		}

		TEST("Get Capacity")
		{
			Vector<int> vec(10);
			EXPECT_TRUE(vec.get_capacity() == 10);

			Vector<int> vec2;
			EXPECT_TRUE(vec2.get_capacity() == 0);
		}

		TEST("Get Size")
		{
			Vector<int> vec(10);
			EXPECT_TRUE(vec.get_size() == 0);

			vec.resize(5);
			EXPECT_TRUE(vec.get_size() == 5);
		}

		TEST("Get Data")
		{
			Vector<int> vec(10);
			EXPECT_TRUE(vec.get_data() != nullptr);
			Vector<int> vec2;
			EXPECT_TRUE(vec2.get_data() == nullptr);
		}

		TEST("Const Get Data")
		{
			Vector<int> const vec(10);
			EXPECT_TRUE(vec.get_data() != nullptr);
			Vector<int> const vec2;
			EXPECT_TRUE(vec2.get_data() == nullptr);
		}

		TEST("Reserve")
		{
			Vector<int> vec(10);
			vec.reserve(20);
			EXPECT_TRUE(vec.get_capacity() == 20);
			vec.reserve(5);
			EXPECT_TRUE(vec.get_capacity() == 20);
		}

		TEST("Resize")
		{
			Vector<int> vec(10);
			vec.resize(5);
			EXPECT_TRUE(vec.get_size() == 5);
			vec.resize(10);
			EXPECT_TRUE(vec.get_size() == 10);
			vec.resize(0);
			EXPECT_TRUE(vec.get_size() == 0);
			EXPECT_TRUE(vec.get_capacity() == 10);
			vec.resize(20);
			EXPECT_TRUE(vec.get_size() == 20);
			EXPECT_TRUE(vec.get_capacity() == 20);
		}

		TEST("Add Index Copy")
		{
			Vector<String> vec(10);
			String str = "5";
			vec.add(str);
			EXPECT_TRUE(vec.get_size() == 1);
			EXPECT_TRUE(vec[0] == "5");
			str = "10";
			vec.add(str);
			EXPECT_TRUE(vec.get_size() == 2);
			EXPECT_TRUE(vec[1] == "10");
		}

		TEST("Add Index Move")
		{
			Vector<String> vec(10);
			String str = "5";
			vec.add(std::move(str));
			EXPECT_TRUE(vec.get_size() == 1);
			EXPECT_TRUE(vec[0] == "5");
			str = "10";
			vec.add(std::move(str));
			EXPECT_TRUE(vec.get_size() == 2);
			EXPECT_TRUE(vec[1] == "10");
		}

		TEST("Add Range")
		{
			Vector<int> vec(10);
			Vector<int> range({ 0, 1, 2, 3, 4 });
			vec.add(range.begin(), range.end());
			EXPECT_TRUE(vec.get_size() == 5);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 2);
			EXPECT_TRUE(vec[3] == 3);
			EXPECT_TRUE(vec[4] == 4);
		}

		TEST("Insert Index Copy")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			vec.insert(2, 5);
			EXPECT_TRUE(vec.get_size() == 6);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 5);
			EXPECT_TRUE(vec[3] == 2);
			EXPECT_TRUE(vec[4] == 3);
			EXPECT_TRUE(vec[5] == 4);
			vec.insert(0, 6);
			EXPECT_TRUE(vec.get_size() == 7);
			EXPECT_TRUE(vec[0] == 6);
			EXPECT_TRUE(vec[1] == 0);
			EXPECT_TRUE(vec[2] == 1);
			EXPECT_TRUE(vec[3] == 5);
			EXPECT_TRUE(vec[4] == 2);
			EXPECT_TRUE(vec[5] == 3);
			EXPECT_TRUE(vec[6] == 4);
			vec.insert(7, 7);
			EXPECT_TRUE(vec.get_size() == 8);
			EXPECT_TRUE(vec[0] == 6);
			EXPECT_TRUE(vec[1] == 0);
			EXPECT_TRUE(vec[2] == 1);
			EXPECT_TRUE(vec[3] == 5);
			EXPECT_TRUE(vec[4] == 2);
			EXPECT_TRUE(vec[5] == 3);
			EXPECT_TRUE(vec[6] == 4);
			EXPECT_TRUE(vec[7] == 7);
		}

		TEST("Insert Index Move")
		{
			Vector<String> vec({ "0", "1", "2", "3", "4" });
			String str = "5";
			vec.insert(2, std::move(str));
			EXPECT_TRUE(vec.get_size() == 6);
			EXPECT_TRUE(vec[0] == "0");
			EXPECT_TRUE(vec[1] == "1");
			EXPECT_TRUE(vec[2] == "5");
			EXPECT_TRUE(vec[3] == "2");
			EXPECT_TRUE(vec[4] == "3");
			EXPECT_TRUE(vec[5] == "4");
			str = "6";
			vec.insert(0, std::move(str));
			EXPECT_TRUE(vec.get_size() == 7);
			EXPECT_TRUE(vec[0] == "6");
			EXPECT_TRUE(vec[1] == "0");
			EXPECT_TRUE(vec[2] == "1");
			EXPECT_TRUE(vec[3] == "5");
			EXPECT_TRUE(vec[4] == "2");
			EXPECT_TRUE(vec[5] == "3");
			EXPECT_TRUE(vec[6] == "4");
			str = "7";
			vec.insert(7, std::move(str));
			EXPECT_TRUE(vec.get_size() == 8);
			EXPECT_TRUE(vec[0] == "6");
			EXPECT_TRUE(vec[1] == "0");
			EXPECT_TRUE(vec[2] == "1");
			EXPECT_TRUE(vec[3] == "5");
			EXPECT_TRUE(vec[4] == "2");
			EXPECT_TRUE(vec[5] == "3");
			EXPECT_TRUE(vec[6] == "4");
			EXPECT_TRUE(vec[7] == "7");
		}

		TEST("Insert Iterator Copy")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			Vector<int> range({ 5, 6, 7 });
			vec.insert(vec.begin() + 2, range.begin(), range.end());
			EXPECT_TRUE(vec.get_size() == 8);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 5);
			EXPECT_TRUE(vec[3] == 6);
			EXPECT_TRUE(vec[4] == 7);
			EXPECT_TRUE(vec[5] == 2);
			EXPECT_TRUE(vec[6] == 3);
			EXPECT_TRUE(vec[7] == 4);
		}

		TEST("Insert Iterator Move")
		{
			Vector<String> vec({ "0", "1", "2", "3", "4" });
			Vector<String> range({ "5", "6", "7" });
			vec.insert(vec.begin() + 2, range.begin(), range.end());
			EXPECT_TRUE(vec.get_size() == 8);
			EXPECT_TRUE(vec[0] == "0");
			EXPECT_TRUE(vec[1] == "1");
			EXPECT_TRUE(vec[2] == "5");
			EXPECT_TRUE(vec[3] == "6");
			EXPECT_TRUE(vec[4] == "7");
			EXPECT_TRUE(vec[5] == "2");
			EXPECT_TRUE(vec[6] == "3");
			EXPECT_TRUE(vec[7] == "4");
		}

		TEST("Insert Index Range")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			Vector<int> range({ 5, 6, 7 });
			vec.insert(2, range.begin(), range.end());
			EXPECT_TRUE(vec.get_size() == 8);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 5);
			EXPECT_TRUE(vec[3] == 6);
			EXPECT_TRUE(vec[4] == 7);
			EXPECT_TRUE(vec[5] == 2);
			EXPECT_TRUE(vec[6] == 3);
			EXPECT_TRUE(vec[7] == 4);
		}

		TEST("Insert Iterator Range")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			Vector<int> range({ 5, 6, 7 });
			vec.insert(vec.begin() + 2, range.begin(), range.end());
			EXPECT_TRUE(vec.get_size() == 8);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 5);
			EXPECT_TRUE(vec[3] == 6);
			EXPECT_TRUE(vec[4] == 7);
			EXPECT_TRUE(vec[5] == 2);
			EXPECT_TRUE(vec[6] == 3);
			EXPECT_TRUE(vec[7] == 4);
		}

		TEST("Remove Index")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			vec.remove(2);
			EXPECT_TRUE(vec.get_size() == 4);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 3);
			EXPECT_TRUE(vec[3] == 4);
			vec.remove(0);
			EXPECT_TRUE(vec.get_size() == 3);
			EXPECT_TRUE(vec[0] == 1);
			EXPECT_TRUE(vec[1] == 3);
			EXPECT_TRUE(vec[2] == 4);
			vec.remove(2);
			EXPECT_TRUE(vec.get_size() == 2);
			EXPECT_TRUE(vec[0] == 1);
			EXPECT_TRUE(vec[1] == 3);
			vec.remove(1);
			EXPECT_TRUE(vec.get_size() == 1);
			EXPECT_TRUE(vec[0] == 1);
			vec.remove(0);
			EXPECT_TRUE(vec.get_size() == 0);
		}

		TEST("Remove Iterator")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			vec.remove(vec.begin() + 2);
			EXPECT_TRUE(vec.get_size() == 4);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 3);
			EXPECT_TRUE(vec[3] == 4);
			vec.remove(vec.begin());
			EXPECT_TRUE(vec.get_size() == 3);
			EXPECT_TRUE(vec[0] == 1);
			EXPECT_TRUE(vec[1] == 3);
			EXPECT_TRUE(vec[2] == 4);
			vec.remove(vec.begin() + 2);
			EXPECT_TRUE(vec.get_size() == 2);
			EXPECT_TRUE(vec[0] == 1);
			EXPECT_TRUE(vec[1] == 3);
			vec.remove(vec.begin() + 1);
			EXPECT_TRUE(vec.get_size() == 1);
			EXPECT_TRUE(vec[0] == 1);
			vec.remove(vec.begin());
			EXPECT_TRUE(vec.get_size() == 0);
		}

		TEST("Remove Index Range")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			vec.remove(1, 3);
			EXPECT_TRUE(vec.get_size() == 2);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 4);
			vec.remove(0, 1);
			EXPECT_TRUE(vec.get_size() == 1);
			EXPECT_TRUE(vec[0] == 4);
			EXPECT_FAIL(vec.remove(0, 0));
			EXPECT_TRUE(vec.get_size() == 1);
			EXPECT_TRUE(vec[0] == 4);
			vec.remove(0, 1);
			EXPECT_TRUE(vec.get_size() == 0);
		}

		TEST("Remove Iterator Range")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			vec.remove(vec.begin() + 1, vec.begin() + 4);
			EXPECT_TRUE(vec.get_size() == 2);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 4);
			vec.remove(vec.begin(), vec.begin() + 1);
			EXPECT_TRUE(vec.get_size() == 1);
			EXPECT_TRUE(vec[0] == 4);
			EXPECT_FAIL(vec.remove(vec.begin(), vec.begin()));
			EXPECT_TRUE(vec.get_size() == 1);
			EXPECT_TRUE(vec[0] == 4);
			vec.remove(vec.begin(), vec.begin() + 1);
			EXPECT_TRUE(vec.get_size() == 0);
		}

		TEST("Is Empty")
		{
			Vector<int> vec;
			EXPECT_TRUE(vec.is_empty());
			vec.add(0);
			EXPECT_TRUE(!vec.is_empty());
			vec.remove(0);
			EXPECT_TRUE(vec.is_empty());
		}

		TEST("At")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.at(0) == 0);
			EXPECT_TRUE(vec.at(1) == 1);
			EXPECT_TRUE(vec.at(2) == 2);
			EXPECT_TRUE(vec.at(3) == 3);
			EXPECT_TRUE(vec.at(4) == 4);
			EXPECT_FAIL(vec.at(5));
			vec.at(0) = 5;
			EXPECT_TRUE(vec.at(0) == 5);
		}

		TEST("Const At")
		{
			Vector<int> const vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.at(0) == 0);
			EXPECT_TRUE(vec.at(1) == 1);
			EXPECT_TRUE(vec.at(2) == 2);
			EXPECT_TRUE(vec.at(3) == 3);
			EXPECT_TRUE(vec.at(4) == 4);
			EXPECT_FAIL(vec.at(5));
		}

		TEST("Sub")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			Vector<int> sub = vec.sub(2, 2);
			EXPECT_TRUE(sub.get_size() == 2);
			EXPECT_TRUE(sub[0] == 2);
			EXPECT_TRUE(sub[1] == 3);
		}

		TEST("Find")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.find(0) == vec.begin());
			EXPECT_TRUE(vec.find(1) == vec.begin() + 1);
			EXPECT_TRUE(vec.find(2) == vec.begin() + 2);
			EXPECT_TRUE(vec.find(3) == vec.begin() + 3);
			EXPECT_TRUE(vec.find(4) == vec.begin() + 4);
			EXPECT_TRUE(vec.find(5) == vec.end());
		}

		TEST("Const Find")
		{
			Vector<int> const vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.find(0) == vec.cbegin());
			EXPECT_TRUE(vec.find(1) == vec.cbegin() + 1);
			EXPECT_TRUE(vec.find(2) == vec.cbegin() + 2);
			EXPECT_TRUE(vec.find(3) == vec.cbegin() + 3);
			EXPECT_TRUE(vec.find(4) == vec.cbegin() + 4);
			EXPECT_TRUE(vec.find(5) == vec.cend());
		}

		TEST("Contains")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.contains(0));
			EXPECT_TRUE(vec.contains(1));
			EXPECT_TRUE(vec.contains(2));
			EXPECT_TRUE(vec.contains(3));
			EXPECT_TRUE(vec.contains(4));
			EXPECT_TRUE(!vec.contains(5));
		}

		TEST("Begin")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(*vec.begin() == 0);
		}

		TEST("Const Begin")
		{
			Vector<int> const vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(*vec.cbegin() == 0);
		}

		TEST("End")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.end() == vec.begin() + 5);
		}

		TEST("Const End")
		{
			Vector<int> const vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.cend() == vec.cbegin() + 5);
		}

		TEST("Reverse Begin")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(*vec.rbegin() == 4);
		}

		TEST("Reverse End")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.rend() == vec.rbegin() + 5);
		}

		TEST("Const Reverse Begin")
		{
			Vector<int> const vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(*vec.crbegin() == 4);
		}

		TEST("Const Reverse End")
		{
			Vector<int> const vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.crend() == vec.crbegin() + 5);
		}
	}

	CATEGORY(Pair)
	{
		TEST("Copy/Copy Constructor")
		{
			String first = "first";
			String second = "second";
			Pair<String, String> pair(first, second);
			EXPECT_TRUE(first == "first");
			EXPECT_TRUE(second == "second");
			EXPECT_TRUE(pair.first == "first");
			EXPECT_TRUE(pair.second == "second");
		}

		TEST("Move/Copy Constructor")
		{
			String first = "first";
			String second = "second";
			Pair<String, String> pair(std::move(first), second);
			EXPECT_TRUE(first == "");
			EXPECT_TRUE(second == "second");
			EXPECT_TRUE(pair.first == "first");
			EXPECT_TRUE(pair.second == "second");
		}

		TEST("Copy/Move Constructor")
		{
			String first = "first";
			String second = "second";
			Pair<String, String> pair(first, std::move(second));
			EXPECT_TRUE(first == "first");
			EXPECT_TRUE(second == "");
			EXPECT_TRUE(pair.first == "first");
			EXPECT_TRUE(pair.second == "second");
		}

		TEST("Move/Move Constructor")
		{
			String first = "first";
			String second = "second";
			Pair<String, String> pair(std::move(first), std::move(second));
			EXPECT_TRUE(first == "");
			EXPECT_TRUE(second == "");
			EXPECT_TRUE(pair.first == "first");
			EXPECT_TRUE(pair.second == "second");
		}

		TEST("Copy Constructor")
		{
			Pair<String, String> pair("First", "Second");
			Pair<String, String> copy(pair);
			EXPECT_TRUE(pair.first == "First");
			EXPECT_TRUE(pair.second == "Second");
			EXPECT_TRUE(copy.first == "First");
			EXPECT_TRUE(copy.second == "Second");
		}

		TEST("Move Constructor")
		{
			Pair<String, String> pair("First", "Second");
			Pair<String, String> copy(std::move(pair));
			EXPECT_TRUE(pair.first == "");
			EXPECT_TRUE(pair.second == "");
			EXPECT_TRUE(copy.first == "First");
			EXPECT_TRUE(copy.second == "Second");
		}

		TEST("Copy Operator")
		{
			Pair<String, String> pair("First", "Second");
			Pair<String, String> copy = pair;
			EXPECT_TRUE(pair.first == "First");
			EXPECT_TRUE(pair.second == "Second");
			EXPECT_TRUE(copy.first == "First");
			EXPECT_TRUE(copy.second == "Second");
		}

		TEST("Move Operator")
		{
			Pair<String, String> pair("First", "Second");
			Pair<String, String> copy = std::move(pair);
			EXPECT_TRUE(pair.first == "");
			EXPECT_TRUE(pair.second == "");
			EXPECT_TRUE(copy.first == "First");
			EXPECT_TRUE(copy.second == "Second");
		}

		TEST("Equal Operator")
		{
			Pair<int, int> pair(4, 2);
			Pair<int, int> copy = pair;
			EXPECT_TRUE(pair == copy);
			EXPECT_TRUE(copy == pair);
			Pair<int, int> pair2(2, 2);
			EXPECT_TRUE(!(pair == pair2));
		}

		TEST("Not Equal Operator")
		{
			Pair<int, int> pair(4, 2);
			Pair<int, int> copy(4, 3);
			EXPECT_TRUE(pair != copy);
			EXPECT_TRUE(copy != pair);
			Pair<int, int> pair2(4, 2);
			EXPECT_TRUE(!(pair != pair2));
		}

		TEST("Less Than Operator")
		{
			Pair<int, int> pair(4, 2);
			Pair<int, int> copy(4, 3);
			EXPECT_TRUE(pair < copy);
			EXPECT_TRUE(!(copy < pair));
			copy = pair;
			EXPECT_TRUE(!(pair < copy));
			EXPECT_TRUE(!(copy < pair));
		}

		TEST("Less Than or Equal To Operator")
		{
			Pair<int, int> pair(4, 2);
			Pair<int, int> copy(4, 3);
			EXPECT_TRUE(pair <= copy);
			EXPECT_TRUE(!(copy <= pair));
			copy = pair;
			EXPECT_TRUE(pair <= copy);
			EXPECT_TRUE(copy <= pair);
		}

		TEST("Greater Than Operator")
		{
			Pair<int, int> pair(4, 2);
			Pair<int, int> copy(4, 3);
			EXPECT_TRUE(copy > pair);
			EXPECT_TRUE(!(pair > copy));
			copy = pair;
			EXPECT_TRUE(!(pair > copy));
			EXPECT_TRUE(!(copy > pair));
		}

		TEST("Greater Than or Equal To Operator")
		{
			Pair<int, int> pair(4, 2);
			Pair<int, int> copy(4, 3);
			EXPECT_TRUE(copy >= pair);
			EXPECT_TRUE(!(pair >= copy));
			copy = pair;
			EXPECT_TRUE(pair >= copy);
			EXPECT_TRUE(copy >= pair);
		}
	}

#pragma endregion

#pragma region Test Teardown

	// restore stdout and stderr
	RESTORE_OUTPUT();

	// print results
	std::cout << "\nFinal Results:\n";
	for (auto const& categoryName : categoryNames)
	{
		int categoryIndex = categories[categoryName];
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
