/*************************************************************
* Author:			Daniel Stotts
* Filename:			LinkedStack.h
* Date Created:		4/22/2016
* Modifications:	None
**************************************************************/

#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include "Linked.h"
#include "Exception.h"

/************************************************************************
* Class: LinkedStack
*
* Purpose: This class manages a linked list based stack for generic use.
*
* Manager functions:
*	LinkedStack();
*	LinkedStack(const LinkedStack<T> &);
*	~LinkedStack();
*	operator = (const LinkedStack<T> &);
*
* Methods:
*	Push(T);
*	Pop();
*	Peek();
*	Size();
*	isEmpty();
*************************************************************************/
template <typename T>
class LinkedStack
{
public:
	LinkedStack();
	LinkedStack(const LinkedStack<T> &);
	~LinkedStack();

	const LinkedStack<T> & operator = (const LinkedStack<T> &);

	void Push(T);
	T Pop();
	T Peek();
	int Size();
	bool isEmpty();

private:
	Linked<T> m_linked;

};

/**********************************************************************
* Purpose: Constructs an instance of a LinkedStack object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
LinkedStack<T>::LinkedStack()
{ }

/**********************************************************************
* Purpose: Constructs an instance of a LinkedStack object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T> & copy) :
	m_linked(copy.m_linked)
{ }

/**********************************************************************
* Purpose: Destroys an instance of the LinkedStack object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance destroyed.
*
************************************************************************/
template <typename T>
LinkedStack<T>::~LinkedStack()
{
	
}

/**********************************************************************
* Purpose: Sets this instance of a LinkedStack equal to another.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance copied.
*
************************************************************************/
template <typename T>
const LinkedStack<T> & LinkedStack<T>::operator = (const LinkedStack<T> & rhs)
{
	if(this != &rhs)
	{
		m_linked = rhs.m_linked;
	}
	return *this;
}

/**********************************************************************
* Purpose: Pushes a data element onto the stack.
*
* Precondition:
*     None
*
* Postcondition:
*     Data element pushed to stack.
*
************************************************************************/
template <typename T>
void LinkedStack<T>::Push(T data)
{
	m_linked.Append(data);
}

/**********************************************************************
* Purpose: Pops a data element from the stack.
*
* Precondition:
*     None
*
* Postcondition:
*     Data element removed and returned from stack.
*
************************************************************************/
template <typename T>
T LinkedStack<T>::Pop()
{
	if (m_linked.GetLength() == 0)
		throw Exception("Cannot pop element, will underflow stack!");

	return m_linked.Extract(m_linked.GetLast());
}

/**********************************************************************
* Purpose: Returns a copy of the next data element to be popped.
*
* Precondition:
*     None
*
* Postcondition:
*     Data element returned from stack.
*
************************************************************************/
template <typename T>
T LinkedStack<T>::Peek()
{
	return m_linked.GetLast();
}

/**********************************************************************
* Purpose: Returns size of stack.
*
* Precondition:
*     None
*
* Postcondition:
*     Size of stack returned.
*
************************************************************************/
template <typename T>
int LinkedStack<T>::Size()
{
	return m_linked.GetLength();
}

/**********************************************************************
* Purpose: Returns a determination of whether or not the stack is empty.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean returned.
*
************************************************************************/
template <typename T>
bool LinkedStack<T>::isEmpty()
{
	return (m_linked.GetLength() > 0 ? false : true);
}

#endif