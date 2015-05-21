#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Scene.h>

#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Scene/SceneEvents.h>

#include "Actor.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>


Actor::Actor(Context* context) :
    LogicComponent(context)
{
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    SetUpdateEventMask(USE_FIXEDUPDATE);
}

void Actor::RegisterObject(Context* context)
{
    context->RegisterFactory<Actor>();

}

/*void Actor::Start()
{
    // Component has been inserted into its scene node. Subscribe to events now
    SubscribeToEvent(GetNode(), E_NODECOLLISION, HANDLER(Actor, HandleNodeCollision));
}*/

void Actor::FixedUpdate(float timeStep)
{
	timeIncrement_+=timeStep;
    // Disappear when duration expired
    if (duration_ >= 0){
      duration_ -= timeStep;
      if (duration_ <= 0)
          node_->Remove();
    }
    /// \todo Could cache the components for faster access instead of finding them each frame
    /*RigidBody* body = GetComponent<RigidBody>();
    AnimationController* animCtrl = GetComponent<AnimationController>();
    
    // Update the in air timer. Reset if grounded
    if (!onGround_)
        inAirTimer_ += timeStep;
    else
        inAirTimer_ = 0.0f;
    // When character has been in air less than 1/10 second, it's still interpreted as being on ground
    bool softGrounded = inAirTimer_ < INAIR_THRESHOLD_TIME;
    
    // Update movement & animation
    const Quaternion& rot = node_->GetRotation();
    Vector3 moveDir = Vector3::ZERO;
    const Vector3& velocity = body->GetLinearVelocity();
    // Velocity on the XZ plane
    Vector3 planeVelocity(velocity.x_, 0.0f, velocity.z_);
    
    if (controls_.IsDown(CTRL_FORWARD))
        moveDir += Vector3::FORWARD;
    if (controls_.IsDown(CTRL_BACK))
        moveDir += Vector3::BACK;
    if (controls_.IsDown(CTRL_LEFT))
        moveDir += Vector3::LEFT;
    if (controls_.IsDown(CTRL_RIGHT))
        moveDir += Vector3::RIGHT;
    
    // Normalize move vector so that diagonal strafing is not faster
    if (moveDir.LengthSquared() > 0.0f)
        moveDir.Normalize();
    
    // If in air, allow control, but slower than when on ground
    body->ApplyImpulse(rot * moveDir * (softGrounded ? MOVE_FORCE : INAIR_MOVE_FORCE));
    
    if (softGrounded)
    {
        // When on ground, apply a braking force to limit maximum ground velocity
        Vector3 brakeForce = -planeVelocity * BRAKE_FORCE;
        body->ApplyImpulse(brakeForce);
        
        // Jump. Must release jump control inbetween jumps
        if (controls_.IsDown(CTRL_JUMP))
        {
            if (okToJump_)
            {
                body->ApplyImpulse(Vector3::UP * JUMP_FORCE);
                okToJump_ = false;
            }
        }
        else
            okToJump_ = true;
    }
    
    // Play walk animation if moving on ground, otherwise fade it out
    if (softGrounded && !moveDir.Equals(Vector3::ZERO))
        animCtrl->PlayExclusive("Models/Jack_Walk.ani", 0, true, 0.2f);
    else
        animCtrl->Stop("Models/Jack_Walk.ani", 0.2f);
    // Set walk animation speed proportional to velocity
    animCtrl->SetSpeed("Models/Jack_Walk.ani", planeVelocity.Length() * 0.3f);
    
    // Reset grounded flag for next frame
    onGround_ = false;*/
}

void Actor::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
{
    // Check collision contacts and see if character is standing on ground (look for a contact that has near vertical normal)
    using namespace NodeCollision;
    
    MemoryBuffer contacts(eventData[P_CONTACTS].GetBuffer());
    
    while (!contacts.IsEof())
    {
        Vector3 contactPosition = contacts.ReadVector3();
        Vector3 contactNormal = contacts.ReadVector3();
        /*float contactDistance = */contacts.ReadFloat();
        /*float contactImpulse = */contacts.ReadFloat();
        
        // If contact is below node center and mostly vertical, assume it's a ground contact
        if (contactPosition.y_ < (node_->GetPosition().y_ + 1.0f))
        {
            float level = Abs(contactNormal.y_);
            if (level > 0.75)
                onGround_ = true;
        }
    }
}