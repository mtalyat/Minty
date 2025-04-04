#pragma once
#include "Minty/Data/Pointer.h"
#include "Minty/Render/BufferUsage.h"

namespace Minty
{
	/// <summary>
	/// The arguments for a Buffer.
	/// </summary>
	struct BufferBuilder
	{
		/// <summary>
		/// The usage of the Buffer.
		/// </summary>
		BufferUsage usage = BufferUsage::Undefined;

		/// <summary>
		/// The size of the Buffer in bytes.
		/// </summary>
		Size size = 0;

		/// <summary>
		/// The data of the Buffer.
		/// </summary>
		void const* data = nullptr;

		/// <summary>
		/// When true, optimize for frequent per-frame usage. When false, optimize for infrequent usage.
		/// </summary>
		Bool frequent = false;
	};

	/// <summary>
	/// Holds an array of data on the GPU.
	/// </summary>
	class Buffer
	{
#pragma region Variables

	private:
		BufferUsage m_usage;
		Bool m_frequent;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Buffer.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		Buffer(BufferBuilder const& builder)
			: m_usage(builder.usage)
			, m_frequent(builder.frequent)
		{
		}

		virtual ~Buffer()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the Byte data of this Buffer. Only works if this Buffer is optimized for frequent usage.
		/// </summary>
		/// <returns>A pointer to the data.</returns>
		virtual void* get_data() const = 0;

		/// <summary>
		/// Sets the Byte data of this Buffer.
		/// </summary>
		/// <param name="data">The new Byte data.</param>
		virtual void set_data(void const* const data) = 0;

		/// <summary>
		/// Gets the size of this Buffer in bytes.
		/// </summary>
		/// <returns>The size.</returns>
		virtual Size get_size() const = 0;

		/// <summary>
		/// Gets the BufferUsage.
		/// </summary>
		/// <returns>The BufferUsage.</returns>
		inline BufferUsage get_usage() const { return m_usage; }

		/// <summary>
		/// Checks if this Buffer is optimized for frequent usage.
		/// </summary>
		/// <returns>True, if frequent.</returns>
		inline Bool is_frequent() const { return m_frequent; }

		/// <summary>
		/// Gets the native Buffer object.
		/// </summary>
		/// <returns>A pointer to the native object.</returns>
		virtual void* get_native() const = 0;

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new Buffer.
		/// </summary>
		/// <param name="builder">The builder to use.</param>
		/// <returns>A Buffer Owner.</returns>
		static Owner<Buffer> create(BufferBuilder const& builder = {});

#pragma endregion
	};
}