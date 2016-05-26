/*************************************************************
* Author:			Daniel Stotts
* Filename:			Edge.h
* Date Created:		5/20/2016
* Modifications:	None
**************************************************************/

#ifndef EDGE_H
#define EDGE_H

template <typename V, typename E>
class Graph;

template <typename V, typename E>
class Vertex;

/************************************************************************
* Class: Edge
*
* Purpose: This class manages an Edge for use with a Graph.
*
* Manager functions:
*	Edge();
*	Edge(Vertex<V, E> *, int, const E &);
*	Edge(const Edge<V, E> &);
*	~Edge();
*	operator = (const Edge<V, E> &);
*
* Methods:
*	operator == (const Edge<V, E> &) const;
*	GetVertex() const;
*	GetWeight() const;
*	GetData() const;
*************************************************************************/
template <typename V, typename E>
class Edge
{
	friend class Graph<V, E>;

public:
	Edge();
	Edge(Vertex<V, E> *, int, const E &);
	Edge(const Edge<V, E> &);
	~Edge();

	const Edge<V, E> & operator = (const Edge<V, E> &);

	bool operator == (const Edge<V, E> &) const;

	const Vertex<V, E> * GetVertex() const;
	int GetWeight() const;
	const E & GetData() const;

private:
	Vertex<V, E> * _vertex;
	int _weight;
	E _data;

};

/**********************************************************************
* Purpose: Constructs an instance of an Edge object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename V, typename E>
Edge<V, E>::Edge() :
	_vertex(nullptr),
	_weight(0),
	_data()
{ }

/**********************************************************************
* Purpose: Constructs an instance of an Edge object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename V, typename E>
Edge<V, E>::Edge(Vertex<V, E> * vertex, int weight, const E & data) :
	_vertex(vertex),
	_weight(weight),
	_data(data)
{ }

/**********************************************************************
* Purpose: Constructs an instance of an Edge object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename V, typename E>
Edge<V, E>::Edge(const Edge<V, E> & copy) :
	_vertex(copy._vertex),
	_weight(copy._weight),
	_data(copy._data)
{ }

/**********************************************************************
* Purpose: Destroys the instance of an Edge object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename V, typename E>
Edge<V, E>::~Edge()
{
	_vertex = nullptr;
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
const Edge<V, E> & Edge<V, E>::operator = (const Edge<V, E> & rhs)
{
	if(this != &rhs)
	{
		_vertex = rhs._vertex;
		_weight = rhs._weight;
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
bool Edge<V, E>::operator == (const Edge<V, E> & rhs) const
{
	return (_vertex == rhs._vertex
		&& _weight == rhs._weight
		&& _data == rhs._data);
}

/**********************************************************************
* Purpose: Returns Vertex data member.
*
* Precondition:
*     None
*
* Postcondition:
*     Member returned.
*
************************************************************************/
template <typename V, typename E>
const Vertex<V, E> * Edge<V, E>::GetVertex() const
{
	return _vertex;
}

/**********************************************************************
* Purpose: Returns Weight data member.
*
* Precondition:
*     None
*
* Postcondition:
*     Member returned.
*
************************************************************************/
template <typename V, typename E>
int Edge<V, E>::GetWeight() const
{
	return _weight;
}

/**********************************************************************
* Purpose: Returns Data data member.
*
* Precondition:
*     None
*
* Postcondition:
*     Member returned.
*
************************************************************************/
template <typename V, typename E>
const E & Edge<V, E>::GetData() const
{
	return _data;
}

#endif
