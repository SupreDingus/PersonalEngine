/*****************************************************************************/
/*!
  Object factory. Creates objects.
*/
/*****************************************************************************/
#pragma once

//System.
#include "GameObject.h"
#include "ComponentTypes.h"
#include "ComponentIncludes.h"

//GLM.
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ObjectFactory
{
public:
  ObjectFactory();
  ~ObjectFactory();
  ObjectFactory(const ObjectFactory& rhs) = delete; //only need 1.

  GameObject* CreateObject(); //Creates an object at (0, 0).
  GameObject* CreateObjectAtPos(float x, float y); //Creates an object at the given position.
  GameObject* CreateObjectAtPos(glm::vec2 vec);
};
