#pragma once
#include <Windows.h>
#include <gl/GL.h> 

struct Vector3
{
public:
	float x;
	float y;
	float z;
};

struct Camera
{
public:
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};

struct Color
{
public:
	GLfloat r, g, b;
};

struct Vertex
{
public:
	GLfloat x, y, z;
};

struct Vector4
{
	float x, y, z, w;
};

struct Lighting 
{
	Vector4 Ambient, Diffuse, Specular;
};

struct Material
{
	Vector4 Ambient, Diffuse, Specular;
	GLfloat Shininess;
};

struct TexCoord
{
	GLfloat u, v;
};

struct Indices
{
	GLushort Indices;
};

struct Mesh
{
	Vertex* Vertices;
	Vector3* Normals;
	GLushort* Indices;
	TexCoord* TexCoords;
	int VertexCount, NormalCount, IndexCount, TexCoordCount;
};


