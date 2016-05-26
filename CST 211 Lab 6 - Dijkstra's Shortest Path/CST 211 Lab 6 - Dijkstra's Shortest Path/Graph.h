/*************************************************************
* Author:			Daniel Stotts
* Filename:			Graph.h
* Date Created:		5/20/2016
* Modifications:	None
**************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <list>
using std::list;
using std::iterator;

#include "Exception.h"
#include "LinkedQueue.h"
#include "LinkedStack.h"

#include "Vertex.h"

/************************************************************************
* Class: Graph
*
* Purpose: This class manages a Graph.
*
* Manager functions:
*	Graph();
*	Graph(Graph<V, E> &);
*	~Graph();
*	operator = (Graph<V, E> &);
*
* Methods:
*	InsertVertex(const V &);
*	RemoveVertex(const V &);
*	InsertEdge(const V &, const V &, const E &, int);
*	RemoveEdge(const V &, const V &);
*	IsEmpty() const;
*	GetList() const;
*	Traverse_BreadthFirst(void(*)(V));
*	Traverse_DepthFirst(void(*)(V));
*************************************************************************/
template <typename V, typename E>
class Graph
{
public:
	Graph();
	Graph(Graph<V, E> &);
	~Graph();

	const Graph<V, E> & operator = (Graph<V, E> &);

	void InsertVertex(const V &);
	void RemoveVertex(const V &);

	void InsertEdge(const V &, const V &, const E &, int);
	void RemoveEdge(const V &, const V &);

	bool IsEmpty() const;

	const list<Vertex<V, E>> & GetList() const;

	void Traverse_BreadthFirst(void(*)(V));
	void Traverse_DepthFirst(void(*)(V));

private:
	list<Vertex<V, E>> _list;

};

/**********************************************************************
* Purpose: Constructs an instance of a Graph object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename V, typename E>
Graph<V, E>::Graph() :
	_list()
{ }

/**********************************************************************
* Purpose: Constructs an instance of a Graph object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename V, typename E>
Graph<V, E>::Graph(Graph<V, E> & copy) :
	_list(copy._list)
{
	for (typename list<Vertex<V, E>>::iterator i = _list.begin(); i != _list.end(); ++i)
		i->_list.clear();
	for (typename list<Vertex<V, E>>::iterator i = copy._list.begin(); i != copy._list.end(); ++i)
		for (typename list<Edge<V, E>>::iterator ii = i->_list.begin(); ii != i->_list.end(); ++ii)
			try {
			InsertEdge(i->_data, ii->_vertex->_data, ii->_data, ii->_weight);
		}
	catch (Exception(pls)) {}
}

/**********************************************************************
* Purpose: Destroys the instance of a Graph object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance destroyed.
*
************************************************************************/
template <typename V, typename E>
Graph<V, E>::~Graph()
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
const Graph<V, E> & Graph<V, E>::operator = (Graph<V, E> & rhs)
{
	if (this != &rhs)
	{
		_list = rhs._list;
		for (typename list<Vertex<V, E>>::iterator i = _list.begin(); i != _list.end(); ++i)
			i->_list.clear();
		for (typename list<Vertex<V, E>>::iterator i = rhs._list.begin(); i != rhs._list.end(); ++i)
			for (typename list<Edge<V, E>>::iterator ii = i->_list.begin(); ii != i->_list.end(); ++ii)
				try {
				InsertEdge(i->_data, ii->_vertex->_data, ii->_data, ii->_weight);
			}
		catch (Exception(pls)) {}
	}
	return *this;
}

/**********************************************************************
* Purpose: Inserts a vertex into the graph.
*
* Precondition:
*     None
*
* Postcondition:
*     Vertex inserted.
*
************************************************************************/
template <typename V, typename E>
void Graph<V, E>::InsertVertex(const V & data)
{
	for (typename list<Vertex<V, E>>::iterator i = _list.begin(); i != _list.end(); ++i)
		if (i->_data == data)
			throw Exception("Vertex already exists!");

	_list.push_back(Vertex<V, E>(data));
}

/**********************************************************************
* Purpose: Removes a vertex from the graph.
*
* Precondition:
*     None
*
* Postcondition:
*     Vertex removed.
*
************************************************************************/
template <typename V, typename E>
void Graph<V, E>::RemoveVertex(const V & key)
{
	bool complete_one = false, complete_two = false;
	for (typename list<Vertex<V, E>>::iterator i = _list.begin(); !complete_one && i != _list.end();)
	{
		if (i->_data == key)
		{
			complete_one = true;
			for (typename list<Vertex<V, E>>::iterator ii = _list.begin(); ii != _list.end(); ++ii)
			{
				complete_two = false;
				for (typename list<Edge<V, E>>::iterator iii = ii->_list.begin(); !complete_two && iii != ii->_list.end();)
					if (iii->_vertex->_data == key)
					{
						ii->_list.erase(iii);
						complete_two = true;
					}
					else
						++iii;
			}
			_list.erase(i);
		}
		else
			++i;
	}
	if (!complete_one)
		throw Exception("Element does not exist!");
}

