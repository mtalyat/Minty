// Minty
#include "Test_Minty.h"

// Core
#include "Test_Base.h"
#include "Test_Compression.h"

// Data
#include "Test_Array.h"
#include "Test_Color.h"
#include "Test_List.h"
#include "Test_Map.h"
#include "Test_Pair.h"
#include "Test_Queue.h"
#include "Test_Set.h"
#include "Test_Stack.h"
#include "Test_String.h"
#include "Test_Vector.h"

// File
#include "Test_PhysicalFile.h"
#include "Test_VirtualFile.h"

// Memory
#include "Test_MemoryManager.h"
#include "Test_MemoryPool.h"
#include "Test_MemoryStack.h"

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

	// Core
	test_Base(_test);
	test_Compression(_test);

	// Data
	test_Array(_test);
	test_Color(_test);
	test_List(_test);
	test_Map(_test);
	test_Pair(_test);
	test_Queue(_test);
	test_Set(_test);
	test_Stack(_test);
	test_String(_test);
	test_Vector(_test);

	// File
	test_PhysicalFile(_test);
	test_VirtualFile(_test);

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
