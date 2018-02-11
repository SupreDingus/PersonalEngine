/*****************************************************************************/
/*!
  Rigid body component. Handles physics stuff. Works with Transform and
    Collider.
*/
/*****************************************************************************/
#include "RigidBody.h"

#include "Transform.h"
#include "Collider.h"
#include "PlayerController.h"

#include "Physics.h"

#define GRAVITY 20.f
#define MAX_SPEED 50.f
#define FRICTION 0.8f
#define CLAMP 0.0001f

RigidBody::RigidBody()
{
  Initialize();
}

RigidBody::~RigidBody() { }

void RigidBody::Initialize()
{
  //Get the pointers, if possible.
  if (owner != nullptr)
  {
    trans = static_cast<Transform*>(owner->HasComponent(C_Transform));
    collide = static_cast<Collider*>(owner->HasComponent(C_Collider));
    player = static_cast<PlayerController*>(owner->HasComponent(C_PlayerController));
  }
  else
  {
    //Set to nothing for now.
    trans = nullptr;
    collide = nullptr;
    player = nullptr;
  }

  //Defaults: no velocity, static object, not bouncy, not grounded.
  velocity = glm::vec3(0.f, 0.f, 0.f);
  stat = true;
  bouncy = false;
  grounded = false;
  moving = false;

  //Set ID.
  ID = C_RigidBody;

  PHYSICS->RegisterComponent(this);
}

void RigidBody::Update(float dt)
{
  //If dynamic, move Transform's position based on velocity.
  if (trans && !stat)
  {
    //Scale down left/right, if not moving.
    if (moving)
    {
      velocity.x = velocity.x * .5f;
    }

    //If it's moving too fast, scale it back.
    if (velocity.length() > MAX_SPEED)
    {
      velocity = velocity * (velocity.length() / MAX_SPEED);
    }

    //Apply gravity.
    glm::vec3 grav(0.f, -GRAVITY, 0.f);
    velocity = velocity + grav;

    //Check for collisions first.
    if (collide)
    {
      collide->CheckCollision(dt);
    }

    //Check for player input.
    if (player)
    {
      if (player->GetMove() == glm::vec3(0.f, 0.f, 0.f))
      {
        ApplyFriction();
      }
      else
      {
        velocity += player->GetMove();
      }
    }
    
    trans->MovePosition(velocity.x * dt, velocity.y * dt, velocity.z * dt);
  }
}

void RigidBody::Destroy()
{
  //Transform will free itself.
  PHYSICS->DeleteComponent(this);
}

void RigidBody::Serialize(std::fstream file)
{
  //Input into the file of it's static and if it's bouncy.
  file << stat << std::endl;
  file << bouncy << std::endl;
}

void RigidBody::Deserialize(std::fstream file)
{
  //Get the static and bouncy bools.
  file >> stat;
  file >> bouncy;

  //Get relevent pointers.
  SetTransform();
  SetCollider();
  SetController();
}

Transform* RigidBody::GetTransform() const
{
  return trans;
}

glm::vec3 RigidBody::GetVelocity() const
{
  return velocity;
}

bool RigidBody::IsStatic() const
{
  return stat;
}

void RigidBody::SetVelocity(glm::vec3 vec)
{
  velocity = vec;
}

void RigidBody::AddVelocity(glm::vec3 vec)
{
  velocity += vec;
}

void RigidBody::ChangeStatic(bool change)
{
  stat = change;
}

void RigidBody::SetTransform()
{
  //Get the transform from the owner.
  if (owner != nullptr)
  {
    trans = static_cast<Transform*>(owner->HasComponent(C_Transform));
  }
}

void RigidBody::SetCollider()
{
  if (owner != nullptr)
  {
    collide = static_cast<Collider*>(owner->HasComponent(C_Collider));
  }
}

void RigidBody::SetController()
{
  if (owner != nullptr)
  {
    player = static_cast<PlayerController*>(owner->HasComponent(C_PlayerController));
  }
}

void RigidBody::ApplyFriction()
{
  //Reduce the x by FRICTION define.
  velocity.x *= FRICTION;

  //Clamp to 0 when it's slow enough.
  if (abs(velocity.x) <= CLAMP)
  {
    velocity.x = 0.f;
  }
}
