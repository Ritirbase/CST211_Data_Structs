/*************************************************************
* Author:			Daniel Stotts
* Filename:			Linked.h
* Date Created:		3/30/2016
* Modifications:	3/9/2016 - Added "Operator []" and "GetLength"
**************************************************************/

#ifndef LINKED_H
#define LINKED_H

#include "Exception.h"
#include "Node.h"

//#define LINKED_DEBUG

#ifdef LINKED_DEBUG
#include <iostream>
using std::cout;
using std::endl;
#endif

/************************************************************************
* Class: Linked
*
* Purpose: This class manages a linked list for generic use.
*
* Manager functions:
* 	Linked();
*	Linked(const Linked<T> &);
*	~Linked();
*	operator = (const Linked<T> &);
*
* Methods:
*	operator[](int);
*	IsEmpty();
*	GetFirst() const;
*	GetLast() const;
*	Prepend(const T &);
*	Append(const T &);
*	Purge();
*	Extract(const T &);
*	InsertAfter(const T &, const T &);
*	InsertBefore(const T &, const T &);
*	GetLength() const;
*************************************************************************/
template <typename T>
class Linked
{
public:
	Linked();
	Linked(const Linked<T> &);
	~Linked();

	const Linked<T> & operator = (const Linked<T> &);
	T & operator[](int);

	bool IsEmpty();
	const T & GetFirst() const;
	T & GetFirstRef(); // For LinkedQueue "Front"
	const T & GetLast() const;
	void Prepend(const T &);
	void Append(const T &);
	void Purge();
	const T & Extract(const T &);
	void InsertAfter(const T &, const T &);
	void InsertBefore(const T &, const T &);
	const int GetLength() const;

#ifdef LINKED_DEBUG
	Node<T> * GetHead();
	Node<T> * GetTail();
	void PrintForwards();
	void PrintBackwards();
#endif

private:
	Node<T> * m_head;
	Node<T> * m_tail;
};

/**********************************************************************
* Purpose: Constructs an instance of a Linked object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
Linked<T>::Linked()
{
	m_head = nullptr;
	m_tail = nullptr;
}

/**********************************************************************
* Purpose: Constructs an instance of a Linked object, using another
			instance as a means of doing so.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
Linked<T>::Linked(const Linked<T> & copy)
{
	m_head = nullptr;
	m_tail = nullptr;

	Node<T> * travel = copy.m_head;
	while (travel != nullptr)
	{
		Append(travel->m_data);
		travel = travel->m_next;
	}
}

/**********************************************************************
* Purpose: Destroys the instance of a Linked object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance destroyed.
*
************************************************************************/
template <typename T>
Linked<T>::~Linked()
{
	Purge();
}

/**********************************************************************
* Purpose: Sets instance equal to another instance of Linked.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance is equal to other instance.
*
************************************************************************/
template <typename T>
const Linked<T> & Linked<T>::operator = (const Linked<T> & rhs)
{
	if (this != &rhs)
	{
		Purge();

		Node<T> * travel = rhs.m_head;
		while (travel != nullptr)
		{
			Append(travel->m_data);
			travel = travel->m_next;
		}
	}
	return *this;
}

/**********************************************************************
* Purpose: Returns data element from specified index.
*
* Precondition:
*     None
*
* Postcondition:
*     Data element returned from location.
*
************************************************************************/
template <typename T>
T & Linked<T>::operator[](int index)
{
	Node<T> * travel = m_head;
	for (int i = 0; travel != nullptr && i < index; ++i)
		travel = travel->m_next;

	if (travel == nullptr)
		throw Exception("Index out of bounds!");

	return travel->m_data;
}

/**********************************************************************
* Purpose: Determines whether list is empty.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean returned.
*
************************************************************************/
template <typename T>
bool Linked<T>::IsEmpty()
{
	return (m_head == nullptr ? true : false);
}

/**********************************************************************
* Purpose: Returns first element in list.
*
* Precondition:
*     None
*
* Postcondition:
*     First element returned.
*
************************************************************************/
template <typename T>
const T & Linked<T>::GetFirst() const
{
	if (m_head == nullptr)
		throw Exception("No elements exist!");

	return m_head->m_data;
}

/**********************************************************************
* Purpose: Returns modifiable first element in list.
*
* Precondition:
*     None
*
* Postcondition:
*     First element returned.
*
************************************************************************/
template <typename T>
T & Linked<T>::GetFirstRef()
{
	if (m_head == nullptr)
		throw Exception("No elements exist!");

	return m_head->m_data;
}

/**********************************************************************
* Purpose: Returns last element in list.
*
* Precondition:
*     None
*
* Postcondition:
*     Last element returned.
*
************************************************************************/
template <typename T>
const T & Linked<T>::GetLast() const
{
	if (m_tail == nullptr)
		throw Exception("No elements exist!");

	return m_tail->m_data;
}

