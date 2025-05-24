#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Render/Camera.h"

namespace Minty
{
	/// <summary>
	/// A component that holds a Camera.
	/// </summary>
	struct CameraComponent
		: public Component
	{
		/// <summary>
		/// The Camera.
		/// </summary>
		Ref<Camera> camera = nullptr;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}