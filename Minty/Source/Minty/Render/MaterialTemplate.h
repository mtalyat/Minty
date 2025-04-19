#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Variable.h"

namespace Minty
{
	class Shader;

	/// <summary>
	/// The arguments for a MaterialTemplate.
	/// </summary>
	struct MaterialTemplateBuilder
	{
		UUID id = INVALID_ID;

		Ref<Shader> shader = nullptr;

		Map<String, Map<String, Variable>> values;
	};

	/// <summary>
	/// Holds a collection of default values for a Material.
	/// </summary>
	class MaterialTemplate
		: public Asset
	{
#pragma region Variables

	private:
		Ref<Shader> m_shader;
		Map<String, Map<String, Variable>> m_values;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new MaterialTemplate.
		/// </summary>
		/// <param name="builder"></param>
		MaterialTemplate(MaterialTemplateBuilder const& builder);

		virtual ~MaterialTemplate() override
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the Shader that this MaterialTemplate uses.
		/// </summary>
		/// <returns>The Shader.</returns>
		Ref<Shader> const& get_shader() const { return m_shader; }

		/// <summary>
		/// Gets the values of this MaterialTemplate.
		/// </summary>
		/// <returns>The values.</returns>
		Map<String, Map<String, Variable>> const& get_values() const { return m_values; }

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>MaterialTemplate.</returns>
		constexpr AssetType get_asset_type() const override { return AssetType::MaterialTemplate; }

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new MaterialTemplate.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		static Owner<MaterialTemplate> create(MaterialTemplateBuilder const& builder = {});

#pragma endregion

	};
}