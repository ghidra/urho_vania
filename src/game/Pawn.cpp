#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Scene.h>

#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/Input/Controls.h>

#include "Pawn.h"
#include "../core/ApplicationInput.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>


Pawn::Pawn(Context* context) :
    Actor(context)
{
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    SetUpdateEventMask(USE_FIXEDUPDATE);
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

void Pawn::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
{
    Actor::HandleNodeCollision(eventType, eventData);
    //
}