/*************************************************************
* Author:			Daniel Stotts
* Filename:			LinkedQueue.h
* Date Created:		4/22/2016
* Modifications:	None
**************************************************************/

#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include "Linked.h"
#include "Exception.h"

/************************************************************************
* Class: LinkedQueue
*
* Purpose: This class manages a Linked Queue.
*
* Manager functions:
*	LinkedQueue();
*	LinkedQueue(const LinkedQueue<T> &);
*	~LinkedQueue();
*	operator = (const LinkedQueue<T> &);
*
* Methods:
*	Enqueue(T);
*	Dequeue();
*	Front();
*	Size();
*	isEmpty();
*************************************************************************/
template <typename T>
class LinkedQueue
{
public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue<T> &);
	~LinkedQueue();

	const LinkedQueue<T> & operator = (const LinkedQueue<T> &);

	void Enqueue(T);
	T Dequeue();
	T & Front();
	int Size();
	bool isEmpty();

private:
	Linked<T> m_array;

};

/**********************************************************************
* Purpose: Constructs an instance of a Linked Queue object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
LinkedQueue<T>::LinkedQueue()
{ }

/**********************************************************************
* Purpose: Constructs an instance of a Linked Queue object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T> & copy) :
	m_array(copy.m_array)
{ }

/**********************************************************************
* Purpose: Destroys the instance of a Linked Queue object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance destroyed.
*
************************************************************************/
template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	
}

/**********************************************************************
* Purpose: Sets this instance equal to another.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance copied.
*
************************************************************************/
template <typename T>
const LinkedQueue<T> & LinkedQueue<T>::operator = (const LinkedQueue<T> & rhs)
{
	if(this != &rhs)
	{
		m_array = rhs.m_array;
	}
	return *this;
}

/**********************************************************************
* Purpose: Enqueues data.
*
* Precondition:
*     None
*
* Postcondition:
*     Data queued.
*
************************************************************************/
template <typename T>
void LinkedQueue<T>::Enqueue(T data)
{
	m_array.Append(data);
}

/**********************************************************************
* Purpose: Dequeues data.
*
* Precondition:
*     None
*
* Postcondition:
*     Data returned.
*
************************************************************************/
template <typename T>
T LinkedQueue<T>::Dequeue()
{
	if (m_array.GetLength() == 0)
		throw Exception("Cannot dequeue element, will underflow queue!");

	return m_array.Extract(m_array.GetFirst());
}

/**********************************************************************
* Purpose: Returns front data element.
*
* Precondition:
*     None
*
* Postcondition:
*     Data returned.
*
************************************************************************/
template <typename T>
T & LinkedQueue<T>::Front()
{
	return m_array.GetFirstRef();
}

/**********************************************************************
* Purpose: Returns size of queue.
*
* Precondition:
*     None
*
* Postcondition:
*     Integer returned.
*
************************************************************************/
template <typename T>
int LinkedQueue<T>::Size()
{
	return m_array.GetLength();
}

/**********************************************************************
* Purpose: Determines if list is empty.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean returned.
*
************************************************************************/
template <typename T>
bool LinkedQueue<T>::isEmpty()
{
	return (m_array.GetLength() > 0 ? false : true);
}

#endif