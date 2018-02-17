/*****************************************************************************/
/*!
  Collider, attempt 2. Checks for, and resolves, collision.
*/
/*****************************************************************************/
#include "Collider.h"

//Components
#include "Transform.h"
#include "RigidBody.h"

//Systems
#include "Physics.h"

//STL
#include <algorithm>

//Defines
#define CORRECTION 0.8f

using namespace glm;

Collider::Collider()
{
  //Init pointers
  body = nullptr;
  trans = nullptr;

  Initialize();
}

Collider::~Collider() { }

void Collider::Initialize()
{
  //Get the transform and rigidbody.
  if (owner)
  {
    SetBody();
    SetTransform();
  }

  //Set bottomLeft and topRight using transform.
  if (trans)
  {
    vec3 temp = trans->GetPosition();
    vec3 scale = trans->GetScale();

    bottomLeft = vec2(temp.x - (scale.x / 2.f), temp.y - (scale.y / 2.f));
    topRight = vec2(temp.x + (scale.x / 2.f), temp.y + (scale.y / 2.f));
  }

  //Set basic mass and restitution.
  mass = 1.f;
  invertMass = 1.f;
  restitution = 1.f;

  //Not colliding at the start.
  colliding = false;

  //Set the correct extents.
  xExtent = topRight.x - bottomLeft.x;
  yExtent = topRight.y - bottomLeft.y;

  //Put in physics, give id.
  PHYSICS->RegisterComponent(this);
  ID = C_Collider;
}

void Collider::Update(float dt)
{
  //Update alongside the transform.
  if (trans)
  {
    colliding = false;

    vec3 temp = trans->GetPosition();
    vec3 scale = trans->GetScale();

    bottomLeft = vec2(temp.x - (scale.x / 2.f), temp.y - (scale.y / 2.f));
    topRight = vec2(temp.x + (scale.x / 2.f), temp.y + (scale.y / 2.f));

    //Check for collisions.
    CheckCollision(dt);
  }
}

void Collider::Destroy()
{
  //Call the delete function.
  PHYSICS->DeleteComponent(this);
}

std::string Collider::Serialize()
{
  //Values that will be put in file: mass, restitution, and AABB corners.
  //Put each value on it's own line.
  std::string str;
  char* temp;
  int check;

  //Use sprintf to put the floats in the char.
  check = sprintf(temp, "%.3f\n%.3f\n", mass, restitution);
  str.append(temp);
}

void Collider::Deserialize(std::string)
{
  //Extract mass, restitution, and AABB corners from the file.
  file >> mass;
  file >> restitution;
  file >> bottomLeft.x;
  file >> bottomLeft.y;
  file >> topRight.x;
  file >> topRight.y;

  //Calculate other values based on given ones.
  invertMass = 1.f / mass;
  xExtent = abs(topRight.x - bottomLeft.x);
  yExtent = abs(topRight.y - bottomLeft.y);

  //Set relevent components.
  SetBody();
  SetTransform();
}

RigidBody* Collider::GetRigidBody() const
{
  return body;
}

void Collider::SetBody()
{
  body = static_cast<RigidBody*>(owner->HasComponent(C_RigidBody));
}

Transform* Collider::GetTransform() const
{
  return trans;
}

void Collider::SetTransform()
{
  trans = static_cast<Transform*>(owner->HasComponent(C_Transform));

  if (trans)
  {
    //Set corners.
    vec3 temp = trans->GetPosition();
    vec3 scale = trans->GetScale();

    bottomLeft = vec2(temp.x - (scale.x / 2.f), temp.y - (scale.y / 2.f));
    topRight = vec2(temp.x + (scale.x / 2.f), temp.y + (scale.y / 2.f));

    //Set extents based on corners.
    xExtent = topRight.x - bottomLeft.x;
    yExtent = topRight.y - bottomLeft.y;
  }
}

float Collider::GetMass() const
{
  return mass;
}

float Collider::GetInvertMass() const
{
  return invertMass;
}

void Collider::SetMass(float a)
{
  mass = a;

  //Don't divide by 0.
  if (mass != 0)
    invertMass = 1 / mass;
  else
    invertMass = 0.f;
}

float Collider::GetRestitution() const
{
  return restitution;
}

void Collider::SetRestitution(float a)
{
  restitution = a;
}

vec2* Collider::GetCorners() const
{
  vec2 ret[2];
  ret[0] = bottomLeft;
  ret[1] = topRight;

  return ret;
}

void Collider::GetExtents(float* ret) const
{
  ret[0] = xExtent;
  ret[1] = yExtent;
}

