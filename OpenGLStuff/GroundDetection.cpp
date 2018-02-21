/*****************************************************************************/
/*!
  Ground detection. When colliding, checks to see if it's on the ground.
*/
/*****************************************************************************/
#include "GroundDetection.h"

//Systems.
#include "Physics.h"

//Components.
#include "Transform.h"
#include "Collider.h"

//Defines.
#define EPSILON 0.001f;

GroundDetection::GroundDetection()
{
  Initialize();
}

GroundDetection::~GroundDetection() { }

void GroundDetection::Initialize()
{
  grounded = false;

  //Get the components, if possible.
  if (owner)
  {
    trans = static_cast<Transform*>(owner->HasComponent(C_Transform));
    collide = static_cast<Collider*>(owner->HasComponent(C_Collider));
  }
  else
  {
    trans = nullptr;
    collide = nullptr;
  }

  ID = C_GroundDetection;
  PHYSICS->RegisterComponent(this);
}

void GroundDetection::Update(float dt)
{
  //Check for skip.
  if (trans == nullptr || collide == nullptr)
  {
    grounded = false;
    return;
  }

  //Check for grounded.
  //First check to see if we're colliding.
  if (!collide->IsColliding())
  {
    grounded = false;
    return;
  }

  //They're colliding.
  //Get relevant points. A == this, B == other.
  Manifold man = collide->GetManifold();
  Transform* otherTrans = man.B->GetTransform();

  float otherTop = otherTrans->GetPosition().y + (otherTrans->GetScale().y / 2.f);
  float otherLeft = otherTrans->GetPosition().x - (otherTrans->GetScale().x / 2.f);
  float otherRight = otherTrans->GetPosition().x + (otherTrans->GetScale().x / 2.f);

  float thisBot = trans->GetPosition().y - (trans->GetScale().y / 2.f) + EPSILON;
  float thisLeft = trans->GetPosition().x - (trans->GetScale().x / 2.f) + EPSILON;
  float thisRight = trans->GetPosition().x + (trans->GetScale().x / 2.f) - EPSILON;

  //Check values, set grounded.
  if (otherTop >= thisBot)
  {
    if (otherLeft >= thisRight || otherRight >= thisLeft)
    {
      grounded = true;
      return;
    }
  }
}

void GroundDetection::Destroy()
{
  //Call delete on this component.
  PHYSICS->DeleteComponent(this);
}

std::string GroundDetection::Serialize()
{
  //Nothing needs to be sent to the file.
  std::string str;
  return str;
}

void GroundDetection::Deserialize(std::string str)
{
  //Set relevent components.
  SetTransform();
  SetCollider();
}

bool GroundDetection::IsGrounded() const
{
  return grounded;
}

void GroundDetection::ChangeGrounded()
{
  grounded = !grounded;
}

void GroundDetection::SetTransform()
{
  if (owner)
  {
    trans = static_cast<Transform*>(owner->HasComponent(C_Transform));
  }
}

void GroundDetection::SetCollider()
{
  if (owner)
  {
    collide = static_cast<Collider*>(owner->HasComponent(C_Collider));
  }
}
