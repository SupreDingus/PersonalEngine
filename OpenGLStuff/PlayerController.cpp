/*****************************************************************************/
/*!
  Player controller. Makes the player do things.
*/
/*****************************************************************************/
#include "PlayerController.h"

//Component includes.
#include "RigidBody.h"
#include "Collider.h"
#include "GroundDetection.h"

PlayerController::PlayerController()
{
  Initialize();
}

PlayerController::~PlayerController() { }

void PlayerController::Initialize()
{
  ID = C_PlayerController;

  if (owner)
  {
    //Get the necessary components from the object.
    body = static_cast<RigidBody*>(owner->HasComponent(C_RigidBody));
    collider = static_cast<Collider*>(owner->HasComponent(C_Collider));
    ground = static_cast<GroundDetection*>(owner->HasComponent(C_GroundDetection));

    //Be sure it's dynamic.
    body->ChangeStatic(false);
  }
  else
  {
    body = nullptr;
    collider = nullptr;
    ground = nullptr;
  }

  move = vec2(0.f, 0.f);

  //Put it in the input system.
  INPUTSYSTEM->RegisterComponent(this);
}

void PlayerController::Update(float dt)
{
  move = vec2(0.f, 0.f);

  //Check for relevant input.
  //If action is pressed or held, do stuff.
  if (INPUTSYSTEM->IsPressed(MOVE_LEFT) != RELEASED)
  {
    move += glm::vec2(-10.f, 0.f);
  }
  if (INPUTSYSTEM->IsPressed(MOVE_RIGHT) != RELEASED)
  {
    move += glm::vec2(10.f, 0.f);
  }

  //To jump, we must be grounded.
  if (INPUTSYSTEM->IsPressed(JUMP) == PRESSED && ground && ground->IsGrounded())
  {
    move += glm::vec2(0.f, 5000.f);
    ground->ChangeGrounded();
  }

  //Testing object destruction.
  if (INPUTSYSTEM->IsPressed(SUICIDE) != RELEASED)
  {
    owner->Destroy();
  }
}

void PlayerController::Destroy()
{
  //RigidBody will take care of itself.
  INPUTSYSTEM->DeleteComponent(this);
}

void PlayerController::Serialize(std::fstream file)
{
  //Nothing to send out...
}

void PlayerController::Deserialize(std::fstream file)
{
  //Get the necessary pointers.
  SetBody();
}

void PlayerController::SetBody()
{
  if (owner)
  {
    //Get the necessary components from the object.
    body = static_cast<RigidBody*>(owner->HasComponent(C_RigidBody));
    collider = static_cast<Collider*>(owner->HasComponent(C_Collider));
    ground = static_cast<GroundDetection*>(owner->HasComponent(C_GroundDetection));

    //Be sure it's dynamic.
    body->ChangeStatic(false);
  }
}

glm::vec3 PlayerController::GetMove()
{
  return glm::vec3(move, 0.f);
}
