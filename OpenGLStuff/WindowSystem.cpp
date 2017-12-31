#include "WindowSystem.h"

GLFWwindow* CreateWindow()
{
  //Instantiate window.
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  //Make the windows object.
  GLFWwindow* window = glfwCreateWindow(800, 600, "Colorblind engine", nullptr, nullptr);
  if (window == nullptr)
  {
    //Return if we failed.
    std::cout << "Failed to create the window!" << std::endl;
    glfwTerminate();
    return nullptr;
  }
  glfwMakeContextCurrent(window);

  //Init glew so that we can use OpenGL functions.
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
  {
    std::cout << "Failed to init GLEW" << std::endl;
    return nullptr;
  }

  //Setup the viewport.
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  return window;
}
