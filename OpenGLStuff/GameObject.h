/*****************************************************************************/
/*!
  Header for game objects. Game objects hold components.
*/
/*****************************************************************************/
#pragma once

//System.
#include "ComponentTypes.h"

//STL.
#include <vector>
#include <string>

class Component;

class GameObject
{
public:
  GameObject();
  ~GameObject();

  void CreateObject(); //Create the game object with this.
  Component* HasComponent(CompID check); //Checks for and returns the given
                                         //component type.
  void AttachComponent(Component* add); //Adds the given component to the obj.
  void Destroy(); //Destroys the object.

  std::vector<Component*> GetComponents(); //Returns ALL components.

  void SetName(std::string str); //Set the name of the object.
  std::string GetName(); //Get the name.

private:
  std::vector<Component*> components; //Components attached to the object.
  std::string name;
};
