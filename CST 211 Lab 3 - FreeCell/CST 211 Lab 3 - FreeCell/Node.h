/*************************************************************
* Author:			Daniel Stotts
* Filename:			Node.h
* Date Created:		3/30/2016
* Modifications:	None
**************************************************************/

#ifndef NODE_H
#define NODE_H

template <typename T>
class Linked;

/************************************************************************
* Class: Node
*
* Purpose: This contains data for use in a linked list.
*
* Manager functions:
* 	Node();
*	Node(const T &, Node<T> *, Node<T> *);
*	Node(const Node &);
*	~Node();
*	operator = (const Node<T> &);
*
* Methods:
*	GetData() const;
*	SetData(const T &);
*	GetNext() const;
*	SetNext(Node<T> *);
*	GetPrevious() const;
*	SetPrevious(Node<T> *);
*************************************************************************/
template <typename T>
class Node
{
	friend class Linked<T>;

public:
	Node();
	Node(const T &, Node<T> * = nullptr, Node<T> * = nullptr);
	Node(const Node &);
	~Node();

	const Node<T> & operator = (const Node<T> &);
	
	const T & GetData() const;
	void SetData(const T &);
	const Node<T> * GetNext() const;
	void SetNext(Node<T> *);
	const Node<T> * GetPrevious() const;
	void SetPrevious(Node<T> *);

private:
	T m_data;
	Node<T> * m_next;
	Node<T> * m_previous;
};

/**********************************************************************
* Purpose: Constructs an instance of a Node object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
Node<T>::Node()
{
	m_next = nullptr;
	m_previous = nullptr;
}

/**********************************************************************
* Purpose: Constructs an instance of a Node object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
Node<T>::Node(const T & data, Node<T> * next, Node<T> * previous)
{
	m_data = data;
	m_next = next;
	m_previous = previous;
}

/**********************************************************************
* Purpose: Constructs an instance of a Node object, using another node
			as a means of doing so.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
Node<T>::Node(const Node & copy)
{
	m_data = copy.m_data;
	m_next = copy.m_next;
	m_previous = copy.m_previous;
}

/**********************************************************************
* Purpose: Destroys the instance of a Node object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance destroyed.
*
************************************************************************/
template <typename T>
Node<T>::~Node()
{
	m_next = nullptr;
	m_previous = nullptr;
}

/**********************************************************************
* Purpose: Sets instance of Node equal to a given instance.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance equal to given Node object.
*
************************************************************************/
template <typename T>
const Node<T> & Node<T>::operator = (const Node<T> & rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_next = rhs.m_next;
		m_previous = rhs.m_previous;
	}
	return *this;
}

/**********************************************************************
* Purpose: Returns Data data member.
*
* Precondition:
*     None
*
* Postcondition:
*     Data data member returned.
*
************************************************************************/
template <typename T>
const T & Node<T>::GetData() const
{
	return m_data;
}

/**********************************************************************
* Purpose: Sets Data data member to a specified value.
*
* Precondition:
*     None
*
* Postcondition:
*     Data data member set.
*
************************************************************************/
template <typename T>
void Node<T>::SetData(const T & data)
{
	m_data = data;
}

/**********************************************************************
* Purpose: Returns Next data member.
*
* Precondition:
*     None
*
* Postcondition:
*     Next data member returned.
*
************************************************************************/
template <typename T>
const Node<T> * Node<T>::GetNext() const
{
	return m_next;
}

/**********************************************************************
* Purpose: Sets Next data member.
*
* Precondition:
*     None
*
* Postcondition:
*     Next data member set.
*
************************************************************************/
template <typename T>
void Node<T>::SetNext(Node<T> * next)
{
	m_next = next;
}

/**********************************************************************
* Purpose: Gets Previous data member.
*
* Precondition:
*     None
*
* Postcondition:
*     Previous data member returned.
*
************************************************************************/
template <typename T>
const Node<T> * Node<T>::GetPrevious() const
{
	return m_previous;
}

/**********************************************************************
* Purpose: Sets Previous data member.
*
* Precondition:
*     None
*
* Postcondition:
*     Previous data member set.
*
************************************************************************/
template <typename T>
void Node<T>::SetPrevious(Node<T> * previous)
{
	m_previous = previous;
}

#endif