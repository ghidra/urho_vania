#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?

#include "StateCharacterGrounded.h"

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
	//get the move direction
	moveDir_ = Vector3::ZERO;
	if (ctrl.IsDown(CTRL_UP))
        moveDir_ += Vector3::FORWARD;
    if (ctrl.IsDown(CTRL_DOWN))
        moveDir_ += Vector3::BACK;
    if (ctrl.IsDown(CTRL_LEFT))
        moveDir_ += Vector3::LEFT;
    if (ctrl.IsDown(CTRL_RIGHT))
        moveDir_ += Vector3::RIGHT;

    // Normalize move vector so that diagonal strafing is not faster
    if (moveDir_.LengthSquared() > 0.0f)
    {
        moveDir_*=Vector3(1.0f,1.0f,0.0f);//flatten movement out to a plane
        moveDir_.Normalize();
    }
    //------------------

	if ( ctrl.IsDown(CTRL_JUMP) ) 
	{
		//we want to jump
		return new StateCharacterJumping(context_);
	}else{
		return NULL;
	}
}
void StateCharacterGrounded::Update()
{
	
}