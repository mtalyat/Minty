#pragma once

namespace Minty
{
	/// <summary>
	/// Defines how the cursor should be displayed.
	/// </summary>
	enum class CursorMode
	{
		/// <summary>
		/// Invalid.
		/// </summary>
		Undefined,

		/// <summary>
		/// Displays normally.
		/// </summary>
		Normal,

		/// <summary>
		/// Does not display.
		/// </summary>
		Hidden,

		/// <summary>
		/// Displays in a disabled state.
		/// </summary>
		Disabled,
	};
}