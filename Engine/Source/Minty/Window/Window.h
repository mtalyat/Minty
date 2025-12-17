#ifndef MINTY_WINDOW_WINDOW_H
#define MINTY_WINDOW_WINDOW_H

/**
 * @file Window.h
 * @brief Header file defining the Window class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Constant.h"
#include "Minty/Core/Math.h"
#include "Minty/Data/Path.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/UUID.h"
#include "Minty/Input/CursorMode.h"

namespace Minty
{
	class Event;
	struct WindowInfo;

	/**
	 * @brief A Window object.
	 */
	class Window
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new Window.
		 */
		Window(WindowInfo const& info);

		virtual ~Window() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the ID of this Window.
		 * @return The UUID.
		 */
		UUID get_id() const { return m_id; }

		/**
		 * @brief Gets the title of the Window.
		 * @return The title.
		 */
		String const& get_title() const { return m_title; }

		/**
		 * @brief Sets the title of the Window.
		 * @param title The title.
		 */
		virtual void set_title(String const& title) { m_title = title; }

		/**
		 * @brief Gets the position of the Window.
		 * @return The position.
		 */
		Int2 get_position() const { return m_position; }

		/**
		 * @brief Sets the position of the Window.
		 * @param position The position.
		 */
		virtual void set_position(Int2 const& position) { m_position = position; }

		/**
		 * @brief Gets the size of the Window.
		 * @return The size.
		 */
		UInt2 get_size() const { return m_size; }

		/**
		 * @brief Sets the size of the Window.
		 * @param size The size.
		 */
		virtual void set_size(UInt2 const& size) { m_size = size; }

		/**
		 * @brief Gets the size of the framebuffer.
		 * @return The framebuffer size.
		 */
		virtual UInt2 get_framebuffer_size() const { return m_size; }

		/**
		 * @brief Gets the cursor mode.
		 * @return The CursorMode.
		 */
		virtual CursorMode get_cursor_mode() const = 0;

		/**
		 * @brief Sets the cursor mode.
		 * @param mode The CursorMode.
		 */
		virtual void set_cursor_mode(CursorMode const mode) = 0;

		/**
		 * @brief Gets the native Window object.
		 * @return A pointer to the native object.
		 */
		virtual Any get_native() const = 0;

		/**
		 * @brief Sets the event callback function.
		 * @param callback The event callback function.
		 */
		void set_event_callback(EventCallback const& callback)
		{
			m_eventCallback = callback;
		}

		/**
		 * @brief Sets the icon of the Window.
		 * @param path The Path to the icon.
		 */
		virtual void set_icon(Path const& path) = 0;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Maximizes the Window.
		 */
		virtual void maximize() = 0;

		/**
		 * @brief Minimizes the Window.
		 */
		virtual void minimize() = 0;

		/**
		 * @brief Restores the Window.
		 */
		virtual void restore() = 0;

		/**
		 * @brief Closes the Window.
		 */
		virtual void close() = 0;

		/**
		 * @brief Checks if this Window is open.
		 * @return True, if this Window is open.
		 */
		virtual Bool is_open() const = 0;

		/**
		 * @brief Polls and processes events.
		 */
		virtual void process_events() = 0;

		/**
		 * @brief Waits for all pending events to be processed.
		 */
		virtual void sync() {}

#pragma endregion

#pragma region Statics

	public:
		/**
		 * @brief Creates a new Window.
		 * @param info The info.
		 * @return A Window Owner.
		 */
		static Unique<Window> create(WindowInfo const& info);

		/**
		 * @brief Creates a new Window with default settings.
		 * @return A Window Owner.
		 */
		static Unique<Window> create();

#pragma endregion

#pragma region Variables

	protected:
		Int2 m_position;
		UInt2 m_size;
		String m_title;
		EventCallback m_eventCallback;

	private:
		UUID m_id;

#pragma endregion
	};
}

#endif // MINTY_WINDOW_WINDOW_H