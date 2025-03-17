// Minty
#include "Test_Minty.h"

// Core
#include "Test_Base.h"
#include "Test_Compression.h"
#include "Test_Math.h"

// Data
#include "Test_Array.h"
#include "Test_Color.h"
#include "Test_ConstantContainer.h"
#include "Test_DynamicContainer.h"
#include "Test_List.h"
#include "Test_Map.h"
#include "Test_Pair.h"
#include "Test_Queue.h"
#include "Test_Set.h"
#include "Test_Stack.h"
#include "Test_StaticContainer.h"
#include "Test_String.h"
#include "Test_UUID.h"
#include "Test_Vector.h"

// Debug
#include "Test_Debug.h"

// File
#include "Test_File.h"
#include "Test_PhysicalFile.h"
#include "Test_VirtualFile.h"

// Memory
#include "Test_MemoryManager.h"
#include "Test_MemoryPool.h"
#include "Test_MemoryStack.h"

// Serialization
#include "Test_Node.h"

// Wrap
#include "Test_Wrap.h"
#include "Test_Wrapper.h"

// runs all of the tests
static void run_tests()
{
#pragma region Test Setup

	// create the test object
	Test _test;

	std::cout << "Running Minty tests..." << std::endl;

	// start capturing the output
	_test.capture_output();

#pragma endregion

#pragma region Tests

	// Minty
	test_Minty(_test);

	// Console
	test_Debug(_test);

	// Core
	test_Base(_test);
	test_Compression(_test);
	test_Math(_test);

	// Data
	test_Array(_test);
	test_Color(_test);
	test_ConstantContainer(_test);
	test_DynamicContainer(_test);
	test_List(_test);
	test_Map(_test);
	test_Pair(_test);
	test_Queue(_test);
	test_Set(_test);
	test_Stack(_test);
	test_StaticContainer(_test);
	test_String(_test);
	test_UUID(_test);
	test_Vector(_test);

	// File
	test_File(_test);
	test_PhysicalFile(_test);
	test_VirtualFile(_test);

	// Memory
	test_MemoryManager(_test);
	test_MemoryPool(_test);
	test_MemoryStack(_test);

	// Serialization
	test_Node(_test);

	// Wrap
	test_Wrap(_test);
	test_Wrapper(_test);

#pragma endregion

#pragma region Test Teardown

	// restore stdout and stderr
	_test.restore_output();

	// print high level results
	size_t passCount = _test.get_pass_count();
	size_t failCount = _test.get_fail_count();
	double passRate = _test.get_pass_rate();
	std::cout << "Results: ";
	if (failCount == 0)
	{
		// bright green
		std::cout << "\033[92m";
	}
	else
	{
		// bright red
		std::cout << "\033[91m";
	}
	std::cout << passCount << " / " << passCount + failCount << " (" << std::fixed << std::setprecision(2) << passRate << "%)\033[0m\n" << std::endl;

	_test.save_results("MintyTestResults.md");

#pragma endregion
}

int main()
{
	run_tests();
}
