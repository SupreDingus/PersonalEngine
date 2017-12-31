/*****************************************************************************/
/*!
  Physics system. Handles physics calculations, such as velocity and gravity.
    Also handles collisions.
*/
/*****************************************************************************/
#pragma once

#include "System.h"

class Physics : public System
{
public:
  Physics();
  ~Physics();
  Physics(const Physics& rhs) = delete;

  void Initialize();
  void Update(float dt);
  void Destroy();
  void RegisterComponent(Component* comp);
  void DeleteComponent(Component* comp);
};

extern Physics* PHYSICS;
