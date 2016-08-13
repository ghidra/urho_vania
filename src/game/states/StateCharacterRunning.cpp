#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?
#include <Urho3D/Physics/RigidBody.h>

#include "../../framework/src/PawnAnimated.h"

#include "StateCharacterRunning.h"
#include "StateCharacterStopping.h"
#include "StateCharacterTurning.h"


StateCharacterRunning::StateCharacterRunning(Context* context):
    StateCharacterGrounded(context)
{
    name_=String("running");
}
StateCharacterRunning::~StateCharacterRunning(){}

State* StateCharacterRunning::HandleInput(Controls& ctrl)
{
	State* state = StateCharacterGrounded::HandleInput(ctrl);
    if(state != NULL)
    {
        return state;
    }
    else
    {
		if (ctrl.IsDown(CTRL_UP) || ctrl.IsDown(CTRL_DOWN) || ctrl.IsDown(CTRL_LEFT) || ctrl.IsDown(CTRL_RIGHT) )
		{
			//keep running
			if(TestTurn())
				return new StateCharacterTurning(context_);
			else
				return NULL;
		}
		else
		{
			return new StateCharacterStopping(context_);
			//defer to grounded
			//StateCharacterGrounded::HandleInput(ctrl,input);
		}
	}
}
void StateCharacterRunning::Update(float timeStep)
{
	StateCharacterGrounded::Update();//apply brake force
	//const Quaternion& rot = pawn_->GetNode()->GetRotation();
	//pawn_->GetBody()->ApplyImpulse(rot * moveDir_ * pawn_->GetMoveForce() );
	RigidBody* body = pawn_->GetBody();
	AnimationController* animCtrl = static_cast<PawnAnimated*>(pawn_)->GetAnimationController(); 
	
	body->ApplyImpulse(moveDir_ * pawn_->GetMoveForce() );

	//animation
	
	animCtrl->PlayExclusive("Models/Man/MAN_RunningGunning.ani", 0, true, 0.2f);
	animCtrl->SetSpeed("Models/Man/MAN_RunningGunning.ani", pawn_->GetPlaneVelocity().Length() * 0.04f);
}