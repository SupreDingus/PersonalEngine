//GLEW stuff.
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW stuff.
#include <glfw3.h>
//Soil, used for image loading.
#include <SOIL.h>

//My includes
#include <iostream>
#include "SystemIncludes.h"
#include "Component.h"
#include "ComponentIncludes.h"
#include "MetaManager.h"
#include "MetaCreator.h"

int main()
{
  //Create the window.
  GLFWwindow* window = CreateWindow();

  //Create necessary systems.
  std::vector<System*> systems_;
  GraphicsSystem* graphics = new GraphicsSystem;
  Logic* logic = new Logic;
  Input* input = new Input;
  Physics* physics = new Physics;

  //Input, update, draw.
  //In my case, input, logic, physics, graphics.
  systems_.push_back(static_cast<System*>(input));
  systems_.push_back(static_cast<System*>(logic));
  systems_.push_back(static_cast<System*>(physics));
  systems_.push_back(static_cast<System*>(graphics));

  //Initialize them.
  for (auto it : systems_)
  {
    it->Initialize();
  }

  //Timer stuff.
  double currTime = 0.0;
  double prevTime = 0.0;
  double frameTime = 0.0; //This is dt.

  //Set callbacks.
  input->SetWindow(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSetJoystickCallback(joystick_callback);

  //TEST OBJECT
  GameObject* obj = new GameObject;
  obj->CreateObject();

  //Give it a texture.
  Sprite* sprite = static_cast<Sprite*>(obj->HasComponent(C_Sprite));
  sprite->SetTexture(graphics->GetBuffer("RD.jpg"));

  //Make it bigger.
  Transform* trans = static_cast<Transform*>(obj->HasComponent(C_Transform));
  trans->SetScale(200.f, 150.f);
  trans->SetPosition(400.f, 400.f, 0.f);

  //Give it a rigidbody.
  RigidBody* body = new RigidBody;
  body->ChangeStatic(false);
  obj->AttachComponent(body);
  body->SetTransform();

  //Collider.
  Collider* collide = new Collider;
  collide->SetRestitution(0.f);
  obj->AttachComponent(collide);
  collide->SetBody();
  collide->SetTransform();
  body->SetCollider();

  //Ground detection.
  GroundDetection* ground = new GroundDetection;
  obj->AttachComponent(ground);
  ground->SetCollider();
  ground->SetTransform();

  //Give it the player controller.
  PlayerController* player = new PlayerController;
  obj->AttachComponent(player);
  player->SetBody();
  body->SetController();

  //Another object.
  GameObject* obj2 = new GameObject;
  obj2->CreateObject();

  Sprite* sprite2 = static_cast<Sprite*>(obj2->HasComponent(C_Sprite));
  sprite2->SetTexture(graphics->GetBuffer("cc.png"));

  Transform* trans2 = static_cast<Transform*>(obj2->HasComponent(C_Transform));
  trans2->SetScale(400.f, 150.f);
  trans2->SetPosition(400.f, 100.f, 0.f);

  //This one is static.
  RigidBody* body2 = new RigidBody;
  //body2->ChangeStatic(true);
  obj2->AttachComponent(body2);
  body2->SetTransform();

  Collider* collide2 = new Collider;
  obj2->AttachComponent(collide2);
  collide2->SetRestitution(0.f);
  collide2->SetBody();
  collide2->SetTransform();
  body2->SetCollider();

  //Game loop.
  //Check for quit.
  while (!glfwWindowShouldClose(window))
  {
    //Get events.
    glfwPollEvents();

    //Get the time between frames.
    prevTime = currTime;
    currTime = glfwGetTime();
    frameTime = currTime - prevTime;

    //Update.
    for (auto it : systems_)
    {
      //Use frameTime as dt.
      it->Update(frameTime);
    }

    //Swap buffers.
    glfwSwapBuffers(window);
  }

  delete obj;

  //Destroy and free everything.
  for (auto it : systems_)
  {
    it->Destroy();
    delete it;
  }

  //Terminate before closing.
  glfwTerminate();
  return 0;
}

DEFINE_META(int)
{
}
