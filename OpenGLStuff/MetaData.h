/*****************************************************************************/
/*!
  Meta data. Holds info about any type for reflection purposes.
*/
/*****************************************************************************/
#pragma once

//STL.
#include <string>

class MetaData
{
public:
  MetaData(std::string string, unsigned val) : name(string), size(val) { }
  ~MetaData();

  const std::string& Name() const { return name; }
  unsigned Size() const { return size; }

private:
  std::string name;
  unsigned size;
};
