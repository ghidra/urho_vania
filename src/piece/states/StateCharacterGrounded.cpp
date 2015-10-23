#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?

#include "StateCharacterGrounded.h"

#include <Urho3D/Input/Input.h>
#include "../../game/Pawn.h"

StateCharacterGrounded::StateCharacterGrounded(Context* context):
    State(context)
{
    name_=String("grounded");
}
StateCharacterGrounded::~StateCharacterGrounded(){}

State* StateCharacterGrounded::HandleInput(Controls& ctrl, Input* input)
{
    return NULL;
    //return new StateCharacterRunning(context_);
}
void StateCharacterGrounded::Update()
{
}