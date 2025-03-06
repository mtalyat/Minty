#pragma once
#include "Results.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>

class Test
{
private:
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

public:
	void capture_output()
	{
#ifndef PRINT_OUTPUT
		std::cout.rdbuf(coutStream.rdbuf()); std::cerr.rdbuf(cerrStream.rdbuf());
#endif // PRINT_OUTPUT
	}

	void restore_output()
	{
#ifndef PRINT_OUTPUT
		std::cout.rdbuf(coutBuf); std::cerr.rdbuf(cerrBuf);
#endif // PRINT_OUTPUT
	}

	void set_category(char const* const categoryName)
	{
		currentCategoryName = categoryName;
		restore_output();
		auto found = categories.find(currentCategoryName);
		if (found == categories.end())
		{
			currentCategoryIndex = static_cast<int>(categories.size());
			categories.emplace(currentCategoryName, currentCategoryIndex);
			categoryNames.push_back(currentCategoryName);
			std::cout << "\n\t" << currentCategoryName << std::endl;
		}
		else
		{
			currentCategoryIndex = found->second;
		}
		capture_output();
	}

	void set_test(char const* const testName)
	{
		currentName = testName;
		auto found2 = results.find(currentCategoryIndex);
		if (found2 == results.end())
		{
			results.emplace(currentCategoryIndex, Results());
			currentResults = &results[currentCategoryIndex];
		}
		else
		{
			currentResults = &found2->second;
		}
	}

	void pass()
	{
		currentResults->passes++;
	}

	void fail(char const* const condition, size_t const line)
	{
		currentResults->fails++;
		restore_output();
		std::cout << "\r[\033[91mFAIL\033[0m] " << currentName << " (" << condition << ") [Line " << line << "]" << std::endl;
		capture_output();
	}

	void print_results()
	{
		// print results
		std::cout << "\nResults:\n";
		for (auto const& categoryName : categoryNames)
		{
			int categoryIndex = categories[categoryName];
			Results const& result = results[categoryIndex];

			std::cout << categoryName << " -> ";

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
	}
};

	// category start macro
#define CATEGORY(categoryName) _test.set_category(#categoryName);

	// test start macro
#define TEST(testName) _test.set_test(testName);

	// evaluation macros
#define PASS(condition) _test.pass();
#define FAIL(condition) _test.fail(#condition, __LINE__);
#define EXPECT_TRUE(condition) try { if(condition) { PASS(condition); } else { FAIL(condition); } } catch(...) { FAIL(condition); }
#define EXPECT_SUCCESS(operation) try { operation; PASS(operation); } catch(...) { FAIL(operation); }
#define EXPECT_FAIL(operation) try { operation; FAIL(operation); } catch(...) { PASS(operation); }
#define PRINT(message) { _test.restore_output(); std::cout << message << std::endl; _test.capture_output(); }