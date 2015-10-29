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
	
	//now we can set the animatoin

	/*Vector3 jumpVector = pawn_->GetJumpVelocity();
	//first we need to set that we are jumping before we check that we are falling.
	//its not working to set a bool in enter, so lest wait and check here
	if(!jumping_ && jumpVector.y_>0.1)
		jumping_=true;
	//now, once we start to decend, we are falling, set the appropriate state
	if(jumpVector.y_<=0.1 && jumping_)
		pawn_->SetState(new StateCharacterFalling(context_));

	AnimationController* animCtrl = pawn_->GetAnimationController();
    float jumpTime = Fit(jumpVector.y_,0.0f,-pawn_->GetJumpForce(),0.5f,1.0f);;
    
    animCtrl->PlayExclusive("Models/Man/MAN_Jumping.ani", 0,false, 0.1f);
    animCtrl->SetTime("Models/Man/MAN_Jumping.ani",jumpTime);*/
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