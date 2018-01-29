/****************************************************************************/
/*!
  Buffer class. Handles vertex and index buffers for each different
  texture.
*/
/****************************************************************************/

//My includes.
#include "Buffer.h"

//stb_image init.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Buffer::Buffer() { }

Buffer::~Buffer()
{
  //Use openGL calls to free data.
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
}

void Buffer::CreateBuffers(char* name, bool stat)
{
  //Pre-define verts and indices.
  GLfloat verts[] = {
    //Verts            //colors      //texture coords.
    0.5f,  0.5f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f, //Top right
    0.5f, -0.5f, 0.f, 0.f, 1.f, 0.f, 1.f, 0.f, //Bottom right
    -0.5f,  0.5f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, //Top left
    -0.5f, -0.5f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f  //Bottom left
  };
  GLuint indices[] = { //Triangles made from the the verts above.
    0, 1, 3,
    3, 2, 0
  };

  //Set name of texture.
  texName = name;

  //Create the buffers.
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  //Create array object.
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  //Set the data. Bind, then copy over data.
  //Make static or dynamic, based on parameters.
  //Vertex.
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  if (stat == true)
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
  else
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_DYNAMIC_DRAW);

  //Element.
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  if (stat == true)
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  else
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

  //Set attribute pointers.
  //Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  //Color
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  //Texture
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);

  //Create the texture.
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  //Set parameters and filtering.
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  //Load image.
  unsigned char* image = stbi_load(name, &width, &height, &channels, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);

  //Unbind image data.
  stbi_image_free(image);
  glBindTexture(GL_TEXTURE_2D, 0);
}

char* Buffer::GetTexName() const
{
  return texName;
}

void Buffer::Draw(Shader* shader, Transform* trans)
{
  GLint check;
  glGetIntegerv(GL_ACTIVE_TEXTURE, &check);

  //Pass the transform to the shader.
  GLuint transLocation = glGetUniformLocation(shader->program, "Transform");
  glUniformMatrix4fv(transLocation, 1, GL_FALSE, glm::value_ptr(trans->GetTransform()));

  //Activate the texture, draw it.
  glActiveTexture(GL_TEXTURE0 + (GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - check));
  glBindTexture(GL_TEXTURE_2D, texture);
  glUniform1i(glGetUniformLocation(shader->program, "ourTexture"), 0);

  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

//This function draws straight to the middle of the screen. For testing purposes.
void Buffer::Draw(Shader* shader)
{
  //Make a transform that does nothing.
  glm::mat4 trans;
  trans = glm::scale(trans, glm::vec3(1.f, 1.f, 1.f));
  trans = glm::translate(trans, glm::vec3(0.f, 0.f, 0.f));

  //Send to the shader.
  GLuint transLocation = glGetUniformLocation(shader->program, "Transform");
  glUniformMatrix4fv(transLocation, 1, GL_FALSE, glm::value_ptr(trans));

  GLint check;
  glGetIntegerv(GL_ACTIVE_TEXTURE, &check);

  //Activate the texture, draw it.
  glActiveTexture(GL_TEXTURE0 + (GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - check));
  glBindTexture(GL_TEXTURE_2D, texture);
  glUniform1i(glGetUniformLocation(shader->program, "ourTexture"), 0);

  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
