#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Scene.h>

#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Scene/SceneEvents.h>

#include "PickUp.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>


PickUp::PickUp(Context* context) :
    Actor(context)
{
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    SetUpdateEventMask(USE_FIXEDUPDATE);
}

void PickUp::FixedUpdate(float timeStep)
{
    Actor::FixedUpdate(timeStep);
    //something
}

void PickUp::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
{
    Actor::HandleNodeCollision(eventType, eventData);
    //
}