/*****************************************************************************/
/*!
  Graphics system header.
*/
/*****************************************************************************/
#pragma once

//OpenGL
#include <glad\glad.h>
#include <GLFW/glfw3.h>

//GLM
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream> //For debugging.
#include <fstream> //File i/o.
#include <map> //Buffer map.
#include <string> //For use with map.

//System includes.
#include "System.h"
#include "Shader.h"

class Buffer;

class GraphicsSystem : public System
{
public:
  GraphicsSystem();
  ~GraphicsSystem();

  void Initialize();
  void Update(float dt);
  void Destroy();
  void RegisterComponent(Component* comp);
  void DeleteComponent(Component* comp);

  Shader* GetShader() const;
  Buffer* GetBuffer(std::string name) const;

private:
  Shader* shader_;
  std::map<std::string, Buffer*> buffers_;
  glm::mat4 proj_;
  glm::mat4 view_;
};

extern GraphicsSystem* GRAPHICS;
