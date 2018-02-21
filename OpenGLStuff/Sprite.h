#pragma once
/*****************************************************************************/
/*!
  Sprite header. Sprite component controls what's displayed and stuff.
*/
/*****************************************************************************/
#include "Component.h"

class Buffer;

class Sprite : public Component
{
public:
  Sprite();
  ~Sprite();
  Sprite(const Sprite &rhs) = delete;

  void Initialize();
  void Update(float dt);
  void Destroy();
  std::string Serialize();
  void Deserialize(std::string);

  void SetTexture(Buffer* buffer);

private:
  Buffer* buffer_;
};
