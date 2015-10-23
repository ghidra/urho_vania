#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?

#include "StateCharacterRunning.h"

#include <Urho3D/Input/Input.h>
#include "../../game/Pawn.h"

StateCharacterRunning::StateCharacterRunning(Context* context):
    StateCharacterGrounded(context)
{
    name_=String("running");
}
StateCharacterRunning::~StateCharacterRunning(){}

State* StateCharacterRunning::HandleInput(Controls& ctrl, Input* input)
{
    return NULL;
    //return new StateCharacterRunning(context_);
}
void StateCharacterRunning::Update()
{
}