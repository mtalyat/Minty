#pragma once
#include "Minty/Entity/Entity.h"
#include "Minty/Library/EnTT.h"

namespace Minty
{
    /// <summary>
    /// A view of Entities in the EntityManager with the given Components.
    /// </summary>
    /// <typeparam name="View">The type of view.</typeparam>
    template<typename View>
    class EntityView
    {
#pragma region Variables

	private:
		View m_view;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new EntityView using the given view.
		/// </summary>
		/// <param name="view">The view.</param>
		EntityView(View const& view)
			: m_view(view)
		{
		}

		~EntityView()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the maximum number of Entities in the view.
		/// </summary>
		/// <returns>The max count.</returns>
		Size get_size() const
		{
			return m_view.size_hint();
		}

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Allows iterating over the Entities and Components in the view.
		/// </summary>
		/// <returns>The iterator.</returns>
		auto each()
		{
			return m_view.each();
		}

		/// <summary>
		/// Allows iterating over the Entities and Components in the view.
		/// </summary>
		/// <returns>The iterator.</returns>
		auto each() const
		{
			return m_view.each();
		}

		/// <summary>
		/// Specifies the Component type to use when ordering the Entities.
		/// </summary>
		/// <typeparam name="T">The Component type.</typeparam>
		template<typename T>
		void use()
		{
			m_view.use<T>();
		}

#pragma endregion
    };
}