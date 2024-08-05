#pragma once
#include "openGL.h" 
#include <iostream>
#include <string>
#include <fstream>

#define NUMOBJECTS 250

// set the window size constants
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 800;

Player* m_player = nullptr;

bool texturePenguins = false;

Texture2D* texture = new Texture2D();
Texture2D* texture2 = new Texture2D(); 

// load the cubes from a text file
Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");

//load the teapot from the obj file
Mesh* teapot = OBJLoader::OBJLoad((char*)"teapot.obj");

openGL::openGL(int argc, char* argv[])
{
	//initiate the openGL files
	InitGL(argc, argv); 

	InitLighting();

	//initialise the cubes and teapot
	InitObjects();

	glutMainLoop();
}

void openGL::InitGL(int argc, char* argv[])
{
	//initiate openGL
	GLUTcallbacks::Init(this);
	glutInit(&argc, argv);

	// help remove some of the flashing
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH); 

	// create window with size 800 by 800 to make a sqaure
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("test program");

	// call the disploay function
	glutDisplayFunc(GLUTcallbacks::Display);

	// call update 60 timea a second
	glutTimerFunc(REFRESHRATE, GLUTcallbacks::Timer, REFRESHRATE);

	// get keyboard inputs
	glutKeyboardFunc(GLUTcallbacks::Keyboard);

	glEnable(GL_NORMAL_ARRAY); 

	//make the lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//matrix load 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); //create the window
	gluPerspective(45, 1, 1, 1000);
	glMatrixMode(GL_MODELVIEW);

	//backface culling
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST); 
	glCullFace(GL_BACK);
}

void openGL::InitObjects()
{
	//load the penguin texture  
	texture->Load((char*)"Penguins.raw", 512, 512); 

	//load the stars texture
	texture2->Load((char*)"stars.raw", 512, 512);

	// cube creation
	for (int i = 0; i < NUMOBJECTS / 2; i++) //half stars texture
	{
		objects[i] = new Cube(cubeMesh, texture2, ((rand() % 400) / 3.0f) - 60.0f, ((rand() % 200) / 2.0f) - 30.0f, -(rand() % 300)); 
	}

	for (int i = NUMOBJECTS / 2; i < NUMOBJECTS - 1; i++) // half penguin texture
	{
		objects[i] = new Cube(cubeMesh, texture, ((rand() % 400) / 3.0f) - 60.0f, ((rand() % 200) / 2.0f) - 30.0f, -(rand() % 300));
	}

	//initialise teapot
	m_player = new Player(teapot, 0, 0, -40); 

	//set last item in array to player 
	objects[249] = m_player;

	//camera creation
	camera = new Camera;
	camera->eye.x = 0.0f;   camera->eye.y = 0.0f;    camera->eye.z = 1.0f;
	camera->center.x = 0.0f;   camera->center.y = 0.0f;    camera->center.z = 0.0f;
	camera->up.x = 0.0f;   camera->up.y = 1.0f;    camera->up.z = 0.0f;
}

openGL::~openGL(void) 
{
	delete(camera);

	//delete all the objects
	for (int i = 0; i < NUMOBJECTS; i++)
	{
		delete(objects[i]);
	}

	camera = nullptr;

	for (int i = 0; i < NUMOBJECTS; i++)
	{
		objects[i] = nullptr;
	}
}

int main(int argc, char* argv[]) 
{
	openGL* game = new openGL(argc, argv);

	glutMainLoop();

	return 0;
}

void openGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set vectors and colour for text display
	Vector3 v = { -0.2, 0.8, 0 };
	Vector3 v2 = { -0.25, 0.6, 0 };
	Vector3 v3 = { -0.3, 0.4, 0 };
	Vector3 v4 = { -0.3, 0.2, 0 };
	Vector3 v5 = { -0.2, -0.2, 0 };
	Color c = { 1.0, 1.0, 1.0 };

	//draw all the objects
	glPushMatrix(); 
	glEnable(GL_TEXTURE_2D);
	for (int i = 0; i < NUMOBJECTS; i++)
	{
		//disable the texture for the teapot so it shows up without lighting affecting it
		if (i == NUMOBJECTS - 1)
		{
			glDisable(GL_TEXTURE_2D); 
		}
		objects[i]->Draw();
	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//display text
	DrawString("OpenGL Program!", &v, &c);
	DrawString("number of objects: 250", &v2, &c);
	DrawString("teapot controls: w a s d q e", &v3, &c);
	DrawString("camera controls: i j k l u o", &v4, &c);
	DrawString("change texture: n", &v5, &c);

	glFlush();

	glutSwapBuffers();
}

