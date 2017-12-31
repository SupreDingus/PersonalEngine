/*****************************************************************************/
/*!
  Rigid body component. Handles physics stuff. Works with Transform and
    Collider.
*/
/*****************************************************************************/
#pragma once

#include "Component.h"

//GLM
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform;
class Collider;
class PlayerController;

class RigidBody : public Component
{
public:
  RigidBody();
  ~RigidBody();
  RigidBody(const RigidBody& rhs) = delete;

  void Initialize();
  void Update(float dt);
  void Destroy();

  //Getters.
  Transform* GetTransform() const;
  glm::vec3 GetVelocity() const;
  bool IsStatic() const;

  //Setters.
  void SetVelocity(glm::vec3 vec);
  void AddVelocity(glm::vec3 vec);
  void ChangeStatic(bool change);
  void SetTransform();
  void SetCollider();
  void SetController();

  //Applies friction by reducing the x-axis.
  void ApplyFriction();

  //If true, it's moving.
  bool moving;

private:
  //Pointers to relevant components.
  Transform* trans;
  Collider* collide;
  PlayerController* player;

  //Velocity. Use with Transform's position.
  glm::vec3 velocity;

  //Static vs. Dynamic. Static objects (true) never move, dynamic objects (false) can.
  bool stat;

  //If the object is bouncy (used with dynamic)
  bool bouncy;

  //If the object is said to be on the ground. Used with player controller.
  bool grounded;
};
