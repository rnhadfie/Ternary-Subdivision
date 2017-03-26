/*
 Edge Class
 	Pair is a reference the adjcent edge object in the edge pair.
	Next and Prev are references to edge ojbect that are connected to the current edge.
	Vert is a reference to the edges's starting vertex
	face is a refernece to face the edge is connected to.
*/

#ifndef EDGE_H
#define EDGE_H
#include <vector>
class Vertex;

class Face;
	class Edge
	{
	public:
		Edge* pair;
		Edge* next;
		Edge* prev;
		Vertex* vert;
		Face* face;
	};

#endif
