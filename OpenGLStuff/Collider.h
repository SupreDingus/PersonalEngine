/*****************************************************************************/
/*!
  Collider, attempt 2. Checks for, and resolves, collision.
*/
/*****************************************************************************/
#pragma once

#include "Component.h"

//GLM
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

//Forward declarations.
class Transform;
class RigidBody;
class Collider;

//Manifold. Use when checking collision.
struct Manifold
{
  Collider* A; //Objects that are colliding.
  Collider* B;
  float depth; //Penetration depth.
  float restitution; //Restitution.
  float invMassSum; //Sum of the inverse masses.
  vec2 normal; //Collision normal.
};

class Collider : public Component
{
public:
  Collider();
  ~Collider();
  Collider(const Collider& rhs) = delete;

  void Initialize();
  void Update(float dt);
  void Destroy();

  //Getters and Setters.
  RigidBody* GetRigidBody() const;
  void SetBody();

  Transform* GetTransform() const;
  void SetTransform();

  float GetMass() const;
  float GetInvertMass() const;
  void SetMass(float);

  float GetRestitution() const;
  void SetRestitution(float);

  vec2* GetCorners() const; //Returns [bottomLeft][topRight]
  void GetExtents(float*) const; //Returns [x][y]
  void SetCorners(vec2 bl, vec2 tr);

  bool IsColliding() const;

  Manifold GetManifold() const;

  //Core functionality.
  void CheckCollision(float dt);

private:
  bool CheckManifold(Manifold* man);

  void ResolveCollisions(Manifold man, float dt);
  void ResolveSinking(Manifold man);

  RigidBody* body;
  Transform* trans;

  //Mass.
  float mass;
  float invertMass;

  //Basically, the bouncyness factor.
  float restitution;

  //Use these points to check for collision.
  vec2 bottomLeft;
  vec2 topRight;

  //Extents are width/height.
  float xExtent;
  float yExtent;

  //True if colliding.
  bool colliding;

  //Manifold.
  Manifold man;
};
