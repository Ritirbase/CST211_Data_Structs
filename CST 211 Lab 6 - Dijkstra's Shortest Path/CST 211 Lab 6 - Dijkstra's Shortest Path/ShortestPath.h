/*************************************************************
* Author:			Daniel Stotts
* Filename:			ShortestPath.h
* Date Created:		5/24/2016
* Modifications:	None
**************************************************************/

#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <windows.h>

#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;

#include "Graph.h"
#include "Exception.h"

/************************************************************************
* Class: ShortestPath
*
* Purpose: This class manages a linked list based stack for generic use.
*
* Manager functions:
*	ShortestPath(const ShortestPath &);
*	ShortestPath(const Graph<V, E> &, const V &);
*	~ShortestPath();
*
* Methods:
*	RouteTo(const V &);
*************************************************************************/
template <typename V, typename E>
class ShortestPath
{
public:
	//ShortestPath(); // Cannot write with a reference data member!
	ShortestPath(const ShortestPath &);
	ShortestPath(const Graph<V, E> &, const V &);
	~ShortestPath();

	const ShortestPath<V, E> operator = (const ShortestPath<V, E> &);

	int RouteTo(const V &);

private:
	int SmallestDistance();
	void CalculateAdjacency(int);
	int FindIndex(Vertex<V, E>);
	Edge<V, E> FindEdge(int, int);

	const Graph<V, E> & _graph;
	vector<Vertex<V, E>> _vertices;
	vector<int> _predecessor;
	vector<int> _distance;
	vector<bool> _processed;

};

//template <typename V, typename E>
//ShortestPath<V, E>::ShortestPath() :
//	_graph(),
//	_vertices(),
//	_predecessor(),
//	_distance(),
//	_processed()
//{
//	throw Exception("Default construction not supported!");
//}

/**********************************************************************
* Purpose: Constructs an instance of a Shortest Path object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename V, typename E>
ShortestPath<V, E>::ShortestPath(const ShortestPath & copy) :
	_graph(copy._graph),
	_vertices(copy._vertices),
	_predecessor(copy._predecessor),
	_distance(copy._distance),
	_processed(copy._processed)
{ }

/**********************************************************************
* Purpose: Constructs an instance of a Shortest Path object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename V, typename E>
ShortestPath<V, E>::ShortestPath(const Graph<V, E> & graph, const V & origin) :
	_graph(graph),
	_vertices(),
	_predecessor(),
	_distance(),
	_processed()
{
	for (const Vertex<V, E> & i : graph.GetList())
		_vertices.push_back(i);

	int index = -1, count = 0;
	for (Vertex<V, E> i : _vertices)
	{
		if (i == origin)
			index = count;
		++count;
	}
	if (index < 0)
		throw Exception("Origin vertex does not exist!");

	int size = _vertices.size();
	_predecessor.assign(size, -1);
	_distance.assign(size, -1);
	_processed.assign(size, false);

	_distance[index] = 0;

	bool complete = false;
	while (!complete)
	{
		index = SmallestDistance();
		CalculateAdjacency(index);

		count = 0;
		for (bool i : _processed)
			if (i == true)
				++count;
		if (count == size - 1)
			complete = true;
	}
}

/**********************************************************************
* Purpose: Destroys the instance of a Shortest Path object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance destroyed.
*
************************************************************************/
template <typename V, typename E>
ShortestPath<V, E>::~ShortestPath()
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
const ShortestPath<V, E> ShortestPath<V, E>::operator = (const ShortestPath<V, E> & rhs)
{
	if(this != &rhs)
	{
		_graph = rhs._graph;
		_vertices = rhs._vertices;
		_predecessor = rhs._predecessor;
		_distance = rhs._distance;
		_processed = rhs._processed;
	}
	return *this;
}

