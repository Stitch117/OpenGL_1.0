#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

class Player : public SceneObject
{
private:
	Material* m_material;
public:
	Vector3 m_position;

	Player(Mesh* mesh, float x, float y, float z); 
	~Player();

	void Draw();
	void Update();
	void SetPosition(Vector3 newPos);
	void SetMaterial();
	void Keyboard(unsigned char key, int x, int y);
};

