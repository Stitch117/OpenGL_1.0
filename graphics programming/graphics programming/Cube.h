#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"


class Cube : public SceneObject
{
private:
	Vector3 m_position; 

	GLfloat m_rotation = 0.0;

	Material* m_material;

public:
	Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Cube();

	void Draw();
	void Update();
	void setMaterial(); 
};
