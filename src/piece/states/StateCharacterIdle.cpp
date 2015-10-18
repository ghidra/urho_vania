#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?

/*
#include "../../game/State.h"

Potentially remove the need for a h file
class StateCharacterIdle : public State
{
        public:
                void HandleInput(Pawn& pawn, Input* input);
                //float someNewProperty;
}

*/

#include "StateCharacterIdle.h"

#include <Urho3D/Input/Input.h>
#include "../../game/Pawn.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>

StateCharacterIdle::StateCharacterIdle(Context* context):
    State(context)
{
    name_=String("idle");
}
StateCharacterIdle::~StateCharacterIdle(){}

State* StateCharacterIdle::HandleInput(Pawn* pawn, Input* input)
{
    return new StateCharacterIdle(context_);
}
void StateCharacterIdle::Update(Pawn* pawn)
{
}
//void StateCharacterIdle::Debug(){
    //GetSubsystem<DebugHud>()->SetAppStats("state:", String("pivot") );
    //float skid = body->GetLinearVelocity().Length();
    //float skidTime_a = Fit( skid,moveForce_,0.0f,0.0f,animCtrl->GetLength("Models/Man/MAN_TurnSkidGunning.ani") );
    //GetSubsystem<DebugHud>()->SetAppStats("animtion speed:", skidTime_a );
//}