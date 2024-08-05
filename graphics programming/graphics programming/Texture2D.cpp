#include "Texture2D.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTcallbacks.h"
#include "openGL.h"

#include <iostream>
#include <fstream>

using namespace std;

Texture2D::Texture2D()
{

}

Texture2D::~Texture2D()
{
	//delete texture
	glDeleteTextures(1, &m_ID);
}

bool Texture2D::Load(char* path, int width, int height)
{
	char* tempTextureData;
	int fileSize;
	ifstream inFile;

	m_height = height;
	m_width = width;

	//get path for file
	inFile.open(path, ios::binary);

	//error check to check the file is open
	if (!inFile.good())
	{
		cerr << "Can't load texture file " << path << endl;
		return false;
	}

	inFile.seekg(0, ios::end); //seek all of the file
	fileSize = (int)inFile.tellg(); //current position - end of file : gives total file size
	tempTextureData = new char[fileSize]; //create array of texture data
	inFile.seekg(0, ios::beg); //set seek back to start
	inFile.read(tempTextureData, fileSize); // read all the data
	inFile.close();

	cout << path << "loaded" << endl;

	glGenTextures(1, &m_ID); // generate the next texture
	glBindTexture(GL_TEXTURE_2D, m_ID); //bind a texture to the ID
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

	delete[] tempTextureData;
	return true;
}