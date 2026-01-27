#ifndef MINTY_RENDER_CAMERA_H
#define MINTY_RENDER_CAMERA_H

/**
 * @file Camera.h
 * @brief Header file defining the Camera class and CameraInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Color.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Render/Perspective.h"
#include "Minty/Render/RenderTarget.h"
#include "Minty/Serialization/Serializer.h"

namespace Minty
{
	struct CameraInfo;

	/**
	 * @brief Holds information used to render a specific view of the Scene.
	 */
	class Camera
		: public Asset
	{
		friend struct Serializer<Camera>;

#pragma region Constructors

	public:
		/**
		 * @brief Creates a new Camera.
		 * @param info The arguments.
		 */
		Camera(CameraInfo const& info);

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the perspective.
		 * @return The value.
		 */
		inline Perspective get_perspective() const { return m_perspective; }

		/**
		 * @brief Sets the perspective.
		 * @param perspective The new value.
		 */
		inline void set_perspective(Perspective perspective) { m_perspective = perspective; }

		/**
		 * @brief Gets the Field of View.
		 * @return The value.
		 */
		inline Float get_fov() const { return m_fov; }

		/**
		 * @brief Sets the Field of View.
		 * @param fov The new value.
		 */
		inline void set_fov(Float fov) { m_fov = fov; }

		/**
		 * @brief Gets the near plane.
		 * @return The value.
		 */
		inline Float get_near_plane() const { return m_nearPlane; }

		/**
		 * @brief Sets the near plane.
		 * @param nearPlane The new value.
		 */
		inline void set_near_plane(Float nearPlane) { m_nearPlane = nearPlane; }

		/**
		 * @brief Gets the far plane.
		 * @return The value.
		 */
		inline Float get_far_plane() const { return m_farPlane; }

		/**
		 * @brief Sets the far plane.
		 * @param farPlane The new value.
		 */
		inline void set_far_plane(Float farPlane) { m_farPlane = farPlane; }

		/**
		 * @brief Gets the clear color.
		 * @return The value.
		 */
		inline Color get_color() const { return m_color; }

		/**
		 * @brief Sets the clear color.
		 * @param color The new value.
		 */
		inline void set_color(Color color) { m_color = color; }

		/**
		 * @brief Gets the aspect ratio.
		 * @return The value.
		 */
		inline Float get_aspect_ratio() const { return m_aspectRatio; }

		/**
		 * @brief Sets the aspect ratio.
		 * @param aspectRatio The new value.
		 */
		inline void set_aspect_ratio(Float aspectRatio) { m_aspectRatio = aspectRatio; }

		/**
		 * @brief Gets the size. The size is equal to the height of the Camera view. Used for orthographic cameras.
		 * @return The value.
		 */
		inline Float get_size() const { return m_size; }

		/**
		 * @brief Sets the size.
		 * @param size The new value.
		 */
		inline void set_size(Float size) { m_size = size; }

		/**
		 * @brief Gets the Layer.
		 * @return The value.
		 */
		inline Layer get_layer_mask() const { return m_layer; }

		/**
		 * @brief Sets the Layer.
		 * @param mask The new value.
		 */
		inline void set_layer_mask(Layer const mask) { m_layer = mask; }

		/**
		 * @brief Gets the RenderTarget.
		 * @return The value.
		 */
		inline Ref<RenderTarget> const& get_render_target() const { return m_renderTarget; }

		/**
		 * @brief Sets the RenderTarget.
		 * @param renderTarget The new value.
		 */
		inline void set_render_target(Ref<RenderTarget> const& renderTarget) { m_renderTarget = renderTarget; }

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return Camera.
		 */
		inline AssetType get_asset_type() const override { return AssetType::Camera; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Creates a new Camera.
		 * @param info The arguments.
		 * @return A Camera Owner.
		 */
		static Shared<Camera> create(CameraInfo const& info);

		/**
		 * @brief Creates a default Camera.
		 * @return A Camera Owner.
		 */
		static Shared<Camera> create();

#pragma endregion

#pragma region Variables

	private:
		Perspective m_perspective;
		Float m_fov;
		Float m_nearPlane;
		Float m_farPlane;
		Color m_color;
		Float m_aspectRatio;
		Float m_size;
		Layer m_layer;
		Ref<RenderTarget> m_renderTarget;

#pragma endregion
	};

	template<>
	struct Serializer<Camera>
	{
		static void serialize(Writer& writer, Camera const& value);
		static Bool deserialize(Reader& reader, Camera& value);
	};
}

#endif // MINTY_RENDER_CAMERA_H