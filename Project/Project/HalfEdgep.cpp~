#include "Window.h"
#include "Object.h"
#include "HalfEdgep.h"
#include "GL/glu.h"
#include "Edge.h"
#include "Vertex.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>
#include <cmath>




glm::vec3 maxvec;
glm::vec3 minvec;
double alpha=5.0/9.0;
double mew=1.0/3.0;
const double PI = atan(1) * 4;
double beta=alpha-pow(mew,2);
using namespace std;
using namespace glm;

Vertex Vertex::operator- (Vertex p){
    Vertex v;
	v.x=x-p.x;
	v.y=y-p.y;
	v.z=z-p.z;
    return v;   
}

Vertex Vertex::operator* (double p){
    Vertex v;
	v.x=x*p;
	v.y=y*p;
	v.z=z*p;
    return v;   
}

Vertex Vertex::operator/ (double p){
    Vertex v;
	v.x=x/p;
	v.y=y/p;
	v.z=z/p;
    return v;   
}

Vertex Vertex::operator+ (Vertex p){
    Vertex v;
	v.x=x+p.x;
	v.y=y+p.y;
	v.z=z+p.z;
    return v;   
}

double getIt(double x,double y, vector<double> pair)
{
	for(int i=0; i<pair.size(); i+=2)
	{
		
		if(pair[i]==y && pair[i+1]==x)
			return i/2;
	}
	return -1;
}


void HEdgeStruct::empty()
{
	for(int i=0; i<Hef.size(); i++)
	{
		Hef[i]=NULL;
		delete Hef[i];
	}
	for(int i=0; i<Hee.size(); i++)
	{
		Hee[i]=NULL;
		delete Hee[i];
	}
	for(int i=0; i<Hev.size(); i++)
	{
		Hev[i]=NULL;
		delete Hev[i];
	}
}

HEdgeStruct::HEdgeStruct(char ** argv)
{
	//vector<float> vert=returnVerticesList();
	vector<double> fac;
	ifstream reader (argv[1]);
	cout<<"Reading file\n";
	char c [256];
	//fileName=argv[1];
	while(reader.peek()=='#')
	{
		reader.getline(c, 256);        
	}
	//Reads the file while it is possible to read characters
	//if the charater is ‘v’ the next 3 character are vector data, else if its a ‘f’ the next three characters are face data

	char s;
	while(reader>>s)
	{
		if(s=='v')
		{
			double v1,v2,v3;
			reader>>v1;
			reader>>v2;
			reader>>v3;

			Vertex* v=new Vertex;
			v->x=v1;
			v->y=v2;
			v->z=v3;
			Hev.push_back(v);
			isMaxOrMin(v1,v2,v3);
		}
		else if(s=='f')
		{
			
			double f;
			reader>>f;
			fac.push_back(--f);
			reader>>f;
			fac.push_back(--f);
			reader>>f;
			fac.push_back(--f);
		}
	}
	reader.close();
	
	for(int i=0; i<fac.size(); i+=3)
	{
		Edge* e1=new Edge;
		Edge* e2=new Edge;
		Edge* e3=new Edge;
		
		Face* f=new Face;
		f->edge=e1;
		
		e1->face=f;
		e2->face=f;
		e3->face=f;
		
		e1->vert=Hev[fac[i]];
		e2->vert=Hev[fac[i+1]];
		e3->vert=Hev[fac[i+2]];
		Hev[fac[i]]->edge=e1;
		Hev[fac[i+1]]->edge=e2;
		Hev[fac[i+2]]->edge=e3;
		
		e1->next=e2;
		e2->next=e3;
		e3->next=e1;

		e1->prev=e3;
		e2->prev=e1;
		e3->prev=e2;

		e1->pair=NULL;
		e2->pair=NULL;
		e3->pair=NULL;

		ePair.push_back(fac[i]); ePair.push_back(fac[i+1]);
		ePair.push_back(fac[i+1]); ePair.push_back(fac[i+2]);
		ePair.push_back(fac[i+2]); ePair.push_back(fac[i]);
		
		double val=getIt(fac[i],fac[i+1],ePair);
		
		if(val!=-1.0)
		{
			e1->pair=Hee[val];
			Hee[val]->pair=e1;
			
		}
		val=getIt(fac[i+1],fac[i+2],ePair);
	
		if(val!=-1.0)
		{
			e2->pair=Hee[val];
			Hee[val]->pair=e2;
			
		}

		val=getIt(fac[i+2],fac[i],ePair);
		
		if(val!=-1.0)
		{
			e3->pair=Hee[val];
			Hee[val]->pair=e3;
			
		}
		Hee.push_back(e1);
		Hee.push_back(e2);
		Hee.push_back(e3);
		Hef.push_back(f);
				
		
	}
	
			
}

