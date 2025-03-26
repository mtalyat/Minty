#pragma once
#include "Minty/Data/Map.h"
#include "Minty/Data/UUID.h"
#include "Minty/Window/Window.h"

namespace Minty
{
	struct WindowManagerBuilder
	{

	};

	class WindowManager
	{
#pragma region Variables

	private:
		// all windows
		Map<UUID, Owner<Window>> m_windows;
		// the main window
		Ref<Window> m_main;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new WindowManager.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		WindowManager(WindowManagerBuilder const& builder)
			: m_windows()
			, m_main()
		{
		}

		~WindowManager()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the main Window.
		/// </summary>
		/// <returns>A reference to the main window.</returns>
		Ref<Window>& get_main() { return m_main; }

		/// <summary>
		/// Gets the main Window.
		/// </summary>
		/// <returns>A reference to the main window.</returns>
		Ref<Window> const& get_main() const { return m_main; }

		/// <summary>
		/// Sets the main Window.
		/// </summary>
		/// <param name="id"></param>
		void set_main(UUID const id);

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Creates a new Window.
		/// </summary>
		/// <param name="builder">The builder.</param>
		/// <returns>A reference to the new Window.</returns>
		Ref<Window> create_window(WindowBuilder const& builder);

		/// <summary>
		/// Destroys the Window with the given ID.
		/// </summary>
		/// <param name="id">The ID of the Window.</param>
		void destroy_window(UUID const id);

		/// <summary>
		/// Gets the Window with the given ID.
		/// </summary>
		/// <param name="id">The ID of the Window to get.</param>
		/// <returns>A reference to the Window, or null if it does not exist.</returns>
		Ref<Window> get_window(UUID const id);

#pragma endregion
	};
}