/*************************************************************
* Author:			Daniel Stotts
* Filename:			ArrayStack.h
* Date Created:		4/22/2016
* Modifications:	None
**************************************************************/

#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include "Array.h"
#include "Exception.h"

/************************************************************************
* Class: ArrayStack
*
* Purpose: This class manages an array based stack for generic use.
*
* Manager functions:
* 	ArrayStack();
*	ArrayStack(int);
*	ArrayStack(const ArrayStack<T> &);
*	~ArrayStack();
*	operator = (const ArrayStack<T> &);
*
* Methods:
*	void Push(T);
*	T Pop();
*	T Peek();
*	Size() const;
*	isEmpty() const;
*	bool isFull() const;
*************************************************************************/
template <typename T>
class ArrayStack
{
public:
	ArrayStack();
	ArrayStack(int);
	ArrayStack(const ArrayStack<T> &);
	~ArrayStack();

	const ArrayStack<T> & operator = (const ArrayStack<T> &);

	void Push(T);
	T Pop();
	T Peek() const;
	int Size() const;
	bool isEmpty() const;
	bool isFull() const;

private:
	Array<T> m_array;
	int m_size;

};

/**********************************************************************
* Purpose: Constructs an instance of an ArrayStack object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
ArrayStack<T>::ArrayStack() :
	m_array(0),
	m_size(0)
{ }

/**********************************************************************
* Purpose: Constructs an instance of an ArrayStack object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
ArrayStack<T>::ArrayStack(int size) :
	m_array(size),
	m_size(0)
{ }

/**********************************************************************
* Purpose: Constructs an instance of an ArrayStack object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
ArrayStack<T>::ArrayStack(const ArrayStack & copy) :
	m_array(copy.m_array),
	m_size(copy.m_size)
{ }

/**********************************************************************
* Purpose: Destroys an instance of the ArrayStack object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance destroyed.
*
************************************************************************/
template <typename T>
ArrayStack<T>::~ArrayStack()
{ }

/**********************************************************************
* Purpose: Sets this instance of ArrayStack equal to another.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance copied.
*
************************************************************************/
template <typename T>
const ArrayStack<T> & ArrayStack<T>::operator = (const ArrayStack<T> & rhs)
{
	if (this != &rhs)
	{
		m_array = rhs.m_array;
		m_size = rhs.m_size;
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
*     Element placed onto stack.
*
************************************************************************/
template <typename T>
void ArrayStack<T>::Push(T data)
{
	if (m_size + 1 > m_array.GetLength())
		throw Exception("Cannot push element, will overflow stack!");

	m_array[m_size++] = data;
}

/**********************************************************************
* Purpose: Pops an element from the stack.
*
* Precondition:
*     None
*
* Postcondition:
*     Element removed and returned from stack.
*
************************************************************************/
template <typename T>
T ArrayStack<T>::Pop()
{
	if (m_size == 0)
		throw Exception("Cannot pop element, will underflow stack!");

	return m_array[--m_size];
}

/**********************************************************************
* Purpose: Returns a copy of next element to be popped.
*
* Precondition:
*     None
*
* Postcondition:
*     Element returned from stack.
*
************************************************************************/
template <typename T>
T ArrayStack<T>::Peek() const
{
	if (m_size == 0)
		throw Exception("No elements on stack!");

	return m_array[m_size - 1];
}

/**********************************************************************
* Purpose: Returns the size of the stack.
*
* Precondition:
*     None
*
* Postcondition:
*     Size of stack returned.
*
************************************************************************/
template <typename T>
int ArrayStack<T>::Size() const
{
	return m_size;
}

/**********************************************************************
* Purpose: Returns a determination of whether or not the stack is empty.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolen returned.
*
************************************************************************/
template <typename T>
bool ArrayStack<T>::isEmpty() const
{
	return (m_size > 0 ? false : true);
}

/**********************************************************************
* Purpose: Returns a determination of whether or not the stack is full.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolen returned.
*
************************************************************************/
template <typename T>
bool ArrayStack<T>::isFull() const
{
	return (m_size == m_array.GetLength() ? true : false);
}

#endif