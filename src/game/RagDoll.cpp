#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?

#include "RagDoll.h"

#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/RigidBody.h>

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>

RagDoll::RagDoll(Context* context):
    Object(context)
{
}
RagDoll::~RagDoll(){}

void RagDoll::Setup(Pawn* pawn)
{

}
