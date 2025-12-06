#ifndef MINTY_INPUT_INPUTMANAGER_H
#define MINTY_INPUT_INPUTMANAGER_H

/**
 * @file InputManager.h
 * @brief Header file for the InputManager class.
 * @author Mitchell Talyat
 */

#include "Minty/Manager/Manager.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Debug/Debug.h"

namespace Minty
{
	struct InputManagerInfo;

	/**
	 * @brief The InputManager handles input devices and events.
	 */
	class InputManager
		: public Manager
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new InputManager.
		 * @param info The arguments.
		 */
		InputManager(InputManagerInfo const& info)
			: Manager()
		{
			MINTY_ASSERT(!s_instance, ErrorCode::Singleton_AlreadyExists);
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

#pragma region Methods

	public:
		/**
		 * @brief Gets the active Context's InputManager.
		 * @return The singleton.
		 */
		static InputManager& get_singleton();

		/**
		 * @brief Gets the singleton InputManager for the application.
		 * @return A reference to the InputManager.
		 */
		static Unique<InputManager> const& get_instance();

		/**
		 * @brief Creates a new InputManager.
		 * @param info The arguments.
		 * @return An InputManager Owner.
		 */
		static Unique<InputManager> create(InputManagerInfo const& info);

		/**
		 * @brief Creates a new InputManager with default settings.
		 * @return An InputManager Owner.
		 */
		static Unique<InputManager> create();

#pragma endregion

#pragma region Variables

	private:
		static InputManager* s_instance;

#pragma endregion
	};
}

#endif // MINTY_INPUT_INPUTMANAGER_H