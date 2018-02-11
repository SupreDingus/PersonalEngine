#pragma once
/*****************************************************************************/
/*!
  Transform component. Holds the position and scale of the object.
*/
/*****************************************************************************/
//My includes.
#include "Component.h"
#include "Math.h"

//GLM
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//GL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Transform : public Component
{
public:
  Transform();
  ~Transform();

  //Component requirements.
  void Initialize();
  void Update(float dt);
  void Destroy();
  void Serialize(std::fstream file);
  void Deserialize(std::fstream file);

  //Change transform stuff here.
  void SetPosition(float, float, float);
  void MovePosition(float, float, float);

  void SetScale(float, float);
  void SetScale(float);

  //Get stuff.
  glm::mat4 GetTransform() const;
  glm::vec3 GetPosition() const;
  glm::vec3 GetScale() const;

private:
  //Stuff for transforms.
  glm::vec3 pos, nextPos;
  glm::vec3 scale; //Only change x and y on this.
  glm::mat4 transform;
};
