#pragma once
#include "Minty/Context/Manager.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Vector.h"
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
		: public Manager
	{
#pragma region Variables

	private:
		Ref<Scene> m_scene;
		Vector<System*> m_systems;
		Map<TypeID, Size> m_systemsByType;

#pragma endregion

#pragma region Constructors

	public:
		SystemManager(SystemManagerBuilder const& builder)
			: Manager()
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

#pragma region Methods

	private:
		void add(TypeID const& typeId, System* system);

	public:
        template<typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
        void add()
        {
			MINTY_ASSERT(!m_systemsByType.contains(typeid(T)), F("System already exists with the TypeID: {}", typeid(T)));

			// create the system
			SystemBuilder builder{};
			builder.scene = m_scene;
			System* system = new T(builder);

			add(typeid(T), system);
        }

		void add(String const& name);

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

		template<typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		Bool contains()
		{
			return m_systemsByType.contains(typeid(T));
		}

		template<typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		T* get() const
		{
			auto it = m_systemsByType.find(typeid(T));
			if (it == m_systemsByType.end())
			{
				return nullptr;
			}
			return static_cast<T*>(m_systems.at(it->get_second()));
		}

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

#pragma endregion

#pragma region Statics

	public:
		static Owner<SystemManager> create(SystemManagerBuilder const& builder = {});

		static SystemManager& get_singleton();

#pragma endregion
	};
}