HEdgeStruct::HEdgeStruct(vector<double> fac, vector<Vertex*> vt)
{
	Hev=vt;
	for(int i=0; i<fac.size(); i+=3)
	{
		Edge* e1=new Edge;
		Edge* e2=new Edge;
		Edge* e3=new Edge;
		
		Face* f=new Face;
		f->edge=e1;
		
		e1->face=f;
		e2->face=f;
		e3->face=f;
		
		e1->vert=Hev[fac[i]];
		e2->vert=Hev[fac[i+1]];
		e3->vert=Hev[fac[i+2]];
		Hev[fac[i]]->edge=e1;
		Hev[fac[i+1]]->edge=e2;
		Hev[fac[i+2]]->edge=e3;
		
		e1->next=e2;
		e2->next=e3;
		e3->next=e1;

		e1->prev=e3;
		e2->prev=e1;
		e3->prev=e2;

		e1->pair=NULL;
		e2->pair=NULL;
		e3->pair=NULL;
		ePair.push_back(fac[i]); ePair.push_back(fac[i+1]);
		ePair.push_back(fac[i+1]); ePair.push_back(fac[i+2]);
		ePair.push_back(fac[i+2]); ePair.push_back(fac[i]);
		
		double val=getIt(fac[i],fac[i+1],ePair);
		//cout<<val<<"\n";
		if(val!=-1.0)
		{
			e1->pair=Hee[val];
			Hee[val]->pair=e1;
			
		}
		val=getIt(fac[i+1],fac[i+2],ePair);
		//cout<<val<<"\n";
		if(val!=-1.0)
		{
			e2->pair=Hee[val];
			Hee[val]->pair=e2;
			
		}

		val=getIt(fac[i+2],fac[i],ePair);
		
		if(val!=-1.0)
		{
			e3->pair=Hee[val];
			Hee[val]->pair=e3;
			
		}
		Hee.push_back(e1);
		Hee.push_back(e2);
		Hee.push_back(e3);
		Hef.push_back(f);

	}
}
vector<Vertex*> HEdgeStruct::getVertices()
{
	return Hev;
}
vector<Face*> HEdgeStruct::getFace()
{
	return Hef;
}

double vExists(vector<Vertex*> ev,Vertex* v)
{
	for(double i=0.0; i<ev.size(); i++)
	{
		if(ev[i]->x==v->x && ev[i]->y==v->y && ev[i]->z==v->z)
			return i;
	}
	return -1.0;
}

double C(int n, int k)
{
	return cos((2*PI*k)/n);
}
double lamnda(int j, int n)
{
	if(j==0)
		return 1-beta;
	else if (j>0 && j<=3)
		return pow(mew, j);
	else if (j>n-4 && j<=n-1)
		return pow(mew, n-j);
	else
		return 0.0;
}