/**********************************************************************
* Purpose: Inserts an edge into the graph.
*
* Precondition:
*     None
*
* Postcondition:
*     Edge inserted.
*
************************************************************************/
template <typename V, typename E>
void Graph<V, E>::InsertEdge(const V & origin, const V & destination, const E & data, int weight)
{
	Vertex<V, E> * target_origin = nullptr;
	Vertex<V, E> * target_destination = nullptr;
	for (typename list<Vertex<V, E>>::iterator i = _list.begin(); i != _list.end(); ++i)
	{
		if (i->_data == origin)
			target_origin = &(*i);
		if (i->_data == destination)
			target_destination = &(*i);
	}
	if (target_origin == nullptr || target_destination == nullptr)
		throw Exception("At least one vertex does not exist!");

	for (typename list <Edge<V, E>>::iterator i = target_origin->_list.begin(); i != target_origin->_list.end(); ++i)
		if (*i == Edge<V, E>(target_destination, weight, data))
			throw Exception("Edge already exists!");

	for (typename list <Edge<V, E>>::iterator i = target_destination->_list.begin(); i != target_destination->_list.end(); ++i)
		if (*i == Edge<V, E>(target_origin, weight, data))
			throw Exception("Edge already exists!");

	target_origin->_list.push_back(Edge<V, E>(target_destination, weight, data));
	target_destination->_list.push_back(Edge<V, E>(target_origin, weight, data));
}

/**********************************************************************
* Purpose: Removes an edge from the graph.
*
* Precondition:
*     None
*
* Postcondition:
*     Edge removed.
*
************************************************************************/
template <typename V, typename E>
void Graph<V, E>::RemoveEdge(const V & origin, const V & destination)
{
	bool complete_one = false;
	Vertex<V, E> * target_origin = nullptr;
	Vertex<V, E> * target_destination = nullptr;
	for (typename list<Vertex<V, E>>::iterator i = _list.begin(); i != _list.end(); ++i)
	{
		if (i->_data == origin)
			target_origin = &(*i);
		if (i->_data == destination)
			target_destination = &(*i);
	}
	if (target_origin == nullptr || target_destination == nullptr)
		throw Exception("At least one vertex does not exist!");

	for (typename list<Vertex<V, E>>::iterator i = _list.begin(); i != _list.end(); ++i)
	{
		complete_one = false;
		for (typename list<Edge<V, E>>::iterator ii = i->_list.begin(); !complete_one && ii != i->_list.end();)
		{
			if (ii->_vertex == target_origin)
			{
				complete_one = true;
				target_destination->_list.erase(ii);
			}
			else if (ii->_vertex == target_destination)
			{
				complete_one = true;
				target_origin->_list.erase(ii);
			}
			else
				++ii;
		}
	}
	if (!complete_one)
		throw Exception("Edge does not exist!");
}

/**********************************************************************
* Purpose: Determines whether the graph is empty.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean returned.
*
************************************************************************/
template <typename V, typename E>
bool Graph<V, E>::IsEmpty() const
{
	return _list.empty();
}

/**********************************************************************
* Purpose: Returns the List data member.
*
* Precondition:
*     None
*
* Postcondition:
*     Member returned.
*
************************************************************************/
template <typename V, typename E>
const list<Vertex<V, E>> & Graph<V, E>::GetList() const
{
	return _list;
}

/**********************************************************************
* Purpose: Traverses graph.
*
* Precondition:
*     None
*
* Postcondition:
*     Graph traversed.
*
************************************************************************/
template <typename V, typename E>
void Graph<V, E>::Traverse_BreadthFirst(void(*visit)(V data))
{
	if (IsEmpty())
		throw Exception("Graph holds no elements!");

	LinkedQueue<Vertex<V, E> *> queue;
	Vertex<V, E> * temp = nullptr;
	queue.Enqueue(&_list.front());
	while (!queue.isEmpty())
	{
		temp = queue.Dequeue();
		if (!temp->_processed)
		{
			visit(temp->_data);
			temp->_processed = true;
			for (typename list<Edge<V, E>>::iterator i = temp->_list.begin(); i != temp->_list.end(); ++i)
				if (!(i->_vertex->_processed))
					queue.Enqueue(i->_vertex);
		}
	}
	for (typename list<Vertex<V, E>>::iterator i = _list.begin(); i != _list.end(); ++i)
		i->_processed = false;
}

/**********************************************************************
* Purpose: Traverses graph.
*
* Precondition:
*     None
*
* Postcondition:
*     Graph traversed.
*
************************************************************************/
template <typename V, typename E>
void Graph<V, E>::Traverse_DepthFirst(void(*visit)(V data))
{
	if (IsEmpty())
		throw Exception("Graph holds no elements!");

	LinkedStack<Vertex<V, E> *> stack;
	Vertex<V, E> * temp = nullptr;
	stack.Push(&_list.front());
	while (!stack.isEmpty())
	{
		temp = stack.Pop();
		if (!temp->_processed)
		{
			visit(temp->_data);
			temp->_processed = true;
			for (typename list<Edge<V, E>>::iterator i = temp->_list.begin(); i != temp->_list.end(); ++i)
				if (!(i->_vertex->_processed))
					stack.Push(i->_vertex);
		}
	}
	for (typename list<Vertex<V, E>>::iterator i = _list.begin(); i != _list.end(); ++i)
		i->_processed = false;
}

#endif