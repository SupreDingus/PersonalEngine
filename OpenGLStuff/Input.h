/*****************************************************************************/
/*!
  Input system. Handles and distributes input.
*/
/*****************************************************************************/
#pragma once

//OpenGL
//#include <glad/glad.h>
#include <GLFW/glfw3.h>

//System includes.
#include "System.h"

//STL includes.
#include <map>

//Enum for player actions.
enum ACTION
{
  MOVE_LEFT,
  MOVE_RIGHT,
  MOVE_UP,
  MOVE_DOWN,

  JUMP,
  ATTACK,
  DASH,

  SUICIDE //Use this to test object destruction.
};

//Enum for key states.
enum STATE
{
  RELEASED,
  PRESSED,
  HELD
};

//Check for button pressed.
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

//For joystick events.
void joystick_callback(int joy, int event);

class Input : public System
{
public:
  Input();
  ~Input();
  Input(const Input& rhs) = delete;

  void Initialize();
  void Update(float dt);
  void Destroy();
  void RegisterComponent(Component* comp);
  void DeleteComponent(Component* comp);

  //Set window on startup with this.
  void SetWindow(GLFWwindow* win_);

  //Return key state (press, held (repeat), release)
  STATE IsPressed(int key);
  STATE IsPressed(ACTION action);

  //Set controller use or not.
  void SetControllerStatus(bool status);

  //Map that contains keys and whether they're being pressed or not.
  std::map<int, STATE> keyState;

private:
  //Use the window to get input stuff.
  GLFWwindow* window;

  //True if there's a controller connected.
  bool useController;

  //Hold controller stuff here.
  float* axes_;
  unsigned char* buttons_;

  ////Map that contains keys and whether they're being pressed or not.
  //std::map<int, STATE> keyState;

  //Map that contains a key and an associated action.
  std::map<ACTION, int> actionKey;
};

extern Input* INPUTSYSTEM;
