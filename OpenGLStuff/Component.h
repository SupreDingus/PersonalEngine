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
#include <fstream> //File IO
#include <string> //String
#include <cstdio> //sprintf

class Component
{
public:
  virtual void Initialize() = 0; //Initialize the stuff.
  virtual void Update(float) = 0; //Update loop.
  virtual void Destroy() = 0; //Free necessary stuff.

  //Serialization functions.
  virtual std::string Serialize() = 0; //Send out.
  virtual void Deserialize(std::string) = 0; //Read in.
  virtual std::string GetCompName() = 0; //Get name.

  //Have an owner pointer and ID.
  GameObject* owner;
  CompID ID;
};
