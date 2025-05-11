#pragma once
#include "Minty/Render/Mesh.h"

namespace Minty
{
	class Vulkan_Mesh
		: public Mesh
	{
#pragma region Constructors

	public:
		Vulkan_Mesh(MeshBuilder const& builder)
			: Mesh(builder)
		{
		}

		~Vulkan_Mesh()
		{
		}

#pragma endregion

#pragma region Methods

	public:
		void on_bind() const override;

#pragma endregion
	};
}