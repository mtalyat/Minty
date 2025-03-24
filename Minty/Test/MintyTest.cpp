// Minty
#include "Test_Minty.h"

// Asset
#include "Test_Asset.h"
#include "Test_AssetManager.h"
#include "Test_GenericAsset.h"

// Core
#include "Test_Base.h"
#include "Test_Compression.h"
#include "Test_Encoding.h"
#include "Test_Math.h"
#include "Test_Type.h"

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
#include "Test_Variable.h"
#include "Test_Vector.h"

// Debug
#include "Test_Debug.h"

// File
#include "Test_File.h"
#include "Test_PhysicalFile.h"
#include "Test_VirtualFile.h"

// Job
#include "Test_JobManager.h"

// Memory
#include "Test_MemoryManager.h"
#include "Test_MemoryPool.h"
#include "Test_MemoryStack.h"

// Render
#include "Test_BufferUsage.h"
#include "Test_Filter.h"
#include "Test_Format.h"
#include "Test_ImageAddressMode.h"
#include "Test_ImageAspect.h"
#include "Test_ImageLayout.h"
#include "Test_ImagePixelFormat.h"
#include "Test_ImageTiling.h"
#include "Test_ImageType.h"
#include "Test_ImageUsage.h"
#include "Test_ShaderCullMode.h"
#include "Test_ShaderInputType.h"
#include "Test_ShaderPrimitiveTopology.h"
#include "Test_ShaderStage.h"

// Serialization
#include "Test_Node.h"
#include "Test_Reader.h"
#include "Test_Writer.h"

// Time
#include "Test_Stopwatch.h"
#include "Test_Time.h"

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

	// Asset
	test_Asset(_test);
	test_AssetManager(_test);
	test_GenericAsset(_test);

	// Console
	test_Debug(_test);

	// Core
	test_Base(_test);
	test_Compression(_test);
	test_Encoding(_test);
	test_Math(_test);
	test_Type(_test);

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
	test_Variable(_test);
	test_Vector(_test);

	// File
	test_File(_test);
	test_PhysicalFile(_test);
	test_VirtualFile(_test);

	// Job
	test_JobManager(_test);

	// Memory
	test_MemoryManager(_test);
	test_MemoryPool(_test);
	test_MemoryStack(_test);

	// Render
	test_BufferUsage(_test);
	test_Filter(_test);
	test_Format(_test);
	test_ImageAddressMode(_test);
	test_ImageAspect(_test);
	test_ImageLayout(_test);
	test_ImagePixelFormat(_test);
	test_ImageTiling(_test);
	test_ImageType(_test);
	test_ImageUsage(_test);
	test_ShaderCullMode(_test);
	test_ShaderInputType(_test);
	test_ShaderPrimitiveTopology(_test);
	test_ShaderStage(_test);

	// Serialization
	test_Node(_test);
	test_Reader(_test);
	test_Writer(_test);

	// Time
	test_Stopwatch(_test);
	test_Time(_test);

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
