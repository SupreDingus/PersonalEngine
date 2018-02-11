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
#include <ostream> //File I/O
#include <istream>

class Serializer
{
public:
  //Constructor, destructor.
  Serializer();
  ~Serializer();

  //Core functionality.
  //TODO: Make component serialize return a string.
  //Output that string to file.
  //Do something similar with Deserialize.
  void Serialize(GameObject* obj); //Serialize the given object.
  GameObject* Deserialize(std::string); //Find and create the given object.

private:
  std::string folder;
};
