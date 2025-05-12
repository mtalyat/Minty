#pragma once
#include "Minty/System/System.h"
#include "Minty/Entity/Entity.h"

namespace Minty
{
	class RenderSystem
		: public System
	{
#pragma region Variables

	private:
		Entity m_mainCameraEntity;

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Sets the main camera for the RenderSystem.
		/// </summary>
		/// <param name="camera">The Entity with a Camera component.</param>
		void set_main_camera(Entity const& camera)
		{
			m_mainCameraEntity = camera;
		}

		/// <summary>
		/// Gets the main camera for the RenderSystem.
		/// </summary>
		/// <returns>The main camera Entity.</returns>
		Entity get_main_camera() const
		{
			return m_mainCameraEntity;
		}

#pragma endregion


#pragma region Methods

	public:
		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
		void on_load() override;
		void on_unload() override;
		void on_update(Time const& time) override;
		void on_finalize() override;
		void on_render() override;

#pragma endregion
	};
}