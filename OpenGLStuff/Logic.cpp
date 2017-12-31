/*****************************************************************************/
/*!
  Logic system. Game logic, such as physics and AI, are handled here.
*/
/*****************************************************************************/
#include "Logic.h"

Logic* LOGIC = nullptr;

Logic::Logic()
{
  LOGIC = this;
}

Logic::~Logic() { }

void Logic::Initialize()
{
  //Nothing to do...?
}

void Logic::Update(float dt)
{
  if (!component_list.empty())
  {
    for (unsigned i = 0; i < component_list.size(); ++i)
    {
      component_list[i]->Update(dt);
    }
  }
}

void Logic::Destroy()
{
  //Destroy each component.
  for (auto it : component_list)
  {
    if (!it)
      continue;

    it->Destroy();
    delete it;
  }
}

void Logic::RegisterComponent(Component* add)
{
  component_list.push_back(add);
}

void Logic::DeleteComponent(Component* comp)
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
