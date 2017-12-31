/*****************************************************************************/
/*!
Input system. Handles and distributes input.
*/
/*****************************************************************************/

//GLEW stuff.
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW stuff.
#include <glfw3.h>

//My includes
#include "Input.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  //Try to find the key on the map.
  auto check = INPUT->keyState.find(key);
  
  if (check != INPUT->keyState.end())
  {
    //If found, update state.
    if (check->second == PRESSED && action == GLFW_PRESS)
    {
      check->second = HELD;
    }
    else if (check->second == RELEASED && action == GLFW_PRESS)
    {
      check->second = PRESSED;
    }
    else if (check->second != RELEASED && action == GLFW_RELEASE)
    {
      check->second = RELEASED;
    }
  }
}

void joystick_callback(int joy, int event)
{
  //Handle controller connect and disconnect here.
  if (event == GLFW_CONNECTED)
  {
    INPUT->SetControllerStatus(true);
  }
  else if (event == GLFW_DISCONNECTED)
  {
    INPUT->SetControllerStatus(false);
  }
}

Input* INPUT = nullptr;

Input::Input() { }
Input::~Input() { }

void Input::Initialize()
{
  INPUT = this;
  window = nullptr;

  //Check for controller on start.
  int check = glfwJoystickPresent(GLFW_JOYSTICK_1);
  
  if (check == 1)
    useController = true;
  else
    useController = false;

  axes_ = nullptr;
  buttons_ = nullptr;

  //Setup initial keybindings.
  //Use these temps to setup maps.
  std::pair<int, STATE> temp_keyState;
  temp_keyState.second = RELEASED;

  //Setting keyState.
  temp_keyState.first = GLFW_KEY_A;
  keyState.insert(temp_keyState);

  temp_keyState.first = GLFW_KEY_D;
  keyState.insert(temp_keyState);

  temp_keyState.first = GLFW_KEY_W;
  keyState.insert(temp_keyState);

  temp_keyState.first = GLFW_KEY_S;
  keyState.insert(temp_keyState);

  temp_keyState.first = GLFW_KEY_J;
  keyState.insert(temp_keyState);

  temp_keyState.first = GLFW_KEY_K;
  keyState.insert(temp_keyState);

  temp_keyState.first = GLFW_KEY_L;
  keyState.insert(temp_keyState);

  temp_keyState.first = GLFW_KEY_0;
  keyState.insert(temp_keyState);

  //Setting actionKey.
  std::pair<ACTION, int> temp;

  temp.first = MOVE_LEFT;
  temp.second = GLFW_KEY_A;
  actionKey.insert(temp);

  temp.first = MOVE_RIGHT;
  temp.second = GLFW_KEY_D;
  actionKey.insert(temp);

  temp.first = MOVE_UP;
  temp.second = GLFW_KEY_W;
  actionKey.insert(temp);

  temp.first = MOVE_DOWN;
  temp.second = GLFW_KEY_S;
  actionKey.insert(temp);

  temp.first = JUMP;
  temp.second = GLFW_KEY_J;
  actionKey.insert(temp);

  temp.first = ATTACK;
  temp.second = GLFW_KEY_K;
  actionKey.insert(temp);

  temp.first = DASH;
  temp.second = GLFW_KEY_L;
  actionKey.insert(temp);

  temp.first = SUICIDE;
  temp.second = GLFW_KEY_0;
  actionKey.insert(temp);
}

void Input::Update(float dt)
{
  //Get controller info, if possible.
  if (glfwJoystickPresent(GLFW_JOYSTICK_1))
  {
    int axisCount;
    const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axisCount);
    axes_ = const_cast<float*>(axes);

    int buttonCount;
    const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
    buttons_ = const_cast<unsigned char*>(buttons);
  }

  //Update components.
  if (!component_list.empty())
  {
    for (unsigned i = 0; i < component_list.size(); ++i)
    {
      component_list[i]->Update(dt);
    }
  }
}

void Input::Destroy()
{
  //Delete each component.
  component_list.erase(component_list.begin(), component_list.end());
}

void Input::RegisterComponent(Component* comp)
{
  component_list.push_back(comp);
}

void Input::DeleteComponent(Component* comp)
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

void Input::SetWindow(GLFWwindow* win_)
{
  window = win_;
}

STATE Input::IsPressed(int key)
{
  //Use the map's find feature.
  auto check = keyState.find(key);

  if (check != keyState.end())
  {
    return check->second;
  }
  else
  {
    return RELEASED;
  }
}

STATE Input::IsPressed(ACTION action)
{
  //Get the key.
  auto check = actionKey.find(action);

  if (check != actionKey.end())
  {
    return IsPressed(check->second);
  }
  else
  {
    return RELEASED;
  }
}

void Input::SetControllerStatus(bool status)
{
  useController = status;
}
