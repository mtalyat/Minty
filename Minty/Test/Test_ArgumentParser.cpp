#include "Test_ArgumentParser.h"  
#include "Minty.h"  

void test_ArgumentParser(Test& _test)  
{  
   CATEGORY(ArgumentParser)  
   {  
       TEST("Constructor")  
       {  
           EXPECT_SUCCESS(ArgumentParser parser);  
       }  

       TEST("Add Parameter")  
       {  
           ArgumentParser parser;

           // positional
		   EXPECT_FAILURE(parser.add_parameter(""));
           EXPECT_SUCCESS(parser.add_parameter("test0"));  
           EXPECT_SUCCESS(parser.add_parameter("test1", 2));
           EXPECT_FAILURE(parser.add_parameter("test2", 0));
		   EXPECT_SUCCESS(parser.add_parameter("test2", -1));

           const char* argv[] = { "test0", "test1", "test2" };  
           parser.parse(3, argv);

		   EXPECT_EQUAL(parser.get_argument("test0").get_size(), 1);
           EXPECT_EQUAL(parser.get_argument("test1").get_size(), 2);
		   EXPECT_FALSE(parser.has_argument("test2"));
		   EXPECT_FALSE(parser.has_argument("test3"));

           // flag
		   parser = ArgumentParser();
		   EXPECT_FAILURE(parser.add_parameter("", "t0"));
		   EXPECT_SUCCESS(parser.add_parameter("test3", "t3"));
		   EXPECT_SUCCESS(parser.add_parameter("test4", "t4", 2));
		   EXPECT_SUCCESS(parser.add_parameter("test5", "t5", 0));
		   EXPECT_SUCCESS(parser.add_parameter("test6", "t6", -1));
		   const char* argv2[] = { "-test3", "test3", "-t4", "test4a", "test4b" };
		   parser.parse(5, argv2);

		   EXPECT_EQUAL(parser.get_argument("test3").get_size(), 1);
		   EXPECT_EQUAL(parser.get_argument("test4").get_size(), 2);
		   EXPECT_FALSE(parser.has_argument("test5"));
		   EXPECT_FALSE(parser.has_argument("test6"));
		   EXPECT_FALSE(parser.has_argument("test0"));
       }

	   TEST("Parse")
	   {
		   const char* argv[] = { "test0", "test1", "test2" };
		   ArgumentParser parser;
		   EXPECT_FAILURE(parser.parse(0, nullptr));
		   EXPECT_FAILURE(parser.parse(1, nullptr));
		   EXPECT_FAILURE(parser.parse(0, argv));
		   // positional
		   parser.add_parameter("test0");
		   parser.add_parameter("test1", 2);
		   parser.add_parameter("test2", -1);
		   parser.parse(3, argv);
		   EXPECT_EQUAL(parser.get_argument("test0").get_size(), 1);
		   EXPECT_EQUAL(parser.get_argument("test1").get_size(), 2);
		   EXPECT_FALSE(parser.has_argument("test2"));
		   EXPECT_FALSE(parser.has_argument("test3"));
		   EXPECT_EQUAL(parser.get_argument("test0").at(0), "test0");
		   EXPECT_EQUAL(parser.get_argument("test1").at(0), "test1");
		   EXPECT_EQUAL(parser.get_argument("test1").at(1), "test2");
		   // flag
		   parser = ArgumentParser();
		   parser.add_parameter("test3", "t3");
		   parser.add_parameter("test4", "t4", 2);
		   parser.add_parameter("test5", "t5", 0);
		   parser.add_parameter("test6", "t6", -1);
		   const char* argv2[] = { "-test3", "test3", "-t5", "-t4", "test4a", "test4b"};
		   parser.parse(6, argv2);
		   EXPECT_EQUAL(parser.get_argument("test3").get_size(), 1);
		   EXPECT_EQUAL(parser.get_argument("test4").get_size(), 2);
		   EXPECT_EQUAL(parser.get_argument("test5").get_size(), 0);
		   EXPECT_EQUAL(parser.get_argument("test3").at(0), "test3");
		   EXPECT_EQUAL(parser.get_argument("test4").at(0), "test4a");
		   EXPECT_EQUAL(parser.get_argument("test4").at(1), "test4b");
	   }

	   TEST("Get Argument")
	   {
		   const char* argv[] = { "test0", "test1", "test2" };
		   ArgumentParser parser;
		   parser.add_parameter("test0");
		   parser.add_parameter("test1", 2);
		   parser.add_parameter("test2", -1);
		   parser.parse(3, argv);
		   EXPECT_EQUAL(parser.get_argument("test0").get_size(), 1);
		   EXPECT_EQUAL(parser.get_argument("test1").get_size(), 2);
		   EXPECT_EQUAL(parser.get_argument("test0").at(0), "test0");
		   EXPECT_EQUAL(parser.get_argument("test1").at(0), "test1");
		   EXPECT_EQUAL(parser.get_argument("test1").at(1), "test2");
		   EXPECT_FAILURE(parser.get_argument("test2"));
		   EXPECT_FAILURE(parser.get_argument(""));
	   }

	   TEST("Has Argument")
	   {
		   const char* argv[] = { "test0", "test1", "test2" };
		   ArgumentParser parser;
		   parser.add_parameter("test0");
		   parser.add_parameter("test1", 2);
		   parser.add_parameter("test2", -1);
		   parser.parse(3, argv);
		   EXPECT_TRUE(parser.has_argument("test0"));
		   EXPECT_TRUE(parser.has_argument("test1"));
		   EXPECT_FALSE(parser.has_argument("test2"));
		   EXPECT_FALSE(parser.has_argument("test3"));
	   }
   }
}
