#pragma once
/*****************************************************************************/
/*!
  Serializer class. Serializes and deserializes game objects.
*/
/*****************************************************************************/
//My includes
#include "GameObject.h" //Game object interaction.

//STL
#include <string> //String
#include <fstream> //File I/O

class Serializer
{
public:
  //Constructor, destructor.
  Serializer();
  ~Serializer();

  //Core functionality.
  void Serialize(GameObject* obj); //Serialize the given object.
  GameObject* Deserialize(std::string); //Find and create the given object.

private:
  std::string folder;
};
