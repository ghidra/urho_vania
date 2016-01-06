#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?

#include "../../framework/src/PawnAnimated.h"

#include "StateCharacterIdle.h"
#include "StateCharacterRunning.h"
#include "StateCharacterJumping.h"
#include "StateCharacterTurning.h"

StateCharacterIdle::StateCharacterIdle(Context* context):
    StateCharacterGrounded(context),
    firing_(false)
{
    name_=String("idle");
}
StateCharacterIdle::~StateCharacterIdle(){}

void StateCharacterIdle::Enter(Pawn* pawn)
{
    State::Enter(pawn);
    pawn_->GetBody()->SetFriction(1.0f);//no sliding on ground
    //GetSubsystem<DebugHud>()->SetAppStats("init distance:", result.distance_ );
}

State* StateCharacterIdle::HandleInput(Controls& ctrl)
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
            if(TestTurn())
                return new StateCharacterTurning(context_);
            else
                return new StateCharacterRunning(context_);
        }
        else
        {
            if(ctrl.IsDown(CTRL_FIRE))
            {
                firing_=true;
            }
            else
            {
                firing_=false;
                return NULL;
            }
        }
    }
}
void StateCharacterIdle::Update()
{
    StateCharacterGrounded::Update();//apply brake force
    AnimationController* animCtrl = static_cast<PawnAnimated*>(pawn_)->GetAnimationController();
    String ani = String("Models/Man/MAN_StandingIdleGun.ani");
    if(firing_)
        ani=String("Models/Man/MAN_StandingShooting.ani");

    animCtrl->PlayExclusive(ani, 0,true, 0.5f);
}
void StateCharacterIdle::Exit()
{
    pawn_->GetBody()->SetFriction(0.0f);//no sliding on ground
}