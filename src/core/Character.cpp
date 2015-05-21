#include <Urho3D/Urho3D.h>

#include <Urho3D/Scene/Scene.h>

#include "Character.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>

Character::Character(Context* context) :
    Actor(context)
    //yaw_(0.0f),
    //pitch_(0.0f),
    //touchEnabled_(false),
    //screenJoystickIndex_(M_MAX_UNSIGNED),
    //screenJoystickSettingsIndex_(M_MAX_UNSIGNED),
    //paused_(false)
{
    //CameraLogic::RegisterObject(context);
}

//-------------------
//-------------------
void Character::Start()
{
    // Execute base class startup
    //ApplicationHandler::Start();
}
void Character::Setup(SharedPtr<Scene> scene, SharedPtr<Node> cameraNode)
{

}
