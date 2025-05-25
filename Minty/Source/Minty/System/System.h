#pragma once
#include "Minty/Data/Pointer.h"
#include "Minty/Event/Event.h"
#include "Minty/Serialization/SerializableObject.h"
#include "Minty/Time/Time.h"

namespace Minty
{
	class Scene;
	class System;
	struct SystemInfo;

	/// <summary>
	/// The arguments for creating a System.
	/// </summary>
	struct SystemBuilder
	{
		/// <summary>
		/// The Scene this System belongs to.
		/// </summary>
		Ref<Scene> scene = nullptr;

		/// <summary>
		/// The SystemInfo for this System.
		/// </summary>
		SystemInfo const* info = nullptr;
	};

	/// <summary>
	/// Info for creating a System.
	/// </summary>
	struct SystemInfo
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
		Function<System* (SystemBuilder const&)> create;
	};

	/// <summary>
	/// The base class for all systems.
	/// Systems are used to provide logic for entities and components.
	/// </summary>
	class System
		: public SerializableObject
	{
#pragma region Variables

	protected:
		Ref<Scene> m_scene;
		SystemInfo const* m_info;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new System using the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		System(SystemBuilder const& builder)
			: SerializableObject()
			, m_scene(builder.scene)
			, m_info(builder.info)
		{
		}

		virtual ~System() = default;

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the Scene this System belongs to.
		/// </summary>
		/// <returns>The Scene.</returns>
		Ref<Scene> get_scene() const { return m_scene; }

		/// <summary>
		/// Gets the SystemInfo for this System.
		/// </summary>
		/// <returns>The SystemInfo.</returns>
		SystemInfo const* get_info() const { return m_info; }

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
		/// <param name="time"></param>
		virtual void on_update(Time const& time) {}

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