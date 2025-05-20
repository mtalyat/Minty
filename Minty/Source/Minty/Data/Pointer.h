#pragma once
#include "Minty/Core/Types.h"

namespace Minty
{
	/// <summary>
	/// Holds smart pointer count data for weak and strong references.
	/// </summary>
	class Counter
	{
	public:
		Int strongCount = 0;
		Int weakCount = 0;
	};

	template<typename T>
	class Ref;

	/// <summary>
	/// A shared pointer.
	/// </summary>
	/// <param name="other"></param>
	template<typename T>
	class Owner
	{
		// so Ref types can access Owner
		friend class Ref<T>;

		// so other Ref types can access Ref
		template<typename U>
		friend class Owner;

#pragma region Variables

	private:
		/// <summary>
		/// A pointer to the data.
		/// </summary>
		T* mp_ptr;

		/// <summary>
		/// A pointer to the counter.
		/// </summary>
		Counter* mp_counter;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Owner.
		/// </summary>
		Owner() : mp_ptr(nullptr), mp_counter(nullptr) {}

		/// <summary>
		/// Creates a new Owner from an existing data instance.
		/// </summary>
		/// <param name="ptr"></param>
		explicit Owner(T* const ptr)
			: mp_ptr(ptr), mp_counter(new Counter())
		{
			mp_counter->strongCount++;
		}

		/// <summary>
		/// Creates a new Owner from an existing data instance and counter.
		/// </summary>
		/// <param name="ptr">The data pointer.</param>
		/// <param name="counter">The counter pointer.</param>
		explicit Owner(T* const ptr, Counter* const counter)
			: mp_ptr(ptr), mp_counter(counter)
		{
			if (mp_counter) mp_counter->strongCount++;
		}

		/// <summary>
		/// Creates a new Owner with a new instance of data.
		/// </summary>
		/// <typeparam name="...Args">The types for the constructor of the data class.</typeparam>
		/// <param name="...args">The arguments for the constructor of the data class.</param>
		template<typename... Args>
		explicit Owner(Args&&... args)
			: mp_ptr(new T(std::forward<Args>(args)...))
			, mp_counter(new Counter())
		{
			mp_counter->strongCount++;
		}

		/// <summary>
		/// Creates a null Owner.
		/// </summary>
		/// <param name=""></param>
		constexpr Owner(std::nullptr_t)
			: mp_ptr(nullptr)
			, mp_counter(nullptr)
		{
		}

		/// <summary>
		/// Implicitly casts from another Owner type.
		/// </summary>
		/// <typeparam name="U">The type to cast from.</typeparam>
		/// <param name="other">The Owner to cast.</param>
		template<typename U>
		Owner(Owner<U> const& other)
			: mp_ptr(static_cast<T*>(other.mp_ptr))
			, mp_counter(other.mp_counter)
		{
			if (mp_counter) mp_counter->strongCount++;
		}

		/// <summary>
		/// Copies the given Owner.
		/// </summary>
		/// <param name="other">The Owner to copy.</param>
		Owner(Owner const& other)
			: mp_ptr(other.mp_ptr)
			, mp_counter(other.mp_counter)
		{
			if (mp_counter) mp_counter->strongCount++;
		}

		/// <summary>
		/// Moves the given Owner.
		/// </summary>
		/// <param name="other">The Owner to move.</param>
		Owner(Owner&& other) noexcept
			: mp_ptr(other.mp_ptr)
			, mp_counter(other.mp_counter)
		{
			other.mp_ptr = nullptr;
			other.mp_counter = nullptr;
		}

		~Owner()
		{
			release();
		}

#pragma endregion

#pragma region Operators

	public:
		Owner& operator=(Owner const& other)
		{
			if (this != &other)
			{
				release();
				mp_ptr = other.mp_ptr;
				mp_counter = other.mp_counter;
				if (mp_counter) mp_counter->strongCount++;
			}
			return *this;
		}

		Owner& operator=(Owner&& other) noexcept {
			if (this != &other) {
				release();
				mp_ptr = other.mp_ptr;
				mp_counter = other.mp_counter;
				other.mp_ptr = nullptr;
				other.mp_counter = nullptr;
			}
			return *this;
		}

		template<typename U>
		Bool operator==(Owner<U> const& other) const { return get() == other.get(); }
		template<typename U>
		Bool operator==(U* const other) const { return get() == other; }
		template<typename U>
		Bool operator==(Ref<U> const& other) const { return get() == other.get(); }
		Bool operator==(std::nullptr_t const other) const { return get() == nullptr; }
		template<typename U>
		Bool operator!=(Owner<U> const& other) const { return !(*this == other); }
		template<typename U>
		Bool operator!=(U* const other) const { return !(*this == other); }
		template<typename U>
		Bool operator!=(Ref<U> const& other) const { return !(*this == other); }
		Bool operator!=(std::nullptr_t const other) const { return get() != nullptr; }
		template<typename U>
		Bool operator<(Owner<U> const& other) const { return get() < other.get(); }
		template<typename U>
		Bool operator<(U* const other) const { return get() < other; }
		template<typename U>
		Bool operator<(Ref<U> const& other) const { return get() < other.get(); }
		Bool operator!() const { return !mp_counter || !static_cast<Bool>(mp_counter->strongCount); }

