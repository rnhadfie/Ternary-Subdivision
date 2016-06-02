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
