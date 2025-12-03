#ifndef MINTY_RENDER_MATERIALTEMPLATE_H
#define MINTY_RENDER_MATERIALTEMPLATE_H

/**
 * @file MaterialTemplate.h
 * @brief Header file defining the MaterialTemplate class.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Cargo.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Debug/Assert.h"

namespace Minty
{
	class Shader;
	struct MaterialTemplateInfo;

	/**
	 * @brief Holds a collection of default values for a Material.
	 */
	class MaterialTemplate
		: public Asset
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new MaterialTemplate.
		 * @param info The arguments.
		 */
		MaterialTemplate(MaterialTemplateInfo const& info);

		virtual ~MaterialTemplate() override
		{
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the Shader that this MaterialTemplate uses.
		 * @return The Shader.
		 */
		inline Ref<Shader> const& get_shader() const { return m_shader; }

		/**
		 * @brief Gets the values of this MaterialTemplate.
		 * @return The values.
		 */
		inline Cargo const& get_inputs() const { return m_cargo; }

		/**
		 * @brief Checks if this MaterialTemplate has an input with the given name.
		 * @param name The name of the input.
		 * @return True if it contains the input.
		 */
		inline Bool has_input(String const& name) const { return m_cargo.contains(name); }

		/**
		 * @brief Gets the input value for this MaterialTemplate.
		 * @param name The name of the input value.
		 * @return A reference to the map of values for the object.
		 */
		inline Object const& get_input(String const& name) const
		{
			MINTY_ASSERT_F(m_cargo.contains(name), ErrorCode::Argument_KeyNotFound, name);
			return m_cargo.at(name);
		}

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return MaterialTemplate.
		 */
		inline AssetType get_asset_type() const override { return AssetType::MaterialTemplate; }

		/**
		 * @brief Creates a new MaterialTemplate.
		 * @param info The arguments.
		 */
		static Shared<MaterialTemplate> create(MaterialTemplateInfo const& info);

		/**
		 * @brief Creates a default MaterialTemplate.
		 * @return A Shared pointer to the created MaterialTemplate.
		 */
		static Shared<MaterialTemplate> create();

#pragma endregion

#pragma region Variables

	private:
		Ref<Shader> m_shader;
		Cargo m_cargo;

#pragma endregion
	};
}

#endif // MINTY_RENDER_MATERIALTEMPLATE_H