#ifndef MINTY_SYSTEM_SYSTEM_H
#define MINTY_SYSTEM_SYSTEM_H

/**
 * @file System.h
 * @brief Header file for the System class.
 * @author Mitchell Talyat
 */

#include "Minty/Data/Pointer.h"
#include "Minty/Data/String.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Serialization/SerializableObject.h"
#include "Minty/Time/Timestep.h"
#include "Minty/Scene/Scene.h"

namespace Minty
{
	class EntityManager;
	class Event;
	class SystemManager;
	class System;
	struct SystemData;
	struct SystemInfo;

	/**
	 * @brief The base class for all Systems. Systems contain logic that operates on Entities and Components within a Scene.
	 */
	class System
		: public SerializableObject
	{
		friend class SystemManager;

#pragma region Constructors

	public:
		/**
		 * @brief Constructs a System with the given SystemInfo.
		 * @param info The SystemInfo containing initialization parameters.
		 */
		System(SystemInfo const &info);

		virtual ~System() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the priority of this System.
		 * @returns The priority.
		 */
		inline Int get_priority() const { return m_priority; }

		/**
		 * @brief Gets the Scene this System belongs to.
		 * @returns The Scene.
		 */
		inline Ref<Scene> const &get_scene_ref() const
		{
			MINTY_ASSERT(m_scene != nullptr, ErrorCode::Object_InvalidState);
			return m_scene;
		}

		/**
		 * @brief Gets the Scene this System belongs to.
		 * @returns The Scene.
		 */
		inline Scene &get_scene() const
		{
			MINTY_ASSERT(m_scene != nullptr, ErrorCode::Object_InvalidState);
			return *m_scene;
		}
		
		/**
		 * @brief Gets the EntityManager for this System's Scene.
		 * @returns The EntityManager.
		 */
		inline EntityManager &get_entity_manager() const
		{
			MINTY_ASSERT(m_scene != nullptr, ErrorCode::Object_InvalidState);
			return m_scene->get_entity_manager();
		}

		/**
		 * @brief Gets the SystemManager for this System's Scene.
		 * @returns The SystemManager.
		 */
		inline SystemManager &get_system_manager() const
		{
			MINTY_ASSERT(m_scene != nullptr, ErrorCode::Object_InvalidState);
			return m_scene->get_system_manager();
		}

		/**
		 * @brief Gets the SystemData for this System.
		 * @returns The SystemData.
		 */
		inline SystemData const *get_data() const { return m_data; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Called when the Scene is loaded.
		 */
		virtual void on_load() {}

		/**
		 * @brief Called when the Scene is unloaded.
		 */
		virtual void on_unload() {}

		/**
		 * @brief Called when the Scene is frame updated.
		 * @param time The time information for the frame update.
		 */
		virtual void on_frame_update(Timestep const time) {}
		
		/**
		 * @brief Called when the Scene is fixed updated.
		 * @param time The time information for the fixed update.
		 */
		virtual void on_fixed_update(Timestep const time) {}

		/**
		 * @brief Called when the Scene is finalized.
		 */
		virtual void on_finalize() {}

		/**
		 * @brief Called when the Scene is rendered.
		 */
		virtual void on_render() {}

		/**
		 * @brief Called when an Event is received.
		 * @param event The Event.
		 */
		virtual void on_event(Event &event) {}

		virtual void serialize(Writer &writer) const override {}
		virtual Bool deserialize(Reader &reader) override { return true; }

#pragma endregion

#pragma region Variables

	protected:
		Ref<Scene> m_scene;
		SystemData const *m_data;

	private:
		Int m_priority;

#pragma endregion
	};
}

#endif // MINTY_SYSTEM_SYSTEM_H