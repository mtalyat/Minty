#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Physics/RigidBody.h"

namespace Minty
{
	/// <summary>
	/// Holds a RigidBody for an Entity.
	/// </summary>
	struct RigidBodyComponent
		: public Component
	{
		/// <summary>
		/// The RigidBody associated with this component.
		/// </summary>
		Owner<RigidBody> rigidBody;
	};
}