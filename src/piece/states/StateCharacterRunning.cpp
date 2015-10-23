#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?

#include "StateCharacterRunning.h"

#include "StateCharacterIdle.h"
#include "StateCharacterJumping.h"

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
void StateCharacterRunning::Update()
{
	//StateCharacterGrounded::Update()
}