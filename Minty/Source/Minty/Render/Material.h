#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Variable.h"

namespace Minty
{
	class MaterialTemplate;

	/// <summary>
	/// Arguments for a Material.
	/// </summary>
	struct MaterialBuilder
	{
		/// <summary>
		/// The ID.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The MaterialTemplate for this Material.
		/// </summary>
		Ref<MaterialTemplate> materialTemplate = nullptr;

		/// <summary>
		/// The values of this Material. These override the default values in the MaterialTemplate.
		/// </summary>
		Map<String, Map<String, Variable>> values;
	};

	class Material
		: public Asset
	{
#pragma region Variables

	private:
		Ref<MaterialTemplate> m_materialTemplate;
		Map<String, Map<String, Variable>> m_values;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Material.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		Material(MaterialBuilder const& builder);

		virtual ~Material() override;

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the MaterialTemplate that this Material uses.
		/// </summary>
		/// <returns>The MaterialTemplate.</returns>
		Ref<MaterialTemplate> const& get_material_template() const { return m_materialTemplate; }

		/// <summary>
		/// Gets the values of this Material.
		/// </summary>
		/// <returns>The values.</returns>
		Map<String, Map<String, Variable>> const& get_values() const { return m_values; }

		/// <summary>
		/// Gets an input value for this Material.
		/// </summary>
		/// <param name="name">The name of the input.</param>
		/// <param name="data">A pointer to the data to set.</param>
		/// <param name="size">The size of the data in bytes.</param>
		virtual void set_input(String const& name, void const* const data, Size const size) = 0;

		/// <summary>
		/// Tries to set the input data for this Material, if it exists.
		/// </summary>
		/// <param name="name">The name of the input.</param>
		/// <param name="data">A pointer to the data to set.</param>
		/// <param name="size">The size of the data in bytes.</param>
		/// <returns>True, on success.</returns>
		Bool try_set_input(String const& name, void const* const data, Size const size);

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>Material.</returns>
		constexpr AssetType get_asset_type() const override { return AssetType::Material; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Called when this Material is binded for rendering.
		/// </summary>
		virtual void on_bind() = 0;

#pragma endregion

#pragma region Statics

	public:
		static Owner<Material> create(MaterialBuilder const& builder = {});

#pragma endregion

	};
}