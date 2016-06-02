
#include "Object.h"

using namespace std;

vector<double> faceIndices;
vector<GLfloat> vertices;
string fileName;
int readFile(int argc, char ** argv){
	if (argc<2)
	{
		cout<< "Usage "<<argv[0]<<" filename\n";
    		return -1;
	}
	ifstream reader (argv[1]);
	if(!reader.is_open())
	{
		cout<<"file not open\n";
		return -1;
	}
	return 1;
}

