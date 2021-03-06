/*****************************************************************************/
/*!
  Ground detection. When colliding, checks to see if it's on the ground.
*/
/*****************************************************************************/
#pragma once

#include "Component.h"

//Forward declarations.
class Transform;
class Collider;

class GroundDetection : public Component
{
public:
  //Standard component functions.
  GroundDetection();
  ~GroundDetection();
  GroundDetection(const GroundDetection& rhs) = delete;

  void Initialize();
  void Update(float dt);
  void Destroy();
  void Serialize(std::fstream file);
  void Deserialize(std::fstream file);

  //Returns true if the object is grounded.
  bool IsGrounded() const;

  //Change grounded status.
  void ChangeGrounded();

  //Set pointers.
  void SetTransform();
  void SetCollider();

private:
  //Bool for whether or not we're on the ground.
  bool grounded;

  //We'll need a collider and transform.
  Transform* trans;
  Collider* collide;
};
