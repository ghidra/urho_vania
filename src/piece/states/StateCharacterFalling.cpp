#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?
#include <Urho3D/Physics/RigidBody.h>

#include "StateCharacterFalling.h"

#include <Urho3D/Input/Input.h>
#include "../../game/Pawn.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>

StateCharacterFalling::StateCharacterFalling(Context* context):
    State(context)
{
    name_=String("falling");
}
StateCharacterFalling::~StateCharacterFalling(){}

void StateCharacterFalling::Enter(Pawn* pawn)
{
	State::Enter(pawn);
	RigidBody* body = pawn_->GetBody();
	body->ApplyImpulse(Vector3::UP * pawn_->GetJumpForce() );
}

State* StateCharacterFalling::HandleInput(Controls& ctrl, Input* input)
{
    return NULL;
    //return new StateCharacterRunning(context_);
}
void StateCharacterFalling::Update()
{
}