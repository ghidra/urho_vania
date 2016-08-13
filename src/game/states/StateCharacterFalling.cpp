#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?
#include <Urho3D/Physics/PhysicsWorld.h>//for the raycasting
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Graphics/Octree.h>//lets me use ray

#include "../../framework/src/PawnAnimated.h"

#include "StateCharacterFalling.h"
#include "StateCharacterIdle.h"

StateCharacterFalling::StateCharacterFalling(Context* context):
    State(context)
{
    name_=String("falling");
}
StateCharacterFalling::~StateCharacterFalling(){}

void StateCharacterFalling::Enter(Pawn* pawn)
{
	State::Enter(pawn);
	//if(pawn_->GetBody()!=NULL)
	if(pawn_->GetNode()->HasComponent<RigidBody>())
	{
		PhysicsRaycastResult result = FindBottom();
		distanceBottom_=result.distance_;
	}
	else
	{
		distanceBottom_=0.1f;//we dont have a rigidbody
	}
	//GetSubsystem<DebugHud>()->SetAppStats("init distance:", result.distance_ );
}

State* StateCharacterFalling::HandleInput(Controls& ctrl)
{
    return NULL;
    //return new StateCharacterRunning(context_);
}
void StateCharacterFalling::Update(float timeStep)
{
	if(pawn_->GetNode()->HasComponent<RigidBody>())
	{
		//get the pawn rigidbody for ray direction and position
		PhysicsRaycastResult result = FindBottom();
		//if we hit the bottom, resume state based on velocity I suppose, right now just go to idle
		if(result.distance_<0.1)
			pawn_->SetState(new StateCharacterIdle(context_));
	}
	else
	{
		pawn_->SetState(new StateCharacterIdle(context_));
	}
	
	//now we can set the animation

	AnimationController* animCtrl = static_cast<PawnAnimated*>(pawn_)->GetAnimationController();
    //Vector3 jumpVector = pawn_->GetJumpVelocity();
    //float jumpTime = Fit(jumpVector.y_,0.0f,-pawn_->GetJumpForce(),0.5f,1.0f);//force based
    //float jumpTime = Fit(result.distance_,distanceBottom_,0.1f,0.5f,1.0f);
    Vector3 vel = pawn_->GetJumpVelocity();
    float jumpTime = Fit(abs(vel.y_),0.0f,pawn_->GetJumpForce(),0.5f,1.0f);
    //GetSubsystem<DebugHud>()->SetAppStats("distance:", result.distance_ );
    //GetSubsystem<DebugHud>()->SetAppStats("fallspeed:", abs(vel.y_) );
    
    animCtrl->PlayExclusive("Models/Man/MAN_Jumping.ani", 0,false, 0.1f);
    animCtrl->SetTime("Models/Man/MAN_Jumping.ani",jumpTime);
}
//specific function to ray cast to find the bottom rigidbody that we can land on
PhysicsRaycastResult StateCharacterFalling::FindBottom()
{
	RigidBody* body = pawn_->GetBody();
	Vector3 dir = body->GetLinearVelocity();
	//get the physics world to do some raycasting
	//i need to do a check to make sure that I am at least getting a vector from linear velocitiy that I can use to check with
	PhysicsRaycastResult result;
	PhysicsWorld* pw = pawn_->GetScene()->GetComponent<PhysicsWorld>();
	pw->RaycastSingle( result,Ray(body->GetPosition(), Vector3::DOWN), 200.0f );

	return result;
}