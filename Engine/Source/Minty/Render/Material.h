#ifndef MINTY_RENDER_MATERIAL_H
#define MINTY_RENDER_MATERIAL_H

/**
 * @file Material.h
 * @brief Header file defining the Material class and MaterialInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Data/Cargo.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Variable.h"

namespace Minty
{
	class MaterialTemplate;
	struct MaterialInfo;

	class Material
		: public Asset
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new Material.
		 * @param info The arguments.
		 */
		Material(MaterialInfo const& info);

		virtual ~Material() override;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the MaterialTemplate that this Material uses.
		 * @return The MaterialTemplate.
		 */
		Ref<MaterialTemplate> const& get_material_template() const { return m_materialTemplate; }

		/**
		 * @brief Gets the values of this Material.
		 * @return The values.
		 */
		Cargo const& get_inputs() const { return m_cargo; }

		/**
		 * @brief Checks if this Material has an input with the given name.
		 * @param name The name of the input.
		 * @return True if the input exists.
		 */
		Bool has_input(String const& name) const;

		/**
		 * @brief Gets the input value for this Material with the given name.
		 * @param name The name of the input.
		 * @return A reference to the Map containing the input object data.
		 */
		Object const& get_input(String const& name) const;

		/**
		 * @brief Gets an input value for this Material.
		 * @param name The name of the input.
		 * @param data A pointer to the data to set.
		 * @param size The size of the data in bytes.
		 */
		virtual void set_input(String const& name, void const* const data, Size const size) = 0;

		/**
		 * @brief Tries to set the input data for this Material, if it exists.
		 * @param name The name of the input.
		 * @param data A pointer to the data to set.
		 * @param size The size of the data in bytes.
		 * @return True, on success.
		 */
		Bool try_set_input(String const& name, void const* const data, Size const size);

		/**
		 * @brief Gets the input data for this Material with the given name.
		 * @param name The name of the input data.
		 * @param data A pointer to the location to copy the data.
		 * @param size The size of the data pointer.
		 * @return True on a successful copy, otherwise false.
		 */
		Bool get_input(String const& name, Any const data, Size const size) const;

		/**
		 * @brief Sets the object's stencil value.
		 * @param stencil The stencil value.
		 */
		void set_stencil(UInt const stencil) { m_stencil = stencil; }

		/**
		 * @brief Gets the object's stencil value.
		 * @return The stencil value.
		 */
		UInt get_stencil() const { return m_stencil; }

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return Material.
		 */
		inline AssetType get_asset_type() const override { return AssetType::Material; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Called when this Material is binded for rendering.
		 */
		virtual void on_bind() = 0;

#pragma endregion

#pragma region Statics

	public:
		static Shared<Material> create(MaterialInfo const& info);

#pragma endregion

#pragma region Variables

	private:
		Ref<MaterialTemplate> m_materialTemplate;
		Cargo m_cargo;
		UInt m_stencil;

#pragma endregion
	};
}

#endif // MINTY_RENDER_MATERIAL_H