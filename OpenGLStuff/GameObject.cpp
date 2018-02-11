/*****************************************************************************/
/*!
  Game object source file.
*/
/*****************************************************************************/
#include "Transform.h"
#include "Sprite.h"
#include "GameObject.h"

GameObject::GameObject() { }
GameObject::~GameObject()
{
  //Call destroy.
  Destroy();
}

void GameObject::CreateObject()
{
  //By default, give each object a transform and sprite.
  Transform* trans = new Transform;
  Sprite* sprite = new Sprite;

  AttachComponent(trans);
  AttachComponent(sprite);
}

Component* GameObject::HasComponent(CompID check)
{
  //Loop through the object's components.
  for (auto it : components)
  {
    //If we find it, return it.
    if (check == it->ID)
    {
      return it;
    }
  }

  //Otherwise, return nullptr.
  return nullptr;
}

void GameObject::AttachComponent(Component* add)
{
  //Set owner, and push onto component list.
  add->owner = this;
  components.push_back(add);
}

void GameObject::Destroy()
{
  //Call each component's destroy function.
  for (auto it : components)
  {
    if (!it)
      continue;

    it->Destroy();
  }
}

std::vector<Component*> GameObject::GetComponents()
{
  return components;
}

void GameObject::SetName(std::string str)
{
  name = str;
}

std::string GameObject::GetName()
{
  return name;
}
