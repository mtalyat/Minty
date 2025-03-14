#include "Test_Math.h"
#include "Minty.h"

void test_Math(Test& _test)
{
	CATEGORY(Math)
	{
		TEST("Min")
		{
			EXPECT_EQUAL(Math::min(1, 2), 1);
			EXPECT_EQUAL(Math::min(2, 1), 1);
			EXPECT_EQUAL(Math::min(1, 1), 1);
			EXPECT_EQUAL(Math::min(1, 2, 3), 1);
			EXPECT_EQUAL(Math::min(2, 1, 3), 1);
			EXPECT_EQUAL(Math::min(3, 2, 1), 1);
		}

		TEST("Max")
		{
			EXPECT_EQUAL(Math::max(1, 2), 2);
			EXPECT_EQUAL(Math::max(2, 1), 2);
			EXPECT_EQUAL(Math::max(1, 1), 1);
			EXPECT_EQUAL(Math::max(1, 2, 3), 3);
			EXPECT_EQUAL(Math::max(2, 1, 3), 3);
			EXPECT_EQUAL(Math::max(3, 2, 1), 3);
		}

		TEST("Clamp")
		{
			EXPECT_EQUAL(Math::clamp(1, 2, 3), 2);
			EXPECT_EQUAL(Math::clamp(2, 2, 3), 2);
			EXPECT_EQUAL(Math::clamp(3, 2, 3), 3);
			EXPECT_EQUAL(Math::clamp(4, 2, 3), 3);
		}

		TEST("Lerp")
		{
			EXPECT_EQUAL(Math::lerp(2.0f, 6.0f, 0.0f), 2.0f);
			EXPECT_EQUAL(Math::lerp(2.0f, 6.0f, 0.5f), 4.0f);
			EXPECT_EQUAL(Math::lerp(2.0f, 6.0f, 1.0f), 6.0f);
			EXPECT_EQUAL(Math::lerp(2.0f, 6.0f, 2.0f), 10.0f);
		}

		TEST("Lerp Clamped")
		{
			EXPECT_EQUAL(Math::lerp_clamped(2.0f, 6.0f, 0.0f), 2.0f);
			EXPECT_EQUAL(Math::lerp_clamped(2.0f, 6.0f, 0.5f), 4.0f);
			EXPECT_EQUAL(Math::lerp_clamped(2.0f, 6.0f, 1.0f), 6.0f);
			EXPECT_EQUAL(Math::lerp_clamped(2.0f, 6.0f, 2.0f), 6.0f);
		}

		TEST("Round")
		{
			EXPECT_CLOSE(Math::round(1.0), 1);
			EXPECT_CLOSE(Math::round(1.4), 1);
			EXPECT_CLOSE(Math::round(1.5), 2);
			EXPECT_CLOSE(Math::round(1.6), 2);
			EXPECT_CLOSE(Math::round(112.567, -2), 112.57);
			EXPECT_CLOSE(Math::round(112.567, -1), 112.6);
			EXPECT_CLOSE(Math::round(112.567, 0), 113.0);
			EXPECT_CLOSE(Math::round(112.567, 1), 110.0);
			EXPECT_CLOSE(Math::round(112.567, 2), 100.0);
		}

		TEST("Floor")
		{
			EXPECT_CLOSE(Math::floor(1.0), 1);
			EXPECT_CLOSE(Math::floor(1.4), 1);
			EXPECT_CLOSE(Math::floor(1.5), 1);
			EXPECT_CLOSE(Math::floor(1.6), 1);
			EXPECT_CLOSE(Math::floor(112.567, -2), 112.56);
			EXPECT_CLOSE(Math::floor(112.567, -1), 112.5);
			EXPECT_CLOSE(Math::floor(112.567, 0), 112.0);
			EXPECT_CLOSE(Math::floor(112.567, 1), 110.0);
			EXPECT_CLOSE(Math::floor(112.567, 2), 100.0);
		}

		TEST("Ceiling")
		{
			EXPECT_CLOSE(Math::ceiling(1.0), 1);
			EXPECT_CLOSE(Math::ceiling(1.4), 2);
			EXPECT_CLOSE(Math::ceiling(1.5), 2);
			EXPECT_CLOSE(Math::ceiling(1.6), 2);
			EXPECT_CLOSE(Math::ceiling(112.567, -2), 112.57);
			EXPECT_CLOSE(Math::ceiling(112.567, -1), 112.6);
			EXPECT_CLOSE(Math::ceiling(112.567, 0), 113.0);
			EXPECT_CLOSE(Math::ceiling(112.567, 1), 120.0);
			EXPECT_CLOSE(Math::ceiling(112.567, 2), 200.0);
		}

		TEST("Abs")
		{
			EXPECT_EQUAL(Math::abs(1), 1);
			EXPECT_EQUAL(Math::abs(-1), 1);
			EXPECT_EQUAL(Math::abs(1.0f), 1.0f);
			EXPECT_EQUAL(Math::abs(-1.0f), 1.0f);
		}

		TEST("Sin")
		{
			EXPECT_CLOSE(Math::sin(0.0f), 0.0f);
			EXPECT_CLOSE(Math::sin(Math::PI / 2.0f), 1.0f);
			EXPECT_CLOSE(Math::sin(Math::PI), 0.0f);
			EXPECT_CLOSE(Math::sin(3.0f * Math::PI / 2.0f), -1.0f);
			EXPECT_CLOSE(Math::sin(2.0f * Math::PI), 0.0f);
		}

		TEST("Cos")
		{
			EXPECT_CLOSE(Math::cos(0.0f), 1.0f);
			EXPECT_CLOSE(Math::cos(Math::PI / 2.0f), 0.0f);
			EXPECT_CLOSE(Math::cos(Math::PI), -1.0f);
			EXPECT_CLOSE(Math::cos(3.0f * Math::PI / 2.0f), 0.0f);
			EXPECT_CLOSE(Math::cos(2.0f * Math::PI), 1.0f);
		}

		TEST("Tan")
		{
			EXPECT_CLOSE(Math::tan(0.0f), 0.0f);
			EXPECT_CLOSE(Math::tan(Math::PI / 4.0f), 1.0f);
			EXPECT_CLOSE(Math::tan(3.0f * Math::PI / 4.0f), -1.0f);
			EXPECT_CLOSE(Math::tan(Math::PI), 0.0f);
		}

		TEST("Acos")
		{
			EXPECT_CLOSE(Math::acos(1.0f), 0.0f);
			EXPECT_CLOSE(Math::acos(0.0f), Math::PI / 2.0f);
			EXPECT_CLOSE(Math::acos(-1.0f), Math::PI);
		}

		TEST("Asin")
		{
			EXPECT_CLOSE(Math::asin(0.0f), 0.0f);
			EXPECT_CLOSE(Math::asin(1.0f), Math::PI / 2.0f);
			EXPECT_CLOSE(Math::asin(-1.0f), -Math::PI / 2.0f);
		}

		TEST("Atan")
		{
			EXPECT_CLOSE(Math::atan(0.0f), 0.0f);
			EXPECT_CLOSE(Math::atan(1.0f), Math::PI / 4.0f);
			EXPECT_CLOSE(Math::atan(-1.0f), -Math::PI / 4.0f);
		}

		TEST("Atan2")
		{
			EXPECT_CLOSE(Math::atan2(0.0f, 1.0f), 0.0f);
			EXPECT_CLOSE(Math::atan2(1.0f, 0.0f), Math::PI / 2.0f);
			EXPECT_CLOSE(Math::atan2(0.0f, -1.0f), Math::PI);
			EXPECT_CLOSE(Math::atan2(-1.0f, 0.0f), -Math::PI / 2.0f);
		}

		TEST("Angle")
		{
			EXPECT_CLOSE(Math::angle(1.0f, 0.0f), 0.0f);
			EXPECT_CLOSE(Math::angle(0.0f, 1.0f), Math::PI / 2.0f);
			EXPECT_CLOSE(Math::angle(-1.0f, 0.0f), Math::PI);
			EXPECT_CLOSE(Math::angle(0.0f, -1.0f), -Math::PI / 2.0f);
		}

		TEST("Sqrt")
		{
			EXPECT_CLOSE(Math::sqrt(0.0f), 0.0f);
			EXPECT_CLOSE(Math::sqrt(1.0f), 1.0f);
			EXPECT_CLOSE(Math::sqrt(4.0f), 2.0f);
			EXPECT_CLOSE(Math::sqrt(9.0f), 3.0f);
			EXPECT_CLOSE(Math::sqrt(16.0f), 4.0f);
		}

		TEST("Pow")
		{
			EXPECT_CLOSE(Math::pow(0.0f, 0.0f), 1.0f);
			EXPECT_CLOSE(Math::pow(0.0f, 1.0f), 0.0f);
			EXPECT_CLOSE(Math::pow(1.0f, 0.0f), 1.0f);
			EXPECT_CLOSE(Math::pow(1.0f, 1.0f), 1.0f);
			EXPECT_CLOSE(Math::pow(2.0f, 0.0f), 1.0f);
			EXPECT_CLOSE(Math::pow(2.0f, 1.0f), 2.0f);
			EXPECT_CLOSE(Math::pow(2.0f, 2.0f), 4.0f);
			EXPECT_CLOSE(Math::pow(2.0f, 3.0f), 8.0f);
		}

		TEST("Magnitude")
		{
			EXPECT_CLOSE(Math::magnitude(0.0f, 0.0f), 0.0f);
			EXPECT_CLOSE(Math::magnitude(1.0f, 0.0f), 1.0f);
			EXPECT_CLOSE(Math::magnitude(0.0f, 1.0f), 1.0f);
			EXPECT_CLOSE(Math::magnitude(1.0f, 1.0f), Math::sqrt(2.0f));
			EXPECT_CLOSE(Math::magnitude(3.0f, 4.0f), 5.0f);
		}

		TEST("Sign")
		{
			EXPECT_CLOSE(Math::sign(0), 0);
			EXPECT_CLOSE(Math::sign(1), 1);
			EXPECT_CLOSE(Math::sign(-1), -1);
			EXPECT_CLOSE(Math::sign(0.0f), 0);
			EXPECT_CLOSE(Math::sign(1.0f), 1);
			EXPECT_CLOSE(Math::sign(-1.0f), -1);
		}

		TEST("Normalize")
		{
			EXPECT_EQUAL(Math::normalize(Float3(0.0f, 0.0f, 0.0f)), Float3(0.0f, 0.0f, 0.0f));
			EXPECT_EQUAL(Math::normalize(Float3(24.0f, 0.0f, 0.0f)), Float3(1.0f, 0.0f, 0.0f));
			EXPECT_EQUAL(Math::normalize(Float3(0.0f, 24.0f, 0.0f)), Float3(0.0f, 1.0f, 0.0f));
			EXPECT_EQUAL(Math::normalize(Float3(0.0f, 0.0f, 24.0f)), Float3(0.0f, 0.0f, 1.0f));
			EXPECT_EQUAL(Math::normalize(Float3(24.0f, 24.0f, 24.0f)), Float3(1.0f / Math::sqrt(3.0f)));
			EXPECT_EQUAL(Math::normalize(Float3(3.0f, 4.0f, 0.0f)), Float3(3.0f / 5.0f, 4.0f / 5.0f, 0.0f));
			EXPECT_EQUAL(Math::normalize(Float3(-24.0f, 0.0f, 0.0f)), Float3(-1.0f, 0.0f, 0.0f));
			EXPECT_EQUAL(Math::normalize(Float3(0.0f, -24.0f, 0.0f)), Float3(0.0f, -1.0f, 0.0f));
			EXPECT_EQUAL(Math::normalize(Float3(0.0f, 0.0f, -24.0f)), Float3(0.0f, 0.0f, -1.0f));
			EXPECT_EQUAL(Math::normalize(Float3(-24.0f, -24.0f, -24.0f)), Float3(-1.0f / Math::sqrt(3.0f)));
			EXPECT_EQUAL(Math::normalize(Float3(-3.0f, -4.0f, 0.0f)), Float3(-3.0f / 5.0f, -4.0f / 5.0f, 0.0f));
		}

		TEST("Magnitude")
		{
			EXPECT_EQUAL(Math::magnitude(Float3(0.0f, 0.0f, 0.0f)), 0.0f);
			EXPECT_EQUAL(Math::magnitude(Float3(1.0f, 0.0f, 0.0f)), 1.0f);
			EXPECT_EQUAL(Math::magnitude(Float3(0.0f, 1.0f, 0.0f)), 1.0f);
			EXPECT_EQUAL(Math::magnitude(Float3(0.0f, 0.0f, 1.0f)), 1.0f);
			EXPECT_EQUAL(Math::magnitude(Float3(1.0f, 1.0f, 1.0f)), Math::sqrt(3.0f));
		}

		TEST("Forward")
		{
			// forward
			Quaternion q = Math::from_euler(0.0f, 0.0f, 0.0f);
			Float3 forward = Math::forward(q);
			Float3 expected(0.0f, 0.0f, 1.0f);
			EXPECT_CLOSE_3(forward, expected);

			// right
			q = Math::from_euler(0.0f, Math::PI / 2.0f, 0.0f);
			forward = Math::forward(q);
			expected = Float3(1.0f, 0.0f, 0.0f);
			EXPECT_CLOSE_3(forward, expected);

			// backward
			q = Math::from_euler(0.0f, Math::PI, 0.0f);
			forward = Math::forward(q);
			expected = Float3(0.0f, 0.0f, -1.0f);
			EXPECT_CLOSE_3(forward, expected);

			// left
			q = Math::from_euler(0.0f, -Math::PI / 2.0f, 0.0f);
			forward = Math::forward(q);
			expected = Float3(-1.0f, 0.0f, 0.0f);
			EXPECT_CLOSE_3(forward, expected);

			// up
			q = Math::from_euler(Math::PI / -2.0f, 0.0f, 0.0f);
			forward = Math::forward(q);
			expected = Float3(0.0f, 1.0f, 0.0f);
			EXPECT_CLOSE_3(forward, expected);

			// down
			q = Math::from_euler(Math::PI / 2.0f, 0.0f, 0.0f);
			forward = Math::forward(q);
			expected = Float3(0.0f, -1.0f, 0.0f);
			EXPECT_CLOSE_3(forward, expected);
		}

		TEST("Backward")
		{
			// forward
			Quaternion q = Math::from_euler(0.0f, 0.0f, 0.0f);
			Float3 backward = Math::backward(q);
			Float3 expected(0.0f, 0.0f, -1.0f);
			EXPECT_CLOSE_3(backward, expected);

			// right
			q = Math::from_euler(0.0f, Math::PI / 2.0f, 0.0f);
			backward = Math::backward(q);
			expected = Float3(-1.0f, 0.0f, 0.0f);
			EXPECT_CLOSE_3(backward, expected);

			// backward
			q = Math::from_euler(0.0f, Math::PI, 0.0f);
			backward = Math::backward(q);
			expected = Float3(0.0f, 0.0f, 1.0f);
			EXPECT_CLOSE_3(backward, expected);

			// left
			q = Math::from_euler(0.0f, -Math::PI / 2.0f, 0.0f);
			backward = Math::backward(q);
			expected = Float3(1.0f, 0.0f, 0.0f);
			EXPECT_CLOSE_3(backward, expected);

			// up
			q = Math::from_euler(Math::PI / -2.0f, 0.0f, 0.0f);
			backward = Math::backward(q);
			expected = Float3(0.0f, -1.0f, 0.0f);
			EXPECT_CLOSE_3(backward, expected);

			// down
			q = Math::from_euler(Math::PI / 2.0f, 0.0f, 0.0f);
			backward = Math::backward(q);
			expected = Float3(0.0f, 1.0f, 0.0f);
			EXPECT_CLOSE_3(backward, expected);
		}

		TEST("Right")
		{
			// forward
			Quaternion q = Math::from_euler(0.0f, 0.0f, 0.0f);
			Float3 right = Math::right(q);
			Float3 expected(1.0f, 0.0f, 0.0f);
			EXPECT_CLOSE_3(right, expected);

			// right
			q = Math::from_euler(0.0f, Math::PI / 2.0f, 0.0f);
			right = Math::right(q);
			expected = Float3(0.0f, 0.0f, -1.0f);
			EXPECT_CLOSE_3(right, expected);

			// backward
			q = Math::from_euler(0.0f, Math::PI, 0.0f);
			right = Math::right(q);
			expected = Float3(-1.0f, 0.0f, 0.0f);
			EXPECT_CLOSE_3(right, expected);

			// left
			q = Math::from_euler(0.0f, -Math::PI / 2.0f, 0.0f);
			right = Math::right(q);
			expected = Float3(0.0f, 0.0f, 1.0f);
			EXPECT_CLOSE_3(right, expected);

			// up
			q = Math::from_euler(Math::PI / -2.0f, 0.0f, 0.0f);
			right = Math::right(q);
			expected = Float3(1.0f, 0.0f, 0.0f);
			EXPECT_CLOSE_3(right, expected);

			// down
			q = Math::from_euler(Math::PI / 2.0f, 0.0f, 0.0f);
			right = Math::right(q);
			expected = Float3(1.0f, 0.0f, 0.0f);
			EXPECT_CLOSE_3(right, expected);
		}

		TEST("Left")
		{
			// forward
			Quaternion q = Math::from_euler(0.0f, 0.0f, 0.0f);
			Float3 left = Math::left(q);
			Float3 expected(-1.0f, 0.0f, 0.0f);
			EXPECT_CLOSE_3(left, expected);

			// right
			q = Math::from_euler(0.0f, Math::PI / 2.0f, 0.0f);
			left = Math::left(q);
			expected = Float3(0.0f, 0.0f, 1.0f);
			EXPECT_CLOSE_3(left, expected);

			// backward
			q = Math::from_euler(0.0f, Math::PI, 0.0f);
			left = Math::left(q);
			expected = Float3(1.0f, 0.0f, 0.0f);
			EXPECT_CLOSE_3(left, expected);

			// left
			q = Math::from_euler(0.0f, -Math::PI / 2.0f, 0.0f);
			left = Math::left(q);
			expected = Float3(0.0f, 0.0f, -1.0f);
			EXPECT_CLOSE_3(left, expected);

			// up
			q = Math::from_euler(Math::PI / -2.0f, 0.0f, 0.0f);
			left = Math::left(q);
			expected = Float3(-1.0f, 0.0f, 0.0f);
			EXPECT_CLOSE_3(left, expected);

			// down
			q = Math::from_euler(Math::PI / 2.0f, 0.0f, 0.0f);
			left = Math::left(q);
			expected = Float3(-1.0f, 0.0f, 0.0f);
			EXPECT_CLOSE_3(left, expected);
		}

		TEST("Up")
		{
			// forward
			Quaternion q = Math::from_euler(0.0f, 0.0f, 0.0f);
			Float3 up = Math::up(q);
			Float3 expected(0.0f, 1.0f, 0.0f);
			EXPECT_CLOSE_3(up, expected);

			// right
			q = Math::from_euler(0.0f, Math::PI / 2.0f, 0.0f);
			up = Math::up(q);
			expected = Float3(0.0f, 1.0f, 0.0f);
			EXPECT_CLOSE_3(up, expected);

			// backward
			q = Math::from_euler(0.0f, Math::PI, 0.0f);
			up = Math::up(q);
			expected = Float3(0.0f, 1.0f, 0.0f);
			EXPECT_CLOSE_3(up, expected);

			// left
			q = Math::from_euler(0.0f, -Math::PI / 2.0f, 0.0f);
			up = Math::up(q);
			expected = Float3(0.0f, 1.0f, 0.0f);
			EXPECT_CLOSE_3(up, expected);

			// up
			q = Math::from_euler(Math::PI / -2.0f, 0.0f, 0.0f);
			up = Math::up(q);
			expected = Float3(0.0f, 0.0f, -1.0f);
			EXPECT_CLOSE_3(up, expected);

			// down
			q = Math::from_euler(Math::PI / 2.0f, 0.0f, 0.0f);
			up = Math::up(q);
			expected = Float3(0.0f, 0.0f, 1.0f);
			EXPECT_CLOSE_3(up, expected);
		}

		TEST("Down")
		{
			// forward
			Quaternion q = Math::from_euler(0.0f, 0.0f, 0.0f);
			Float3 down = Math::down(q);
			Float3 expected(0.0f, -1.0f, 0.0f);
			EXPECT_CLOSE_3(down, expected);

			// right
			q = Math::from_euler(0.0f, Math::PI / 2.0f, 0.0f);
			down = Math::down(q);
			expected = Float3(0.0f, -1.0f, 0.0f);
			EXPECT_CLOSE_3(down, expected);

			// backward
			q = Math::from_euler(0.0f, Math::PI, 0.0f);
			down = Math::down(q);
			expected = Float3(0.0f, -1.0f, 0.0f);
			EXPECT_CLOSE_3(down, expected);

			// left
			q = Math::from_euler(0.0f, -Math::PI / 2.0f, 0.0f);
			down = Math::down(q);
			expected = Float3(0.0f, -1.0f, 0.0f);
			EXPECT_CLOSE_3(down, expected);

			// up
			q = Math::from_euler(Math::PI / -2.0f, 0.0f, 0.0f);
			down = Math::down(q);
			expected = Float3(0.0f, 0.0f, 1.0f);
			EXPECT_CLOSE_3(down, expected);

			// down
			q = Math::from_euler(Math::PI / 2.0f, 0.0f, 0.0f);
			down = Math::down(q);
			expected = Float3(0.0f, 0.0f, -1.0f);
			EXPECT_CLOSE_3(down, expected);
		}

		TEST("Angle Axis")
		{
			// forward
			Quaternion q = Math::angle_axis(0.0f, Float3(0.0f, 1.0f, 0.0f));
			Float3 forward = Math::forward(q);
			Float3 expected(0.0f, 0.0f, 1.0f);
			EXPECT_CLOSE_3(forward, expected);

			// right
			q = Math::angle_axis(Math::PI / 2.0f, Float3(0.0f, 1.0f, 0.0f));
			forward = Math::forward(q);
			expected = Float3(1.0f, 0.0f, 0.0f);
			EXPECT_CLOSE_3(forward, expected);

			// backward
			q = Math::angle_axis(Math::PI, Float3(0.0f, 1.0f, 0.0f));
			forward = Math::forward(q);
			expected = Float3(0.0f, 0.0f, -1.0f);
			EXPECT_CLOSE_3(forward, expected);

			// left
			q = Math::angle_axis(-Math::PI / 2.0f, Float3(0.0f, 1.0f, 0.0f));
			forward = Math::forward(q);
			expected = Float3(-1.0f, 0.0f, 0.0f);
			EXPECT_CLOSE_3(forward, expected);

			// up
			q = Math::angle_axis(Math::PI / -2.0f, Float3(1.0f, 0.0f, 0.0f));
			forward = Math::forward(q);
			expected = Float3(0.0f, 1.0f, 0.0f);
			EXPECT_CLOSE_3(forward, expected);

			// down
			q = Math::angle_axis(Math::PI / 2.0f, Float3(1.0f, 0.0f, 0.0f));
			forward = Math::forward(q);
			expected = Float3(0.0f, -1.0f, 0.0f);
			EXPECT_CLOSE_3(forward, expected);
		}

		TEST("From/To Euler")
		{
			// forward
			Quaternion expected = Math::from_euler(0.0f, 0.0f, 0.0f);
			Float3 euler = Math::to_euler(expected);
			Quaternion actual = Math::from_euler(euler);
			EXPECT_CLOSE_4(actual, expected);

			// right
			expected = Math::from_euler(0.0f, Math::PI / 2.0f, 0.0f);
			euler = Math::to_euler(expected);
			actual = Math::from_euler(euler);
			EXPECT_CLOSE_4(actual, expected);

			// backward
			expected = Math::from_euler(0.0f, Math::PI, 0.0f);
			euler = Math::to_euler(expected);
			actual = Math::from_euler(euler);
			EXPECT_CLOSE_4(actual, expected);

			// left
			expected = Math::from_euler(0.0f, -Math::PI / 2.0f, 0.0f);
			euler = Math::to_euler(expected);
			actual = Math::from_euler(euler);
			EXPECT_CLOSE_4(actual, expected);

			// up
			expected = Math::from_euler(Math::PI / -2.0f, 0.0f, 0.0f);
			euler = Math::to_euler(expected);
			actual = Math::from_euler(euler);
			EXPECT_CLOSE_4(actual, expected);

			// down
			expected = Math::from_euler(Math::PI / 2.0f, 0.0f, 0.0f);
			euler = Math::to_euler(expected);
			actual = Math::from_euler(euler);
			EXPECT_CLOSE_4(actual, expected);
		}

		TEST("Identity")
		{
			Quaternion q = Math::identity<Quaternion>();
			Float3 actual = Math::forward(q);
			Float3 expected(0.0f, 0.0f, 1.0f);
			EXPECT_CLOSE_3(actual, expected);

			Matrix4 m = Math::identity<Matrix4>();
			actual = Math::extract_position(m);
			expected = Float3(0.0f, 0.0f, 0.0f);
			EXPECT_CLOSE_3(actual, expected);
			actual = Math::extract_scale(m);
			expected = Float3(1.0f, 1.0f, 1.0f);
			EXPECT_CLOSE_3(actual, expected);
			q = Math::extract_rotation(m);
			Quaternion expected_q = Math::identity<Quaternion>();
			EXPECT_CLOSE_4(q, expected_q);
		}

		TEST("To Matrix")
		{
			// identity
			Quaternion q = Math::identity<Quaternion>();
			Matrix4 m = Math::to_matrix(q);
			Quaternion actual_q = Math::extract_rotation(m);
			EXPECT_CLOSE_4(actual_q, q);

			m = Math::identity<Matrix4>();
			m = Math::translate(m, Float3(1.0f, 2.0f, 3.0f));
			m = Math::rotate(m, Math::PI / 2.0f, Float3(0.0f, 1.0f, 0.0f));
			m = Math::scale(m, Float3(2.0f, 3.0f, 4.0f));
			actual_q = Math::extract_rotation(m);
			q = Math::angle_axis(Math::PI / 2.0f, Float3(0.0f, 1.0f, 0.0f));
			EXPECT_CLOSE_4(actual_q, q);
			Float3 actual = Math::extract_position(m);
			Float3 expected(1.0f, 2.0f, 3.0f);
			EXPECT_CLOSE_3(actual, expected);
			actual = Math::extract_scale(m);
			expected = Float3(2.0f, 3.0f, 4.0f);
			EXPECT_CLOSE_3(actual, expected);
		}

		TEST("Translate")
		{
			Matrix4 m = Math::identity<Matrix4>();
			Float3 actual = Math::extract_position(m);
			Float3 expected(0.0f, 0.0f, 0.0f);
			EXPECT_CLOSE_3(actual, expected);
			m = Math::translate(m, Float3(1.0f, 2.0f, 3.0f));
			actual = Math::extract_position(m);
			expected = Float3(1.0f, 2.0f, 3.0f);
			EXPECT_CLOSE_3(actual, expected);
		}

		TEST("Scale")
		{
			Matrix4 m = Math::identity<Matrix4>();
			Float3 actual = Math::extract_scale(m);
			Float3 expected(1.0f, 1.0f, 1.0f);
			EXPECT_CLOSE_3(actual, expected);
			m = Math::scale(m, Float3(2.0f, 3.0f, 4.0f));
			actual = Math::extract_scale(m);
			expected = Float3(2.0f, 3.0f, 4.0f);
			EXPECT_CLOSE_3(actual, expected);
		}

		TEST("Scale")
		{
			Matrix4 m = Math::identity<Matrix4>();
			Float3 actual = Math::extract_scale(m);
			Float3 expected(1.0f, 1.0f, 1.0f);
			EXPECT_CLOSE_3(actual, expected);
			m = Math::scale(m, Float3(2.0f, 3.0f, 4.0f));
			actual = Math::extract_scale(m);
			expected = Float3(2.0f, 3.0f, 4.0f);
			EXPECT_CLOSE_3(actual, expected);
		}

		TEST("Rotate")
		{
			Matrix4 m = Math::identity<Matrix4>();
			Quaternion q = Math::identity<Quaternion>();
			Quaternion actual = Math::extract_rotation(m);
			Quaternion expected = Math::identity<Quaternion>();
			EXPECT_CLOSE_4(actual, expected);
			m = Math::rotate(m, Math::PI / 2.0f, Float3(0.0f, 1.0f, 0.0f));
			actual = Math::extract_rotation(m);
			q = Math::angle_axis(Math::PI / 2.0f, Float3(0.0f, 1.0f, 0.0f));
			EXPECT_CLOSE_4(actual, q);
		}

		TEST("Extract Position")
		{
			Matrix4 m = Math::identity<Matrix4>();
			Float3 actual = Math::extract_position(m);
			Float3 expected(0.0f, 0.0f, 0.0f);
			EXPECT_CLOSE_3(actual, expected);
			m = Math::translate(m, Float3(1.0f, 2.0f, 3.0f));
			actual = Math::extract_position(m);
			expected = Float3(1.0f, 2.0f, 3.0f);
			EXPECT_CLOSE_3(actual, expected);
		}

		TEST("Extract Scale")
		{
			Matrix4 m = Math::identity<Matrix4>();
			Float3 actual = Math::extract_scale(m);
			Float3 expected(1.0f, 1.0f, 1.0f);
			EXPECT_CLOSE_3(actual, expected);
			m = Math::scale(m, Float3(2.0f, 3.0f, 4.0f));
			actual = Math::extract_scale(m);
			expected = Float3(2.0f, 3.0f, 4.0f);
			EXPECT_CLOSE_3(actual, expected);
		}

		TEST("Extract Rotation")
		{
			Matrix4 m = Math::identity<Matrix4>();
			Quaternion q = Math::identity<Quaternion>();
			Quaternion actual = Math::extract_rotation(m);
			Quaternion expected = Math::identity<Quaternion>();
			EXPECT_CLOSE_4(actual, expected);
			m = Math::rotate(m, Math::PI / 2.0f, Float3(0.0f, 1.0f, 0.0f));
			actual = Math::extract_rotation(m);
			q = Math::angle_axis(Math::PI / 2.0f, Float3(0.0f, 1.0f, 0.0f));
			EXPECT_CLOSE_4(actual, q);
		}
	}
}
