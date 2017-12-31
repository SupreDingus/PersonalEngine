#include "Graphics.h"
#include "Buffer.h"

GraphicsSystem* GRAPHICS = nullptr;

//These don't do anything yet.
GraphicsSystem::GraphicsSystem()
{
  GRAPHICS = this;
}

GraphicsSystem::~GraphicsSystem()
{
  //Free each buffer.
  for (auto it : buffers_)
  {
    delete it.second;
  }
}

void GraphicsSystem::Initialize()
{
  //Make the shader.
  shader_ = new Shader("../OpenGLStuff/shader.vs", "../OpenGLStuff/shader.frag");

  //Make a buffer for each texture.
  //Open the file.
  std::fstream file("../OpenGLStuff/Textures.txt", std::fstream::in);
  std::string str;

  //Check for failure.
  if (file.is_open())
  {
    while (!file.eof())
    {
      //Create a new buffer from the fiel.
      Buffer* buff;
      std::string name("../Assets/");
      file >> str;
      name.append(str);

      buff = new Buffer;
      buff->CreateBuffers(const_cast<char*>(name.data()), false);

      //Insert onto map.
      buffers_.insert(std::pair<std::string, Buffer*>(str, buff));

      str.clear();
    }
  }

  //Make an projection matrix.
  //Orthographic.
  //Args: far left, far right, bottom, top, near, far.
  proj_ = glm::ortho(0.f, 800.f, 0.f, 600.f, 0.1f, 10.f);

  //Perspective.
  //proj_ = glm::perspective(60.f, 16.f / 9.f, 0.1f, 10.f);

  //Make the view matrix.
  view_ = glm::translate(view_, glm::vec3(0.f, 0.f, -1.f));
}

void GraphicsSystem::Update(float dt)
{
  //Use the shader.
  shader_->Use();

  //Pass the transform matrices to the shader.
  GLuint projLocation = glGetUniformLocation(shader_->program, "Projection");
  glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(proj_));

  GLuint viewLocation = glGetUniformLocation(shader_->program, "View");
  glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view_));

  //Clear the screen.
  glClearColor(1.f, 1.f, 1.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);

  //Loop through each component and call their update.
  if (!component_list.empty())
  {
    for (unsigned i = 0; i < component_list.size(); ++i)
    {
      component_list[i]->Update(dt);
    }
  }

  //After it's done updating, unbind the last vertex array.
  glBindVertexArray(0);
}

void GraphicsSystem::Destroy()
{
  //Destroy each component.
  component_list.erase(component_list.begin(), component_list.end());

  //Free each buffer.
  buffers_.erase(buffers_.begin(), buffers_.end());

  //Free the shader.
  delete shader_;
}

void GraphicsSystem::RegisterComponent(Component* comp)
{
  //Push back onto the vector.
  component_list.push_back(comp);
}

void GraphicsSystem::DeleteComponent(Component* comp)
{
  unsigned pos = 0;

  //Find the component in the vector.
  for (auto it : component_list)
  {
    if (comp == it)
    {
      //Use the erase function.
      component_list.erase(component_list.begin() + pos);
      return;
    }
    else
    {
      pos++;
    }
  }
}

Shader* GraphicsSystem::GetShader() const
{
  return shader_;
}

Buffer* GraphicsSystem::GetBuffer(std::string name) const
{
  //Use the map's find function to find the correct buffer.
  auto it = buffers_.find(name);
  if (it != buffers_.end())
  {
    return it->second;
  }

  //Return nothing if no buffer of that name was found.
  return nullptr;
}
