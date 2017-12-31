/*****************************************************************************/
/*!
  Meta creator. Used to make metadata instances.
*/
/*****************************************************************************/
#pragma once

#include "MetaData.h"

template <typename Metatype>
class MetaCreator
{
public:
  MetaCreator(std::string name, unsigned size)
  {
    Init(name, size);
  }

  static void Init(std::string name, unsigned size)
  {
    Get()->Init(name, size);
  }

  //Be sure only 1 instance exists for this class type.
  static MetaData *Get(void)
  {
    static MetaData instance;
    return &instance;
  }
};
