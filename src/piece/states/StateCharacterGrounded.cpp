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
    RigidBody* body = pawn_->GetBody();
    body->ApplyImpulse(-pawn_->GetPlaneVelocity() * pawn_->GetBrakeForce());
}

bool StateCharacterGrounded::DoTurn()
{
    Node* root = pawn_->GetNode()->GetChild(pawn_->GetRootName(),true);
    const Quaternion& rot = root->GetRotation();

    Vector3 euler = rot.EulerAngles();//get the direction that this this is going -90 is looking left 90 is looking right
    float dp = moveDir_.DotProduct(Vector3::LEFT);//if 1 we are trying to go left, -1 we are trying to go right
          
    //so, if we are facing -90 and want to go -1, we need to turn around
    //if we are facing 90 and want to go 1, we need to turn around
    //so if we multiply them, -90*-1=90, 90*1=90, so positive values turn around, -90*1=-90, 90*-1=-90, negative values, dont turn

    return dp*euler.y_>0;
}