/**********************************************************************
* Purpose: Prepends data to list.
*
* Precondition:
*     None
*
* Postcondition:
*     Data prepended.
*
************************************************************************/
template <typename T>
void Linked<T>::Prepend(const T & data)
{
	if (m_head == nullptr) // List is empty
	{
		m_head = new Node<T>(data);
		m_tail = m_head;
	}
	else
	{
		Node<T> * node = new Node<T>(data, m_head);
		m_head->SetPrevious(node);
		m_head = node;
	}
}

/**********************************************************************
* Purpose: Appends data to list.
*
* Precondition:
*     None
*
* Postcondition:
*     Data appended.
*
************************************************************************/
template <typename T>
void Linked<T>::Append(const T & data)
{
	if (m_head == nullptr) // List is empty
	{
		m_head = new Node<T>(data);
		m_tail = m_head;
	}
	else
	{
		Node<T> * node = new Node<T>(data, nullptr, m_tail);
		m_tail->SetNext(node);
		m_tail = node;
	}
}

/**********************************************************************
* Purpose: Removes all data elements from list.
*
* Precondition:
*     None
*
* Postcondition:
*     List completely deleted.
*
************************************************************************/
template <typename T>
void Linked<T>::Purge()
{
	m_tail = nullptr;

	Node<T> * travel = nullptr;
	while (m_head != nullptr)
	{
		travel = m_head;
		m_head = m_head->m_next;
		delete travel;
	}
}

/**********************************************************************
* Purpose: Removes and returns specified data element from list.
*
* Precondition:
*     None
*
* Postcondition:
*     Data element removed and returned.
*
************************************************************************/
template <typename T>
const T & Linked<T>::Extract(const T & key)
{
	Node<T> * travel = m_head;
	while (travel != nullptr && travel->m_data != key)
	{
		travel = travel->m_next;
	}
	if (travel == nullptr)
		throw Exception("Element does not exist!");

	T data = travel->m_data;

	if (travel->m_previous == nullptr && travel->m_next == nullptr) // Final element in list
	{
		m_head = nullptr;
		m_tail = nullptr;
	}
	else if (travel->m_previous == nullptr) // Head element
	{
		m_head = travel->m_next;
		travel->m_next->m_previous = travel->m_previous;
	}
	else if (travel->m_next == nullptr) // Tail element
	{
		m_tail = travel->m_previous;
		travel->m_previous->m_next = travel->m_next;
	}
	else // Middle element
	{
		travel->m_previous->m_next = travel->m_next;
		travel->m_next->m_previous = travel->m_previous;
	}

	delete travel;
	travel = nullptr;

	return data;
}

/**********************************************************************
* Purpose: Inserts data into list after specified point.
*
* Precondition:
*     None
*
* Postcondition:
*    Data inserted at specified location.
*
************************************************************************/
template <typename T>
void Linked<T>::InsertAfter(const T & data, const T & key)
{
	Node<T> * travel = m_head;
	while (travel != nullptr && travel->m_data != key)
	{
		travel = travel->m_next;
	}
	if (travel == nullptr)
		throw Exception("Element does not exist!");

	Node<T> * node = new Node<T>(data, travel->m_next, travel);
	travel->m_next = node;

	if (node->m_next == nullptr)
	{
		m_tail = node;
	}
	else
	{
		node->m_next->m_previous = node;
	}
}

/**********************************************************************
* Purpose: Inserts data into list before specified point.
*
* Precondition:
*     None
*
* Postcondition:
*     Data inserted at specified location.
*
************************************************************************/
template <typename T>
void Linked<T>::InsertBefore(const T & data, const T & key)
{
	Node<T> * travel = m_head;
	while (travel != nullptr && travel->m_data != key)
	{
		travel = travel->m_next;
	}
	if (travel == nullptr)
		throw Exception("Element does not exist!");

	Node<T> * node = new Node<T>(data, travel, travel->m_previous);
	travel->m_previous = node;

	if (node->m_previous == nullptr)
	{
		m_head = node;
	}
	else
	{
		node->m_previous->m_next = node;
	}
}

/**********************************************************************
* Purpose: Returns length of list.
*
* Precondition:
*     None
*
* Postcondition:
*     Length of list returned.
*
************************************************************************/
template <typename T>
const int Linked<T>::GetLength() const
{
	int length = 0;

	Node<T> * travel = m_head;
	if (travel != nullptr && travel->m_next == nullptr)
		length = 1;
	else
	{
		while (travel != nullptr)
		{
			length++;
			travel = travel->m_next;
		}
	}
	return length;
}

#ifdef LINKED_DEBUG

	template <typename T>
	Node<T> * Linked<T>::GetHead()
	{
		return m_head;
	}

	template <typename T>
	Node<T> * Linked<T>::GetTail()
	{
		return m_tail;
	}

	template <typename T>
	void Linked<T>::PrintForwards()
	{
		Node<T> * travel = m_head;
		while (travel != nullptr)
		{
			cout << travel->m_data << endl;
			travel = travel->m_next;
		}
	}

	template <typename T>
	void Linked<T>::PrintBackwards()
	{
		Node<T> * travel = m_tail;
		while (travel != nullptr)
		{
			cout << travel->m_data << endl;
			travel = travel->m_previous;
		}
	}
#endif

#endif