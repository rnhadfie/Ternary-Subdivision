#include "Window.h"
#include "Object.h"
#include "HalfEdgep.h"
#include "GL/glu.h"
#include "Edge.h"
#include "Vertex.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
using namespace glm;
int dm=0;

void setup(int w, int h)
{
	vec3 max=returnMax();
	vec3 min=returnMin();
	vec3 center = (max + min) * 0.5f;
  	float radius = length (max - min) * 0.5f;
	glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
        glMatrixMode(GL_PROJECTION_MATRIX);
	
        glLoadIdentity();
      	gluPerspective(60,800/800*1.0f,0.1,100);

        glMatrixMode(GL_MODELVIEW_MATRIX);
	glTranslatef(0.0f,0.0f,-center.z-3);
  	glRotatef(6.0f,1.0f,0.0f,0.0f);
	float s=0.95f/radius;
	glScalef(s,s,s);
    
}

void drawObj(HEdgeStruct* h)
{
	vector<Face*> faces=h->getFace();
	for(int i=0; i<faces.size(); i++)
	{
		
		glBegin(GL_TRIANGLES);
		Vertex v=*(*faces[i]->edge).vert;
		glVertex3f(v.x,v.y,v.z);
		v=*(*(*faces[i]->edge).next).vert;
		glVertex3f(v.x,v.y,v.z);
		v=*(*(*(*faces[i]->edge).next).next).vert;
		glVertex3f(v.x,v.y,v.z);
		glEnd();
	}
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	//cout<<"Object data has been displayed\n";
}
	
double findVertex(vector<Vertex*> vert, Vertex v)
{
	for(double n=0; n<vert.size(); n++)
	{
		if(vert[n]->x==v.x && vert[n]->y==v.y && vert[n]->z==v.z )
			return n;
	}
	return -1.0;
}
void saveObj(HEdgeStruct* h)
{
	vector<Face*> faces=h->getFace();
	vector<Vertex*> vertex=h->getVertices();
	
	ofstream newObj("new.obj");
	if(!newObj)
	{
			cout<<"Test: new.obj...\nnew.obj cannot open.\n";
			return;
	}
	newObj<<"#"<<"Test"<<endl;
	newObj<<"#Number of Vertices: "<<vertex.size()<<endl;
	newObj<<"#Number of Faces: "<<faces.size()<<endl;
	for(int i=0; i<vertex.size(); i++)
	{
			newObj<<"v "<<vertex[i]->x<<" "<<vertex[i]->y<<" "<<vertex[i]->z<<endl;
	}
	newObj<<endl;
	for(int i=0; i<faces.size(); i++)
	{
		
		newObj<<"f ";
		Vertex v=*(*faces[i]->edge).vert;
		newObj<<findVertex(vertex,v)+1<<" ";
		v=*(*(*faces[i]->edge).next).vert;
		newObj<<findVertex(vertex,v)+1<<" ";
		v=*(*(*(*faces[i]->edge).next).next).vert;
		newObj<<findVertex(vertex,v)+1<<endl;

	}
	newObj.close();
}

int main(int argc, char ** argv){
  	//Creating Window/*
	GLFWwindow* window=setupWindow();
		//Draws the Window
	int s=readFile(argc,argv);
	if(s==-1)
		return 1;
	HEdgeStruct* h=new HEdgeStruct(argv);
	cout<<"HalfEdge data structure is loaded\n";
	while (!glfwWindowShouldClose(window))
	{
	      	
		GLint width, height;
	       	glfwGetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);
			
		setup(width, height);
		if(subDivTrue())
		{
			h=h->subdivision();
			cout<<"Subdivision compelete\n";
		}
	  	drawObj(h);	
		if(saveObjFile()){	
			saveObj(h);
			cout<<"Object data has Saved\n";
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//Terminates the window     
	glfwDestroyWindow(window);
	h->empty();
	h=NULL;
	delete h;
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
