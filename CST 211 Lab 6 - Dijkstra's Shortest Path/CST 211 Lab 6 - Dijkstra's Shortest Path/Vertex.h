/*************************************************************
* Author:			Daniel Stotts
* Filename:			Vertex.h
* Date Created:		5/20/2016
* Modifications:	None
**************************************************************/

#ifndef VERTEX_H
#define VERTEX_H

#include <list>
using std::list;

#include "Edge.h"

template <typename V, typename E>
class Graph;

/************************************************************************
* Class: Vertex
*
* Purpose: This class manages a Vertex for use with a Graph.
*
* Manager functions:
*	Vertex();
*	Vertex(const V &, bool = false);
*	Vertex(const Vertex<V, E> &);
*	~Vertex();
*	const Vertex<V, E> & operator = (const Vertex<V, E> &);
*
* Methods:
*	operator == (const Vertex<V, E> &) const;
*	operator == (const V &) const;
*	operator != (const Vertex<V, E> &) const;
*	GetData() const;
*	GetList() const;
*************************************************************************/
template <typename V, typename E>
class Vertex
{
	friend class Graph<V, E>;

public:
	Vertex();
	Vertex(const V &, bool = false);
	Vertex(const Vertex<V, E> &);
	~Vertex();

	const Vertex<V, E> & operator = (const Vertex<V, E> &);

	bool operator == (const Vertex<V, E> &) const;
	bool operator == (const V &) const;
	bool operator != (const Vertex<V, E> &) const;

	const V & GetData() const;
	const list<Edge<V, E>> & GetList() const;

private:
	list<Edge<V, E>> _list;
	bool _processed;
	V _data;

};

/**********************************************************************
* Purpose: Constructs an instance of a Vertex object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename V, typename E>
Vertex<V, E>::Vertex() :
	_list(),
	_processed(false),
	_data()
{ }

/**********************************************************************
* Purpose: Constructs an instance of a Vertex object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename V, typename E>
Vertex<V, E>::Vertex(const V & data, bool processed) :
	_list(),
	_processed(processed),
	_data(data)
{ }

/**********************************************************************
* Purpose: Constructs an instance of a Vertex object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename V, typename E>
Vertex<V, E>::Vertex(const Vertex<V, E> & copy) :
	_list(copy._list),
	_processed(copy._processed),
	_data(copy._data)
{ }

/**********************************************************************
* Purpose: Destroys the instance of a Vertex object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance destroyed.
*
************************************************************************/
template <typename V, typename E>
Vertex<V, E>::~Vertex()
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
template <typename V, typename E>
const Vertex<V, E> & Vertex<V, E>::operator = (const Vertex<V, E> & rhs)
{
	if(this != &rhs)
	{
		_list = rhs._list;
		_processed = rhs._processed;
		_data = rhs._data;
	}
	return *this;
}

/**********************************************************************
* Purpose: Determines if this instance is equal to another.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean returned.
*
************************************************************************/
template <typename V, typename E>
bool Vertex<V, E>::operator == (const Vertex<V, E> & rhs) const
{
	return (_list == rhs._list
		&& _processed == rhs._processed
		&& _data == rhs._data);
}

/**********************************************************************
* Purpose: Determines if this instance is equal to another.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean returned.
*
************************************************************************/
template <typename V, typename E>
bool Vertex<V, E>::operator == (const V & data) const
{
	return (_data == data);
}

/**********************************************************************
* Purpose: Determines if this instance is not equal to another.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean returned.
*
************************************************************************/
template <typename V, typename E>
bool Vertex<V, E>::operator != (const Vertex<V, E> & rhs) const
{
	return !(*this == rhs);
}

/**********************************************************************
* Purpose: Returns data data member.
*
* Precondition:
*     None
*
* Postcondition:
*     Member returned.
*
************************************************************************/
template <typename V, typename E>
const V & Vertex<V, E>::GetData() const
{
	return _data;
}

/**********************************************************************
* Purpose: Returns list data member.
*
* Precondition:
*     None
*
* Postcondition:
*     Member returned.
*
************************************************************************/
template <typename V, typename E>
const list<Edge<V, E>> & Vertex<V, E>::GetList() const
{
	return _list;
}

#endif