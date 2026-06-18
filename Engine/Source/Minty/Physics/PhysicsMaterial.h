#ifndef MINTY_PHYSICS_PHYSICSMATERIAL_H
#define MINTY_PHYSICS_PHYSICSMATERIAL_H

/**
 * @file PhysicsMaterial.h
 * @brief Header file defining the PhysicsMaterial class and PhysicsMaterialInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Core/Types.h"

namespace Minty
{
    struct PhysicsMaterialInfo;

    /**
     * @brief A material that defines the physical properties of a Collider, such as friction and bounce.
     */
    class PhysicsMaterial
        : public Asset
    {
#pragma region Constructors

    public:
        /**
         * @brief Creates a new physics material with the given arguments.
         * @param info The arguments.
         */
        PhysicsMaterial(PhysicsMaterialInfo const& info);

        ~PhysicsMaterial() = default;

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Gets the AssetType of this Asset.
         * @return PhysicsMaterial.
         */
        inline AssetType get_asset_type() const override { return AssetType::PhysicsMaterial; }
    
        /**
         * @brief Gets the dynamic friction of this material.
         * @return The dynamic friction.
         */
        inline Float get_dynamic_friction() const { return m_dynamicFriction; }

        /**
         * @brief Gets the static friction of this material.
         * @return The static friction.
         */
        inline Float get_static_friction() const { return m_staticFriction; }

        /**
         * @brief Gets the bounciness of this material.
         * @return The bounciness.
         */
        inline Float get_bounce() const { return m_bounce; }

#pragma endregion

#pragma region Methods

    public:
		/**
		 * @brief Creates a new PhysicsMaterial.
		 * @param info The arguments.
		 * @return A PhysicsMaterial Owner.
		 */
		static Shared<PhysicsMaterial> create(PhysicsMaterialInfo const& info);

		/**
		 * @brief Creates a default PhysicsMaterial.
		 * @return A PhysicsMaterial Owner.
		 */
		static Shared<PhysicsMaterial> create();

#pragma endregion

#pragma region Variables

    private:
        Float m_dynamicFriction;
        Float m_staticFriction;
        Float m_bounce;

#pragma endregion
    };
}

#endif // MINTY_PHYSICS_PHYSICSMATERIAL_H