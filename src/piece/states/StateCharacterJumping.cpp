#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?
#include <Urho3D/Physics/RigidBody.h>

#include "StateCharacterJumping.h"

#include "StateCharacterFalling.h"

//#include <Urho3D/Input/Input.h>
#include "../../game/Pawn.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>

StateCharacterJumping::StateCharacterJumping(Context* context):
    State(context),
    jumping_(false)
{
    name_=String("jumping");
}
StateCharacterJumping::~StateCharacterJumping(){}

void StateCharacterJumping::Enter(Pawn* pawn)
{
	State::Enter(pawn);
	RigidBody* body = pawn_->GetBody();
	body->ApplyImpulse(Vector3::UP * pawn_->GetJumpForce() );
}

State* StateCharacterJumping::HandleInput(Controls& ctrl)
{
    return NULL;
    //return new StateCharacterRunning(context_);
}
void StateCharacterJumping::Update()
{
	Vector3 jumpVector = pawn_->GetJumpVelocity();
	//first we need to set that we are jumping before we check that we are falling.
	//its not working to set a bool in enter, so lest wait and check here
	if(!jumping_ && jumpVector.y_>0.1)
		jumping_=true;
	//now, once we start to decend, we are falling, set the appropriate state
	if(jumpVector.y_<=0.1 && jumping_)
		pawn_->SetState(new StateCharacterFalling(context_));

	//now carry on with the animation
	AnimationController* animCtrl = pawn_->GetAnimationController();
	/*float jumpTime = 0.0f;
    if(jumpVector.y_>0.0f)
        jumpTime = Fit(jumpVector.y_,pawn_->GetJumpForce(),0.0f,0.0f,0.5f);
    else
        jumpTime = Fit(jumpVector.y_,0.0f,-pawn_->GetJumpForce(),0.5f,1.0f);*/
    float jumpTime = Fit(jumpVector.y_,pawn_->GetJumpForce(),0.1f,0.0f,0.5f);
    
    animCtrl->PlayExclusive("Models/Man/MAN_Jumping.ani", 0,false, 0.1f);
    animCtrl->SetTime("Models/Man/MAN_Jumping.ani",jumpTime);
}