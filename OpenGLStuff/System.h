#pragma once
/*****************************************************************************/
/*!
  Public system. All systems will inherit this.
*/
/*****************************************************************************/
#include <vector>
#include <map>
#include "Component.h"

class System
{
public:
  virtual void Initialize() = 0; //Initialize everything in the system.
  virtual void Update(float dt) = 0; //Used for update loop.
  virtual void Destroy() = 0; //Free each component.
  virtual void RegisterComponent(Component*) = 0; //Add to the component list.
  virtual void DeleteComponent(Component*) = 0; //Removes a component from the list.

  std::vector<Component*> component_list; //Use this to update relevant components.
};
