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
  std::filebuf fb;
  fb.open(folder + obj->GetName(), std::ios::out);
  std::ostream file(&fb);

  //Iterate through the list.
  for (unsigned i = 0; i < list.size(); ++i)
  {
    //list[i]->Serialize(file);
  }
}
