#pragma once
#include "Minty/Core/Constant.h"
#include "Minty/Core/Math.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/UUID.h"
#include "Minty/Input/CursorMode.h"
#include "Minty/Event/Event.h"
#include <functional>

namespace Minty
{
	/// <summary>
	/// Arguments for a Window.
	/// </summary>
	struct WindowBuilder
	{
		/// <summary>
		/// The ID.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The position of the Window.
		/// </summary>
		Int2 position = { 100, 100 };

		/// <summary>
		/// The size of the Window.
		/// </summary>
		UInt2 size = { 960, 540 };

		/// <summary>
		/// The title of the Window.
		/// </summary>
		String title = MINTY_NAME;

		/// <summary>
		/// Called when an Event is triggered.
		/// </summary>
		EventCallbackFunction eventCallback = nullptr;
	};

	/// <summary>
	/// A Window object.
	/// </summary>
	class Window
	{
#pragma region Variables

	private:
		UUID m_id;

	protected:
		Int2 m_position;
		UInt2 m_size;
		String m_title;
		EventCallbackFunction m_eventCallback;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Window.
		/// </summary>
		Window(WindowBuilder const& builder);

		virtual ~Window()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the ID of this Window.
		/// </summary>
		/// <returns>The UUID.</returns>
		UUID get_id() const { return m_id; }

		/// <summary>
		/// Gets the title of the Window.
		/// </summary>
		/// <returns>The title.</returns>
		String const& get_title() const { return m_title; }

		/// <summary>
		/// Sets the title of the Window.
		/// </summary>
		/// <param name="title">The title.</param>
		virtual void set_title(String const& title) { m_title = title; }

		/// <summary>
		/// Gets the position of the Window.
		/// </summary>
		/// <returns>The position.</returns>
		Int2 get_position() const { return m_position; }

		/// <summary>
		/// Sets the position of the Window.
		/// </summary>
		/// <param name="position">The position.</param>
		virtual void set_position(Int2 const& position) { m_position = position; }

		/// <summary>
		/// Gets the size of the Window.
		/// </summary>
		/// <returns>The size.</returns>
		UInt2 get_size() const { return m_size; }

		/// <summary>
		/// Sets the size of the Window.
		/// </summary>
		/// <param name="size">The size.</param>
		virtual void set_size(UInt2 const& size) { m_size = size; }

		/// <summary>
		/// Gets the size of the framebuffer.
		/// </summary>
		/// <returns>The framebuffer size.</returns>
		virtual UInt2 get_framebuffer_size() const { return m_size; }

		/// <summary>
		/// Gets the cursor mode.
		/// </summary>
		/// <returns>The CursorMode.</returns>
		virtual CursorMode get_cursor_mode() const = 0;

		/// <summary>
		/// Sets the cursor mode.
		/// </summary>
		/// <param name="mode">The CursorMode.</param>
		virtual void set_cursor_mode(CursorMode const mode) = 0;

		/// <summary>
		/// Gets the native Window object.
		/// </summary>
		/// <returns>A pointer to the native object.</returns>
		virtual void* get_native() const = 0;

		/// <summary>
		/// Sets the event callback function.
		/// </summary>
		/// <param name="callback">The event callback function.</param>
		void set_event_callback(EventCallbackFunction const& callback)
		{
			m_eventCallback = callback;
		}

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Maximizes the Window.
		/// </summary>
		virtual void maximize() = 0;

		/// <summary>
		/// Minimizes the Window.
		/// </summary>
		virtual void minimize() = 0;

		/// <summary>
		/// Restores the Window.
		/// </summary>
		virtual void restore() = 0;

		/// <summary>
		/// Closes the Window.
		/// </summary>
		virtual void close() = 0;

		/// <summary>
		/// Checks if this Window is open.
		/// </summary>
		/// <returns>True, if this Window is open.</returns>
		virtual Bool is_open() const = 0;

		/// <summary>
		/// Polls and processes events.
		/// </summary>
		virtual void process_events() = 0;

		/// <summary>
		/// Waits for all pending events to be processed.
		/// </summary>
		virtual void sync() {}

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new Window.
		/// </summary>
		/// <param name="builder">The builder.</param>
		/// <returns>A Window Owner.</returns>
		static Owner<Window> create(WindowBuilder const& builder = {});

#pragma endregion
	};
}