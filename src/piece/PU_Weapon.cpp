#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Context.h>

#include <Urho3D/Graphics/AnimatedModel.h>

#include <Urho3D/Physics/CollisionShape.h>

#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/Material.h>

#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>

#include "PU_Weapon.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>

PU_Weapon::PU_Weapon(Context* context) :
    PickUp(context)
    //yaw_(0.0f),
    //pitch_(0.0f),
    //touchEnabled_(false),
    //screenJoystickIndex_(M_MAX_UNSIGNED),
    //screenJoystickSettingsIndex_(M_MAX_UNSIGNED),
    //paused_(false)
{
    //CameraLogic::RegisterObject(context);
    SetUpdateEventMask(USE_FIXEDUPDATE);
    collision_layer_ = 4;
    collision_mask_ = 33;
    mesh_ = String("Man/MAN_gun.mdl");
}

//-------------------
//-------------------
void PU_Weapon::RegisterObject(Context* context)
{
    context->RegisterFactory<PU_Weapon>();

}

void PU_Weapon::Start()
{
    // Execute base class startup
    //ApplicationHandler::Start();
    //LOGINFO("Character start");
    SubscribeToEvent(GetNode(), E_NODECOLLISION, HANDLER(PU_Weapon, HandleNodeCollision));

}
void PU_Weapon::Setup()
{
    PickUp::Setup();
    // Set a capsule shape for collision
    CollisionShape* shape = node_->CreateComponent<CollisionShape>();
    shape->SetCapsule(0.7f, 1.8f, Vector3(0.0f, 0.9f, 0.0f));

    // Create the character logic component, which takes care of steering the rigidbody
    // Remember it so that we can set the controls. Use a WeakPtr because the scene hierarchy already owns it
    // and keeps it alive as long as it's not removed from the hierarchy
    //character_ = objectNode->CreateComponent<Character>();

}

void PU_Weapon::FixedUpdate(float timeStep)
{
    
    //body->ApplyImpulse(Vector3::FORWARD);
}
