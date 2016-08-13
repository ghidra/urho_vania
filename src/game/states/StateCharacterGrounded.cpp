#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?

#include "StateCharacterGrounded.h"
#include "StateCharacterJumping.h"

StateCharacterGrounded::StateCharacterGrounded(Context* context):
    State(context)
{
    name_=String("grounded");
}
StateCharacterGrounded::~StateCharacterGrounded(){}

State* StateCharacterGrounded::HandleInput(Controls& ctrl)
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

    Debug("direction", String(moveDir_));

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
void StateCharacterGrounded::Update(float timeStep)
{
    RigidBody* body = pawn_->GetBody();
    body->ApplyImpulse(-pawn_->GetPlaneVelocity() * pawn_->GetBrakeForce());//this is the brake force
}

bool StateCharacterGrounded::TestTurn()
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
void StateCharacterGrounded::Turn()
{
    //0 * 2 - 1 = -1
    //1 * 2 - 1 = 1
    //float rot = 90.0f * -(static_cast<float>(pawn_->GetFacingDirection())*2-1 );//get the rotation value based on what is set
    float rot = 90.0f * -(float(pawn_->GetFacingDirection())*2-1 );//get the rotation value based on what is set
    //GetSubsystem<DebugHud>()->SetAppStats("cast:", String(rot) );
    Node* root = pawn_->GetNode()->GetChild(pawn_->GetRootName(),true);//get the root node
    root->SetRotation(Quaternion(0.0f,rot,0.0f));//rotate the node
    pawn_->SetFacingDirection(!pawn_->GetFacingDirection());//then set the facing direction
}