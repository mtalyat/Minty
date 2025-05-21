#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Library/GLFW.h"
#include "Minty/Window/Window.h"
#include "Minty/Data/Map.h"

namespace Minty
{
	class Windows_Window
		: public Window
	{
#pragma region Classes

	private:
		struct GamepadData
		{
			GLFWgamepadstate state;

			Char const* name;
		};

#pragma endregion


#pragma region Variables

	private:
		GLFWwindow* mp_window;
		Map<Int, GamepadData> m_gamepads;
		Int2 m_restorePosition;
		Int2 m_restoreSize;

		static Int s_windowCount;

#pragma endregion

#pragma region Constructors

	public:
		Windows_Window(WindowBuilder const& builder);

		~Windows_Window();

#pragma endregion

#pragma region Get Set

	public:
		void set_title(String const& title) override;

		void set_position(Int2 const& position) override;

		void set_size(UInt2 const& size) override;

		UInt2 get_framebuffer_size() const override;

		CursorMode get_cursor_mode() const override;

		void set_cursor_mode(CursorMode const mode) override;

		void* get_native() const override;

#pragma endregion

#pragma region Methods

	private:
		void save_restore_info();

		void process_window_events();

		void process_gamepad_events();

	public:
		void maximize() override;

		void minimize() override;

		void restore() override;

		void close() override;

		Bool is_open() const override;

		void process_events() override;

		void sync() override;

#pragma endregion
	};
}