/****************************************************************************/
//Buffer class. Handles vertex and index buffers for each different
//texture.
/****************************************************************************/
#pragma once

#include "Graphics.h" //openGL stuff.
#include "Transform.h" //Transform.

class Buffer
{
public:
  Buffer();
  ~Buffer();
  Buffer(const Buffer& rhs) = delete; //Don't want this.

  void CreateBuffers(char* name, bool stat);
  char* GetTexName() const;

  void Draw(Shader* shader, Transform* trans);
  void Draw(Shader* shader); //Use this to test.

private:
  //Buffers.
  GLuint vbo; //vertex
  GLuint ebo; //element / index

  //Array object.
  GLuint vao;

  //Name of the texture.
  char* texName;

  //Texture itself.
  GLuint texture;

  //Size of the texture.
  int width;
  int height;
  int channels;
};
