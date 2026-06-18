#ifndef MINTY_PHYSICS_COLLIDER_H
#define MINTY_PHYSICS_COLLIDER_H

/**
 * @file Collider.h
 * @brief Header file defining the Collider class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Shape.h"
#include "Minty/Physics/PhysicsMaterial.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Serialization/Serializer.h"

namespace Minty
{
	class Mesh;
	class Transform;
	class PhysicsMaterial;
	struct ColliderInfo;
	struct CollisionData;

	/**
	 * @brief The base class for all physics Colliders.
	 */
	class Collider
	{
		friend struct Serializer<Collider>;

#pragma region Constructors

	public:
		/**
		 * @brief Creates a new collider with the given arguments.
		 * @param info The arguments.
		 */
		Collider(ColliderInfo const& info);

		virtual ~Collider() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Checks if this Collider is static.
		 * @return True if static, otherwise false.
		 */
		inline Bool is_static() const { return m_isStatic; }

		/**
		 * @brief Checks if this Collider is a trigger.
		 * @return True if a trigger, otherwise false.
		 */
		inline Bool is_trigger() const { return m_isTrigger; }

		/**
		 * @brief Gets the Shape of this Collider.
		 * @return The Shape.
		 */
		inline Shape get_shape() const { return m_shape; }

		/**
		 * @brief Gets the offset of this Collider.
		 * @return The offset.
		 */
		inline Float3 get_offset() const { return m_offset; }

		/**
		 * @brief Gets the size of this Collider.
		 * @return The size.
		 */
		inline Float3 get_size() const { return m_size; }

		/**
		 * @brief Gets the Mesh used for this Collider if the Shape is Custom.
		 * @return The Mesh Owner.
		 */
		inline Shared<Mesh> const& get_mesh() const { return m_mesh; }

		/**
		 * @brief Gets the PhysicsMaterial associated with this Collider.
		 * @return The PhysicsMaterial Owner.
		 */
		inline Shared<PhysicsMaterial> const& get_material() const { return m_material; }

		/**
		 * @brief Sets the on stay collision function.
		 * @param func The function to set.
		 */
		void set_on_enter(CollisionCallback const& func) { m_onEnter = func; }

		/**
		 * @brief Sets the on stay collision function.
		 * @param func The function to set.
		 */
		void set_on_stay(CollisionCallback const& func) { m_onStay = func; }

		/**
		 * @brief Sets the on exit collision function.
		 * @param func The function to set.
		 */
		void set_on_exit(CollisionCallback const& func) { m_onExit = func; }

		/**
		 * @brief Gets the native pointer to the underlying physics object.
		 * @return The pointer to the native object.
		 */
		virtual Any get_native() const = 0;

#pragma endregion

#pragma region Methods

	public:

		/**
		 * @brief Calls the on enter collision function.
		 * @param func The function to call.
		 */
		void invoke_on_enter(CollisionData const& data) const
		{
			if (m_onEnter)
			{
				m_onEnter(data);
			}
		}

		/**
		 * @brief Calls the on stay collision function.
		 * @param func The function to call.
		 */
		void invoke_on_stay(CollisionData const& data) const
		{
			if (m_onStay)
			{
				m_onStay(data);
			}
		}

		/**
		 * @brief Calls the on exit collision function.
		 * @param func The function to call.
		 */
		void invoke_on_exit(CollisionData const& data) const
		{
			if (m_onExit)
			{
				m_onExit(data);
			}
		}

		/**
		 * @brief Creates a new Collider with the given arguments.
		 * @param info The arguments.
		 * @return A Collider Owner.
		 */
		static Shared<Collider> create(ColliderInfo const& info);

		/**
		 * @brief Creates a default Collider (Box shape, size (1,1,1), non-static).
		 * @return A Collider Owner.
		 */
		static Shared<Collider> create();

#pragma endregion

#pragma region Variables

	private:
		Shape m_shape;
		Shared<Mesh> m_mesh; // only used if shape is Custom
		Shared<PhysicsMaterial> m_material;
		CollisionCallback m_onEnter;
		CollisionCallback m_onStay;
		CollisionCallback m_onExit;
		Float3 m_offset;
		Float3 m_size;
		Bool m_isStatic;
		Bool m_isTrigger;

#pragma endregion
	};

	template<>
	struct Serializer<Collider>
	{
		static void serialize(Writer& writer, Collider const& value);
		static Bool deserialize(Reader& reader, Collider& value);
	};
}

#endif // MINTY_PHYSICS_COLLIDER_H