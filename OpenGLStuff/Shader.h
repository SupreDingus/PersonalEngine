#pragma once
/*****************************************************************************/
/*!
  Shader header. Loads, compiles, and links shaders.
*/
/*****************************************************************************/
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//Can't forget glew, since this is still OpenGL.
#include <glad/glad.h>

class Shader
{
public:
  //We'll need the paths to the shaders to build them.
  Shader(const GLchar* vertexPath, const GLchar* fragPath);
  void Use(); //Uses the shader.

  void operator()(const GLchar* vertexPath, const GLchar* fragPath); //Builds the shader with the given files.
  
  //Set the uniform in the shader, if it exists. Overloaded function.
  void SetUniform(int var, const GLchar* name);
  void SetUniform(float var, const GLchar* name);

  GLuint program; //Shader program ID
};
