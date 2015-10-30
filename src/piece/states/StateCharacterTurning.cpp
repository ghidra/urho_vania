#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?

#include "StateCharacterTurning.h"

#include "StateCharacterRunning.h"

#include <Urho3D/Input/Input.h>
#include "../../game/Pawn.h"

StateCharacterTurning::StateCharacterTurning(Context* context):
    StateCharacterGrounded(context)
{
    name_=String("turning");
}
StateCharacterTurning::~StateCharacterTurning(){}

State* StateCharacterTurning::HandleInput(Controls& ctrl, Input* input)
{
	if (ctrl.IsDown(CTRL_UP) || ctrl.IsDown(CTRL_DOWN) || ctrl.IsDown(CTRL_LEFT) || ctrl.IsDown(CTRL_RIGHT) )
	{
		//keep running
		return NULL;
	}
	else
	{
		//defer to grounded
		StateCharacterGrounded::HandleInput(ctrl,input);
	}
}
void StateCharacterTurning::Update()
{
	//StateCharacterGrounded::Update()
}