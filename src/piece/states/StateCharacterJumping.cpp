#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?
#include <Urho3D/Physics/RigidBody.h>

#include "StateCharacterJumping.h"

#include "StateCharacterFalling.h"

#include <Urho3D/Input/Input.h>
#include "../../game/Pawn.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>

StateCharacterJumping::StateCharacterJumping(Context* context):
    State(context)
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

State* StateCharacterJumping::HandleInput(Controls& ctrl, Input* input)
{
    return NULL;
    //return new StateCharacterRunning(context_);
}
void StateCharacterJumping::Update()
{
	//i need to get the dot product against gravity to do this right, cause it starts out falling
	float jumpspeed = pawn_->GetJumpVelocity().Length();
	if(jumpspeed<=0.1)
		pawn_->SetState(new StateCharacterFalling(context_));
}