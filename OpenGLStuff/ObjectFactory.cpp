/*****************************************************************************/
/*!
Object factory. Creates objects.
*/
/*****************************************************************************/
#include "ObjectFactory.h"

ObjectFactory::ObjectFactory() { }
ObjectFactory::~ObjectFactory() { }

GameObject* ObjectFactory::CreateObject()
{
  //Create the object, return it.
  GameObject* obj = new GameObject;
  obj->CreateObject();

  return obj;
}

GameObject* ObjectFactory::CreateObjectAtPos(float x, float y)
{
  //Create an object.
  GameObject* obj = new GameObject;
  obj->CreateObject();

  //Move it.
  Transform* trans = static_cast<Transform*>(obj->HasComponent(C_Transform));
  trans->SetPosition(x, y, 0.f);

  return obj;
}

GameObject* ObjectFactory::CreateObjectAtPos(glm::vec2 vec)
{
  //Reuse function.
  return CreateObjectAtPos(vec.x, vec.y);
}