		T& operator*() const { return *get(); }
		T* operator->() const { return get(); }

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the data pointer.
		/// </summary>
		/// <returns>The internal pointer to the data.</returns>
		T* get() const { return mp_ptr; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Sets the Owner to null.
		/// </summary>
		void release()
		{
			if (mp_ptr == nullptr) return;

			mp_counter->strongCount--;
			//MINTY_ASSERT_FORMAT(mp_counter->strongCount >= 0, "Owner counter invalid in release ({}).", mp_counter->strongCount);

			// no more owners, so delete the data
			if (!mp_counter->strongCount)
			{
				delete mp_ptr;

				// if also no more weak references, also delete the counter
				if (!mp_counter->weakCount)
				{
					delete mp_counter;
				}
			}

			mp_ptr = nullptr;
			mp_counter = nullptr;
		}

		Ref<T> create_ref() const
		{
			return Ref<T>(mp_ptr, mp_counter);
		}

		template<typename U>
		Ref<U> create_ref() const
		{
			return Ref<U>(static_cast<U*>(mp_ptr), mp_counter);
		}

		/// <summary>
		/// Casts this Owner<T> to a Owner<U>.
		/// </summary>
		/// <typeparam name="U">The type to cast to.</typeparam>
		/// <returns>A new Owner, casted as the given type.</returns>
		template<typename U>
		Owner<U> cast_to() const { return Owner<U>(static_cast<U*>(mp_ptr), mp_counter); }

#pragma endregion
	};

	/// <summary>
	/// A weak pointer. 
	/// </summary>
	template<typename T>
	class Ref
	{
		// so Owners can access Ref
		friend class Owner<T>;

		// so other Ref types can access Ref
		template<typename U>
		friend class Ref;

#pragma region Variables

	private:
		T* mp_ptr;
		Counter* mp_counter;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a null Ref.
		/// </summary>
		Ref()
			: mp_ptr(nullptr)
			, mp_counter(nullptr)
		{
		}

		/// <summary>
		/// Creates a new Ref from an existing data instance.
		/// </summary>
		/// <param name="ptr">The pointer to the data.</param>
		/// <param name="counter">The Counter to use.</param>
		explicit Ref(T* const ptr, Counter* const counter)
			: mp_ptr(ptr), mp_counter(counter)
		{
			if (mp_counter) mp_counter->weakCount++;
		}

		/// <summary>
		/// Creates a null Ref.
		/// </summary>
		/// <param name="">Null.</param>
		Ref(std::nullptr_t) : mp_ptr(nullptr), mp_counter(nullptr) {}

		/// <summary>
		/// Implicitly casts from another Ref type.
		/// </summary>
		/// <typeparam name="U">The other type.</typeparam>
		/// <param name="other">The other object.</param>
		template<typename U>
		Ref(Ref<U> const& other)
			: mp_ptr(static_cast<T*>(const_cast<U*>(other.mp_ptr)))
			, mp_counter(other.mp_counter)
		{
			if (mp_counter) mp_counter->weakCount++;
		}

		/// <summary>
		/// Implicitly creates a Ref from an Owner.
		/// </summary>
		/// <param name="owner">The Owner pointer.</param>
		Ref(Owner<T> const& owner)
			: mp_ptr(owner.mp_ptr), mp_counter(owner.mp_counter)
		{
			if (mp_counter) mp_counter->weakCount++;
		}

		/// <summary>
		/// Copies the given Ref.
		/// </summary>
		/// <param name="other">The other Ref.</param>
		Ref(Ref const& other)
			: mp_ptr(other.mp_ptr)
			, mp_counter(other.mp_counter)
		{
			if (mp_counter) mp_counter->weakCount++;
		}

		/// <summary>
		/// Moves the given Ref.
		/// </summary>
		/// <param name="other">The other Ref.</param>
		Ref(Ref&& other) noexcept
			: mp_ptr(other.mp_ptr)
			, mp_counter(other.mp_counter)
		{
			other.mp_ptr = nullptr;
			other.mp_counter = nullptr;
		}

		~Ref()
		{
			release();
		}

#pragma endregion

#pragma region Operators

	public:
		Ref& operator=(Owner<T> const& other)
		{
			if (mp_counter) mp_counter->weakCount--;
			//MINTY_ASSERT_FORMAT(!mp_counter || mp_counter->weakCount >= 0, "Ref counter invalid in copy ({}).", mp_counter->weakCount);
			mp_ptr = other.mp_ptr;
			mp_counter = other.mp_counter;
			if (mp_counter) mp_counter->weakCount++;

			return *this;
		}

