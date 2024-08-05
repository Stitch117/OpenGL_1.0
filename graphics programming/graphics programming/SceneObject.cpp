#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, Texture2D* texture)
{
	m_texture = texture;
	m_mesh = mesh;
}

SceneObject::~SceneObject()
{

}

void SceneObject::Update()
{

}

void SceneObject::Draw()
{

}