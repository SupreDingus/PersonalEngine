#pragma once

//GLEW stuff.
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW stuff.
#include <glfw3.h>

#include <iostream>

//Make the window
GLFWwindow* CreateWindow();
