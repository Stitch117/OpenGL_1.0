#include "Player.h"
#include <string>
#include <iostream>
#include <fstream>

Player::Player(Mesh* mesh, float x, float y, float z) : SceneObject(mesh, nullptr) 
{
	m_mesh = mesh;

	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

Player::~Player()
{

}

void Player::Draw()
{
	if (m_mesh->Vertices != nullptr && m_mesh->Normals != nullptr && m_mesh->Indices != nullptr)
	{
		//glBindTexture(GL_TEXTURE_2D, m_texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnable(GL_NORMAL_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, m_mesh->Vertices);
		//glTexCoordPointer(2, GL_FLOAT, 0, m_mesh->TexCoords);
		glNormalPointer(GL_FLOAT, 0, m_mesh->Normals);

		SetMaterial();
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(m_material->Ambient.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(m_material->Diffuse.x));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(m_material->Specular.x));
		glMaterialf(GL_FRONT, GL_SHININESS, m_material->Shininess);

		glEnable(GL_NORMALIZE);

		glPushMatrix();

		glTranslatef(m_position.x, m_position.y, m_position.z);

		glDrawElements(GL_TRIANGLES, 6320 * 3, GL_UNSIGNED_SHORT, m_mesh->Indices);

		glPopMatrix();

		//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}

void Player::Update()
{

}

void Player::SetPosition(Vector3 newPos)
{
	m_position = newPos;
}

void Player::SetMaterial()  
{
	m_material = new Material();
	m_material->Ambient.x = 1; m_material->Ambient.y = 1; m_material->Ambient.z = 1; m_material->Ambient.w = 1.0;
	m_material->Diffuse.x = 1; m_material->Diffuse.y = 1; m_material->Diffuse.z = 1; m_material->Diffuse.w = 1.0;
	m_material->Specular.x = 1; m_material->Specular.y = 1; m_material->Specular.z = 1; m_material->Specular.w = 1.0;
	m_material->Shininess = 300.0f;
}

//get keyboard inputs
void Player::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'w':
		m_position.y += 0.01;
		break;
	case 'a':
		m_position.x -= 0.01;
		break;
	case 's':
		m_position.y -= 0.01;
		break;
	case 'd':
		m_position.x -= 0.01;
		break;
	case 'q':
		m_position.z += 0.1;
		if (m_position.z <= -1)
		{
			m_position.z = -1;
		}
		break;
	case 'e':
		m_position.z -= 0.1;
		break;
	default:;
	}
}