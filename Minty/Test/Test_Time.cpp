#include "Test_Time.h"
#include "Minty.h"

void test_Time(Test& _test)
{
	CATEGORY(Time)
	{
		TEST("Constructor")
		{
			Time time;
			EXPECT_EQUAL(time.get_total(), 0.0f);
			EXPECT_EQUAL(time.get_elapsed(), 0.0f);
		}

		TEST("Get/Set Total")
		{
			Time time;
			EXPECT_EQUAL(time.get_total(), 0.0f);
			time.set_total(1.0f);
			EXPECT_EQUAL(time.get_total(), 1.0f);
		}

		TEST("Get/Set Elapsed")
		{
			Time time;
			EXPECT_EQUAL(time.get_elapsed(), 0.0f);
			time.set_elapsed(1.0f);
			EXPECT_EQUAL(time.get_elapsed(), 1.0f);
		}

		TEST("Update")
		{
			Time time;
			time.update(1.0f, 2.0f);
			EXPECT_EQUAL(time.get_total(), 1.0f);
			EXPECT_EQUAL(time.get_elapsed(), 2.0f);
		}

		TEST("Now")
		{
			TimePoint now0 = Time::now();
			TimePoint now1 = Time::now();
			EXPECT(now1, >= , now0);
			TimePoint now2 = Time::now();
			EXPECT(now2, >= , now1);
		}

		TEST("Calculate Duration in Seconds")
		{
			TimePoint start = Time::now();
			Time::sleep(ONE_MILLISECOND * 100);
			TimePoint end = Time::now();
			Float duration = Time::calculate_duration_seconds(start, end);
			EXPECT(duration, >= , 0.1f);
			EXPECT(duration, < , 0.2f);
		}

		TEST("Timestamp")
		{
			String timestamp = Time::timestamp();
			EXPECT_EQUAL(timestamp.get_size(), 27);
			EXPECT_EQUAL(timestamp[4], '-');
			EXPECT_EQUAL(timestamp[7], '-');
			EXPECT_EQUAL(timestamp[10], ' ');
			EXPECT_EQUAL(timestamp[13], ':');
			EXPECT_EQUAL(timestamp[16], ':');
			EXPECT_EQUAL(timestamp[19], '.');
		}

		TEST("Sleep")
		{
			TimePoint start = Time::now();
			Time::sleep(ONE_MILLISECOND * 100);
			TimePoint end = Time::now();
			Float duration = Time::calculate_duration_seconds(start, end);
			EXPECT(duration, >= , 0.1f);
			EXPECT(duration, < , 0.2f);
		}
	}
}
