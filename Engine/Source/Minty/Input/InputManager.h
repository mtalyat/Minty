#pragma once
#include "Minty/Manager/Manager.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Debug/Debug.h"

namespace Minty
{
	/// <summary>
	/// The arguments for an InputManager.
	/// </summary>
	struct InputManagerBuilder
	{

	};

	class InputManager
		: public Manager
	{
#pragma region Variables

	private:
		static InputManager* s_instance;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new InputManager.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		InputManager(InputManagerBuilder const& builder)
			: Manager()
		{
			MINTY_ASSERT(!s_instance, "InputManager already exists.");
			s_instance = this;
		}

		~InputManager()
		{
			if (s_instance == this)
			{
				s_instance = nullptr;
			}
		}

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Gets the active Context's InputManager.
		/// </summary>
		/// <returns>The singleton.</returns>
		static InputManager& get_instance();

		/// <summary>
		/// Creates a new InputManager.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>An InputManager Owner.</returns>
		static Owner<InputManager> create(InputManagerBuilder const& builder = {});

#pragma endregion

	};
}