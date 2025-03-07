#include "Test_Color.h"
#include "Minty.h"

void test_Color(Test& _test)
{
	CATEGORY(Color)
	{
		TEST("RGBA Channel_t Constructor")
		{
			Color color(static_cast<Color::Channel_t>(255), static_cast<Color::Channel_t>(127), static_cast<Color::Channel_t>(63), static_cast<Color::Channel_t>(0));
			EXPECT_TRUE(color.r == 255);
			EXPECT_TRUE(color.g == 127);
			EXPECT_TRUE(color.b == 63);
			EXPECT_TRUE(color.a == 0);
			Color color2(static_cast<Color::Channel_t>(0), static_cast<Color::Channel_t>(0), static_cast<Color::Channel_t>(0));
			EXPECT_TRUE(color2.r == 0);
			EXPECT_TRUE(color2.g == 0);
			EXPECT_TRUE(color2.b == 0);
			EXPECT_TRUE(color2.a == 255);
		}

		TEST("RGBA Int Constructor")
		{
			Color color(255, 127, 63, 0);
			EXPECT_TRUE(color.r == 255);
			EXPECT_TRUE(color.g == 127);
			EXPECT_TRUE(color.b == 63);
			EXPECT_TRUE(color.a == 0);
			Color color2(0, 0, 0);
			EXPECT_TRUE(color2.r == 0);
			EXPECT_TRUE(color2.g == 0);
			EXPECT_TRUE(color2.b == 0);
			EXPECT_TRUE(color2.a == 255);
			
			EXPECT_FAIL(Color color3(Color::MAX_CHANNEL + 1, 0, 0));
			EXPECT_FAIL(Color color4(0, Color::MAX_CHANNEL + 1, 0));
			EXPECT_FAIL(Color color5(0, 0, Color::MAX_CHANNEL + 1));
			EXPECT_FAIL(Color color6(0, 0, 0, Color::MAX_CHANNEL + 1));
			EXPECT_FAIL(Color color7(Color::MIN_CHANNEL - 1, 0, 0));
			EXPECT_FAIL(Color color8(0, Color::MIN_CHANNEL - 1, 0));
			EXPECT_FAIL(Color color9(0, 0, Color::MIN_CHANNEL - 1));
			EXPECT_FAIL(Color color10(0, 0, 0, Color::MIN_CHANNEL - 1));
		}

		TEST("RGBA Float Constructor")
		{
			Color color(1.0f, 0.5f, 0.25f, 0.0f);
			EXPECT_TRUE(color.r == 255);
			EXPECT_TRUE(color.g == 127);
			EXPECT_TRUE(color.b == 63);
			EXPECT_TRUE(color.a == 0);
			Color color2(0.0f, 0.0f, 0.0f);
			EXPECT_TRUE(color2.r == 0);
			EXPECT_TRUE(color2.g == 0);
			EXPECT_TRUE(color2.b == 0);
			EXPECT_TRUE(color2.a == 255);

			EXPECT_FAIL(Color color3(1.1f, 0.0f, 0.0f));
			EXPECT_FAIL(Color color4(0.0f, 1.1f, 0.0f));
			EXPECT_FAIL(Color color5(0.0f, 0.0f, 1.1f));
			EXPECT_FAIL(Color color6(0.0f, 0.0f, 0.0f, 1.1f));
			EXPECT_FAIL(Color color7(-0.1f, 0.0f, 0.0f));
			EXPECT_FAIL(Color color8(0.0f, -0.1f, 0.0f));
			EXPECT_FAIL(Color color9(0.0f, 0.0f, -0.1f));
			EXPECT_FAIL(Color color10(0.0f, 0.0f, 0.0f, -0.1f));
		}

		TEST("Value Constructor")
		{
			Color color(0x003F7FFF);
			EXPECT_TRUE(color.r == 255);
			EXPECT_TRUE(color.g == 127);
			EXPECT_TRUE(color.b == 63);
			EXPECT_TRUE(color.a == 0);
			Color color2(0xFF000000);
			EXPECT_TRUE(color2.r == 0);
			EXPECT_TRUE(color2.g == 0);
			EXPECT_TRUE(color2.b == 0);
			EXPECT_TRUE(color2.a == 255);
		}

		TEST("Equal Operator")
		{
			Color color(255, 127, 63, 0);
			Color color2(255, 127, 63, 0);
			EXPECT_TRUE(color == color2);
			EXPECT_TRUE(color2 == color);
			Color color3(0, 0, 0, 255);
			EXPECT_TRUE(!(color == color3));
			EXPECT_TRUE(!(color3 == color));
		}

		TEST("Not Equal Operator")
		{
			Color color(255, 127, 63, 0);
			Color color2(255, 127, 63, 0);
			EXPECT_TRUE(!(color != color2));
			EXPECT_TRUE(!(color2 != color));
			Color color3(0, 0, 0, 255);
			EXPECT_TRUE(color != color3);
			EXPECT_TRUE(color3 != color);
		}

		TEST("Less Than Operator")
		{
			Color color(255, 127, 63, 0);
			Color color2(255, 127, 63, 0);
			EXPECT_TRUE(!(color < color2));
			EXPECT_TRUE(!(color2 < color));
			Color color3(0, 0, 0, 255);
			EXPECT_TRUE(color3 < color);
			EXPECT_TRUE(!(color < color3));
		}

		TEST("Less Than Or Equal Operator")
		{
			Color color(255, 127, 63, 0);
			Color color2(255, 127, 63, 0);
			EXPECT_TRUE(color <= color2);
			EXPECT_TRUE(color2 <= color);
			Color color3(0, 0, 0, 255);
			EXPECT_TRUE(color3 <= color);
			EXPECT_TRUE(!(color <= color3));
		}

		TEST("Greater Than Operator")
		{
			Color color(255, 127, 63, 0);
			Color color2(255, 127, 63, 0);
			EXPECT_TRUE(!(color > color2));
			EXPECT_TRUE(!(color2 > color));
			Color color3(0, 0, 0, 255);
			EXPECT_TRUE(color > color3);
			EXPECT_TRUE(!(color3 > color));
		}

		TEST("Greater Than Or Equal Operator")
		{
			Color color(255, 127, 63, 0);
			Color color2(255, 127, 63, 0);
			EXPECT_TRUE(color >= color2);
			EXPECT_TRUE(color2 >= color);
			Color color3(0, 0, 0, 255);
			EXPECT_TRUE(color >= color3);
			EXPECT_TRUE(!(color3 >= color));
		}
	}
}
