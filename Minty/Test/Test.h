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
	std::ostringstream outputStream;

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

	std::string get_output() const { return outputStream.str(); }

	void clear_output() { outputStream.str(""); outputStream.clear(); }

	void set_category(char const* const categoryName);

	void set_test(char const* const testName);

	void pass(char const* const condition, size_t const line);

	void fail(char const* const condition, size_t const line);

	void write_message(std::string const& message);

	void save_results(std::filesystem::path const& path) const;
};

	// category start macro
#define CATEGORY(categoryName) _test.set_category(#categoryName);

	// test start macro
#define TEST(testName) _test.set_test(testName);

	// helper macros
#define PRINT(message) { _test.restore_output(); std::cout << message << std::endl; _test.capture_output(); }
#define WRITE(message) { _test.write_message(message); }
#define CLEAR_OUTPUT() _test.clear_output()
#define GET_OUTPUT() _test.get_output()

	// evaluation macros
#define PASS(condition) _test.pass(#condition, __LINE__)
#define FAIL(condition) _test.fail(#condition, __LINE__)
#define EXPECT_TRUE(condition) try { if(condition) { PASS(condition); } else { FAIL(condition); } } catch(...) { FAIL(condition); }
#define EXPECT_FALSE(condition) EXPECT_TRUE(!(condition))
#define EXPECT_SUCCESS(operation) try { operation; PASS(operation); } catch(...) { FAIL(operation); }
#define EXPECT_FAIL(operation) try { operation; FAIL(operation); } catch(...) { PASS(operation); }
#define EXPECT_EQUAL(expected, actual) EXPECT_TRUE(expected == actual)
#define EXPECT_NOT_EQUAL(expected, actual) EXPECT_TRUE(expected != actual)
#define CLOSE_DELTA 0.01f
#define EXPECT_CLOSE_DELTA(expected, actual, delta) EXPECT_TRUE(std::abs(expected - actual) < delta)
#define EXPECT_CLOSE(expected, actual) EXPECT_TRUE(std::abs(expected - actual) < CLOSE_DELTA)
#define EXPECT_CLOSE_3(expected, actual) EXPECT_TRUE(std::abs(expected.x - actual.x) < CLOSE_DELTA && std::abs(expected.y - actual.y) < CLOSE_DELTA && std::abs(expected.z - actual.z) < CLOSE_DELTA)
#define EXPECT_CLOSE_4(expected, actual) EXPECT_TRUE(std::abs(expected.x - actual.x) < CLOSE_DELTA && std::abs(expected.y - actual.y) < CLOSE_DELTA && std::abs(expected.z - actual.z) < CLOSE_DELTA && std::abs(expected.w - actual.w) < CLOSE_DELTA)
#define EXPECT_OUTPUT(expected) EXPECT_TRUE(GET_OUTPUT() == expected)
#define EXPECT_OUTPUT_SINGLE(operation, expected) try { CLEAR_OUTPUT(); operation; if(GET_OUTPUT() == expected) { PASS(OUTPUT == expected); } else { FAIL(OUTPUT == expected); } } catch(...) { FAIL(OUTPUT == expected); }