void Collider::SetCorners(vec2 bl, vec2 tr)
{
  bottomLeft = bl;
  topRight = tr;

  //Calculate new extents.
  xExtent = tr.x - bl.x;
  yExtent = tr.y - bl.y;
}

bool Collider::IsColliding() const
{
  return colliding;
}

Manifold Collider::GetManifold() const
{
  return man;
}

void Collider::CheckCollision(float dt)
{
  //Check against every other collider.
  for (auto it : PHYSICS->component_list)
  {
    //Check for no collider, skip self.
    if (it->ID != C_Collider || it == this)
      continue;

    //Make it a collider.
    Collider* temp = static_cast<Collider*>(it);

    //Create a manifold.
    //Manifold man;
    man.A = this;
    man.B = temp;
    man.depth = 0.f;
    man.restitution = min(restitution, temp->restitution);
    man.invMassSum = GetInvertMass() + temp->GetInvertMass();
    man.normal = vec2(0.f);

    //Check for skip.
    if (man.A->GetRigidBody()->IsStatic() && man.B->GetRigidBody()->IsStatic())
      continue;

    //Check for collision.
    if (!(CheckManifold(&man)))
    {
      continue;
    }

    //If we got here, they are colliding.
    colliding = true;
    ResolveSinking(man);
    ResolveCollisions(man, dt);
  }
}

bool Collider::CheckManifold(Manifold* man)
{
  //Use this to hold the objects easier.
  Collider* tempA = man->A;
  Collider* tempB = man->B;

  //Get the velocity from one position to another.
  vec2 n = tempB->GetTransform()->GetPosition() - tempA->GetTransform()->GetPosition();

  //Get extents.
  float* aExes = new float[2];
  float* bExes = new float[2];

  tempA->GetExtents(aExes);
  tempB->GetExtents(bExes);

  //Calculate half x-extents.
  float aX = aExes[0] / 2.f;
  float bX = bExes[0] / 2.f;

  //Calculate x overlap, if there is any.
  float xOverlap = aX + bX - abs(n.x);

  if (xOverlap > 0.f)
  {
    //Do the same for the y.
    float aY = aExes[1] / 2.f;
    float bY = aExes[1] / 2.f;

    float yOverlap = aY + bY - abs(n.y);

    if (yOverlap > 0.f)
    {
      //Check the for the smaller overlap.
      if (xOverlap < yOverlap)
      {
        //Use the right contact normal.
        if (n.x < 0.f)
        {
          man->normal = vec2(-1.f, 0.f);
        }
        else
        {
          man->normal = vec2(1.f, 0.f);
        }

        //Set the depth and return true.
        man->depth = xOverlap;
        return true;
      }
      else
      {
        //Do the same for other
        if (n.y < 0.f)
        {
          man->normal = vec2(0.f, -1.f);
        }
        else
        {
          man->normal = vec2(0.f, 1.f);
        }

        man->depth = yOverlap;
        return true;
      }
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

void Collider::ResolveCollisions(Manifold man, float dt)
{
  //Reflect the motion vector across collision normal, scale by bounciness.
  //Hold the movement vectors.
  vec3 aMove = man.A->GetRigidBody()->GetVelocity();
  vec3 bMove = man.B->GetRigidBody()->GetVelocity();

  //Check the normal.
  if (man.normal.y != 0)
  {
    //If collision normal goes up or down, switch they y and scale it.
    if (!man.A->GetRigidBody()->IsStatic())
    {
      aMove.y *= -man.restitution;
    }
    if (!man.B->GetRigidBody()->IsStatic())
    {
      bMove.y *= -man.restitution;
    }
  }
  else
  {
    if (!man.A->GetRigidBody()->IsStatic())
    {
      aMove.x *= -man.restitution;
    }
    if (!man.B->GetRigidBody()->IsStatic())
    {
      bMove.x *= -man.restitution;
    }
  }

  //Reset them.
  man.A->GetRigidBody()->SetVelocity(aMove);
  man.B->GetRigidBody()->SetVelocity(bMove);
}

void Collider::ResolveSinking(Manifold man)
{
  //Calculate movement per mass.
  vec2 movePerMass = man.normal * (man.depth / man.invMassSum) * CORRECTION;
  vec3 move = vec3(movePerMass, 0.f);

  //Move positions accordingly.
  if (!man.A->GetRigidBody()->IsStatic())
  {
    vec3 check = -move * man.A->GetInvertMass();
    man.A->GetTransform()->MovePosition(check.x, check.y, check.z);
  }

  if (!man.B->GetRigidBody()->IsStatic())
  {
    vec3 check = move * man.B->GetInvertMass();
    man.B->GetTransform()->MovePosition(check.x, check.y, check.z);
  }
}
