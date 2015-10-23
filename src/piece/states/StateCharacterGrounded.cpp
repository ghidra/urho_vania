#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?

#include "StateCharacterGrounded.h"

#include "StateCharacterIdle.h"
#include "StateCharacterRunning.h"
#include "StateCharacterJumping.h"

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
	if (ctrl.IsDown(CTRL_UP) || ctrl.IsDown(CTRL_DOWN) || ctrl.IsDown(CTRL_LEFT) || ctrl.IsDown(CTRL_RIGHT) )
	{
		return new StateCharacterRunning(context_);
	}
	else if ( ctrl.IsDown(CTRL_JUMP) ) 
	{
		//we want to jump
		return new StateCharacterJumping(context_);
	}
	else
	{
		return new StateCharacterIdle(context_);
	}
    //return NULL;
    //return new StateCharacterRunning(context_);
}
void StateCharacterGrounded::Update()
{
}