#include "OBJLoader.h"
#include <iostream>
#include <fstream>
#include<string>
#include<sstream>


using namespace std;

namespace OBJLoader
{
	Mesh* OBJLoader::OBJLoad(char* path)
	{
		//define new mesh
		Mesh* mesh = new Mesh();

		stringstream ss; //create string stream for storing obj file data
		ifstream inFile(path);
		string line = ""; //store line number
		string prefix = ""; //store the first letter

		int vertexNumber = 0;
		int indicieNumber = 0;
		int texCoordNumber = 0;
		int normalNumber = 0;

		while (getline(inFile, line))
		{
			ss.clear(); //reset the string stream
			ss.str(line);
			ss >> prefix;

			//set the number of each component 
			if (prefix == "v")
			{
				vertexNumber++;
			}
			else if (prefix == "f")
			{
				indicieNumber++;
			}
			else if (prefix == "vt")
			{
				texCoordNumber++;
			}
			else if (prefix == "vn")
			{
				normalNumber++;
			}
		}

		//create arrays of the size
		mesh->Vertices = new Vertex[vertexNumber];
		mesh->TexCoords = new TexCoord[texCoordNumber];
		mesh->Normals = new Vector3[normalNumber];
		mesh->Indices = new GLushort[indicieNumber*3];

		//go back to line one of file
		inFile.clear();
		inFile.seekg(0);

		Vertex tempVertex;
		TexCoord tempTexCoord;
		Vector3 tempNormal;
		GLushort tempIndicie;
		int counter1 = 0;
		int counter2 = 0;
		int counter3 = 0;
		int counter4 = 0;

		//chekc incase file didn't open correctly
		if (!inFile.is_open())
		{
			cout << "OBJ file could not load.";
		}

		//input the data from obj file
		while (getline(inFile, line))
		{
			ss.clear();
			ss.str(line);
			ss >> prefix;

			//store vertexes
			if (prefix == "v")
			{
				ss >> tempVertex.x >> tempVertex.y >> tempVertex.z;
				mesh->Vertices[counter1] = tempVertex;
				counter1++;
			}

			//store texstures
			else if (prefix == "vt")
			{
				ss >> tempTexCoord.u >> tempTexCoord.v;
				mesh->TexCoords[counter2] = tempTexCoord;
				counter2++;
			}

			//store normals
			else if (prefix == "vn")
			{
				ss >> tempNormal.x >> tempNormal.y >> tempNormal.z;
				mesh->Normals[counter3] = tempNormal;
				counter3++;
			}

			//store indicies
			else if (prefix == "f")
			{
				ss >> tempIndicie;
				mesh->Indices[counter4] = tempIndicie - 1;
				counter4++;

				ss >> tempIndicie;
				mesh->Indices[counter4] = tempIndicie - 1;
				counter4++;

				ss >> tempIndicie;
				mesh->Indices[counter4] = tempIndicie - 1;
				counter4++;
				
			}
			//ignore comments in the obj file
			else if (prefix == "#")
			{
				continue;
			}
		}

		return mesh;
	}
}
