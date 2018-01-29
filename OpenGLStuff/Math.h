#pragma once
/*****************************************************************************/
/*!
  Math header. Has all the defines for the math structs that I need.
*/
/*****************************************************************************/
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Vec3
{
  float x;
  float y;
  float z;
};

struct Vec4
{
  float x;
  float y;
  float z;
  float w;
};

struct GLVec3
{
  GLfloat x;
  GLfloat y;
  GLfloat z;
};

struct GLVec4
{
  GLfloat x;
  GLfloat y;
  GLfloat z;
  GLfloat w;
};

void Normalize(Vec3&);
void Normalize(Vec4&);

void Normalize(GLVec3&);
void Normalize(GLVec4&);

Vec3 XYPerpendicular(Vec3);
