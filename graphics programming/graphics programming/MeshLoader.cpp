#include "MeshLoader.h"
#include <iostream>
#include <fstream>



using namespace std;

namespace MeshLoader
{
	//define the functions that will be used
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			//create array for vertexes
			mesh.Vertices = new Vertex[mesh.VertexCount];

			//get vertexes from text file
			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.NormalCount;

		//create array for normals
		mesh.Normals = new Vector3[mesh.NormalCount];

		//load normals from text file
		for (int i = 0; i < mesh.NormalCount; i++)
		{
			inFile >> mesh.Normals[i].x;
			inFile >> mesh.Normals[i].y;
			inFile >> mesh.Normals[i].z;

		}
	}

	void LoadTexCoords(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.TexCoordCount;

		//create array for texture co-ordinates
		mesh.TexCoords = new TexCoord[mesh.TexCoordCount];

		//load in texture co-ordinates from text file
		for (int i = 0; i < mesh.TexCoordCount; i++)
		{
			inFile >> mesh.TexCoords[i].u;
			inFile >> mesh.TexCoords[i].v;
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.IndexCount;

		//create array for indicies
		mesh.Indices = new GLushort[mesh.IndexCount];

		//load in indicies from the text file
		for (int i = 0; i < mesh.IndexCount; i++)
		{
			inFile >> mesh.Indices[i];
		}
	}

	Mesh* MeshLoader::Load(char* path)
	{
		//make a new mesh
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		//check for an error with the file path
		if (!inFile.good())
		{
			cerr << "Can't open text file " << path << endl;
			return nullptr;
		}

		//load in the information for the mesh
		LoadVertices(inFile, *mesh);
		LoadTexCoords(inFile, *mesh);
		LoadNormals(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		return mesh;
	}
}
