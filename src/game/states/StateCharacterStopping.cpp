#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?

#include "../../framework/src/PawnAnimated.h"

#include "StateCharacterStopping.h"
#include "StateCharacterIdle.h"
#include "StateCharacterRunning.h"


StateCharacterStopping::StateCharacterStopping(Context* context):
    StateCharacterGrounded(context)
{
    name_=String("stopping");
}
StateCharacterStopping::~StateCharacterStopping(){}

void StateCharacterStopping::Enter(Pawn* pawn)
{
    State::Enter(pawn);
    pawn_->GetBody()->SetFriction(1.0f);//no sliding on ground
}


State* StateCharacterStopping::HandleInput(Controls& ctrl)
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
			return new StateCharacterRunning(context_);
		}
		else
		{
			return NULL;
			//defer to grounded
			
		}
	}
}
void StateCharacterStopping::Update(float timeStep)
{
	StateCharacterGrounded::Update();//apply the brake force

	RigidBody* body = pawn_->GetBody();
	AnimationController* animCtrl = static_cast<PawnAnimated*>(pawn_)->GetAnimationController();

	//animation

	float skid = pawn_->GetPlaneVelocity().Length();

	if(skid<=0.1)
		pawn_->SetState(new StateCharacterIdle(context_));

    float skidTime = Fit(skid,pawn_->GetMoveForce(),0.0f,0.0f,0.03f);

    //GetSubsystem<DebugHud>()->SetAppStats("animtion speed:", skidTime );

    animCtrl->PlayExclusive("Models/Man/MAN_TurnSkidGunning.ani", 0,false, 0.2f);
    animCtrl->SetTime("Models/Man/MAN_TurnSkidGunning.ani",skidTime);
}