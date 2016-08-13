#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Scene.h>

#include "Gun01.h"
#include "../framework/src/Weapon.h"
#include "Projectile01.h"

Gun01::Gun01(Context* context) :
    Weapon(context)
{
    mesh_ = String("Man/MAN_gun.mdl");
}
Gun01::~Gun01(){}
//-------------------
//-------------------
void Gun01::RegisterObject(Context* context)
{
    context->RegisterFactory<Gun01>();

}

void Gun01::Start()
{

}
void Gun01::Setup()
{
    Weapon::Setup();

}

void Gun01::FixedUpdate(float timeStep)
{
    
    //body->ApplyImpulse(Vector3::FORWARD);
}

void Gun01::SpawnProjectile()
{
    Weapon::SpawnProjectile();

    Node* projectileNode_ = node_->GetScene()->CreateChild("projectile");
    projectileNode_->SetPosition(projectile_spawn_position_);

    Projectile01* projectile_ = projectileNode_->CreateComponent<Projectile01>();
    projectile_->Setup(projectile_spawn_direction_);
}

