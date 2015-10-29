#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Scene.h>

#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/AnimationController.h>

#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/Material.h>

#include <Urho3D/Input/Controls.h>

#include "Pawn.h"
#include "../core/ApplicationInput.h"
#include "../game/Weapon.h"
#include "State.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>


Pawn::Pawn(Context* context) :
    Actor(context),
    moveForce_(3.0f),
    inAirMoveForce_(0.02f),
    brakeForce_(0.1f),
    jumpForce_(14.0f),
    //jumpDownForce_(0.5f),
    yawSensitivity_(0.1f),
    inAirThresholdTime_(0.1f),
    okToJump_(true),
    inAirTimer_(0.0f)
{
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    //SetUpdateEventMask(USE_FIXEDUPDATE);
}
Pawn::~Pawn(){}

//void Actor::RegisterObject(Context* context)
//{
//    context->RegisterFactory<Actor>();
//}

void Pawn::Possess(ApplicationInput* applicationInput)
{
    applicationInput_ = applicationInput;
}
void Pawn::EquipWeapon(Weapon* weapon)
{
    weapon_ = weapon;
}
//to be able to manually set the state from another state
void Pawn::SetState(State* state)
{
    state_ = state;
    //state_->Enter(static_cast<Pawn*>(this));
    state_->Enter(this);
}
void Pawn::SetArmsState(State* state)
{
    stateArms_ = state;
    //stateArms_->Enter(static_cast<Pawn*>(this));
    stateArms_->Enter(this);
}

void Pawn::FixedUpdate(float timeStep)
{
    Actor::FixedUpdate(timeStep);
    //rigid body data
    velocity_ = body_->GetLinearVelocity();
    planeVelocity_ = Vector3(velocity_.x_, 0.0f, velocity_.z_);
    jumpVelocity_ = Vector3(0.0f, velocity_.y_, 0.0f);
}

void Pawn::Setup()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    node_->SetPosition(Vector3(0.0f, 1.0f, 0.0f));//objectNode

    // Create the rendering component + animation controller
    AnimatedModel* object = node_->CreateComponent<AnimatedModel>();
    object->SetModel(cache->GetResource<Model>("Models/"+mesh_));
    //object->SetMaterial(cache->GetResource<Material>("Materials/Jack.xml"));
    object->SetCastShadows(true);

    animationController_ = node_->CreateComponent<AnimationController>();

    // Set the head bone for manual control
    //object->GetSkeleton().GetBone("Bip01_Head")->animated_ = false;

    // Create rigidbody, and set non-zero mass so that the body becomes dynamic
    //RigidBody* body = node_->CreateComponent<RigidBody>();
    body_ = node_->CreateComponent<RigidBody>();
    body_->SetCollisionLayer(collision_layer_);
    body_->SetCollisionMask(collision_mask_);
    body_->SetMass(1.0f);

    // Set zero angular factor so that physics doesn't turn the character on its own.
    // Instead we will control the character yaw manually
    body_->SetAngularFactor(Vector3::ZERO);

    // Set the rigidbody to signal collision also when in rest, so that we get ground collisions properly
    body_->SetCollisionEventMode(COLLISION_ALWAYS);

    //we still need to setup the collisionshape in the child class
}

void Pawn::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
{
    Actor::HandleNodeCollision(eventType, eventData);
    //
}