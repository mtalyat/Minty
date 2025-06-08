#pragma once
#include "Minty/Data/Container.h"
#include "Minty/Render/Buffer.h"

namespace Minty
{
	/// <summary>
	/// A container that uses a Buffer.
	/// </summary>
	class BufferContainer
		: public Container
	{
#pragma region Variables

	private:
		Owner<Buffer> m_buffer;
		BufferUsage m_usage;
		Size m_capacity;
		Size m_size;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty BufferContainer.
		/// </summary>
		BufferContainer()
			: Container()
			, m_buffer(nullptr)
			, m_usage(BufferUsage::Undefined)
			, m_capacity(0)
			, m_size(0)
		{
		}

		BufferContainer(BufferUsage const usage)
			: Container()
			, m_buffer(nullptr)
			, m_usage(usage)
			, m_capacity(0)
			, m_size(0)
		{
		}

		BufferContainer(Size const capacity, BufferUsage const usage)
			: Container()
			, m_buffer(nullptr)
			, m_usage(usage)
			, m_capacity(0)
			, m_size(0)
		{
			reserve(capacity);
		}

		BufferContainer(BufferContainer const& other)
			: Container()
			, m_buffer(other.m_buffer)
			, m_usage(other.m_usage)
			, m_capacity(other.m_capacity)
			, m_size(other.m_size)
		{
		}

		BufferContainer(BufferContainer&& other) noexcept
			: Container()
			, m_buffer(std::move(other.m_buffer))
			, m_usage(std::move(other.m_usage))
			, m_capacity(std::move(other.m_capacity))
			, m_size(std::move(other.m_size))
		{
			other.m_buffer = nullptr;
			other.m_capacity = 0;
			other.m_size = 0;
		}

#pragma endregion

#pragma region Operators

	public:
		BufferContainer& operator=(BufferContainer const& other)
		{
			if (this != &other)
			{
				m_buffer = other.m_buffer;
				m_usage = other.m_usage;
				m_capacity = other.m_capacity;
				m_size = other.m_size;
			}

			return *this;
		}

		BufferContainer& operator=(BufferContainer&& other) noexcept
		{
			if (this != &other)
			{
				m_buffer = std::move(other.m_buffer);
				m_usage = std::move(other.m_usage);
				m_capacity = std::move(other.m_capacity);
				m_size = std::move(other.m_size);
			}
			return *this;
		}

#pragma endregion

#pragma region Get Set

	public:
		void* get_data() const override { return m_buffer->get_data(); }

		Size get_size() const override { return m_size; }

		Size get_capacity() const override { return m_capacity; }

		Ref<Buffer> get_buffer() const { return m_buffer.create_ref(); }

#pragma endregion

#pragma region Methods

	public:
		void set_at(void const* const data, Size const size, Size const index) override;

		void const* get_at(Size const index) const override;

		Bool append(void const* const data, Size const size) override;

		void clear() override;

		Bool reserve(Size const newCapacity) override;

		Bool resize(Size const newSize) override;

#pragma endregion
	};
}