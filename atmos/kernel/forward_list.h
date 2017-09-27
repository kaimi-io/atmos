#pragma once

#include "defines.h"

namespace atmos
{
namespace container
{

///Base class for strongly typed element of singly-linked list.
///Can be contained in single list only.
struct ATMOS_PACKED forward_list_element
{
	///Next list item or nullptr.
	forward_list_element* next = nullptr;
};

///Base class for strongly typed singly-linked list.
struct ATMOS_PACKED forward_list_base
{
	///Pointer to first list element or nullptr if list is empty.
	forward_list_element* first_element = nullptr;
	
	///<summary>Push new element to front of list.</summary>
	///<param name="elem">Element not attached to any list. Can not be nullptr.</param>
	void push_front(forward_list_element* elem) ATMOS_NONNULL(1);

	///<summary>Pop front element of list.</summary>
	///<returns>Front list element or nullptr if list is empty.</returns>
	forward_list_element* pop_front();
	
	///<summary>Remove element from list.</summary>
	///<remarks>Has O(n) time complexity.</remarks>
	///<param name="elem">Any element of any list. Can not be nullptr.</param>
	///<returns>True if element was removed. False if element was not found in list.</returns>
	bool remove(forward_list_element* elem) ATMOS_NONNULL(1);
	
	///<summary>Insert element "elem" before element "current".</summary>
	///<param name="prev">Element which is before "current" element. Can be nullptr.</param>
	///<param name="current">Element after which "elem" element must be inserted. Can not be nullptr.</param>
	///<param name="elem">Element not attached to any list. Can not be nullptr.</param>
	void insert_before(forward_list_element* prev, forward_list_element* current, forward_list_element* elem) ATMOS_NONNULL(2, 3);
	
	///<summary>Returns true if list is empty.</summary>
	///<returns>True if list is empty, false otherwise.</returns>
	bool empty() const;
	
	///<summary>Returns first element of the list or nullptr if list is empty.</summary>
	///<returns>First element of the list or nullptr if list is empty.</returns>
	forward_list_element* first();
};

inline void forward_list_base::push_front(forward_list_element* elem)
{
	elem->next = first_element;
	first_element = elem;
}

inline forward_list_element* forward_list_base::pop_front()
{
	auto* result = first_element;
	if(result)
		first_element = result->next;
	return result;
}

inline bool forward_list_base::remove(forward_list_element* elem)
{
	auto* current = first_element;
	forward_list_element* prev = nullptr;
	while(current != elem)
	{
		if(!current)
			return false;
			
		prev = current;
		current = current->next;
	}
		
	if(prev)
		prev->next = elem->next;
	else
		first_element = elem->next;
		
	elem->next = nullptr;
	return true;
}

inline void forward_list_base::insert_before(forward_list_element* prev,
	forward_list_element* current, forward_list_element* elem)
{
	elem->next = current;
		
	if(prev)
		prev->next = elem;
	else
		first_element = elem;
}

inline bool forward_list_base::empty() const
{
	return !first_element;
}

inline forward_list_element* forward_list_base::first()
{
	return first_element;
}

///Base class for typed element of singly-linked list. Supports tags, allowing element to be in several different
///singly-linked lists simultaneously.
template<typename Tag, typename ContainedType>
struct ATMOS_PACKED forward_list_element_tagged : forward_list_element
{
	using tag_type = Tag;
	using contained_type = ContainedType;
	using list_element_type = forward_list_element_tagged<tag_type, contained_type>;

	///<summary>Downcasts list element to contained element type.</summary>
	///<returns>Contained element pointer.</returns>
	contained_type* operator->()
	{
		return static_cast<contained_type*>(this);
	}
};

///Typed singly-linked list which allows its typed contained elements to be contained in several different lists.
template<typename ForwardListElement>
struct ATMOS_PACKED forward_list_tagged : private forward_list_base
{
	using list_element_type = ForwardListElement;
	using tag_type = typename list_element_type::tag_type;
	using contained_type = typename list_element_type::contained_type;

	using forward_list_base::empty;

	///<summary>Push new element to front of list.</summary>
	///<param name="elem">Element not attached to any list of the same type. Can not be nullptr.</param>
	void push_front(list_element_type* elem) ATMOS_NONNULL(1);

	///<summary>Pop front element of list.</summary>
	///<returns>Front list element or nullptr if list is empty.</returns>
	list_element_type* pop_front();

	///<summary>Remove element from list.</summary>
	///<remarks>Has O(n) time complexity.</remarks>
	///<param name="elem">Any element of any list. Can not be nullptr.</param>
	///<returns>True if element was removed. False if element was not found in list.</returns>
	bool remove(list_element_type* elem) ATMOS_NONNULL(1);
	
	///<summary>Returns first element of the list or nullptr if list is empty.</summary>
	///<returns>First element of the list or nullptr if list is empty.</returns>
	list_element_type* first();

	///<summary>Insert element "elem" before any element that satisfies the condition.</summary>
	///<remarks>If list is empty, element "elem" is just inserted.</remarks>
	///<param name="elem">Element not attached to any list of the same type. Can not be nullptr.</param>
	///<param name="compare">Functor "compare" should return true, if the element satisfies the condition, and false otherwise.
	///                      This functor is called for each element of a list.</param>
	template<typename Func>
	void insert_before(list_element_type* elem, Func&& compare) ATMOS_NONNULL(1);
	
	///<summary>Returns element after "elem" element.</summary>
	///<param name="elem">Any element of any list. Can not be nullptr.</param>
	///<returns>Element after "elem" element or nullptr if there is no element.</returns>
	static list_element_type* next(list_element_type* elem) ATMOS_NONNULL(1);
};

template<typename ForwardListElement>
void forward_list_tagged<ForwardListElement>::push_front(list_element_type* elem)
{
	forward_list_base::push_front(elem);
}

template<typename ForwardListElement>
typename forward_list_tagged<ForwardListElement>::list_element_type*
	forward_list_tagged<ForwardListElement>::pop_front()
{
	return static_cast<list_element_type*>(forward_list_base::pop_front());
}

template<typename ForwardListElement>
bool forward_list_tagged<ForwardListElement>::remove(list_element_type* elem)
{
	return forward_list_base::remove(elem);
}

template<typename ForwardListElement>
typename forward_list_tagged<ForwardListElement>::list_element_type*
	forward_list_tagged<ForwardListElement>::first()
{
	return static_cast<list_element_type*>(first_element);
}

template<typename ForwardListElement>
template<typename Func>
void forward_list_tagged<ForwardListElement>::insert_before(list_element_type* elem, Func&& compare)
{
	forward_list_element* current = first_element;
	forward_list_element* prev = nullptr;
	while(current)
	{
		if(compare(static_cast<contained_type*>(static_cast<list_element_type*>(current))))
			break;

		prev = current;
		current = current->next;
	}
		
	return forward_list_base::insert_before(prev, current, elem);
}

template<typename ForwardListElement>
typename forward_list_tagged<ForwardListElement>::list_element_type*
	forward_list_tagged<ForwardListElement>::next(list_element_type* elem)
{
	return static_cast<list_element_type*>(elem->next);
}

} //namespace container
} //namespace atmos
