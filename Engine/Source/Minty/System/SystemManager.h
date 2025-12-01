#ifndef MINTY_SYSTEM_SYSTEMMANAGER_H
#define MINTY_SYSTEM_SYSTEMMANAGER_H

/**
 * @file SystemManager.h
 * @brief Header file defining the SystemManager class and SystemManagerInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Data/Dictionary.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Set.h"
#include "Minty/Data/Vector.h"
#include "Minty/Manager/SubManager.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	struct SystemManagerInfo;
	struct SystemData;
	class System;
	class Scene;

	/**
	 * @brief Manages all Systems in the game.
	 */
	class SystemManager
		: public SubManager,
		  public SerializableObject
	{
#pragma region Variables

	private:
		Ref<Scene> m_scene;
		Dictionary<Int, Set<System *>> m_systems;
		Map<TypeID, System *> m_systemsByType;

#pragma endregion

#pragma region Constructors

	public:
		SystemManager(Scene *scene, SystemManagerInfo const &info);

		~SystemManager() override;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the number of Systems in this SystemManager.
		 * @return The count.
		 */
		Size get_size() const { return m_systems.get_size(); }

#pragma endregion

#pragma region Methods

	private:
		System *add(SystemData const& data, Int const priority);

		System *add(SystemData const& data);

		System *add(TypeID const &typeId);

	public:
		/**
		 * @brief Adds the type of System to the SystemManager, creating a new instance of it.
		 * @tparam T The type.
		 * @return The new instance of the System.
		 */
		template <typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		T *add()
		{
			MINTY_ASSERT(!m_systemsByType.contains(typeid(T)), ErrorCode::Argument_KeyAlreadyExists, typeid(T).name());

			// add using type
			return static_cast<T *>(add(typeid(T)));
		}

		/**
		 * @brief Adds the type of System to the SystemManager, creating a new instance of it.
		 * @tparam T The type.
		 * @param priority
		 * @return The new instance of the System.
		 */
		template <typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		T *add(Int const priority)
		{
			MINTY_ASSERT(!m_systemsByType.contains(typeid(T)), ErrorCode::Argument_KeyAlreadyExists, typeid(T).name());

			// add using type
			return static_cast<T *>(add(typeid(T), priority));
		}

		/**
		 * @brief Adds the System with the given name to the SystemManager, creating a new instance of it.
		 * Uses the default priority for the type.
		 * @param name The name of the System type.
		 * @return The new instance of the System.
		 */
		System *add(String const &name);

		/**
		 * @brief Adds the System with the given name to the SystemManager, creating a new instance of it.
		 * Uses the given priority for the new System.
		 * @param name The name of the System type.
		 * @param priority The priority of the System.
		 * @return The new instance of the System.
		 */
		System *add(String const &name, Int const priority);

		/**
		 * @brief Removes the System with the given type from the SystemManager.
		 * @tparam T The type.
		 * @return True if the system was removed, otherwise false.
		 */
		template <typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		Bool remove()
		{
			auto it = m_systemsByType.find(typeid(T));
			if (it == m_systemsByType.end())
			{
				return false;
			}
			m_systems.remove(it->get_second());
			m_systemsByType.remove(typeid(T));
			return true;
		}

		/**
		 * @brief Checks if the SystemManager contains a System of the given type.
		 * @tparam T The type.
		 * @return True if a System of the given type exists.
		 */
		template <typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		Bool contains()
		{
			return m_systemsByType.contains(typeid(T));
		}

		/**
		 * @brief Gets the System of the given type from the SystemManager.
		 * @tparam T The type.
		 * @return The System, or null if not found.
		 */
		template <typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		T *get() const
		{
			auto it = m_systemsByType.find(typeid(T));
			if (it == m_systemsByType.end())
			{
				return nullptr;
			}
			return static_cast<T *>(it->get_second());
		}

		System *get_system(String const &name) const;

		/**
		 * @brief Gets the System of the given type from the SystemManager, or asserts if not found.
		 * @tparam T The type.
		 * @return The System, or null if not found.
		 */
		template <typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		T &at() const
		{
			MINTY_ASSERT(m_systemsByType.contains(typeid(T)), ErrorCode::Argument_KeyNotFound, typeid(T).name());
			return static_cast<T &>(*m_systems.at(m_systemsByType.at(typeid(T))));
		}

		/**
		 * @brief Called every frame.
		 * @param time The time information for the frame update.
		 */
		void frame_update(Timestep const &time) override;

		/**
		 * @brief Called at a fixed interval.
		 * @param time The time information for the fixed update.
		 */
		void fixed_update(Timestep const &time) override;

		/**
		 * @brief Called after every update operation.
		 */
		void finalize() override;

		/**
		 * @brief Called every frame to perform rendering.
		 */
		void render() override;

		/**
		 * @brief Handles the given Event.
		 * @param event The Event.
		 */
		void handle_event(Event &event) override;

		void serialize(Writer &writer) const override;
		Bool deserialize(Reader &reader) override;

		/**
		 * @brief Creates a new SystemManager with the given arguments.
		 * @param info The arguments.
		 * @return A SystemManager Owner.
		 */
		static Shared<SystemManager> create(Scene *scene, SystemManagerInfo const &info);

		/**
		 * @brief Gets the SystemManager for the active Scene.
		 * @return The SystemManager.
		 */
		static SystemManager &get_singleton();

#pragma endregion
	};
}

#endif // MINTY_SYSTEM_SYSTEMMANAGER_H