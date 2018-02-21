/*****************************************************************************/
/*!
  Transform component. Holds the position and scale of the object.
*/
/*****************************************************************************/
#include "Transform.h"

//Components
#include "RigidBody.h"

//Systems
#include "Physics.h"

Transform::Transform()
{
  Initialize();
}

Transform::~Transform() { }

void Transform::Initialize()
{
  //Attach to the system here, and set id.
  ID = C_Transform;

  //Add to logic system.
  PHYSICS->RegisterComponent(this);

  //Init defaults to 0 or 1.
  pos = glm::vec3(0.f, 0.f, 0.f);
  nextPos = pos;
  scale = glm::vec3(1.f, 1.f, 1.f);
}

void Transform::Update(float dt)
{
  //Construct the transform matrix.
  //Translate to origin, scale, rotate, translate.
  transform = glm::mat4(); //reset transform.
  //transform = glm::translate(transform, -(pos));
  transform = glm::scale(transform, scale);
  transform = glm::translate(transform, pos / scale);
}

void Transform::Destroy()
{
  //Call the delete function on this.
  PHYSICS->DeleteComponent(this);
}

std::string Transform::Serialize()
{
  //Send out position and scale.
  std::string str;
  char* temp;
  int check;

  check = sprintf(temp, "%.3f %.3f %.3f\n", pos.x, pos.y, pos.z);
  str.append(temp);

  check = sprintf(temp, "%.3f %.3f %.3f", scale.x, scale.y, scale.z);
  str.append(temp);
}

void Transform::Deserialize(std::string str)
{
  //Get the position and scale.
  sscanf(str.c_str(), "%.3f %.3f %.3f %.3f %.3f %.3f",
    pos.x, pos.y, pos.z, scale.x, scale.y, scale.z);
}

void Transform::SetPosition(float x, float y, float z)
{
  pos = glm::vec3(x, y, z);
}

void Transform::MovePosition(float x, float y, float z)
{
  if (owner && owner->HasComponent(C_RigidBody))
  {
    RigidBody* temp = static_cast<RigidBody*>(owner->HasComponent(C_RigidBody));
    if (temp->IsStatic() == true)
      return;
  }

  pos += glm::vec3(x, y, z);
}

void Transform::SetScale(float x, float y)
{
  scale = glm::vec3(x, y, 1.f);
}

void Transform::SetScale(float x)
{
  scale = glm::vec3(x, x, 1.f);
}

glm::mat4 Transform::GetTransform() const
{
  return transform;
}

glm::vec3 Transform::GetPosition() const
{
  return pos;
}

glm::vec3 Transform::GetScale() const
{
  return scale;
}
