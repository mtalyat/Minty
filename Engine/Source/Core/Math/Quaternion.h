#pragma once

/**
 * @file Quaternion.h
 * @brief Header file defining the Quaternion type for the Minty engine.
 * @author Mitchell Talyat
 */

#include "Library/GLM/GLM.h"
#include "Core/Type/Float3.h"
#include "Core/Math/Math.h"

namespace Minty
{
    using Quaternion = glm::quat;

    namespace Math
    {
        /**
		 * @brief Gets the spherical linear interpolation between two quaternions.
		 * @param left The starting quaternion.
		 * @param right The ending quaternion.
		 * @param t The interpolation factor. 0.0 is left, 1.0 is right.
		 * @return The slerped quaternion.
		 */
		inline Quaternion slerp(Quaternion const& left, Quaternion const& right, Float const t)
		{
			return glm::slerp(left, right, t);
		}

		/**
		 * @brief Gets the inverse of the given quaternion.
		 * @param value The quaternion to invert.
		 * @return The inverse of the given quaternion.
		 */
		Quaternion inverse(Quaternion const& value);

        /// <summary>
		/// Gets the forward vector of the given Quaternion.
		/// </summary>
		/// <param name="value">The rotation.</param>
		/// <returns>The result.</returns>
		Float3 forward(Quaternion const& value);

		/// <summary>
		/// Gets the backward vector of the given Quaternion.
		/// </summary>
		/// <param name="value">The rotation.</param>
		/// <returns>The result.</returns>
		Float3 backward(Quaternion const& value);

		/// <summary>
		/// Gets the up vector of the given Quaternion.
		/// </summary>
		/// <param name="value">The rotation.</param>
		/// <returns>The result.</returns>
		Float3 up(Quaternion const& value);

		/// <summary>
		/// Gets the down vector of the given Quaternion.
		/// </summary>
		/// <param name="value">The rotation.</param>
		/// <returns>The result.</returns>
		Float3 down(Quaternion const& value);

		/// <summary>
		/// Gets the right vector of the given Quaternion.
		/// </summary>
		/// <param name="value">The rotation.</param>
		/// <returns>The result.</returns>
		Float3 right(Quaternion const& value);

		/// <summary>
		/// Gets the left vector of the given Quaternion.
		/// </summary>
		/// <param name="value">The rotation.</param>
		/// <returns>The result.</returns>
		Float3 left(Quaternion const& value);

		/// <summary>
		/// Creates a Quaternion from the given angle and axis.
		/// </summary>
		/// <param name="angle">The angle to use.</param>
		/// <param name="axis">The axis the given angle is on.</param>
		/// <returns>The rotation, as a Quaternion.</returns>
		Quaternion angle_axis(Float const angle, Float3 const& axis);

		/// <summary>
		/// Creates a Quaternion that looks at the target position from the given eye position, using the given up vector.
		/// </summary>
		/// <param name="eye">The location of the object that is looking.</param>
		/// <param name="target">The location to look at.</param>
		/// <param name="up">The up direction.</param>
		/// <returns>A Quaternion reflecting the given values.</returns>
		Quaternion look_at(Float3 const& eye, Float3 const& target, Float3 const& up = UP);

		/// <summary>
		/// Converts the given Quaternion to Euler angles.
		/// </summary>
		/// <param name="value">The rotation, as a Quaternion.</param>
		/// <returns>The rotation, as Euler angles.</returns>
		Float3 to_euler(Quaternion const& value);

		/// <summary>
		/// Converts the given Euler angles to a Quaternion.
		/// </summary>
		/// <param name="value">The rotation, as Euler angles.</param>
		/// <returns>The rotation, as a Quaternion.</returns>
		Quaternion to_cartesian(Float3 const& value);

		/// <summary>
		/// Converts the given Euler angles to a Quaternion.
		/// </summary>
		/// <param name="x">The rotation on the X axis.</param>
		/// <param name="y">The rotation on the Y axis.</param>
		/// <param name="z">The rotation on the Z axis.</param>
		/// <returns>The rotation, as a Quaternion.</returns>
		inline Quaternion to_cartesian(Float const x, Float const y, Float const z)
		{
			return to_cartesian(Float3(x, y, z));
		}
    }
}