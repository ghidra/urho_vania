#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Scene.h>

#include <Urho3D/Physics/PhysicsEvents.h>

#include "Projectile01.h"


Projectile01::Projectile01(Context* context) :
    Projectile(context)
{
    mesh_ = String("Sphere.mdl");
    speed_ = 10.0f;
}
Projectile01::~Projectile01(){}
//-------------------
//-------------------
void Projectile01::RegisterObject(Context* context)
{
    context->RegisterFactory<Projectile01>();

}

void Projectile01::Start()
{
    Projectile::Start();
    //debug_->LogWarning("projectile01 start");
    SubscribeToEvent(GetNode(), E_NODECOLLISION, URHO3D_HANDLER(Projectile01, HandleNodeCollision));

}
void Projectile01::Setup(const Vector3 direction)
{
    Projectile::Setup(direction);

}

void Projectile01::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeCollision;
    Projectile::HandleNodeCollision(eventType, eventData);
}


