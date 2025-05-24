#include "Test_Encoding.h"
#include "Minty.h"

void test_Encoding(Test& _test)
{
	CATEGORY(Encoding)
	{
		TEST("Encode Base 16")
		{
			Size value = 6023872063743461931;
			String expected = "539917B9E3D40A2B";
			String actual = encode_base16(&value, sizeof(Size));
			EXPECT_EQUAL(actual, expected);
		}

		TEST("Decode Base 16")
		{
			String value = "539917B9E3D40A2B";
			Size expected = 6023872063743461931;
			Size actual;
			decode_base16(value, &actual, sizeof(Size));
			EXPECT_EQUAL(actual, expected);
		}
	}
}
