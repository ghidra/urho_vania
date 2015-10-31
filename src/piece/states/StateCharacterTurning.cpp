#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?

#include "StateCharacterTurning.h"

#include "StateCharacterRunning.h"
#include "StateCharacterStopping.h"

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
	State* state = StateCharacterGrounded::HandleInput(ctrl,input);
    if(state != NULL)
    {
        return state;
    }
    else
    {
		if (ctrl.IsDown(CTRL_UP) || ctrl.IsDown(CTRL_DOWN) || ctrl.IsDown(CTRL_LEFT) || ctrl.IsDown(CTRL_RIGHT) )
		{
			//keep running
			return NULL;
		}
		else
		{
			return new StateCharacterStopping(context_);
		}
	}
}
void StateCharacterTurning::Update()
{
	StateCharacterGrounded::Update();
	
	RigidBody* body = pawn_->GetBody();
	AnimationController* animCtrl = pawn_->GetAnimationController();

	//from a stand still
	body->ApplyImpulse(moveDir_ * pawn_->GetMoveForce() *0.25);//0.25 to dampen it

	//Node* root = pawn_->GetNode()->GetChild(pawn_->GetRootName(),true);
	//const Quaternion& rot = root->GetRotation();

	//body->ApplyImpulse(rot * -moveDir_ * 0.9f * pawn_->GetMoveForce());//i ned to make it turn around slower
	//body->ApplyImpulse(moveDir_ * 0.9f * pawn_->GetMoveForce());
    //GetSubsystem<DebugHud>()->SetAppStats("animtion:", String("pivot") );
    //float skid = body->GetLinearVelocity().Length();
    //float skidTime = Fit( skid,pawn_->GetMoveForce(),0.0f,0.0f,animCtrl->GetLength("Models/Man/MAN_TurnSkidGunning.ani") );
    if( animCtrl->GetTime("Models/Man/MAN_TurnSkidGunning.ani") >= animCtrl->GetLength("Models/Man/MAN_TurnSkidGunning.ani")-0.05 )
    {
    //if(body->GetLinearVelocity().Length()>=pawn_->GetMoveForce()-0.05)
    	//i need to also rotate the fucker
    	Turn();
    	pawn_->SetState( new StateCharacterRunning(context_) );
    }      
    animCtrl->PlayExclusive("Models/Man/MAN_TurnSkidGunning.ani", false, 0.1f);
    //turning = true;

	//this one, when it reaches 0, i need to rotate the null, and them play the flipped version?
	/*
    float skid = pawn_->GetPlaneVelocity().Length();
    float skidTime = Fit(skid,pawn_->GetMoveForce(),0.0f,0.0f,0.03f);
    animCtrl->PlayExclusive("Models/Man/MAN_TurnSkidGunning.ani", 0,false, 0.2f);
    animCtrl->SetTime("Models/Man/MAN_TurnSkidGunning.ani",skidTime);
    */
}