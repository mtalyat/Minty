// THIS FILE IS AUTO GENERATED
// DO NOT MODIFY THIS FILE DIRECTLY

#include "Minty/Application/Application.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Component/_Component.h"

using namespace Minty;

void Minty::Application::register_components()
{
    EntityManager::register_component<AnimatorComponent>("Animator");
	EntityManager::register_component<AudioListenerComponent>("AudioListener");
	EntityManager::register_component<AudioSourceComponent>("AudioSource");
	EntityManager::register_component<CameraComponent>("Camera");
	EntityManager::register_component<CanvasComponent>("Canvas");
	EntityManager::register_component<ColliderComponent>("Collider");
	EntityManager::register_component<DestroyComponent>("Destroy");
	EntityManager::register_component<DirtyComponent>("Dirty");
	EntityManager::register_component<EnabledComponent>("Enabled");
	EntityManager::register_component<LayerComponent>("Layer");
	EntityManager::register_component<MaskComponent>("Mask");
	EntityManager::register_component<MaskedComponent>("Masked");
	EntityManager::register_component<MeshComponent>("Mesh");
	EntityManager::register_component<NameComponent>("Name");
	EntityManager::register_component<RelationshipComponent>("Relationship");
	EntityManager::register_component<RigidBodyComponent>("RigidBody");
	EntityManager::register_component<SpriteComponent>("Sprite");
	EntityManager::register_component<TextComponent>("Text");
	EntityManager::register_component<TransformComponent>("Transform");
	EntityManager::register_component<UITransformComponent>("UITransform");
	EntityManager::register_component<UUIDComponent>("UUID");
	EntityManager::register_component<VisibleComponent>("Visible");
}