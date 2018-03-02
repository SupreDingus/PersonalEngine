/*****************************************************************************/
/*!
  Player controller. Makes the player do things.
*/
/*****************************************************************************/
#pragma once

//System includes.
#include "Input.h"
#include "Component.h"

//GLM
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Forward declarations.
class RigidBody;
class Collider;
class GroundDetection;

class PlayerController : public Component
{
public:
  PlayerController();
  ~PlayerController();
  PlayerController(const PlayerController& rhs) = delete;

  //Required component functions.
  void Initialize();
  void Update(float dt);
  void Destroy();

  std::string Serialize();
  void Deserialize(std::string);
  std::string GetCompName();

  //Setters, getters.
  void SetBody();
  glm::vec3 GetMove();

private:
  //Component pointers.
  RigidBody* body;
  Collider* collider;
  GroundDetection* ground;

  //Movement vector.
  glm::vec2 move;
};
