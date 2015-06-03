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

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>


Pawn::Pawn(Context* context) :
    Actor(context)
{
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    //SetUpdateEventMask(USE_FIXEDUPDATE);
}

//void Actor::RegisterObject(Context* context)
//{
//    context->RegisterFactory<Actor>();
//}

void Pawn::Possess(ApplicationInput* applicationInput)
{
    applicationInput_ = applicationInput;
}

void Pawn::FixedUpdate(float timeStep)
{
    Actor::FixedUpdate(timeStep);
    //something
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
    node_->CreateComponent<AnimationController>();

    // Set the head bone for manual control
    //object->GetSkeleton().GetBone("Bip01_Head")->animated_ = false;

    // Create rigidbody, and set non-zero mass so that the body becomes dynamic
    RigidBody* body = node_->CreateComponent<RigidBody>();
    body->SetCollisionLayer(collision_layer_);
    body->SetCollisionMask(collision_mask_);
    body->SetMass(1.0f);

    // Set zero angular factor so that physics doesn't turn the character on its own.
    // Instead we will control the character yaw manually
    body->SetAngularFactor(Vector3::ZERO);

    // Set the rigidbody to signal collision also when in rest, so that we get ground collisions properly
    body->SetCollisionEventMode(COLLISION_ALWAYS);

    //we still need to setup the collisionshape in the child class
}

void Pawn::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
{
    Actor::HandleNodeCollision(eventType, eventData);
    //
}