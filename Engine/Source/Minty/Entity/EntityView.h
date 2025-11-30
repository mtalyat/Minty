#ifndef MINTY_ENTITY_ENTITYVIEW_H
#define MINTY_ENTITY_ENTITYVIEW_H

/**
 * @file EntityView.h
 * @brief Header file defining the EntityView class.
 * @author Mitchell Talyat
 */

#include "Minty/Entity/Entity.h"
#include "Minty/Library/EnTT.h"

namespace Minty
{
    /**
     * @brief A view of Entities in the EntityManager with the given Components.
     * @tparam View The type of view.
     */
    template<typename View>
    class EntityView
    {
#pragma region Variables

	private:
		View m_view;

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates a new EntityView using the given view.
		 * @param view The view.
		 */
		EntityView(View const& view)
			: m_view(view)
		{
		}

		~EntityView()
		{
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the maximum number of Entities in the view.
		 * @return The max count.
		 */
		Size get_size() const
		{
			return m_view.size();
		}

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Allows iterating over the Entities and Components in the view.
		 * @return The iterator.
		 */
		auto each()
		{
			return m_view.each();
		}

		/**
		 * @brief Allows iterating over the Entities and Components in the view.
		 * @return The iterator.
		 */
		auto each() const
		{
			return m_view.each();
		}

		/**
		 * @brief Specifies the Component type to use when ordering the Entities.
		 * @tparam T The Component type.
		 */
		template<typename T>
		void use()
		{
			m_view.use<T>();
		}

#pragma endregion
    };
}

#endif // MINTY_ENTITY_ENTITYVIEW_H