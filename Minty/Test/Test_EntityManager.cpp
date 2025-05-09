#include "Test_EntityManager.h"
#include "Minty.h"

void test_EntityManager(Test& _test)
{
	CATEGORY(EntityManager)
	{
		TEST("Constructor/Create")
		{
			EXPECT_SUCCESS(EntityManager::create());
		}

		TEST("Get ID")
		{
			Owner<EntityManager> manager = EntityManager::create();
			EXPECT_FAILURE(manager->get_id(INVALID_ENTITY));
			Entity entity = manager->create_entity();
			EXPECT_EQUAL(manager->get_id(entity), INVALID_ID);
			entity = manager->create_entity(UUID(1));
			EXPECT_EQUAL(manager->get_id(entity), UUID(1));
		}

		TEST("Get Entity")
		{
			Owner<EntityManager> manager = EntityManager::create();
			EXPECT_FAILURE(manager->get_entity(INVALID_ID));
			Entity entity = manager->create_entity(UUID(1));
			EXPECT_EQUAL(manager->get_entity(UUID(1)), entity);
		}

		TEST("Get/Set Enabled")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity entity = manager->create_entity();
			EXPECT_FALSE(manager->get_enabled(entity));
			manager->set_enabled(entity, true);
			EXPECT_TRUE(manager->get_enabled(entity));
			manager->set_enabled(entity, false);
			EXPECT_FALSE(manager->get_enabled(entity));
		}

		TEST("Get/Set Visible")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity entity = manager->create_entity();
			EXPECT_FALSE(manager->get_visible(entity));
			manager->set_visible(entity, true);
			EXPECT_TRUE(manager->get_visible(entity));
			manager->set_visible(entity, false);
			EXPECT_FALSE(manager->get_visible(entity));
		}

		TEST("Get/Set Layer")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity entity = manager->create_entity();
			EXPECT_EQUAL(manager->get_layer(entity), LAYER_DEFAULT);
			manager->set_layer(entity, 3);
			EXPECT_EQUAL(manager->get_layer(entity), 3);
			manager->set_layer(entity, LAYER_NONE);
			EXPECT_EQUAL(manager->get_layer(entity), LAYER_NONE);
		}

		TEST("Get/Set Parent")
		{
			// generic get/set
			Owner<EntityManager> manager = EntityManager::create();
			Entity entity = manager->create_entity();
			EXPECT_EQUAL(manager->get_parent(entity), INVALID_ENTITY);
			Entity parent = manager->create_entity();
			manager->set_parent(entity, parent);
			EXPECT_EQUAL(manager->get_parent(entity), parent);
			manager->set_parent(entity, INVALID_ENTITY);
			EXPECT_EQUAL(manager->get_parent(entity), INVALID_ENTITY);
			
			// siblings
			manager->clear();
			parent = manager->create_entity();
			Vector<Entity> children;
			children.resize(5, INVALID_ENTITY);
			for (int i = 0; i < 5; ++i)
			{
				children[i] = manager->create_entity();
				manager->set_parent(children[i], parent);
			}

			// check that all children have correct values
			for (unsigned int i = 0; i < 5; ++i)
			{
				RelationshipComponent& relationship = manager->get_component<RelationshipComponent>(children[i]);
				EXPECT_EQUAL(relationship.parent, parent);
				EXPECT_EQUAL(relationship.index, i);

				if (i == 0)
				{
					EXPECT_EQUAL(relationship.prev, INVALID_ENTITY);
				}
				else
				{
					EXPECT_EQUAL(relationship.prev, children[i - 1]);
				}

				if (i == 4)
				{
					EXPECT_EQUAL(relationship.next, INVALID_ENTITY);
				}
				else
				{
					EXPECT_EQUAL(relationship.next, children[i + 1]);
				}
			}
		}

		TEST("Get/Set Name")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity entity = manager->create_entity();
			EXPECT_EQUAL(manager->get_name(entity), "");
			manager->set_name(entity, "Test");
			EXPECT_EQUAL(manager->get_name(entity), "Test");
			manager->set_name(entity, "");
			EXPECT_EQUAL(manager->get_name(entity), "");
		}

		TEST("Contains")
		{
			Owner<EntityManager> manager = EntityManager::create();
			UUID uuid(1);
			Entity entity = manager->create_entity(uuid);
			EXPECT_TRUE(manager->contains(entity));
			EXPECT_FALSE(manager->contains(INVALID_ENTITY));
			EXPECT_TRUE(manager->contains(uuid));
			EXPECT_FALSE(manager->contains(INVALID_ID));
		}

		TEST("Is In Layer")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity entity = manager->create_entity();
			EXPECT_TRUE(manager->is_in_layer(entity, LAYER_DEFAULT));
			EXPECT_FALSE(manager->is_in_layer(entity, LAYER_NONE));
			manager->set_layer(entity, 2);
			EXPECT_TRUE(manager->is_in_layer(entity, 2));
			EXPECT_FALSE(manager->is_in_layer(entity, LAYER_DEFAULT));
			manager->set_layer(entity, LAYER_NONE);
			EXPECT_TRUE(manager->is_in_layer(entity, LAYER_NONE));
			manager->set_layer(entity, 7);
			EXPECT_TRUE(manager->is_in_layer(entity, 1));
			EXPECT_TRUE(manager->is_in_layer(entity, 2));
			EXPECT_TRUE(manager->is_in_layer(entity, 7));
			EXPECT_FALSE(manager->is_in_layer(entity, 15));
		}

		TEST("Dirty")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity entity = manager->create_entity();
			EXPECT_FALSE(manager->has_component<DirtyComponent>(entity));
			manager->dirty(entity);
			EXPECT_TRUE(manager->has_component<DirtyComponent>(entity));
		}

		TEST("Create Entity Default")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity entity = manager->create_entity();
			EXPECT_TRUE(manager->contains(entity));
			EXPECT_FALSE(manager->get_enabled(entity));
			EXPECT_FALSE(manager->get_visible(entity));
			EXPECT_EQUAL(manager->get_layer(entity), LAYER_DEFAULT);
			EXPECT_EQUAL(manager->get_parent(entity), INVALID_ENTITY);
			EXPECT_FALSE(manager->has_component<DirtyComponent>(entity));
		}

		TEST("Create Entity with ID")
		{
			Owner<EntityManager> manager = EntityManager::create();
			UUID id = UUID(1);
			Entity entity = manager->create_entity(id);
			EXPECT_TRUE(manager->contains(entity));
			EXPECT_TRUE(manager->contains(id));
			EXPECT_EQUAL(manager->get_id(entity), id);
			EXPECT_FALSE(manager->get_enabled(entity));
			EXPECT_FALSE(manager->get_visible(entity));
			EXPECT_EQUAL(manager->get_layer(entity), LAYER_DEFAULT);
			EXPECT_EQUAL(manager->get_parent(entity), INVALID_ENTITY);
			EXPECT_FALSE(manager->has_component<DirtyComponent>(entity));
		}

		TEST("Create Entity with Name")
		{
			Owner<EntityManager> manager = EntityManager::create();
			String name = "Test";
			Entity entity = manager->create_entity(name);
			EXPECT_TRUE(manager->contains(entity));
			EXPECT_EQUAL(manager->get_name(entity), name);
			EXPECT_FALSE(manager->get_enabled(entity));
			EXPECT_FALSE(manager->get_visible(entity));
			EXPECT_EQUAL(manager->get_layer(entity), LAYER_DEFAULT);
			EXPECT_EQUAL(manager->get_parent(entity), INVALID_ENTITY);
			EXPECT_FALSE(manager->has_component<DirtyComponent>(entity));
		}

		TEST("Create Entity with Name and ID")
		{
			Owner<EntityManager> manager = EntityManager::create();
			String name = "Test";
			UUID id = UUID(1);
			Entity entity = manager->create_entity(name, id);
			EXPECT_TRUE(manager->contains(entity));
			EXPECT_TRUE(manager->contains(id));
			EXPECT_EQUAL(manager->get_id(entity), id);
			EXPECT_EQUAL(manager->get_name(entity), name);
			EXPECT_FALSE(manager->get_enabled(entity));
			EXPECT_FALSE(manager->get_visible(entity));
			EXPECT_EQUAL(manager->get_layer(entity), LAYER_DEFAULT);
			EXPECT_EQUAL(manager->get_parent(entity), INVALID_ENTITY);
			EXPECT_FALSE(manager->has_component<DirtyComponent>(entity));
		}

		TEST("Add Component")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity entity = manager->create_entity();
			EXPECT_FALSE(manager->has_component<NameComponent>(entity));
			NameComponent& nameComp = manager->add_component<NameComponent>(entity);
			nameComp.name = "Test";
			EXPECT_TRUE(manager->has_component<NameComponent>(entity));
			EXPECT_EQUAL(manager->get_component<NameComponent>(entity).name, nameComp.name);
		}

		TEST("Get Component")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity entity = manager->create_entity();
			NameComponent& nameComp = manager->add_component<NameComponent>(entity);
			nameComp.name = "Test";
			EXPECT_EQUAL(manager->get_component<NameComponent>(entity).name, nameComp.name);
		}

		TEST("Get Component Const")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity entity = manager->create_entity();
			NameComponent& nameComp = manager->add_component<NameComponent>(entity);
			nameComp.name = "Test";
			const EntityManager& constManager = *manager;
			EXPECT_EQUAL(constManager.get_component<NameComponent>(entity).name, nameComp.name);
		}

		TEST("Try Get Component")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity entity = manager->create_entity();
			EXPECT_EQUAL(manager->try_get_component<NameComponent>(entity), nullptr);
			NameComponent& nameComp = manager->add_component<NameComponent>(entity);
			nameComp.name = "Test";
			EXPECT_EQUAL(manager->try_get_component<NameComponent>(entity)->name, nameComp.name);
		}

		TEST("Try Get Component Const")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity entity = manager->create_entity();
			EXPECT_EQUAL(manager->try_get_component<NameComponent>(entity), nullptr);
			NameComponent& nameComp = manager->add_component<NameComponent>(entity);
			nameComp.name = "Test";
			const EntityManager& constManager = *manager;
			EXPECT_EQUAL(constManager.try_get_component<NameComponent>(entity)->name, nameComp.name);
		}

		TEST("Has Component")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity entity = manager->create_entity();
			EXPECT_FALSE(manager->has_component<NameComponent>(entity));
			NameComponent& nameComp = manager->add_component<NameComponent>(entity);
			nameComp.name = "Test";
			EXPECT_TRUE(manager->has_component<NameComponent>(entity));
		}

		TEST("Remove Component")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity entity = manager->create_entity();
			EXPECT_FALSE(manager->has_component<NameComponent>(entity));
			NameComponent& nameComp = manager->add_component<NameComponent>(entity);
			nameComp.name = "Test";
			EXPECT_TRUE(manager->has_component<NameComponent>(entity));
			manager->remove_component<NameComponent>(entity);
			EXPECT_FALSE(manager->has_component<NameComponent>(entity));
		}

		TEST("Clear")
		{
			Owner<EntityManager> manager = EntityManager::create();
			UUID id(1);
			Entity entity = manager->create_entity(id);
			EXPECT_TRUE(manager->contains(entity));
			EXPECT_TRUE(manager->contains(id));
			manager->clear();
			EXPECT_FALSE(manager->contains(entity));
			EXPECT_FALSE(manager->contains(id));
		}

		TEST("View")
		{

		}

		TEST("Sort")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity entity0 = manager->create_entity("Entity0");
			Entity entity1 = manager->create_entity("Entity1");
			Entity entity2 = manager->create_entity("Entity2");
			Entity entity3 = manager->create_entity("Entity3");

			manager->set_parent(entity1, entity0);
			manager->set_parent(entity3, entity1);
			manager->set_parent(entity2, entity0);
			EXPECT_FAILURE(manager->set_parent(entity0, entity0)); // cannot set self as parent
			EXPECT_FAILURE(manager->set_parent(entity0, entity3)); // cannot set loop

			/*
				Final Hierarchy Tree:
				entity0
					- entity1
						- entity3
					- entity2
			*/

			EXPECT_SUCCESS(manager->sort());

			// check the order
			Vector<Entity> correctOrder = { entity0, entity1, entity3, entity2 };
			Size i = 0;
			manager->view<RelationshipComponent>().each([&](Entity const entity, RelationshipComponent const& relationship)
				{
					EXPECT_EQUAL(entity, correctOrder[i]);
					++i;
				});
		}

		TEST("Swap Siblings")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity parent = manager->create_entity("Parent");
			Entity entity0 = manager->create_entity("Entity0");
			Entity entity1 = manager->create_entity("Entity1");
			Entity entity2 = manager->create_entity("Entity2");
			Entity entity3 = manager->create_entity("Entity3");
			manager->set_parent(entity0, parent);
			manager->set_parent(entity1, parent);
			manager->set_parent(entity2, parent);
			manager->set_parent(entity3, parent);
			EXPECT_FAILURE(manager->swap_siblings(entity0, parent)); // cannot swap siblings if not in same parent
			EXPECT_FAILURE(manager->swap_siblings(entity0, entity0)); // cannot swap same entity
			EXPECT_SUCCESS(manager->swap_siblings(entity0, entity1));
			EXPECT_SUCCESS(manager->swap_siblings(entity2, entity3));

			manager->sort();

			// check the order
			Vector<Entity> correctOrder = { parent, entity1, entity0, entity3, entity2 };
			Size i = 0;
			manager->view<RelationshipComponent>().each([&](Entity const entity, RelationshipComponent const& relationship)
				{
					EXPECT_EQUAL(entity, correctOrder[i]);
					++i;
				});
		}

		TEST("Move to Next")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity parent = manager->create_entity("Parent");
			Entity entity0 = manager->create_entity("Entity0");
			Entity entity1 = manager->create_entity("Entity1");
			Entity entity2 = manager->create_entity("Entity2");
			Entity entity3 = manager->create_entity("Entity3");
			manager->set_parent(entity0, parent);
			manager->set_parent(entity1, parent);
			manager->set_parent(entity2, parent);
			manager->set_parent(entity3, parent);
			EXPECT_FAILURE(manager->move_to_next(INVALID_ENTITY));
			EXPECT_SUCCESS(manager->move_to_next(entity0));
			EXPECT_SUCCESS(manager->move_to_next(entity2));
			EXPECT_SUCCESS(manager->move_to_next(entity3)); // does nothing
			manager->sort();
			// check the order
			Vector<Entity> correctOrder = { parent, entity1, entity0, entity2, entity3 };
			Size i = 0;
			manager->view<RelationshipComponent>().each([&](Entity const entity, RelationshipComponent const& relationship)
				{
					EXPECT_EQUAL(entity, correctOrder[i]);
					++i;
				});
		}

		TEST("Move to Previous")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity parent = manager->create_entity("Parent");
			Entity entity0 = manager->create_entity("Entity0");
			Entity entity1 = manager->create_entity("Entity1");
			Entity entity2 = manager->create_entity("Entity2");
			Entity entity3 = manager->create_entity("Entity3");
			manager->set_parent(entity0, parent);
			manager->set_parent(entity1, parent);
			manager->set_parent(entity2, parent);
			manager->set_parent(entity3, parent);
			EXPECT_FAILURE(manager->move_to_previous(INVALID_ENTITY));
			EXPECT_SUCCESS(manager->move_to_previous(entity0)); // does nothing
			EXPECT_SUCCESS(manager->move_to_previous(entity1));
			EXPECT_SUCCESS(manager->move_to_previous(entity3));
			manager->sort();
			// check the order
			Vector<Entity> correctOrder = { parent, entity1, entity0, entity3, entity2 };
			Size i = 0;
			manager->view<RelationshipComponent>().each([&](Entity const entity, RelationshipComponent const& relationship)
				{
					EXPECT_EQUAL(entity, correctOrder[i]);
					++i;
				});
		}

		TEST("Move to First")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity parent = manager->create_entity("Parent");
			Entity entity0 = manager->create_entity("Entity0");
			Entity entity1 = manager->create_entity("Entity1");
			Entity entity2 = manager->create_entity("Entity2");
			Entity entity3 = manager->create_entity("Entity3");
			manager->set_parent(entity0, parent);
			manager->set_parent(entity1, parent);
			manager->set_parent(entity2, parent);
			manager->set_parent(entity3, parent);
			EXPECT_FAILURE(manager->move_to_first(INVALID_ENTITY));
			EXPECT_SUCCESS(manager->move_to_first(entity0)); // does nothing
			EXPECT_SUCCESS(manager->move_to_first(entity3));
			manager->sort();
			// check the order
			Vector<Entity> correctOrder = { parent, entity3, entity0, entity1, entity2 };
			Size i = 0;
			manager->view<RelationshipComponent>().each([&](Entity const entity, RelationshipComponent const& relationship)
				{
					EXPECT_EQUAL(entity, correctOrder[i]);
					++i;
				});
		}

		TEST("Move to Last")
		{
			Owner<EntityManager> manager = EntityManager::create();
			Entity parent = manager->create_entity("Parent");
			Entity entity0 = manager->create_entity("Entity0");
			Entity entity1 = manager->create_entity("Entity1");
			Entity entity2 = manager->create_entity("Entity2");
			Entity entity3 = manager->create_entity("Entity3");
			manager->set_parent(entity0, parent);
			manager->set_parent(entity1, parent);
			manager->set_parent(entity2, parent);
			manager->set_parent(entity3, parent);
			EXPECT_FAILURE(manager->move_to_last(INVALID_ENTITY));
			EXPECT_SUCCESS(manager->move_to_last(entity3)); // does nothing
			EXPECT_SUCCESS(manager->move_to_last(entity0));
			manager->sort();
			// check the order
			Vector<Entity> correctOrder = { parent, entity1, entity2, entity3, entity0 };
			Size i = 0;
			manager->view<RelationshipComponent>().each([&](Entity const entity, RelationshipComponent const& relationship)
				{
					EXPECT_EQUAL(entity, correctOrder[i]);
					++i;
				});
		}
	}
}
