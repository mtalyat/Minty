#pragma once
#include "Minty/Data/Pointer.h"
#include "Minty/Data/String.h"
#include "Minty/Event/Event.h"
#include "Minty/Serialization/SerializableObject.h"
#include "Minty/Time/Timestep.h"

namespace Minty
{
	class Scene;
	class EntityManager;
	class SystemManager;
	class System;
	struct SystemData;

	/// <summary>
	/// The arguments for creating a System.
	/// </summary>
	struct SystemInfo
	{
		/// <summary>
		/// The priority of this System.
		/// </summary>
		Int priority = 0;

		/// <summary>
		/// The Scene this System belongs to.
		/// </summary>
		Ref<Scene> scene = nullptr;

		/// <summary>
		/// The SystemData for this System.
		/// </summary>
		SystemData const* info = nullptr;
	};

	/// <summary>
	/// Data for creating a System.
	/// </summary>
	struct SystemData
	{
		/// <summary>
		/// The name of the System.
		/// </summary>
		String name;

		/// <summary>
		/// The type of the System.
		/// </summary>
		TypeID typeId;

		/// <summary>
		/// The function to create the System.
		/// </summary>
		Function<System* (SystemInfo const&)> create;

		/// <summary>
		/// The default priority of the System, if none is specified.
		/// </summary>
		Int defaultPriority = 0;
	};

	/// <summary>
	/// The base class for all systems.
	/// Systems are used to provide logic for entities and components.
	/// </summary>
	class System
		: public SerializableObject
	{
		friend class SystemManager;

#pragma region Variables

	private:
		Int m_priority;

	protected:
		Ref<Scene> m_scene;
		SystemData const* m_data;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new System using the given arguments.
		/// </summary>
		/// <param name="info">The arguments.</param>
		System(SystemInfo const& info)
			: SerializableObject()
			, m_priority(info.priority)
			, m_scene(info.scene)
			, m_data(info.info)
		{
		}

		virtual ~System() = default;

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the priority of this System.
		/// </summary>
		/// <returns>The priority.</returns>
		Int get_priority() const { return m_priority; }

		/// <summary>
		/// Gets the Scene this System belongs to.
		/// </summary>
		/// <returns>The Scene.</returns>
		Ref<Scene> const& get_scene() const;

		/// <summary>
		/// Gets the EntityManager for this System's Scene.
		/// </summary>
		/// <returns>The EntityManager.</returns>
		EntityManager& get_entity_manager() const;

		/// <summary>
		/// Gets the SystemManager for this System's Scene.
		/// </summary>
		/// <returns>The SystemManager.</returns>
		SystemManager& get_system_manager() const;

		/// <summary>
		/// Gets the SystemInfo for this System.
		/// </summary>
		/// <returns>The SystemInfo.</returns>
		SystemData const* get_data() const { return m_data; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Called when the Scene is loaded.
		/// </summary>
		virtual void on_load() {}

		/// <summary>
		/// Called when the Scene is unloaded.
		/// </summary>
		virtual void on_unload() {}

		/// <summary>
		/// Called when the Scene is updated.
		/// </summary>
		/// <param name="time">The time information for the update.</param>
		virtual void on_frame_update(Timestep const& time) {}

		/// <summary>
		/// Called when the Scene is fixed updated.
		/// </summary>
		/// <param name="time">The time information for the fixed update.</param>
		virtual void on_fixed_update(Timestep const& time) {}

		/// <summary>
		/// Called when the Scene is finalized.
		/// </summary>
		virtual void on_finalize() {}

		/// <summary>
		/// Called when the Scene is rendered.
		/// </summary>
		virtual void on_render() {}

		/// <summary>
		/// Called when an Event is received.
		/// </summary>
		/// <param name="event">The Event.</param>
		virtual void on_event(Event& event) {}

		virtual void serialize(Writer& writer) const override {}
		virtual Bool deserialize(Reader& reader) override { return true; }

#pragma endregion
	};
}