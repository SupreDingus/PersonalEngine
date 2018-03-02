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

  //Open it, check for failure.
  std::fstream file(fileName.c_str(), std::fstream::out);
  if (!file.is_open())
    return;

  //Setup for serialization.
  std::string temp;

  //Iterate through the list.
  for (unsigned i = 0; i < list.size(); ++i)
  {
    //Get the name, start the setup.
    temp = list[i]->GetCompName();
    temp.append(" {\n");

    //Get the rest of the component stuff.
    temp.append(list[i]->Serialize());
    temp.append("\n}\n");

    //Send it out to the file.
    file << temp;
  }
}

GameObject* Serializer::Deserialize(std::string fileName)
{
  //Open the file.
  std::fstream file(fileName.c_str(), std::fstream::in);

  //Check for failure.
  if (!file.is_open())
    return nullptr;

  //Allocate a new GameObject.
  GameObject* ret = new GameObject;

  //Hold file output here.
  std::string temp;

  //Move through the file.
  while (!file.eof())
  {

  }
}
