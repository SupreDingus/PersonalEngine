/*****************************************************************************/
/*!
  The Sprite component controls what's displayed and stuff.
*/
/*****************************************************************************/
#include "Sprite.h"
#include "Transform.h"
#include "Buffer.h"

Sprite::Sprite()
{
  Initialize();
}
Sprite::~Sprite() { }

void Sprite::Initialize()
{
  //Set the id.
  ID = C_Sprite;

  //Add to graphics.
  GRAPHICS->RegisterComponent(this);
}

void Sprite::Update(float dt)
{
  //Get the transform and send it to the shader.
  Transform* trans = static_cast<Transform*>(owner->HasComponent(C_Transform));

  //Draw the buffer.
  GRAPHICS->GetShader()->SetUniform(0, "Grey");
  buffer_->Draw(GRAPHICS->GetShader(), trans);
}

void Sprite::Destroy()
{
  //Call the delete function on this.
  GRAPHICS->DeleteComponent(this);
}

std::string Sprite::Serialize()
{
  //Nothing to send out...
  return std::string();
}

void Sprite::Deserialize(std::string str)
{
  //Nothing to get...
}

std::string Sprite::GetCompName()
{
  return "Sprite";
}

void Sprite::SetTexture(Buffer* buffer)
{
  //Just set the buffer pointer. It's already made.
  buffer_ = buffer;
}
