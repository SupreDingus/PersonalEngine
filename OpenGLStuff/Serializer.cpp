/*****************************************************************************/
/*!
  Serializer class. Serializes and deserializes game objects.
*/
/*****************************************************************************/
//My includes
#include "Serializer.h"

//Nothing to allocate / destroy.
Serializer::Serializer() { }
Serializer::~Serializer() { }

void Serialize(GameObject* obj)
{
  //Get the components.
  auto list = obj->GetComponents();

  //Setup the output.

  //Iterate through the list.
  for (auto it : list)
  {

  }
}
