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

StateCharacterIdle::StateCharacterIdle(Context* context):
    StateCharacterGrounded(context)
{
    name_=String("idle");
}
StateCharacterIdle::~StateCharacterIdle(){}

State* StateCharacterIdle::HandleInput(Controls& ctrl, Input* input)
{
    State* state = StateCharacterGrounded::HandleInput(ctrl,input);
    if(state != NULL)
    {
        return state;
    }
    else
    {
        if (ctrl.IsDown(CTRL_UP) || ctrl.IsDown(CTRL_DOWN) || ctrl.IsDown(CTRL_LEFT) || ctrl.IsDown(CTRL_RIGHT) )
        {
            return new StateCharacterRunning(context_);
        }
        else
        {
            return NULL;
        }
    }
}
void StateCharacterIdle::Update()
{
}