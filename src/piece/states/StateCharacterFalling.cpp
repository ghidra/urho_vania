#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?
#include <Urho3D/Physics/PhysicsWorld.h>//for the raycasting
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Graphics/Octree.h>//lets me use ray

#include "StateCharacterFalling.h"
#include "StateCharacterIdle.h"

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
	//set the distanceBottom_
	PhysicsRaycastResult result = FindBottom();

	distanceBottom_=result.distance_;
}

State* StateCharacterFalling::HandleInput(Controls& ctrl, Input* input)
{
    return NULL;
    //return new StateCharacterRunning(context_);
}
void StateCharacterFalling::Update()
{
	//get the pawn rigidbody for ray direction and position
	PhysicsRaycastResult result = FindBottom();
	//if we hit the bottom, resume state based on velocity I suppose, right now just go to idle
	if(result.distance_<0.1)
		pawn_->SetState(new StateCharacterIdle(context_));
	//GetSubsystem<DebugHud>()->SetAppStats("distance:", result.distance_ );
}
//specific function to ray cast to find the bottom rigidbody that we can land on
PhysicsRaycastResult StateCharacterFalling::FindBottom()
{
	RigidBody* body = pawn_->GetBody();
	Vector3 dir = body->GetLinearVelocity();
	//get the physics world to do some raycasting
	PhysicsRaycastResult result;
	PhysicsWorld* pw = pawn_->GetScene()->GetComponent<PhysicsWorld>();
	pw->RaycastSingle( result,Ray(body->GetPosition(), dir.Normalized()), dir.Length()*3 );

	return result;
}