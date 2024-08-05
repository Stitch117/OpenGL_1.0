#include "Cube.h"
#include <string>
#include <iostream>
#include <fstream>

void Cube::Draw()
{
	if (m_mesh->Vertices != nullptr && m_mesh->Normals != nullptr && m_mesh->Indices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, m_texture->GetID()); // bind texture to ID

		//enable client states
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnable(GL_NORMAL_ARRAY);

		//set pointers to start of arrays
		glVertexPointer(3, GL_FLOAT, 0, m_mesh->Vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, m_mesh->TexCoords);
		glNormalPointer(GL_FLOAT, 0, m_mesh->Normals);

		//set the material
		setMaterial();
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(m_material->Ambient.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(m_material->Diffuse.x));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(m_material->Specular.x));
		glMaterialf(GL_FRONT, GL_SHININESS, m_material->Shininess);

		glEnable(GL_NORMALIZE);

		glPushMatrix();

		//draw the cubes
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(m_rotation, 1, 1, 0);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, m_mesh->Indices);

		glPopMatrix();

		//disable the client states
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}

void Cube::Update()
{
	//rotate every frame
	m_rotation += 1;

	//move cubes towards camers
	m_position.z ++;

	//reset position to back of screen when hitting the near frustrum
	if (m_position.z >= 1)
	{
		m_position.z = -300;
	}
}

Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

Cube::~Cube()
{

}

//set the material values
void Cube::setMaterial()
{
	m_material = new Material();
	m_material->Ambient.x = 0.25; m_material->Ambient.y = 0.25; m_material->Ambient.z = 0.25; m_material->Ambient.w = 1.0;
	m_material->Diffuse.x = 0.6; m_material->Diffuse.y = 0.6; m_material->Diffuse.z = 0.6; m_material->Diffuse.w = 1.0;
	m_material->Specular.x = 1; m_material->Specular.y = 1; m_material->Specular.z = 1; m_material->Specular.w = 1.0;
	m_material->Shininess = 300.0f;
}
