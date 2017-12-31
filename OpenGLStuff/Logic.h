/*****************************************************************************/
/*!
  Logic system. Game logic, such as physics and AI, are handled here.
*/
/*****************************************************************************/
#pragma once

//My includes
#include "System.h"

class Logic : public System
{
public:
  Logic();
  ~Logic();
  Logic(const Logic& rhs) = delete;

  void Initialize();
  void Update(float dt);
  void Destroy();
  void RegisterComponent(Component*);
  void DeleteComponent(Component*);
};

extern Logic* LOGIC;