		Ref& operator=(Ref const& other)
		{
			if (this != &other)
			{
				if (mp_counter) mp_counter->weakCount--;
				//MINTY_ASSERT_FORMAT(!mp_counter || mp_counter->weakCount >= 0, "Ref counter invalid in copy ({}).", mp_counter->weakCount);
				mp_ptr = other.mp_ptr;
				mp_counter = other.mp_counter;
				if (mp_counter) mp_counter->weakCount++;
			}
			return *this;
		}

		Ref& operator=(Ref&& other) noexcept {
			if (this != &other) {
				if (mp_counter) mp_counter->weakCount--;
				//MINTY_ASSERT_FORMAT(!mp_counter || mp_counter->weakCount >= 0, "Ref counter invalid in move ({}).", mp_counter->weakCount);
				mp_ptr = other.mp_ptr;
				mp_counter = other.mp_counter;
				other.mp_ptr = nullptr;
				other.mp_counter = nullptr;
			}
			return *this;
		}

		template<typename U>
		Bool operator==(Owner<U> const& other) const { return get() == other.get(); }
		template<typename U>
		Bool operator==(U* const other) const { return get() == other; }
		template<typename U>
		Bool operator==(Ref<U> const& other) const { return get() == other.get(); }
		Bool operator==(std::nullptr_t const other) const { return get() == nullptr; }
		template<typename U>
		Bool operator!=(Owner<U> const& other) const { return !(*this == other); }
		template<typename U>
		Bool operator!=(U* const other) const { return !(*this == other); }
		template<typename U>
		Bool operator!=(Ref<U> const& other) const { return !(*this == other); }
		Bool operator!=(std::nullptr_t const other) const { return get() != nullptr; }
		template<typename U>
		Bool operator<(Owner<U> const& other) const { return get() < other.get(); }
		template<typename U>
		Bool operator<(U* const other) const { return get() < other; }
		template<typename U>
		Bool operator<(Ref<U> const& other) const { return get() < other.get(); }
		Bool operator!() const { return !mp_counter || !mp_counter->strongCount; }

		T& operator*() const { return *get(); }
		T* operator->() const { return get(); }

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the data pointer.
		/// </summary>
		/// <returns>The internal pointer to the data, or null if it does not exist.</returns>
		T* get() const
		{
			if (mp_counter && mp_counter->strongCount > 0)
			{
				return mp_ptr;
			}

			return nullptr;
		}

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Sets the Ref to null.
		/// </summary>
		void release()
		{
			if (mp_counter == nullptr) return;

			mp_counter->weakCount--;
			//MINTY_ASSERT_FORMAT(mp_counter->weakCount >= 0, "Ref counter invalid in release ({}).", mp_counter->weakCount);

			// if no more strong and no more weak, delete counter
			if (!mp_counter->strongCount && !mp_counter->weakCount)
			{
				delete mp_counter;
			}

			mp_ptr = nullptr;
			mp_counter = nullptr;
		}

		/// <summary>
		/// Casts this Ref<T> to a Ref<U>.
		/// </summary>
		/// <typeparam name="U">The type to cast to.</typeparam>
		/// <returns>A new Ref, casted as the given type.</returns>
		template<typename U>
		Ref<U> cast_to() const { return Ref<U>(static_cast<U*>(mp_ptr), mp_counter); }

#pragma endregion
	};

	/// <summary>
	/// A Source is an Owner, but this object is where the pointer originates from.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class Source
	{
#pragma region Variables

	private:
		Counter* mp_counter;

#pragma endregion

#pragma region Constructors

	public:
		Source()
			: mp_counter(new Counter({ 1, 0 }))
		{
		}

		virtual ~Source()
		{
			release();
		}

#pragma endregion

#pragma region Methods

	public:
		void release()
		{
			if (mp_counter == nullptr) return;

			mp_counter->strongCount--;
			//MINTY_ASSERT_FORMAT(mp_counter->strongCount >= 0, "Ref counter invalid in release ({}).", mp_counter->strongCount);

			// if no more strong and no more weak, delete counter
			if (!mp_counter->strongCount && !mp_counter->weakCount)
			{
				delete mp_counter;
			}

			mp_counter = nullptr;
		}

		Ref<T> create_ref()
		{
			return Ref<T>(static_cast<T*>(this), mp_counter);
		}

#pragma endregion		
	};
}

namespace std {
	template <typename T>
	struct hash<Minty::Owner<T>> {
		Minty::Size operator()(Minty::Owner<T> const& sp) const noexcept {
			return std::hash<T*>()(sp.get());
		}
	};

	template <typename T>
	struct hash<Minty::Ref<T>> {
		Minty::Size operator()(Minty::Ref<T> const& sp) const noexcept {
			return std::hash<T*>()(sp.get());
		}
	};
}