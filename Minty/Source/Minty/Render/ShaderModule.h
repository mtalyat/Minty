#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Data/Pointer.h"

namespace Minty
{
	/// <summary>
	/// The arguments for a ShaderModule.
	/// </summary>
	struct ShaderModuleBuilder
	{
		/// <summary>
		/// The ID.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The data of the ShaderModule.
		/// </summary>
		void const* data = nullptr;

		/// <summary>
		/// The size of the ShaderModule in bytes.
		/// </summary>
		Size size = 0;
	};

	/// <summary>
	/// Represents a Shader program.
	/// </summary>
	class ShaderModule
		: public Asset
	{
#pragma region Constructors

	public:
		/// <summary>
		/// Creates a ShaderModule with the given ID.
		/// </summary>
		/// <param name="builder"></param>
		ShaderModule(ShaderModuleBuilder const& builder)
			: Asset(builder.id)
		{
			MINTY_ASSERT(builder.data != nullptr, "ShaderModuleBuilder data must not be null.");
			MINTY_ASSERT(builder.size > 0, "ShaderModuleBuilder size must be greater than 0.");
		}

		virtual ~ShaderModule()
		{
		}

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>ShaderModule.</returns>
		constexpr AssetType get_asset_type() const { return AssetType::ShaderModule; }

		/// <summary>
		/// Gets the native ShaderModule object.
		/// </summary>
		/// <returns>A pointer to the native object.</returns>
		virtual void* get_native() const = 0;

#pragma endregion

#pragma region Statics

	public:
		static Owner<ShaderModule> create(ShaderModuleBuilder const& builder = {});

#pragma endregion
	};
}