#pragma once  
#include "Minty/Entity/Entity.h"
#include "Minty/Library/EnTT.h"

namespace Minty  
{
    /// <summary>
	/// A view of Entities in the EntityManager with the given Components.
    /// </summary>
    /// <typeparam name="...Get">The Component types.</typeparam>
    template<typename... Get>
    class EntityView
    {
#pragma region Variables

	private:
		entt::view<entt::get_t<Get...>> m_view;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new EntityView using the given registry.
		/// </summary>
		/// <param name="registry">The EnTT registry.</param>
		EntityView(entt::registry& registry)
			: m_view(registry.view<Get...>())
		{
		}

		/// <summary>
		/// Creates a new EntityView using the given registry.
		/// </summary>
		/// <param name="registry">The EnTT registry.</param>
		EntityView(entt::registry const& registry)
			: m_view(registry.view<Get...>())
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the maximum number of Entities that could be in the view.
		/// </summary>
		/// <returns>The maximum count.</returns>
		Size get_size() const
		{
			return m_view.size_hint();
		}

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Iterates through all of the Entities in the view and calls the function for each one.
		/// </summary>
		/// <typeparam name="Func">The type of Function.</typeparam>
		/// <param name="func">The function.</param>
		template<typename Func>
		void each(Func&& func)
		{
			m_view.each(func);
		}

		/// <summary>
		/// Returns the iterator for the view.
		/// </summary>
		/// <returns>The iterator.</returns>
		auto each()
		{
			return m_view.each();
		}

		/// <summary>
		/// Returns the iterator for the view.
		/// </summary>
		/// <returns>The iterator.</returns>
		auto each() const
		{
			return m_view.each();
		}

		/// <summary>
		/// Specifies the type to use for ordering.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		template<typename T>
		void use()
		{
			m_view.use<T>();
		}

#pragma endregion
    };
}