/**********************************************************************
* Purpose: Calculates and outputs path to specified vertex.
*
* Precondition:
*     None
*
* Postcondition:
*     Distance returned.
*
************************************************************************/
template <typename V, typename E>
int ShortestPath<V, E>::RouteTo(const V & key)
{
	HANDLE handle = nullptr;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);

	int index = -1, count = 0;
	for (Vertex<V, E> i : _vertices)
	{
		if (i == key)
			index = count;
		++count;
	}
	if (index < 0)
		throw Exception("Destination vertex does not exist!");

	list<Vertex<V, E>> path_vertices;
	int distance = _distance[index], path_index = index;
	while (path_index != -1)
	{
		path_vertices.push_back(_vertices[path_index]);
		path_index = _predecessor[path_index];
	}
	Vertex<V, E> temp_one, temp_two;
	count = 0;
	while (path_vertices.size() > 1)
	{
		temp_one = path_vertices.back();
		if (count > 0)
		{
			cout << "> to <";

			SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << temp_one.GetData();
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

			cout << '>'
				<< endl;
		}
		else
		{
			cout << "  "
				<< ++count
				<< ". Start from <";

			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << temp_one.GetData();
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

			cout << '>'
				<< endl;
		}

		path_vertices.pop_back();
		temp_two = path_vertices.back();
		cout << "  "
			<< ++count
			<< ". From <";

		SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << temp_one.GetData();
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		cout << "> through <";

		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << FindEdge(FindIndex(temp_one), FindIndex(temp_two)).GetData();
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	if (!count)
	{
		cout << "  "
			<< ++count
			<< ". Start from <";

		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << path_vertices.back().GetData();
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	else
	{
		cout << "> to <";

		SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << path_vertices.back().GetData();
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

	cout << '>'
		<< endl
		<< "  "
		<< ++count
		<< ". Arrived at <";

	SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << path_vertices.back().GetData();
	SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	cout << ">! "
		<< endl
		<< "  >> Total distance travelled: ";

	SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << distance;
	SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	cout << endl;

	return distance;
}

/**********************************************************************
* Purpose: Finds next element to process.
*
* Precondition:
*     None
*
* Postcondition:
*     Index created.
*
************************************************************************/
template <typename V, typename E>
int ShortestPath<V, E>::SmallestDistance()
{
	unsigned int distance = -1;
	int index = -1, count = 0;
	for (int i : _distance)
	{
		if (static_cast<unsigned int>(i) < distance && !_processed[count])
		{
			index = count;
			distance = _distance[count];
		}
		++count;
	}
	return index;
}

/**********************************************************************
* Purpose: Calculates adjacency values for parallel arrays.
*
* Precondition:
*     None
*
* Postcondition:
*     Values set.
*
************************************************************************/
template <typename V, typename E>
void ShortestPath<V, E>::CalculateAdjacency(int index)
{
	int location = 0;
	for (Edge<V, E> i : _vertices[index].GetList())
	{
		location = FindIndex(*i.GetVertex());
		if (!_processed[location])
		{
			int weight = i.GetWeight();
			if (_distance[location] < 0 || _distance[location] > weight + _distance[index])
			{
				_distance[location] = weight + _distance[index];
				_predecessor[location] = index;
			}
		}
	}
	_processed[index] = true;
}

/**********************************************************************
* Purpose: Finds index of a specified vertex.
*
* Precondition:
*     None
*
* Postcondition:
*     Index returned.
*
************************************************************************/
template <typename V, typename E>
int ShortestPath<V, E>::FindIndex(Vertex<V, E> key)
{
	int index = -1, count = 0;
	for (Vertex<V, E> i : _vertices)
	{
		if (i == key)
			index = count;
		++count;
	}
	return index;
}

/**********************************************************************
* Purpose: Finds the edge between two vertices.
*
* Precondition:
*     Edge exists.
*
* Postcondition:
*     Edge returned.
*
************************************************************************/
template <typename V, typename E>
Edge<V, E> ShortestPath<V, E>::FindEdge(int origin, int destination)
{
	Edge<V, E> edge;
	bool found = false;
	for (Edge<V, E> i : _vertices[origin].GetList())
		if (*(i.GetVertex()) == _vertices[destination])
		{
			edge = i;
			found = true;
		}
	if (!found)
		throw Exception("Specified edge does not exist!");

	return edge;
}

#endif