double Fn(int n, int k)
{
	double yk;
	yk=lamnda(0,n)*C(n,0);
	
	int h=ceil((double)n/2);
	for(int j=1; j<h; j++)
	{
		yk+=2*lamnda(j,n)*C(n,j*k);
		
	}
	if(n%2==0)
		yk+=lamnda(h,n)*C(n,h*k);
	
	return yk/n;
}
vector <double> weights(int n)
{
	vector<double> temp;

	for(int k=0; k<n; k++)
	{
		double yk=Fn(n, k);
		temp.push_back(yk);
	}
	return temp;
}
int valance(Vertex * v)
{
	int n=0;
	Edge* e=(v->edge)->pair;
	if(e==NULL)
		return 0;
	Edge* e0=e;
	if(e0==NULL)
		return 0;
	do
	{
		n++;
		e=(e->next)->pair;
		if(e==NULL)
			return n;
	}
	while(e0!=e);
	return n;
}
Vertex* vertexMask(Vertex* v)
{
	Vertex newV;
	newV.x=0; newV.y=0; newV.z=0;
	int n=valance(v);
	double m=(1-alpha)/n;
	Edge* e=(v->edge)->pair;
	newV=newV*alpha;
	Vertex* newVi=new Vertex;
	newVi->x=newV.x; newVi->y=newV.y; newVi->z=newV.z;
	if(e==NULL)
		return newVi;
	Edge* e0=e;
	if(e0==NULL)
		return newVi;
	do
	{
		n++;
		Vertex vi=*(e->vert);
		newV=newV+vi*m;
		e=(e->next)->pair;
		if(e==NULL){
			newVi->x=newV.x; newVi->y=newV.y; newVi->z=newV.z;
			return newVi;
		}
	}
	while(e0!=e);
	newVi->x=newV.x; newVi->y=newV.y; newVi->z=newV.z;
	return newVi;
}

Vertex* edgeMask(Edge* ed)
{
	Vertex tempE; 
	tempE.x=0; tempE.y=0; tempE.z=0;
	int n=valance(ed->vert);
	if(n==3)
		mew=1/9;
	vector<double> w=weights(n);
	
	Vertex* newEdge=new Vertex;
	newEdge->x=tempE.x; newEdge->y=tempE.y; newEdge->z=tempE.z;
	Edge* e=ed->pair;
	if(e==NULL)
		return newEdge;
	Edge* e0=e;
	if(e0==NULL)
		return newEdge;
	double b=0.0;
	int i=0;
	do
	{
		n++;
		Vertex vi=*(e->vert);
		tempE=tempE+vi*w[i];
		e=(e->next)->pair;
		if(e==NULL){
			newEdge->x=tempE.x; newEdge->y=tempE.y; newEdge->z=tempE.z;
			return newEdge;
		}
		b+=w[i];
		i++;
		
	}
	while(e0!=e && i<w.size());
	tempE=tempE+((*(ed->vert))*beta);
	newEdge->x=tempE.x; newEdge->y=tempE.y; newEdge->z=tempE.z;
	return newEdge;
	
}


