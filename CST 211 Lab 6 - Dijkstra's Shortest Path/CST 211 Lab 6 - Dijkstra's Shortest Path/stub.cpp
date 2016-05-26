#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

#include "ShortestPath.h"

#ifndef ATTEMPT
#include <iostream>
using std::cout; using std::endl;
#include "Exception.h"
#define ATTEMPT(function) try { function; } catch(Exception msg) { cout \
<< ">>\t Location: " << __LINE__ << "\tError: <" << msg << '>' << endl; }
#endif

using std::cin;
using std::ifstream;

#include <string>
using std::string;

#define BUF_LEN 1024

void Display(char *);

int main(int argc, char * argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Graph<string, string> graph;

	char full_input[BUF_LEN];
	string vertex_one;
	string vertex_two;
	string edge_title;
	int edge_weight = 0;
	char * token = nullptr;

	cout << endl
		<< "  Type 'EXIT' for either the origin or destination to quit!"
		<< endl;

	ifstream fin("locations.txt");
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			fin.getline(full_input, sizeof(full_input) / sizeof(char));

			token = strtok(full_input, ",");
			vertex_one = token;

			token = strtok(nullptr, ",");
			vertex_two = token;

			token = strtok(nullptr, ",");
			edge_title = token;

			token = strtok(nullptr, ",");
			edge_weight = atoi(token);

			try
			{
				graph.InsertVertex(vertex_one);
			}
			catch (...) {}
			try
			{
				graph.InsertVertex(vertex_two);
			}
			catch (...) {}
			try
			{
				graph.InsertEdge(vertex_one, vertex_two, edge_title, edge_weight);
			}
			catch (...) {}
		}
		fin.close();
	}
	else
		throw Exception("File could not open!");

	char origin[BUF_LEN]{ '\0' }, destination[BUF_LEN]{ '\0' };

	bool exit = false;
	while (!exit)
	{
		cout << endl;
		do
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << "  Enter an origin: ";
		} while (!cin.getline(origin, BUF_LEN) || !strlen(origin));
		if (stricmp(origin, "EXIT") == 0)
			exit = true;

		if (!exit)
		{
			do
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "  Enter a destination: ";
			} while (!cin.getline(destination, BUF_LEN) || !strlen(origin));
			if (stricmp(destination, "EXIT") == 0)
				exit = true;
		}
		if (!exit)
		{
			cout << endl;
			try
			{
				ShortestPath<string, string> path(graph, origin);
				path.RouteTo(destination);
			}
			catch (Exception(msg))
			{
				cout << "  " << msg << endl;
			}
		}
	}

	//a.InsertVertex(1);
	//a.InsertVertex(2);
	//a.InsertVertex(3);
	//a.InsertVertex(4);
	//a.InsertVertex(5);
	//a.InsertVertex(6);
	//a.InsertVertex(7);
	//a.InsertVertex(8);
	//a.InsertVertex(9);
	//a.InsertEdge(1, 2, "1 to 2", 3);
	//a.InsertEdge(1, 3, "1 to 3", 4);
	//a.InsertEdge(2, 3, "2 to 3", 3);
	//a.InsertEdge(2, 4, "2 to 4", 7);
	//a.InsertEdge(4, 5, "4 to 5", 9);
	//a.InsertEdge(4, 6, "4 to 6", 6);
	//a.InsertEdge(5, 7, "5 to 7", 16);
	//a.InsertEdge(5, 9, "5 to 9", 3);
	//a.InsertEdge(6, 9, "6 to 9", 8);
	//a.InsertEdge(7, 8, "7 to 8", 2);
	//a.InsertEdge(7, 9, "7 to 9", 10);

	//ShortestPath<int, char *> b(a, 5);
	//cout << "  Distance travelled: "
	//	<< b.RouteTo(2)
	//	<< endl;

	//ATTEMPT(cout << b.RouteTo(1) << endl);

	return 0;
}

void Display(char * str)
{
	cout << str << endl;
}