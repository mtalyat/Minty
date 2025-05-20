#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Cargo.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Variable.h"
#include "Minty/Data/Vector.h"

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

		Cargo values;
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
		Cargo m_cargo;

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
		Cargo const& get_inputs() const { return m_cargo; }

		/// <summary>
		/// Checks if this MaterialTemplate has an input with the given name.
		/// </summary>
		/// <param name="name">The name of the input.</param>
		/// <returns>True if it contains the input.</returns>
		Bool has_input(String const& name) const { return m_cargo.contains(name); }

		/// <summary>
		/// Gets the input value for this MaterialTemplate.
		/// </summary>
		/// <param name="name">The name of the input value.</param>
		/// <returns>A reference to the map of values for the object.</returns>
		Object const& get_input(String const& name) const
		{
			MINTY_ASSERT(m_cargo.contains(name), "MaterialTemplate does not contain input with name: " + name);
			return m_cargo.at(name);
		}

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