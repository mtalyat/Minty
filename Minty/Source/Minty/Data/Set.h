#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Core/Types.h"

namespace Minty
{
	template<typename T>
	class Set
	{
#pragma region Classes

	private:
		struct Node
		{
			T data;
			Node* next;
			Node(T const& data)
				: data(data)
				, next(nullptr)
			{
			}
			Node(T&& data)
				: data(std::move(data))
				, next(nullptr)
			{
			}
		};

#pragma endregion

#pragma region Iterators



#pragma endregion


#pragma region Variables



#pragma endregion

	};
}