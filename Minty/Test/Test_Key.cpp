#include "Test_Key.h"
#include "Minty.h"

void test_Key(Test& _test)
{
	CATEGORY(Key)
	{
		std::vector<std::pair<Key, String>> VALUES = {
			{Key::Space, "Space"},
			{Key::Apostrophe, "Apostrophe"},
			{Key::Comma, "Comma"},
			{Key::Minus, "Minus"},
			{Key::Period, "Period"},
			{Key::Slash, "Slash"},
			{Key::D0, "D0"},
			{Key::D1, "D1"},
			{Key::D2, "D2"},
			{Key::D3, "D3"},
			{Key::D4, "D4"},
			{Key::D5, "D5"},
			{Key::D6, "D6"},
			{Key::D7, "D7"},
			{Key::D8, "D8"},
			{Key::D9, "D9"},
			{Key::Semicolon, "Semicolon"},
			{Key::Equal, "Equal"},
			{Key::A, "A"},
			{Key::B, "B"},
			{Key::C, "C"},
			{Key::D, "D"},
			{Key::E, "E"},
			{Key::F, "F"},
			{Key::G, "G"},
			{Key::H, "H"},
			{Key::I, "I"},
			{Key::J, "J"},
			{Key::K, "K"},
			{Key::L, "L"},
			{Key::M, "M"},
			{Key::N, "N"},
			{Key::O, "O"},
			{Key::P, "P"},
			{Key::Q, "Q"},
			{Key::R, "R"},
			{Key::S, "S"},
			{Key::T, "T"},
			{Key::U, "U"},
			{Key::V, "V"},
			{Key::W, "W"},
			{Key::X, "X"},
			{Key::Y, "Y"},
			{Key::Z, "Z"},
			{Key::LeftBracket, "LeftBracket"},
			{Key::Backslash, "Backslash"},
			{Key::RightBracket, "RightBracket"},
			{Key::Grave, "Grave"},
			{Key::Escape, "Escape"},
			{Key::Enter, "Enter"},
			{Key::Tab, "Tab"},
			{Key::Backspace, "Backspace"},
			{Key::Insert, "Insert"},
			{Key::Delete, "Delete"},
			{Key::Right, "Right"},
			{Key::Left, "Left"},
			{Key::Down, "Down"},
			{Key::Up, "Up"},
			{Key::PageUp, "PageUp"},
			{Key::PageDown, "PageDown"},
			{Key::Home, "Home"},
			{Key::End, "End"},
			{Key::CapsLock, "CapsLock"},
			{Key::ScrollLock, "ScrollLock"},
			{Key::NumLock, "NumLock"},
			{Key::PrintScreen, "PrintScreen"},
			{Key::Pause, "Pause"},
			{Key::F1, "F1"},
			{Key::F2, "F2"},
			{Key::F3, "F3"},
			{Key::F4, "F4"},
			{Key::F5, "F5"},
			{Key::F6, "F6"},
			{Key::F7, "F7"},
			{Key::F8, "F8"},
			{Key::F9, "F9"},
			{Key::F10, "F10"},
			{Key::F11, "F11"},
			{Key::F12, "F12"},
			{Key::F13, "F13"},
			{Key::F14, "F14"},
			{Key::F15, "F15"},
			{Key::F16, "F16"},
			{Key::F17, "F17"},
			{Key::F18, "F18"},
			{Key::F19, "F19"},
			{Key::F20, "F20"},
			{Key::F21, "F21"},
			{Key::F22, "F22"},
			{Key::F23, "F23"},
			{Key::F24, "F24"},
			{Key::F25, "F25"},
			{Key::KeyPad0, "KeyPad0"},
			{Key::KeyPad1, "KeyPad1"},
			{Key::KeyPad2, "KeyPad2"},
			{Key::KeyPad3, "KeyPad3"},
			{Key::KeyPad4, "KeyPad4"},
			{Key::KeyPad5, "KeyPad5"},
			{Key::KeyPad6, "KeyPad6"},
			{Key::KeyPad7, "KeyPad7"},
			{Key::KeyPad8, "KeyPad8"},
			{Key::KeyPad9, "KeyPad9"},
			{Key::KeyPadDecimal, "KeyPadDecimal"},
			{Key::KeyPadDivide, "KeyPadDivide"},
			{Key::KeyPadMultiply, "KeyPadMultiply"},
			{Key::KeyPadSubtract, "KeyPadSubtract"},
			{Key::KeyPadAdd, "KeyPadAdd"},
			{Key::KeyPadEnter, "KeyPadEnter"},
			{Key::KeyPadEqual, "KeyPadEqual"},
			{Key::LeftShift, "LeftShift"},
			{Key::LeftControl, "LeftControl"},
			{Key::LeftAlt, "LeftAlt"},
			{Key::LeftSuper, "LeftSuper"},
			{Key::RightShift, "RightShift"},
			{Key::RightControl, "RightControl"},
			{Key::RightAlt, "RightAlt"},
			{Key::RightSuper, "RightSuper"},
			{Key::Menu, "Menu"},
		};

		TEST("To String")
		{
			for (auto const& [value, name] : VALUES)
			{
				EXPECT_EQUAL(to_string(value), name);
			}
		}

		TEST("Parse To")
		{
			for (auto const& [value, name] : VALUES)
			{
				EXPECT_EQUAL(parse_to_key(name), value);
			}

			EXPECT_EQUAL(parse_to_key(""), Key());
		}

		TEST("Parse Try")
		{
			Key result;
			for (auto const& [value, name] : VALUES)
			{
				EXPECT_TRUE(parse_try_key(name, result));
				EXPECT_EQUAL(result, value);
			}

			EXPECT_FALSE(parse_try_key("", result));
			EXPECT_EQUAL(result, Key());
		}
	}
}