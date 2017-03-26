/*
Vertex stores a reference to an edge object, and x,y,and z values, and location value.
*/

#ifndef Vertex_H
#define Vertex_H


class Edge;
	class Vertex
	{
	public:
		Edge* edge;
		double x,y,z;	
		double loc;
		Vertex operator - (Vertex);
		Vertex operator + (Vertex);
		Vertex operator * (double);
		Vertex operator / (double);	
	};
	
	class Face
	{
	public:
		Edge* edge;	
	};

#endif

