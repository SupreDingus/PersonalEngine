#pragma once
/*****************************************************************************/
/*!
  Header for components.
*/
/*****************************************************************************/
//My includes.
#include "ComponentTypes.h"
#include "GameObject.h"

//STL
#include <iostream> //File IO
#include <fstream>

class Component
{
public:
  virtual void Initialize() = 0; //Initialize the stuff.
  virtual void Update(float dt) = 0; //Update loop.
  virtual void Destroy() = 0; //Free necessary stuff.

  //Serialization functions.
  virtual void Serialize(std::ostream file) = 0;
  virtual void Deserialize(std::istream file) = 0;

  //Have an owner pointer and ID.
  GameObject* owner;
  CompID ID;
};
