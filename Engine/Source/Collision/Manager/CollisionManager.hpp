#pragma once

#include "Core/Data/Map.hpp"
#include "Core/Data/Array.hpp"
#include "Collision/CollisionMask/CollisionMask.hpp"

namespace Minty
{
    struct CollisionManagerInfo;

    class CollisionManager
    {
#pragma region Constructor

    public:
        CollisionManager(CollisionManagerInfo const& info);
        ~CollisionManager();

        CollisionManager(CollisionManager const& other) = delete;
        CollisionManager(CollisionManager&& other) = delete;

#pragma endregion

#pragma region Operators

    public:
        CollisionManager& operator=(CollisionManager const& other) = delete;
        CollisionManager& operator=(CollisionManager&& other) = delete;

#pragma endregion

#pragma region Accessor

    public:
        Collision get_collision(String const& name) const;
        String get_collision_name(Collision const collision) const;
        CollisionMask get_collision_mask(Collision const collision) const;
        Bool is_valid(Collision const collision) const;
        Bool is_valid(String const& name) const;

#pragma region Method

    public:

        Collision create_collision(String const& name, CollisionMask const mask);
        void create_collision(String const& name, CollisionMask const mask, Collision const collision);
        void destroy_collision(Collision const collision);

        static CollisionManager& get_singleton();

#pragma endregion

#pragma region Variables

    private:
        Map<StringView, Collision> m_nameToCollision;
        Array<String, COLLISION_COUNT> m_collisionToName;
        Array<CollisionMask, COLLISION_COUNT> m_collisionMasks;

        static CollisionManager* sp_singleton;

#pragma endregion
    };
}