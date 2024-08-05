#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

class staticObjects : public SceneObject
{
private:
	Vector3 m_position; 
public:
	staticObjects(Mesh* mesh, float x, float y, float z);
	~staticObjects();

	void Draw();
	void Update();
};