void openGL::Update()
{
	glLoadIdentity();

	//set camera to look at base point
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera -> center.y, 
		camera->center.z, camera->up.x, camera->up.y, camera->up.z);

	glPushMatrix();

	//update all the objects
	for (int i = 0; i < 250; i++)
	{
		objects[i]->Update();

	}
	glPopMatrix();


	// update the screen with a new image
	glutPostRedisplay();
}
 
//get keyboard inputs
void openGL::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		//camera controls
	case 'l':
		camera->eye.x += 0.01;
		break;
	case 'j':
		camera->eye.x -= 0.01;
		break;
	case 'i':
		camera->eye.y += 0.01;
		break;
	case 'k':
		camera->eye.y -= 0.01;
		break;
	case 'u':
		camera->eye.z += 0.1;
		break;
	case 'o':
		camera->eye.z -= 0.1;
		break;

		//teapot controls
	case 'w':
		m_player->m_position.y += 0.1;
		break;
	case 'a':
		m_player->m_position.x -= 0.1;
		break;
	case 's':
		m_player->m_position.y -= 0.1;
		break;
	case 'd':
		m_player->m_position.x += 0.1;
		break;
	case 'q':
		m_player->m_position.z += 0.1;
		if (m_player->m_position.z >= -1)
		{
			m_player->m_position.z = -1;
		}
		break;
	case 'e':
		m_player->m_position.z -= 0.1;
		break;

		//change texture
	case 'n':

		//load the penguin texture
		texture->Load((char*)"Penguins.raw", 512, 512);

		//load the stars texture
		texture2->Load((char*)"stars.raw", 512, 512);

		//check if current texture is penguins
		if (texturePenguins == false)
		{
			//remake the cubes with a different texture
			for (int i = 0; i < NUMOBJECTS - 2; i++)
			{
				objects[i] = new Cube(cubeMesh, texture, ((rand() % 400) / 3.0f) - 60.0f, ((rand() % 200) / 2.0f) - 30.0f, -(rand() % 300));

			}
			texturePenguins = true;
		}
		else
		{
			for (int i = 0; i < NUMOBJECTS - 2; i++)
			{
				objects[i] = new Cube(cubeMesh, texture2, ((rand() % 400) / 3.0f) - 60.0f, ((rand() % 200) / 2.0f) - 30.0f, -(rand() % 300));

			}
			texturePenguins = false;
		}
	default:; 
	}
}

//draw he string to the screen
void openGL::DrawString(const char* text, Vector3* position, Color* color)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1); //setr boundry for text ; size of screen

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glTranslatef(position->x, position->y, position->z); // set position on screen
	glRasterPos2f(0.0f, 0.0f); // keep the text anchored to the screen
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void openGL::InitLighting()
{
	//set lighting
	m_lightPosition = new Vector4();
	m_lightPosition->x = 0.0;
	m_lightPosition->y = 0.0;
	m_lightPosition->z = 1.0;
	m_lightPosition->w = 0.0;

	m_lightData = new Lighting();
	m_lightData->Ambient.x = 0.2;
	m_lightData->Ambient.y = 0.2;
	m_lightData->Ambient.z = 0.2;
	m_lightData->Ambient.w = 1.0;

	m_lightData->Diffuse.x = 0.8;
	m_lightData->Diffuse.y = 0.8;
	m_lightData->Diffuse.z = 0.8;
	m_lightData->Diffuse.w = 1.0;

	m_lightData->Specular.x = 0.2;
	m_lightData->Specular.y = 0.2;
	m_lightData->Specular.z = 0.2;
	m_lightData->Specular.w = 1.0;

	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(m_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(m_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(m_lightData->Specular.x));

	glLightfv(GL_LIGHT0, GL_POSITION, &(m_lightPosition->x));
	glPopMatrix();
}



