#ifndef MINTY_RENDER_SHADERMODULE_H
#define MINTY_RENDER_SHADERMODULE_H

/**
 * @file ShaderModule.h
 * @brief Header file defining the ShaderModule class and ShaderModuleInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Data/Pointer.h"

namespace Minty
{
	struct ShaderModuleInfo;

	/**
	 * @brief Represents a Shader program.
	 */
	class ShaderModule
		: public Asset
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a ShaderModule with the given ID.
		 * @param info The arguments.
		 */
		ShaderModule(ShaderModuleInfo const& info);

		virtual ~ShaderModule() = default;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return ShaderModule.
		 */
		inline AssetType get_asset_type() const { return AssetType::ShaderModule; }

		/**
		 * @brief Gets the native ShaderModule object.
		 * @return A pointer to the native object.
		 */
		virtual Any get_native() const = 0;

		/**
		 * @brief Creates a new ShaderModule.
		 * @param info The arguments.
		 * @return A ShaderModule Owner.
		 */
		static Shared<ShaderModule> create(ShaderModuleInfo const& info);

#pragma endregion
	};
}

#endif // MINTY_RENDER_SHADERMODULE_H