Vertex* faceMask(Vertex* vn)
{	
	Edge* e=vn->edge;
	Vertex* f=new Vertex;
	Vertex p=(*vn)*(8/27);
	e=e->next;
	Vertex n=*(e->vert)*(8/27);
	e=e->next;
	Vertex v=*(e->vert)*(8/27);
	e=e->next;
	Edge * p0=e->pair;
	Vertex c;
	c=p+v+n;
	
	if(!(p0==NULL))
	{	
	Vertex pp=*(((p0->next)->next)->vert)*1/27;
	c=c+pp;
	}
	e=e->next;
	p0=e->pair;
	if(!(p0==NULL))
	{	
	Vertex pp=*(((p0->next)->next)->vert)*1/27;
	c=c+pp;
	}	
	e=e->next;
	p0=e->pair;
	if(!(p0==NULL))
	{	
	Vertex pp=*(((p0->next)->next)->vert)*1/27;
	c=c+pp;
	}	
	f->x=c.x;
	f->y=c.y;
	f->z=c.z;
	return f;
}
HEdgeStruct* HEdgeStruct::createNewMask()
{	
	
	vector<Vertex*>ev;
	
	vector<double>fac;
	for(int i=0; i<Hef.size(); i++)
	{
		
		Edge* e=Hef[i]->edge;
		vector<Vertex*>nv;
		
		for(int j=0; j<3; j++)
		{

			Vertex* p=new Vertex;
			Vertex* n=new Vertex;
			Vertex* nVer1=new Vertex;
			Vertex* nVer2=new Vertex;		
			nVer1=edgeMask(e);
			nVer2=edgeMask(e->prev);
			p=vertexMask(e->vert);
			n=vertexMask((e->next)->vert);
			
			Vertex n1=((*n)*(1.0/3.0)+(*p)*(2.0/3.0));
			Vertex n2=((*n)*(2.0/3.0)+(*p)*(1.0/3.0));
		/*
			nVer1->x=n1.x;
			nVer1->y=n1.y;
			nVer1->z=n1.z;
			
			nVer2->x=n2.x;
			nVer2->y=n2.y;
			nVer2->z=n2.z;
			*/
			
			if(vExists(ev,p)==-1.0)
				ev.push_back(p);
			if(vExists(ev,nVer1)==-1.0)
				ev.push_back(nVer1);
			if(vExists(ev,nVer2)==-1.0)
				ev.push_back(nVer2);
			
			isMaxOrMin(p->x,p->y,p->z);
			isMaxOrMin(nVer1->x,nVer1->y,nVer1->z);
			isMaxOrMin(nVer2->x,nVer2->y,nVer2->z);
			nv.push_back(p);
			nv.push_back(nVer1);
			nv.push_back(nVer2);
			e=e->next;
		}
		
		Edge* p1=e;
		Edge* p2=e->next;
		Edge* p3=p2->next;
		Vertex p=*(e->vert);
		Vertex n=*(p2->vert);
		Vertex v=*((p3->next)->vert);
		Vertex pp=*(((p1->pair)->next)->next)->vert;
		Vertex nn=*((((p2->pair)->next)->next)->vert);
		Vertex vn=*((((p3->pair)->next)->next)->vert);
		Vertex c=(p+v+n)*(8/27)+(pp+nn+vn)/27;
		
		Vertex* cn=new Vertex;
		cn=faceMask(e->vert);
		
		ev.push_back(cn);
		nv.push_back(cn);
		isMaxOrMin(cn->x,cn->y,cn->z);
		
		double e1=1.0;
		fac.push_back(vExists(ev,nv[0.0]));
		fac.push_back(vExists(ev,nv[1.0]));
		fac.push_back(vExists(ev,nv[8.0]));
		for(int k=0; k<5; k++)
		{
			if(k%2==0)
			{
				fac.push_back(vExists(ev,nv[e1++]));
				fac.push_back(vExists(ev,nv[e1]));
				fac.push_back(vExists(ev,nv[9.0]));
			}
			else
			{
				fac.push_back(vExists(ev,nv[e1++]));
				fac.push_back(vExists(ev,nv[e1++]));
				fac.push_back(vExists(ev,nv[e1]));
			}	
		}
		e1=1.0;
		for(int k=0; k<3; k++)
		{
			if(k==0)
			{
				fac.push_back(vExists(ev,nv[9.0]));
				fac.push_back(vExists(ev,nv[9.0-e1]));
				fac.push_back(vExists(ev,nv[e1]));
			}
			else if(k==1)
			{
				fac.push_back(vExists(ev,nv[9.0]));
				fac.push_back(vExists(ev,nv[9.0-(e1+3.0)]));
				fac.push_back(vExists(ev,nv[e1]));
			}
			else
			{
				fac.push_back(vExists(ev,nv[9.0]));
				fac.push_back(vExists(ev,nv[9.0-(e1-3.0)]));
				fac.push_back(vExists(ev,nv[e1++]));
			}
		e1+=3.0;	
		}
	}
	HEdgeStruct* n=new HEdgeStruct(fac,ev);
	return n;
}
HEdgeStruct* HEdgeStruct::subdivision()
{
	HEdgeStruct* n=createNewMask();
	return n;
}
void isMaxOrMin(GLfloat n1,GLfloat n2,GLfloat n3)
{
	if(n1>=maxvec.x)
		maxvec.x=n1;
	if(n1<=minvec.x)
		minvec.x=n1;
	if(n2>=maxvec.y)
		maxvec.y=n2;
	if(n2<=minvec.y)
		minvec.y=n2;
	if(n3>=maxvec.z)
		maxvec.z=n3;
	if(n3<=minvec.z)
		minvec.z=n3;	
}
glm::vec3 returnMax()
{
	return maxvec;
}
glm::vec3 returnMin()
{
	return minvec;
}

