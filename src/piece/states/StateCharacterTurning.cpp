#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?

#include "StateCharacterTurning.h"

#include "StateCharacterRunning.h"
#include "StateCharacterStopping.h"

#include <Urho3D/Input/Input.h>
#include "../../game/Pawn.h"

StateCharacterTurning::StateCharacterTurning(Context* context):
    StateCharacterGrounded(context),
    flipped_(false)
{
    name_=String("turning");
}
StateCharacterTurning::~StateCharacterTurning(){}

void StateCharacterTurning::Enter(Pawn* pawn)
{
    State::Enter(pawn);
    speed_ = pawn_->GetPlaneVelocity().Length();
    //GetSubsystem<DebugHud>()->SetAppStats("init distance:", result.distance_ );
}

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

	//apply a force to slow it down further, since we are changing direction
	body->ApplyImpulse(moveDir_ * pawn_->GetMoveForce() *0.25);//0.25 to dampen it

    //get the speed that we are travelling, that will determine when we turn around
    if(!flipped_)
    {
        //before we are flipped around, we drive the turning animation
        //float spd = pawn_->GetPlaneVelocity().Length();
        //float turnTime = Fit(spd,0.0f,speed_,1.0f,0.0f);
        
        animCtrl->PlayExclusive("Models/Man/MAN_TurnSkidGunning.ani", 0,false, 0.1f);
        //animCtrl->SetTime("Models/Man/MAN_TurnSkidGunning.ani",turnTime);

        if(animCtrl->IsAtEnd("Models/Man/MAN_TurnSkidGunning.ani"))
        {
            Turn();
            animCtrl->Play("Models/Man/MAN_TurnSkidGunningFlipped.ani", false, 0.0f);
            flipped_=true;
        }
    }
    else
    {
        animCtrl->Play("Models/Man/MAN_TurnSkidGunningFlipped.ani", false, 0.0f);
        //now that we are flipped we can set it to the next state too
        pawn_->SetState( new StateCharacterRunning(context_) );
    }
}