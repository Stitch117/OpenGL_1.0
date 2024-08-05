#include "staticObjects.h"
#include <string>
#include <iostream>
#include <fstream>

staticObjects::staticObjects(Mesh* mesh, float x, float y, float z) : SceneObject(mesh, nullptr)
{
	m_mesh = mesh;

	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

staticObjects::~staticObjects()
{

}

void staticObjects::Draw()
{
	if (m_mesh->Vertices != nullptr && m_mesh->Normals != nullptr && m_mesh->Indices != nullptr)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnable(GL_NORMAL_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, m_mesh->Vertices);
		//glNormalPointer(GL_FLOAT, 0, m_mesh->Normals); 

		glPushMatrix();

		glTranslatef(m_position.x, m_position.y, m_position.z); 
		//draw the objects
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, m_mesh->Indices);

		glPopMatrix();

		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void staticObjects::Update()
{

}