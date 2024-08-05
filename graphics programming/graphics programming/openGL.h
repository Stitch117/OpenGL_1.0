#pragma once
#include "GLUTcallbacks.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h" 
#include "Structures.h"
#include "Cube.h"
#include "staticObjects.h"
#include "MeshLoader.h"
#include "OBJLoader.h"
#include "Player.h"

#define REFRESHRATE 16

class openGL
{
public:

	openGL(int argc, char* argv[]);

	~openGL(void);

	void InitObjects();
	void InitLighting();
	void InitGL(int argc, char* argv[]);

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);

	void DrawString(const char* text, Vector3* position, Color* color);

private: 
	Camera* camera;

	Vector4* m_lightPosition;
	Lighting* m_lightData;

	SceneObject* objects[250];
};

