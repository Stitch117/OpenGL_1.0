#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include "GLUTcallbacks.h"

class Texture2D
{
private:
	GLuint m_ID;
	int m_width, m_height;

public:
	Texture2D();
	~Texture2D();

	bool Load(char* path, int width, int height);

	GLuint GetID() const { return m_ID;  }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
};

