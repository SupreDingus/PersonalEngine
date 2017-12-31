/*****************************************************************************/
/*!
  Physics system. Handles physics calculations, such as velocity and gravity.
  Also handles collisions.
*/
/*****************************************************************************/

#include "Physics.h"

Physics* PHYSICS = nullptr;

Physics::Physics() { }
Physics::~Physics() { }

void Physics::Initialize()
{
  PHYSICS = this;
}

void Physics::Update(float dt)
{
  //Update each component.
  if (!component_list.empty())
  {
    for (unsigned i = 0; i < component_list.size(); ++i)
    {
      component_list[i]->Update(dt);
    }
  }
}

void Physics::Destroy()
{
  //Delete and free each component.
  component_list.erase(component_list.begin(), component_list.end());
}

void Physics::RegisterComponent(Component* comp)
{
  component_list.push_back(comp);
}

void Physics::DeleteComponent(Component* comp)
{
  unsigned pos = 0;

  //Find the component in the vector.
  for (auto it : component_list)
  {
    if (comp == it)
    {
      //Use the erase function.
      component_list.erase(component_list.begin() + pos);
      return;
    }
    else
    {
      pos++;
    }
  }
}
