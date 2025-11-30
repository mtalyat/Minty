#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Data/Pointer.h"

namespace Minty
{
	/// <summary>
	/// The arguments for a ShaderModule.
	/// </summary>
	struct ShaderModuleInfo
	{
		/// <summary>
		/// The ID.
		/// </summary>
		UUID id = UUID();

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
		/// <param name="info"></param>
		ShaderModule(ShaderModuleInfo const& info)
			: Asset(info.id)
		{
			MINTY_ASSERT(info.data != nullptr, ErrorCode::Argument_ExpectedNonNull);
			MINTY_ASSERT(info.size > 0, ErrorCode::Argument_ExpectedAboveZero);
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
		inline AssetType get_asset_type() const { return AssetType::ShaderModule; }

		/// <summary>
		/// Gets the native ShaderModule object.
		/// </summary>
		/// <returns>A pointer to the native object.</returns>
		virtual Any get_native() const = 0;

#pragma endregion

#pragma region Statics

	public:
		static Shared<ShaderModule> create(ShaderModuleInfo const& info = {});

#pragma endregion
	};
}