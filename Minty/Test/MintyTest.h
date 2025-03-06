#pragma once

//#define PRINT_OUTPUT
#include "Test.h"
#include <Minty.h>

using namespace Minty;

// Minty
void test_Minty(Test& _test);

// Data
void test_Array(Test& _test);
void test_List(Test& _test);
void test_Pair(Test& _test);
void test_String(Test& _test);
void test_Vector(Test& _test);

// Memory
void test_MemoryManager(Test& _test);
void test_MemoryPool(Test& _test);
void test_MemoryStack(Test& _test);