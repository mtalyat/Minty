#include "Test_Node.h"
#include "Minty.h"

void test_Node(Test& _test)
{
	CATEGORY(Node)
	{
		TEST("Default Constructor")
		{
			Node node;
			EXPECT_TRUE(node.get_name().is_empty());
			EXPECT_EQUAL(node.get_data().get_size(), 0);
			EXPECT_EQUAL(node.get_children_size(), 0);
		}

		TEST("Values Constructor")
		{
			Node node("Node", nullptr, 0);
			EXPECT_EQUAL(node.get_name(), "Node");
			EXPECT_EQUAL(node.get_data().get_size(), 0);
			EXPECT_EQUAL(node.get_children_size(), 0);

			Size data = 5;
			Node node2("Node2", &data, sizeof(Size));
			EXPECT_EQUAL(node2.get_name(), "Node2");
			EXPECT_EQUAL(*static_cast<Size*>(node2.get_data().get_data()), data);
			EXPECT_EQUAL(node2.get_data().get_size(), sizeof(Size));
			EXPECT_EQUAL(node2.get_children_size(), 0);
		}

		TEST("String Constructor")
		{
			String const name = "Node";
			String const value = "Value";
			Node node(name, value);
			EXPECT_EQUAL(node.get_name(), name);
			EXPECT_EQUAL(node.get_data_string(), value);
			EXPECT_EQUAL(node.get_data().get_size(), value.get_size());
			EXPECT_EQUAL(node.get_children_size(), 0);
		}

		TEST("Name Constructor")
		{
			Node node("Node");
			EXPECT_EQUAL(node.get_name(), "Node");
			EXPECT_EQUAL(node.get_data().get_size(), 0);
			EXPECT_EQUAL(node.get_children_size(), 0);
		}

		TEST("Copy Constructor")
		{
			Size const data = 5;
			Node node("Node", &data, sizeof(Size));
			node.add_child("Child0");
			node.add_child("Child1");
			node.add_child("Child2");
			Node node2(node);
			EXPECT_EQUAL(node2.get_name(), "Node");
			EXPECT_EQUAL(*static_cast<Size*>(node2.get_data().get_data()), data);
			EXPECT_EQUAL(node2.get_data().get_size(), sizeof(Size));
			EXPECT_EQUAL(node2.get_children_size(), 3);
			EXPECT_EQUAL(node2.get_child(0).get_name(), "Child0");
			EXPECT_EQUAL(node2.get_child(1).get_name(), "Child1");
			EXPECT_EQUAL(node2.get_child(2).get_name(), "Child2");
		}

		TEST("Move Constructor")
		{
			Size const data = 5;
			Node node("Node", &data, sizeof(Size));
			node.add_child("Child0");
			node.add_child("Child1");
			node.add_child("Child2");
			Node node2(std::move(node));
			EXPECT_EQUAL(node2.get_name(), "Node");
			EXPECT_EQUAL(*static_cast<Size*>(node2.get_data().get_data()), data);
			EXPECT_EQUAL(node2.get_data().get_size(), sizeof(Size));
			EXPECT_EQUAL(node2.get_children_size(), 3);
			EXPECT_EQUAL(node2.get_child(0).get_name(), "Child0");
			EXPECT_EQUAL(node2.get_child(1).get_name(), "Child1");
			EXPECT_EQUAL(node2.get_child(2).get_name(), "Child2");
		}

		TEST("Copy Assignment Operator")
		{
			Size const data = 5;
			Node node("Node", &data, sizeof(Size));
			node.add_child("Child0");
			node.add_child("Child1");
			node.add_child("Child2");
			Node node2;
			node2 = node;
			EXPECT_EQUAL(node2.get_name(), "Node");
			EXPECT_EQUAL(*static_cast<Size*>(node2.get_data().get_data()), data);
			EXPECT_EQUAL(node2.get_data().get_size(), sizeof(Size));
			EXPECT_EQUAL(node2.get_children_size(), 3);
			EXPECT_EQUAL(node2.get_child(0).get_name(), "Child0");
			EXPECT_EQUAL(node2.get_child(1).get_name(), "Child1");
			EXPECT_EQUAL(node2.get_child(2).get_name(), "Child2");
		}

		TEST("Move Assignment Operator")
		{
			Size const data = 5;
			Node node("Node", &data, sizeof(Size));
			node.add_child("Child0");
			node.add_child("Child1");
			node.add_child("Child2");
			Node node2;
			node2 = std::move(node);
			EXPECT_EQUAL(node2.get_name(), "Node");
			EXPECT_EQUAL(*static_cast<Size*>(node2.get_data().get_data()), data);
			EXPECT_EQUAL(node2.get_data().get_size(), sizeof(Size));
			EXPECT_EQUAL(node2.get_children_size(), 3);
			EXPECT_EQUAL(node2.get_child(0).get_name(), "Child0");
			EXPECT_EQUAL(node2.get_child(1).get_name(), "Child1");
			EXPECT_EQUAL(node2.get_child(2).get_name(), "Child2");
		}

		TEST("Get Name")
		{
			Node node("Node");
			EXPECT_EQUAL(node.get_name(), "Node");
		}

		TEST("Get Data")
		{
			Size const data = 5;
			Node node("Node", &data, sizeof(Size));
			EXPECT_EQUAL(*static_cast<Size*>(node.get_data().get_data()), data);
			EXPECT_EQUAL(node.get_data().get_size(), sizeof(Size));
		}

		TEST("Get Data Const")
		{
			Size const data = 5;
			Node const node("Node", &data, sizeof(Size));
			EXPECT_EQUAL(*static_cast<Size const*>(node.get_data().get_data()), data);
			EXPECT_EQUAL(node.get_data().get_size(), sizeof(Size));
		}

		TEST("Get Data String")
		{
			String const data = "Data";
			Node node("Node", data.get_data(), data.get_size());
			EXPECT_EQUAL(node.get_data_string(), data);
		}

		TEST("Set Data")
		{
			Size const data = 5;
			Node node("Node");
			node.set_data(&data, sizeof(Size));
			EXPECT_EQUAL(*static_cast<Size*>(node.get_data().get_data()), data);
			EXPECT_EQUAL(node.get_data().get_size(), sizeof(Size));
		}

		TEST("Set Data String")
		{
			String const data = "Data";
			Node node("Node");
			node.set_data(data);
			EXPECT_EQUAL(node.get_data_string(), data);
		}

		TEST("Get Children Size")
		{
			Node node("Node");
			EXPECT_EQUAL(node.get_children_size(), 0);
			node.add_child("Child0");
			EXPECT_EQUAL(node.get_children_size(), 1);
			node.add_child("Child1");
			EXPECT_EQUAL(node.get_children_size(), 2);
			node.add_child("Child2");
			EXPECT_EQUAL(node.get_children_size(), 3);
		}

		TEST("Get Children")
		{
			Node node("Node");
			node.add_child("Child0");
			node.add_child("Child1");
			node.add_child("Child2");
			EXPECT_EQUAL(node.get_children().at(0).get_name(), "Child0");
			EXPECT_EQUAL(node.get_children().at(1).get_name(), "Child1");
			EXPECT_EQUAL(node.get_children().at(2).get_name(), "Child2");
		}

		TEST("Has Child Index")
		{
			Node node("Node");
			node.add_child("Child0");
			node.add_child("Child1");
			node.add_child("Child2");
			EXPECT_TRUE(node.has_child(0));
			EXPECT_TRUE(node.has_child(1));
			EXPECT_TRUE(node.has_child(2));
			EXPECT_FALSE(node.has_child(3));
		}

		TEST("Has Child Name")
		{
			Node node("Node");
			node.add_child("Child0");
			node.add_child("Child1");
			node.add_child("Child2");
			EXPECT_TRUE(node.has_child("Child0"));
			EXPECT_TRUE(node.has_child("Child1"));
			EXPECT_TRUE(node.has_child("Child2"));
			EXPECT_FALSE(node.has_child("Child3"));
		}

		TEST("Get Child Index")
		{
			Node node("Node");
			node.add_child("Child0");
			node.add_child("Child1");
			node.add_child("Child2");
			EXPECT_EQUAL(node.get_child(0).get_name(), "Child0");
			EXPECT_EQUAL(node.get_child(1).get_name(), "Child1");
			EXPECT_EQUAL(node.get_child(2).get_name(), "Child2");
			EXPECT_FAILURE(node.get_child(3));
		}

		TEST("Get Child Name")
		{
			Node node("Node");
			node.add_child("Child0");
			node.add_child("Child1");
			node.add_child("Child2");
			EXPECT_EQUAL(node.get_child("Child0").get_name(), "Child0");
			EXPECT_EQUAL(node.get_child("Child1").get_name(), "Child1");
			EXPECT_EQUAL(node.get_child("Child2").get_name(), "Child2");
			EXPECT_FAILURE(node.get_child("Child3"));
		}

		TEST("Add Child")
		{
			Size const data = 5;
			Node node("Node");
			Node& child0 = node.add_child("Child0", &data, sizeof(Size));
			Node& child1 = node.add_child("Child1");
			EXPECT_EQUAL(node.get_children_size(), 2);
			EXPECT_EQUAL(child0.get_name(), "Child0");
			DynamicContainer const& container = child0.get_data();
			EXPECT_EQUAL(container.get_size(), sizeof(Size));
			EXPECT_EQUAL(*static_cast<Size*>(container.get_data()), data);
			EXPECT_EQUAL(child1.get_name(), "Child1");
			EXPECT_EQUAL(child1.get_data().get_size(), 0);
			EXPECT_EQUAL(node.get_child(0).get_name(), "Child0");
			EXPECT_EQUAL(node.get_child(1).get_name(), "Child1");
			EXPECT_EQUAL(node.add_child("Child2", "Data").get_name(), "Child2");
			EXPECT_EQUAL(node.add_child("Child3", "Data").get_data_string(), "Data");


			EXPECT_FAILURE(node.add_child(""));
			EXPECT_FAILURE(node.add_child("Child0"));
			EXPECT_FAILURE(node.add_child("Child1"));
			EXPECT_FAILURE(node.add_child("", nullptr, 0));
			EXPECT_FAILURE(node.add_child("Child0", nullptr, 0));
			EXPECT_FAILURE(node.add_child("Child1", nullptr, 0));
		}
	}
}
