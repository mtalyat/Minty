#include "Test_Cargo.h"
#include "Minty.h"

void test_Cargo(Test& _test)
{
	CATEGORY(Cargo)
	{
		TEST("Default Constructor")
		{
			Cargo cargo;
			EXPECT_TRUE(cargo.is_empty());
		}

		TEST("Capacity Constructor")
		{
			Cargo cargo(10);
			EXPECT_TRUE(cargo.is_empty());
		}

		TEST("Variables Constructor")
		{
			Vector<Tuple<String, Variable>> variables;
			/*Cargo cargo({Tuple<String, Vector<Tuple<String, Variable>>>("object1", {
					{"key1", Variable(10)},
					{"key2", Variable(20.0f) }
				}),
				{ "object2", {
					{"key3", Variable(30)},
					{"key4", Variable(40.0f) }
				}}
				});*/
			Cargo cargo({
				Tuple<String, Vector<Tuple<String, Variable>>>( "object1", Vector<Tuple<String, Variable>>{
					{"key1", Variable(10)},
					{"key2", Variable(20.0f) }
				}),
				Tuple<String, Vector<Tuple<String, Variable>>>{ "object2", Vector<Tuple<String, Variable>>{
					{"key3", Variable(30)},
					{"key4", Variable(40.0f) }
				}}
				});
			EXPECT_FALSE(cargo.is_empty());
			EXPECT_EQUAL(cargo.get_size(), 2);
			EXPECT_EQUAL(cargo.at("object1").at("key1").get<Int>(), 10);
			EXPECT_EQUAL(cargo.at("object1").at("key2").get<Float>(), 20.0f);
			EXPECT_EQUAL(cargo.at("object2").at("key3").get<Int>(), 30);
			EXPECT_EQUAL(cargo.at("object2").at("key4").get<Float>(), 40.0f);
		}

		TEST("Copy Constructor")
		{
			Cargo cargo(10);
			Cargo copy(cargo);
			EXPECT_TRUE(copy.is_empty());
			cargo.add("object1", {
				{"key1", Variable(10)},
				{"key2", Variable(20.0f) }
				});
			copy = Cargo(cargo);
			EXPECT_FALSE(copy.is_empty());
		}

		TEST("Move Constructor")
		{
			Cargo cargo(10);
			Cargo move(std::move(cargo));
			EXPECT_TRUE(move.is_empty());
			cargo.add("object1", {
				{"key1", Variable(10)},
				{"key2", Variable(20.0f) }
				});
			move = Cargo(std::move(cargo));
			EXPECT_FALSE(move.is_empty());
		}

		TEST("Begin")
		{
			Cargo cargo(10);
			cargo.add("object1", {
				{"key1", Variable(10)},
				{"key2", Variable(20.0f) }
				});
			auto it = cargo.begin();
			EXPECT_EQUAL(it->get_first(), "object1");
			EXPECT_EQUAL(it->get_second().at("key1").get<Int>(), 10);
		}

		TEST("Begin Const")
		{
			Cargo cargo(10);
			cargo.add("object1", {
				{"key1", Variable(10)},
				{"key2", Variable(20.0f) }
				});
			Cargo const& constCargo = cargo;
			auto it = constCargo.begin();
			EXPECT_EQUAL(it->get_first(), "object1");
			EXPECT_EQUAL(it->get_second().at("key1").get<Int>(), 10);
		}

		TEST("End")
		{
			Cargo cargo(10);
			cargo.add("object1", {
				{"key1", Variable(10)},
				{"key2", Variable(20.0f) }
				});
			auto it = cargo.end();
			auto bit = cargo.begin();
			for (Size i = 0; i < cargo.get_size(); i++)
			{
				++bit;
			}
			EXPECT_EQUAL(it, bit);
		}

		TEST("End Const")
		{
			Cargo cargo(10);
			cargo.add("object1", {
				{"key1", Variable(10)},
				{"key2", Variable(20.0f) }
				});
			Cargo const& constCargo = cargo;
			auto it = constCargo.end();
			auto bit = constCargo.begin();
			for (Size i = 0; i < constCargo.get_size(); i++)
			{
				++bit;
			}
			EXPECT_EQUAL(it, bit);
		}

		TEST("Is Empty")
		{
			Cargo cargo(10);
			EXPECT_TRUE(cargo.is_empty());
			cargo.add("object1", {
				{"key1", Variable(10)},
				{"key2", Variable(20.0f) }
				});
			EXPECT_FALSE(cargo.is_empty());
		}

		TEST("Get Size")
		{
			Cargo cargo(10);
			EXPECT_EQUAL(cargo.get_size(), 0);
			cargo.add("object1", {
				{"key1", Variable(10)},
				{"key2", Variable(20.0f) }
				});
			EXPECT_EQUAL(cargo.get_size(), 1);
		}

		TEST("Contains")
		{
			Cargo cargo(10);
			cargo.add("object1", {
				{"key1", Variable(10)},
				{"key2", Variable(20.0f) }
				});
			EXPECT_TRUE(cargo.contains("object1"));
			EXPECT_FALSE(cargo.contains("nonexistent"));
		}

		TEST("At")
		{
			Cargo cargo(10);
			cargo.add("object1", {
				{"key1", Variable(10)},
				{"key2", Variable(20.0f) }
				});
			EXPECT_EQUAL(cargo.at("object1").at("key1").get<Int>(), 10);
			EXPECT_FAILURE(cargo.at("nonexistent"));
		}

		TEST("At Const")
		{
			Cargo cargo(10);
			cargo.add("object1", {
				{"key1", Variable(10)},
				{"key2", Variable(20.0f) }
				});
			Cargo const& constCargo = cargo;
			EXPECT_EQUAL(constCargo.at("object1").at("key1").get<Int>(), 10);
			EXPECT_FAILURE(constCargo.at("nonexistent"));
		}

		TEST("Add")
		{
			Cargo cargo(10);
			EXPECT_EQUAL(cargo.get_size(), 0);
			cargo.add("object1", {
				{"key1", Variable(10)},
				{"key2", Variable(20.0f) }
				});
			EXPECT_EQUAL(cargo.get_size(), 1);
			EXPECT_EQUAL(cargo.at("object1").at("key1").get<Int>(), 10);
		}

		TEST("Set")
		{
			Cargo cargo(10);
			EXPECT_FALSE(cargo.contains("object1"));
			cargo.set("object1", {
				{"key1", Variable(10)},
				{"key2", Variable(20.0f) }
				});
			EXPECT_EQUAL(cargo.at("object1").at("key1").get<Int>(), 10);
			cargo.set("object1", {
				{"key1", Variable(30)},
				{"key2", Variable(40.0f) }
				});
			EXPECT_EQUAL(cargo.at("object1").at("key1").get<Int>(), 30);
		}

		TEST("Remove")
		{
			Cargo cargo(10);
			cargo.add("object1", {
				{"key1", Variable(10)},
				{"key2", Variable(20.0f) }
				});
			EXPECT_EQUAL(cargo.get_size(), 1);
			EXPECT_TRUE(cargo.remove("object1"));
			EXPECT_EQUAL(cargo.get_size(), 0);
			EXPECT_FALSE(cargo.contains("object1"));
			EXPECT_FALSE(cargo.remove("object1"));
		}

		TEST("Find")
		{
			Cargo cargo(10);
			cargo.add("object1", {
				{"key1", Variable(10)},
				{"key2", Variable(20.0f) }
				});
			auto it = cargo.find("object1");
			EXPECT_EQUAL(it->get_first(), "object1");
			EXPECT_EQUAL(it->get_second().at("key1").get<Int>(), 10);
			EXPECT_EQUAL(cargo.find("nonexistent"), cargo.end());
		}

		TEST("Find Const")
		{
			Cargo cargo(10);
			cargo.add("object1", {
				{"key1", Variable(10)},
				{"key2", Variable(20.0f) }
				});
			Cargo const& constCargo = cargo;
			auto it = constCargo.find("object1");
			EXPECT_EQUAL(it->get_first(), "object1");
			EXPECT_EQUAL(it->get_second().at("key1").get<Int>(), 10);
			EXPECT_EQUAL(constCargo.find("nonexistent"), constCargo.end());
		}

		TEST("Pack")
		{
			// setup
			Int value0 = 10;
			Size value0Size = sizeof(Int);
			Float value1 = 20.0f;
			Size value1Size = sizeof(Float);
			Byte value2 = 30;
			Size value2Size = sizeof(Byte);
			Object object1({
				{"key1", Variable(value0)},
				{"key2", Variable(value1) },
				{"key3", Variable(value2) }
				});
			Object object2({
				{"key1", Variable(value2)},
				{"key2", Variable(value0) },
				{"key3", Variable(value1) }
				});
			Cargo cargo(10);
			cargo.add("object1", object1);
			cargo.add("object2", object2);

			// pack
			ConstantContainer container = cargo.pack();
			EXPECT_EQUAL(container.get_size(), value0Size + value1Size + value2Size + value2Size + value0Size + value1Size);
			EXPECT_EQUAL(*static_cast<Int*>(container.get_data()), 10);
			EXPECT_EQUAL(*static_cast<Float*>(static_cast<void*>(static_cast<Byte*>(container.get_data()) + value0Size)), 20.0f);
			EXPECT_EQUAL(*static_cast<Byte*>(static_cast<void*>(static_cast<Byte*>(container.get_data()) + value0Size + value1Size)), 30);
			EXPECT_EQUAL(*static_cast<Byte*>(static_cast<void*>(static_cast<Byte*>(container.get_data()) + value0Size + value1Size + value2Size)), 30);
			EXPECT_EQUAL(*static_cast<Int*>(static_cast<void*>(static_cast<Byte*>(container.get_data()) + value0Size + value1Size + value2Size + value2Size)), 10);
			EXPECT_EQUAL(*static_cast<Float*>(static_cast<void*>(static_cast<Byte*>(container.get_data()) + value0Size + value1Size + value2Size + value2Size + value0Size)), 20.0f);
		}
	}
}
