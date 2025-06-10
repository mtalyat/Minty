#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Color.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Render/Perspective.h"
#include "Minty/Render/RenderTarget.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	/// <summary>
	/// The arguments for a Camera.
	/// </summary>
	struct CameraBuilder
	{
		/// <summary>
		/// The Asset ID.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The perspective.
		/// </summary>
		Perspective perspective = Perspective::Perspective;

		/// <summary>
		/// The Field of View.
		/// </summary>
		Float fov = 45.0f;

		/// <summary>
		/// The near plane. Nothing close than this distance are rendered.
		/// </summary>
		Float nearPlane = 0.1f;

		/// <summary>
		/// The far plane. Nothing further than this distance are rendered.
		/// </summary>
		Float farPlane = 100.0f;

		/// <summary>
		/// The clear color.
		/// </summary>
		Color color = Color::black();

		/// <summary>
		/// The aspect ratio.
		/// </summary>
		Float aspectRatio = 16.0f / 9.0f;

		/// <summary>
		/// The size/height of the Camera view. This is used for orthographic cameras.
		/// </summary>
		Float size = 5.0f;

		/// <summary>
		/// The layers to render.
		/// </summary>
		Layer layer = LAYER_ALL;

		/// <summary>
		/// The RenderTarget to render to.
		/// </summary>
		Ref<RenderTarget> renderTarget = nullptr;
	};

	/// <summary>
	/// Holds information used to render a specific view of the Scene.
	/// </summary>
	class Camera
		: public Asset
	{
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

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Camera.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		Camera(CameraBuilder const& builder);

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the perspective.
		/// </summary>
		/// <returns>The value.</returns>
		Perspective get_perspective() const { return m_perspective; }

		/// <summary>
		/// Sets the perspective.
		/// </summary>
		/// <param name="perspective">The new value.</param>
		void set_perspective(Perspective perspective) { m_perspective = perspective; }

		/// <summary>
		/// Gets the Field of View.
		/// </summary>
		/// <returns>The value.</returns>
		Float get_fov() const { return m_fov; }

		/// <summary>
		/// Sets the Field of View.
		/// </summary>
		/// <param name="fov">The new value.</param>
		void set_fov(Float fov) { m_fov = fov; }

		/// <summary>
		/// Gets the near plane.
		/// </summary>
		/// <returns>The value.</returns>
		Float get_near_plane() const { return m_nearPlane; }

		/// <summary>
		/// Sets the near plane.
		/// </summary>
		/// <param name="nearPlane">The new value.</param>
		void set_near_plane(Float nearPlane) { m_nearPlane = nearPlane; }

		/// <summary>
		/// Gets the far plane.
		/// </summary>
		/// <returns>The value.</returns>
		Float get_far_plane() const { return m_farPlane; }

		/// <summary>
		/// Sets the far plane.
		/// </summary>
		/// <param name="farPlane">The new value.</param>
		void set_far_plane(Float farPlane) { m_farPlane = farPlane; }

		/// <summary>
		/// Gets the clear color.
		/// </summary>
		/// <returns>The value.</returns>
		Color get_color() const { return m_color; }

		/// <summary>
		/// Sets the clear color.
		/// </summary>
		/// <param name="color">The new value.</param>
		void set_color(Color color) { m_color = color; }

		/// <summary>
		/// Gets the aspect ratio.
		/// </summary>
		/// <returns>The value.</returns>
		Float get_aspect_ratio() const { return m_aspectRatio; }

		/// <summary>
		/// Sets the aspect ratio.
		/// </summary>
		/// <param name="aspectRatio">The new value.</param>
		void set_aspect_ratio(Float aspectRatio) { m_aspectRatio = aspectRatio; }

		/// <summary>
		/// Gets the size.
		/// </summary>
		/// <returns>The value.</returns>
		Float get_size() const { return m_size; }

		/// <summary>
		/// Sets the size.
		/// </summary>
		/// <param name="size">The new value.</param>
		void set_size(Float size) { m_size = size; }

		/// <summary>
		/// Gets the Layer.
		/// </summary>
		/// <returns>The value.</returns>
		Layer get_layer() const { return m_layer; }

		/// <summary>
		/// Sets the Layer.
		/// </summary>
		/// <param name="layer">The new value.</param>
		void set_layer(Layer layer) { m_layer = layer; }

		/// <summary>
		/// Gets the RenderTarget.
		/// </summary>
		/// <returns>The value.</returns>
		Ref<RenderTarget> const& get_render_target() const { return m_renderTarget; }

		/// <summary>
		/// Sets the RenderTarget.
		/// </summary>
		/// <param name="renderTarget">The new value.</param>
		void set_render_target(Ref<RenderTarget> const& renderTarget) { m_renderTarget = renderTarget; }

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>Camera.</returns>
		constexpr AssetType get_asset_type() const override { return AssetType::Camera; }

#pragma endregion

#pragma region Methods

	public:
		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new Camera.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>A Camera Owner.</returns>
		static Owner<Camera> create(CameraBuilder const& builder = {});

#pragma endregion

	};
}