#pragma once
#include "Results.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <filesystem>
#include <fstream>

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

	size_t passCount = 0;
	size_t failCount = 0;

private:
	std::string generate_message(char const* const condition, size_t const line, bool const pass) const;

public:
	size_t get_pass_count() const { return passCount; }

	size_t get_fail_count() const { return failCount; }

	double get_pass_rate() const { return failCount == 0 ? 100.0 : static_cast<double>(passCount) / static_cast<double>(passCount + failCount) * 100.0; }

	void capture_output();

	void restore_output();

	void set_category(char const* const categoryName);

	void set_test(char const* const testName);

	void pass(char const* const condition, size_t const line);

	void fail(char const* const condition, size_t const line);

	void save_results(std::filesystem::path const& path) const;
};

	// category start macro
#define CATEGORY(categoryName) _test.set_category(#categoryName);

	// test start macro
#define TEST(testName) _test.set_test(testName);

	// evaluation macros
#define PASS(condition) _test.pass(#condition, __LINE__);
#define FAIL(condition) _test.fail(#condition, __LINE__);
#define EXPECT_TRUE(condition) try { if(condition) { PASS(condition); } else { FAIL(condition); } } catch(...) { FAIL(condition); }
#define EXPECT_SUCCESS(operation) try { operation; PASS(operation); } catch(...) { FAIL(operation); }
#define EXPECT_FAIL(operation) try { operation; FAIL(operation); } catch(...) { PASS(operation); }
#define PRINT(message) { _test.restore_output(); std::cout << message << std::endl; _test.capture_output(); }