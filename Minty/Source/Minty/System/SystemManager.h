#pragma once
#include "Minty/Data/Dictionary.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Vector.h"
#include "Minty/Manager/SubManager.h"
#include "Minty/Serialization/SerializableObject.h"
#include "Minty/System/System.h"

namespace Minty
{
	/// <summary>
	/// The arguments for creating a SystemManager.
	/// </summary>
	struct SystemManagerBuilder
	{
		/// <summary>
		/// The Scene this SystemManager belongs to.
		/// </summary>
		Ref<Scene> scene = nullptr;
	};

	/// <summary>
	/// Manages all Systems in the game.
	/// </summary>
	class SystemManager
		: public SubManager, public SerializableObject
	{
#pragma region Variables

	private:
		Ref<Scene> m_scene;
		Dictionary<Int, Vector<System*>> m_systems;
		Map<TypeID, System*> m_systemsByType;

#pragma endregion

#pragma region Constructors

	public:
		SystemManager(Scene* scene, SystemManagerBuilder const& builder)
			: SubManager(scene)
			, m_scene(builder.scene)
			, m_systems()
			, m_systemsByType()
		{
		}

		~SystemManager()
		{
			MINTY_ASSERT_ERROR(!is_initialized(), "SystemManager is not disposed before destruction.");
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the number of Systems in this SystemManager.
		/// </summary>
		/// <returns>The count.</returns>
		Size get_size() const { return m_systems.get_size(); }

#pragma endregion

#pragma region Methods

	private:
		System* add(SystemInfo const* info, Int const priority);

		System* add(SystemInfo const* info);

		System* add(TypeID const& typeId);

	public:
        /// <summary>
		/// Adds the type of System to the SystemManager, creating a new instance of it.
        /// </summary>
        /// <typeparam name="T">The type.</typeparam>
        /// <returns>The new instance of the System.</returns>
        template<typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
        T* add()
        {
			MINTY_ASSERT(!m_systemsByType.contains(typeid(T)), F("System already exists with the TypeID: {}", typeid(T)));

			// add using type
			return static_cast<T*>(add(typeid(T)));
        }

        /// <summary>
        /// Adds the type of System to the SystemManager, creating a new instance of it.
        /// </summary>
        /// <typeparam name="T">The type.</typeparam>
        /// <param name="priority"></param>
        /// <returns>The new instance of the System.</returns>
        template<typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
        T* add(Int const priority)
        {
			MINTY_ASSERT(!m_systemsByType.contains(typeid(T)), F("System already exists with the TypeID: {}", typeid(T)));

			// add using type
			return static_cast<T*>(add(typeid(T), priority));
        }

		/// <summary>
		/// Adds the System with the given name to the SystemManager, creating a new instance of it.
		/// Uses the default priority for the type.
		/// </summary>
		/// <param name="name">The name of the System type.</param>
		/// <returns>The new instance of the System.</returns>
		System* add(String const& name);

		/// <summary>
		/// Adds the System with the given name to the SystemManager, creating a new instance of it.
		/// Uses the given priority for the new System.
		/// </summary>
		/// <param name="name">The name of the System type.</param>
		/// <param name="priority">The priority of the System.</param>
		/// <returns>The new instance of the System.</returns>
		System* add(String const& name, Int const priority);

		/// <summary>
		/// Removes the System with the given type from the SystemManager.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <returns>True if the system was removed, otherwise false.</returns>
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
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

		/// <summary>
		/// Checks if the SystemManager contains a System of the given type.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <returns>True if a System of the given type exists.</returns>
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		Bool contains()
		{
			return m_systemsByType.contains(typeid(T));
		}

		/// <summary>
		/// Gets the System of the given type from the SystemManager.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <returns>The System, or null if not found.</returns>
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		T* get() const
		{
			auto it = m_systemsByType.find(typeid(T));
			if (it == m_systemsByType.end())
			{
				return nullptr;
			}
			return static_cast<T*>(it->get_second());
		}

		/// <summary>
		/// Gets the System of the given type from the SystemManager, or asserts if not found.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <returns>The System, or null if not found.</returns>
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		T& at() const
		{
			MINTY_ASSERT(m_systemsByType.contains(typeid(T)), F("System does not exist with the TypeID: {}", typeid(T)));
			return static_cast<T&>(*m_systems.at(m_systemsByType.at(typeid(T))));
		}

		/// <summary>
		/// Called when the Manager is created.
		/// </summary>
		void initialize() override;

		/// <summary>
		/// Called when the Manager is destroyed.
		/// </summary>
		void dispose() override;

		/// <summary>
		/// Called every frame.
		/// </summary>
		void update(Time const& time) override;

		/// <summary>
		/// Called after every update operation.
		/// </summary>
		void finalize() override;

		/// <summary>
		/// Called every frame to perform rendering.
		/// </summary>
		void render() override;

		/// <summary>
		/// Handles the given Event.
		/// </summary>
		/// <param name="event">The Event.</param>
		void handle_event(Event& event) override;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new SystemManager with the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>A SystemManager Owner.</returns>
		static Owner<SystemManager> create(Scene* scene, SystemManagerBuilder const& builder = {});

		/// <summary>
		/// Gets the SystemManager for the active Scene.
		/// </summary>
		/// <returns>The SystemManager.</returns>
		static SystemManager& get_singleton();

#pragma endregion
};
}