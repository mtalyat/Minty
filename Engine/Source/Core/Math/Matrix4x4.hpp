#pragma once

/**
 * @file Matrix4x4.hpp
 * @brief Header file defining the Matrix4x4 type for the Minty engine.
 * @author Mitchell Talyat
 */

#include "Quaternion.hpp"
#include "Library/GLM/GLM.hpp"

namespace Minty
{
    using Matrix4x4 = glm::mat4;
	using Matrix4 = Matrix4x4;

    namespace Math
    {
		/// <summary>
		/// Converts the given Quaternion to a 3D matrix.
		/// </summary>
		/// <param name="value">The Quaternion.</param>
		/// <returns>The matrix.</returns>
		Matrix4 to_matrix(Quaternion const& value);

        /// <summary>
		/// Translates the given matrix by the given value.
		/// </summary>
		/// <param name="matrix">The matrix to translate.</param>
		/// <param name="value">The amount to translate by.</param>
		/// <returns>A copy of the given Matrix, tranlated.</returns>
		Matrix4 translate(Matrix4 const& matrix, Float3 const value);

		/// <summary>
		/// Scales the given matrix by the given value.
		/// </summary>
		/// <param name="matrix">The matrix to scale.</param>
		/// <param name="value">The amount to scale by.</param>
		/// <returns>A copy of the given Matrix, scaled.</returns>
		Matrix4 scale(Matrix4 const& matrix, Float3 const value);

        /// <summary>
		/// Gets the position from this 3D matrix.
		/// </summary>
		/// <param name="value">The matrix.</param>
		/// <returns>The position.</returns>
		Float3 extract_position(Matrix4 const& value);

		/// <summary>
		/// Gets the scale from this 3D matrix.
		/// </summary>
		/// <param name="value">The matrix.</param>
		/// <returns>The scale.</returns>
		Float3 extract_scale(Matrix4 const& value);

        /// <summary>
		/// Rotates the given matrix by the given angle around the given axis.
		/// </summary>
		/// <param name="matrix">The Matrix to rotate.</param>
		/// <param name="angle">The angle to rotate by.</param>
		/// <param name="axis">The axis to rotate on.</param>
		/// <returns>A copy of the given Matrix, rotated.</returns>
		Matrix4 rotate(Matrix4 const& matrix, Float const angle, Float3 const& axis);

		/// <summary>
		/// Rotates the given matrix by the given Quaternion.
		/// </summary>
		/// <param name="matrix">The Matrix to rotate.</param>
		/// <param name="value">The Quaternion to rotate by.</param>
		/// <returns>A copy of the given Matrix, rotated.</returns>
		Matrix4 rotate(Matrix4 const& matrix, Quaternion const& value);

		/// <summary>
		/// Gets the rotation from this 3D matrix.
		/// </summary>
		/// <param name="value">The matrix.</param>
		/// <param name="scale">The scale of the matrix.</param>
		/// <returns>The rotation.</returns>
		Quaternion extract_rotation(Matrix4 const& value, Float3 const& scale);

		/// <summary>
		/// Gets the rotation from this 3D matrix.
		/// </summary>
		/// <param name="value">The matrix.</param>
		/// <returns>The rotation.</returns>
		Quaternion extract_rotation(Matrix4 const& value);

		Matrix4 perspective(Float const fov, Float const aspectRatio, Float const nearPlane, Float const farPlane);

		Matrix4 orthographic(Float const size, Float const aspectRatio, Float const nearPlane, Float const farPlane);

		Matrix4 look_at(Float3 const& eye, Float3 const& target, Float3 const& up = UP);
    }
}