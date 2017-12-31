/*****************************************************************************/
/*!
  Meta manager. Collection of functions used to manage metadata objects. 
*/
/*****************************************************************************/
#pragma once

//System.
#include "MetaData.h"

//STL.
#include <map>
#include <string>

//Macros.
//META_TYPE finds the proper metadata instance of an object by type.
#define META_TYPE(TYPE) (MetaCreator<TYPE>::Get( ))

//META finds the proper metadata instance of an object by an object's type.
//decltype returns the type of an object.
#define META(OBJECT) (MetaCreator<decltype(OBJECT)>::Get( ))

//META_STR fidns a metadata instance by string name.
#define META_STR(STRING) (MetaManager::Get(STRING))

//DEFINE_META defines a MetaCreator for a specific type of data.
//Call before main!
#define DEFINE_META(TYPE) MetaCreator<TYPE> NAME_GENERATOR( )(#TYPE, sizeof(TYPE))

//NAME_GENERATOR generates a name. A bit tricky, but it can be done.
#define PASTE( _, __ ) _##__
#define NAME_GENERATOR_INTERNAL ( _ ) PASTE(GENERATED_NAME, _ )
#define NAME_GENERATOR( ) NAME_GENERATOR_INTERNAL( __COUNTER__ )

class MetaManager
{
public:
  typedef std::map<std::string, const MetaData*> MetaMap;

  //Insert metadata into map.
  static void RegisterMeta(const MetaData* instance);

  //Get a metadata instance, using it's name. Returns nullptr if not found.
  static const MetaData *Get(std::string name);

  //Return the map.
  static MetaMap& GetMap()
  {
    //Define the map as static here.
    static MetaMap map;
    return map;
  }
};
