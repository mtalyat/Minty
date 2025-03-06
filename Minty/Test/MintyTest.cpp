#include "MintyTest.h"

// runs all of the tests
static void run_tests()
{
#pragma region Test Setup

	// create the test object
	Test _test;

	// start capturing the output
	_test.capture_output();

#pragma endregion

#pragma region Tests

	// Minty
	test_Minty(_test);

	// Data
	test_Array(_test);
	test_List(_test);
	test_Pair(_test);
	test_String(_test);
	test_Vector(_test);

	// Memory
	test_MemoryManager(_test);
	test_MemoryPool(_test);
	test_MemoryStack(_test);

#pragma endregion

#pragma region Test Teardown

	// restore stdout and stderr
	_test.restore_output();

	_test.print_results();

#pragma endregion
}

int main()
{
	run_tests();
}
