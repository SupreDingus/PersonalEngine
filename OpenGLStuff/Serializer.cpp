/*****************************************************************************/
/*!
  Serializer class. Serializes and deserializes game objects.
*/
/*****************************************************************************/
//My includes
#include "Serializer.h"
#include "Component.h"

Serializer::Serializer()
{
  //Set what the folder prefix will be.
  folder = "Objects/";
}

//Nothing to destroy.
Serializer::~Serializer() { }

void Serializer::Serialize(GameObject* obj)
{
  //Get the components.
  std::vector<Component *> list = obj->GetComponents();

  //Setup the output file.
  std::string fileName = folder + obj->GetName();
  fileName.append(".txt");

  std::fstream file(fileName.c_str(), std::fstream::out);

  //Setup for serialization.
  std::string temp;

  //Iterate through the list.
  for (unsigned i = 0; i < list.size(); ++i)
  {

  }
}
