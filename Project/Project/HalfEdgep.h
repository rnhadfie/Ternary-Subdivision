/*
Hafedge Structure
Stores and manipulates edge, vertex and face data.
Contains a vectors containing references to faces, vertexes, edges, and edge pairs.
Overloaded Constructor
 One constructor read information form a file, the second constructor reads data form existing objects.
 Contains method for subdivision.
*/

#ifndef HALFEDGE_H
#define HALFEDGE_H

#include <utility>  
#include "Vertex.h"
class HEdgeStruct
{
 public:
vector<Face*> Hef;
vector<Vertex*> Hev;
vector<Edge*> Hee;
vector<double> ePair;

HEdgeStruct(char ** );
HEdgeStruct(vector<double>,vector<Vertex*>);
vector<Vertex*> getVertices();
vector<Face*> getFace();
HEdgeStruct* createNewMask();
HEdgeStruct* subdivision();
void empty();


};
//HEdgeStruct * returnHEFile(char ** argv);

void isMaxOrMin(float n1,float n2,float n3);
int valance(Vertex*);
glm::vec3 returnMax();
glm::vec3 returnMin();
#endif

