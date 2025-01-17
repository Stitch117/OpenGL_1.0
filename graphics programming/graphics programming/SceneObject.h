#pragma once 
#include "Structures.h"
#include "Texture2D.h"

class SceneObject
{
protected:
	Mesh* m_mesh;
	Texture2D* m_texture;  

public:
	SceneObject(Mesh* mesh, Texture2D* texture);
	virtual ~SceneObject();

	virtual void Update();
	virtual void Draw();
};

