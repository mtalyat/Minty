#include "Test_Stopwatch.h"
#include "Minty.h"

void test_Stopwatch(Test& _test)
{
	CATEGORY(Stopwatch)
	{
		TEST("Constructor")
		{
			Stopwatch stopwatch;
			EXPECT_EQUAL(stopwatch.get_elapsed(), 0);
			EXPECT_FALSE(stopwatch.is_running());
		}

		TEST("Get Elapsed")
		{
			Stopwatch stopwatch;
			EXPECT_EQUAL(stopwatch.get_elapsed(), 0);
			stopwatch.start();
			Time::sleep(ONE_MILLISECOND * 100);
			stopwatch.stop();
			EXPECT(stopwatch.get_elapsed(), >= , ONE_MILLISECOND * 100);
			EXPECT(stopwatch.get_elapsed(), < , ONE_MILLISECOND * 200);
		}
		
		TEST("Get Elapsed Seconds")
		{
			Stopwatch stopwatch;
			EXPECT_EQUAL(stopwatch.get_elapsed_s(), 0.0f);
			stopwatch.start();
			Time::sleep(ONE_MILLISECOND * 100);
			stopwatch.stop();
			EXPECT(stopwatch.get_elapsed_s(), >= , 0.1f);
			EXPECT(stopwatch.get_elapsed_s(), < , 0.2f);
		}

		TEST("Get Elapsed String")
		{
			Stopwatch stopwatch;
			EXPECT_EQUAL(stopwatch.get_elapsed_string(), "0:0:0.0");
			stopwatch.start();
			Time::sleep(ONE_MILLISECOND * 100);
			stopwatch.stop();
			EXPECT(stopwatch.get_elapsed_string().get_size(), > , 7);
		}

		TEST("Start")
		{
			Stopwatch stopwatch;
			EXPECT_FALSE(stopwatch.is_running());
			stopwatch.start();
			EXPECT_TRUE(stopwatch.is_running());
			EXPECT(stopwatch.get_elapsed(), > , 0);
		}

		TEST("Stop")
		{
			Stopwatch stopwatch;
			EXPECT_FALSE(stopwatch.is_running());
			stopwatch.start();
			EXPECT_TRUE(stopwatch.is_running());
			stopwatch.stop();
			EXPECT_FALSE(stopwatch.is_running());
			EXPECT(stopwatch.get_elapsed(), > , 0);
		}

		TEST("Reset")
		{
			Stopwatch stopwatch;
			stopwatch.start();
			Time::sleep(ONE_MILLISECOND * 100);
			stopwatch.stop();
			EXPECT(stopwatch.get_elapsed(), > , 0);
			stopwatch.reset();
			EXPECT_EQUAL(stopwatch.get_elapsed(), 0);
		}

		TEST("Is Running")
		{
			Stopwatch stopwatch;
			EXPECT_FALSE(stopwatch.is_running());
			stopwatch.start();
			EXPECT_TRUE(stopwatch.is_running());
			stopwatch.stop();
			EXPECT_FALSE(stopwatch.is_running());
		}

		TEST("Lap")
		{
			Stopwatch stopwatch;
			stopwatch.start();
			Time::sleep(ONE_MILLISECOND * 100);
			stopwatch.stop();
			Size lapCount = stopwatch.lap(ONE_MILLISECOND * 30);
			EXPECT_EQUAL(lapCount, 3);
			EXPECT(stopwatch.get_elapsed(), > , 0);
			EXPECT(stopwatch.get_elapsed(), < , ONE_MILLISECOND * 100);
			EXPECT_FAILURE(stopwatch.lap(0));
		}

		TEST("Restart")
		{
			Stopwatch stopwatch;
			stopwatch.start();
			EXPECT_TRUE(stopwatch.is_running());
			EXPECT(stopwatch.get_elapsed(), > , 0);
			stopwatch.restart();
			EXPECT_TRUE(stopwatch.is_running());
			EXPECT(stopwatch.get_elapsed(), > , 0);
		}

		TEST("Start New")
		{
			Stopwatch stopwatch = Stopwatch::start_new();
			EXPECT_TRUE(stopwatch.is_running());
		}
	}
}
