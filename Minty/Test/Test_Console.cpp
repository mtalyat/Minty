#include "Test_Console.h"
#include "Minty.h"

void test_Console(Test& _test)
{
	CATEGORY(Console)
	{
		TEST("Set Foreground Color")
		{
			EXPECT_OUTPUT_SINGLE(Console::set_foreground_color(Console::Color::Black), "\033[30m");
			EXPECT_OUTPUT_SINGLE(Console::set_foreground_color(Console::Color::Red), "\033[31m");
			EXPECT_OUTPUT_SINGLE(Console::set_foreground_color(Console::Color::Green), "\033[32m");
			EXPECT_OUTPUT_SINGLE(Console::set_foreground_color(Console::Color::Yellow), "\033[33m");
			EXPECT_OUTPUT_SINGLE(Console::set_foreground_color(Console::Color::Blue), "\033[34m");
			EXPECT_OUTPUT_SINGLE(Console::set_foreground_color(Console::Color::Magenta), "\033[35m");
			EXPECT_OUTPUT_SINGLE(Console::set_foreground_color(Console::Color::Cyan), "\033[36m");
			EXPECT_OUTPUT_SINGLE(Console::set_foreground_color(Console::Color::White), "\033[37m");
			EXPECT_OUTPUT_SINGLE(Console::set_foreground_color(Console::Color::BrightBlack), "\033[90m");
			EXPECT_OUTPUT_SINGLE(Console::set_foreground_color(Console::Color::BrightRed), "\033[91m");
			EXPECT_OUTPUT_SINGLE(Console::set_foreground_color(Console::Color::BrightGreen), "\033[92m");
			EXPECT_OUTPUT_SINGLE(Console::set_foreground_color(Console::Color::BrightYellow), "\033[93m");
			EXPECT_OUTPUT_SINGLE(Console::set_foreground_color(Console::Color::BrightBlue), "\033[94m");
			EXPECT_OUTPUT_SINGLE(Console::set_foreground_color(Console::Color::BrightMagenta), "\033[95m");
			EXPECT_OUTPUT_SINGLE(Console::set_foreground_color(Console::Color::BrightCyan), "\033[96m");
			EXPECT_OUTPUT_SINGLE(Console::set_foreground_color(Console::Color::BrightWhite), "\033[97m");
		}

		TEST("Set Background Color")
		{
			EXPECT_OUTPUT_SINGLE(Console::set_background_color(Console::Color::Black), "\033[40m");
			EXPECT_OUTPUT_SINGLE(Console::set_background_color(Console::Color::Red), "\033[41m");
			EXPECT_OUTPUT_SINGLE(Console::set_background_color(Console::Color::Green), "\033[42m");
			EXPECT_OUTPUT_SINGLE(Console::set_background_color(Console::Color::Yellow), "\033[43m");
			EXPECT_OUTPUT_SINGLE(Console::set_background_color(Console::Color::Blue), "\033[44m");
			EXPECT_OUTPUT_SINGLE(Console::set_background_color(Console::Color::Magenta), "\033[45m");
			EXPECT_OUTPUT_SINGLE(Console::set_background_color(Console::Color::Cyan), "\033[46m");
			EXPECT_OUTPUT_SINGLE(Console::set_background_color(Console::Color::White), "\033[47m");
			EXPECT_OUTPUT_SINGLE(Console::set_background_color(Console::Color::BrightBlack), "\033[100m");
			EXPECT_OUTPUT_SINGLE(Console::set_background_color(Console::Color::BrightRed), "\033[101m");
			EXPECT_OUTPUT_SINGLE(Console::set_background_color(Console::Color::BrightGreen), "\033[102m");
			EXPECT_OUTPUT_SINGLE(Console::set_background_color(Console::Color::BrightYellow), "\033[103m");
			EXPECT_OUTPUT_SINGLE(Console::set_background_color(Console::Color::BrightBlue), "\033[104m");
			EXPECT_OUTPUT_SINGLE(Console::set_background_color(Console::Color::BrightMagenta), "\033[105m");
			EXPECT_OUTPUT_SINGLE(Console::set_background_color(Console::Color::BrightCyan), "\033[106m");
			EXPECT_OUTPUT_SINGLE(Console::set_background_color(Console::Color::BrightWhite), "\033[107m");
		}

		TEST("Reset")
		{
			EXPECT_OUTPUT_SINGLE(Console::reset(), "\033[0m");

			CLEAR_OUTPUT();
			Console::set_foreground_color(Console::Color::Red);
			Console::reset();
			EXPECT_OUTPUT("\033[31m\033[0m");
		}

		TEST("Write")
		{
			EXPECT_OUTPUT_SINGLE(Console::write(), "");

			EXPECT_OUTPUT_SINGLE(Console::write("Hello, World!"), "Hello, World!");
			EXPECT_OUTPUT_SINGLE(Console::write("Hello, World! ", 13), "Hello, World! 13");
		}

		TEST("Write Line")
		{
			EXPECT_OUTPUT_SINGLE(Console::write_line(), "\n");

			EXPECT_OUTPUT_SINGLE(Console::write_line("Hello, World!"), "Hello, World!\n");
			EXPECT_OUTPUT_SINGLE(Console::write_line("Hello, World! ", 13), "Hello, World! 13\n");
		}

		TEST("Flush")
		{
			EXPECT_OUTPUT_SINGLE(Console::flush(), "");
		}
	}
}
