#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?

/*
#include "../../game/State.h"

Potentially remove the need for a h file
class StateCharacterIdle : public State
{
        public:
                void HandleInput(Pawn& pawn, Input* input);
                //float someNewProperty;
}

*/

#include "StateCharacterIdle.h"

#include "StateCharacterRunning.h"
#include "StateCharacterJumping.h"

#include <Urho3D/Input/Input.h>
#include "../../game/Pawn.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>

StateCharacterIdle::StateCharacterIdle(Context* context):
    State(context)
{
    name_=String("idle");
}
StateCharacterIdle::~StateCharacterIdle(){}

State* StateCharacterIdle::HandleInput(Pawn* pawn, Controls& ctrl, Input* input)
{
    if (ctrl.IsDown(CTRL_UP) || ctrl.IsDown(CTRL_DOWN) || ctrl.IsDown(CTRL_LEFT) || ctrl.IsDown(CTRL_RIGHT) )
        return new StateCharacterRunning(context_);
    else
        return NULL;
}
void StateCharacterIdle::Update(Pawn* pawn)
{
}