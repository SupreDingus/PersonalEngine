#pragma once
/*****************************************************************************/
/*!
  Header for components.
*/
/*****************************************************************************/
#include "ComponentTypes.h"
#include "GameObject.h"
#include <fstream>

class Component
{
public:
  virtual void Initialize() = 0; //Initialize the stuff.
  virtual void Update(float dt) = 0; //Update loop.
  virtual void Destroy() = 0; //Free necessary stuff.

  virtual void Serialize(std::fstream file) = 0;

  //Have an owner pointer and ID.
  GameObject* owner;
  CompID ID;
};
