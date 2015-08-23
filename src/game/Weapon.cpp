#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Scene.h>

#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
//#include <Urho3D/Graphics/AnimationController.h>

#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/Material.h>

#include "Weapon.h"
#include "Projectile.h"
//#include "../piece/Character.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>


Weapon::Weapon(Context* context) :
    Actor(context),
    firing_(0),
    fire_velocity_(50.0f),
    firing_timer_(0.0f),
    firing_interval_(0.2f),
    fire_off_(Vector3(0.0f,0.0f,2.0f)),
    lefthand_off_(Vector3(-0.2f,0.0f,1.1f))
{
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    SetUpdateEventMask(USE_FIXEDUPDATE);
    mesh_ = String("Man/MAN_gun.mdl");
    //collision_layer_ = 4;
    //collision_mask_ = 33;
    //SubscribeToEvent(E_SCENEDRAWABLEUPDATEFINISHED, HANDLER(Weapon, HandleSceneDrawableUpdateFinished));
}
Weapon::~Weapon(){}

void Weapon::FixedUpdate(float timeStep)
{
    Actor::FixedUpdate(timeStep);
    //something
    //SetLeftHandOffset();
}
void Weapon::Setup()
{
	ResourceCache* cache = GetSubsystem<ResourceCache>();

    //node_->SetPosition(Vector3(4.0f, 1.0f, 0.0f));//objectNode

    // Create the rendering component + animation controller
    //AnimatedModel* object = node_->CreateComponent<AnimatedModel>();
    StaticModel* object = node_->CreateComponent<StaticModel>();
    object->SetModel(cache->GetResource<Model>("Models/"+mesh_));
    object->SetMaterial(cache->GetResource<Material>("Materials/Jack.xml"));
    object->SetCastShadows(true);
    //node_->CreateComponent<AnimationController>();

    // Set the head bone for manual control
    //object->GetSkeleton().GetBone("Bip01_Head")->animated_ = false;

    // Create rigidbody, and set non-zero mass so that the body becomes dynamic
    /*RigidBody* body = node_->CreateComponent<RigidBody>();
    body->SetCollisionLayer(collision_layer_);
    body->SetCollisionMask(collision_mask_);
    body->SetMass(1.0f);

    // Set zero angular factor so that physics doesn't turn the character on its own.
    // Instead we will control the character yaw manually
    body->SetAngularFactor(Vector3::ZERO);

    // Set the rigidbody to signal collision also when in rest, so that we get ground collisions properly
    body->SetCollisionEventMode(COLLISION_ALWAYS);*/
}
/*void Weapon::Attach(Node* bone)
{

}*/
//void Weapon::HandleSceneDrawableUpdateFinished(StringHash eventType, VariantMap& eventData)
//{ 
//    node_->Rotate(kick_rot_);
//}

void Weapon::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
{
    //Weapons only really care about collision with the character
   /* using namespace NodeCollision;
    //Actor::HandleNodeCollision(eventType, eventData);
    //
    Node* otherNode = static_cast<Node*>(eventData[P_OTHERNODE].GetPtr());
    //RigidBody* otherBody = static_cast<RigidBody*>(eventData[P_OTHERBODY].GetPtr());
    //MemoryBuffer contacts(eventData[P_CONTACTS].GetBuffer());

    Actor* actor = static_cast<Actor*>(otherNode->GetComponent<Character>());
    if(actor != NULL)
    {
        Actor::HandleNodeCollision(eventType,eventData);
        //collected_=true;
        //LOGINFO("ACTOR CHARACTER COLLISION");
    }*/
}

////firing mechanisms
void Weapon::SetFireRate(float fireRate)
{
    //i should send in an actual rate and do the math, fire rate per second.
    //as it is now, i send in the edsired interval
    firing_interval_ = fireRate;
}
void Weapon::Fire(float timeStep)
{
    //do the firing part
    if(firing_)//if we are firing, just deal with the timer
    {
        firing_timer_ += timeStep;

        //this is a lame attempt at setting it back
        //node_->SetRotation(Quaternion());
        //node_->Translate(-kick_off_);
        //kick_off_=Vector3(0.0f,0.0f,0.0f);
        
        if(firing_timer_ > firing_interval_)
        {
            firing_timer_=0.0f;
            SpawnProjectile();
        }
    }
    else
    {
        firing_ = 1;
        firing_timer_ = timeStep;
        SpawnProjectile();
    }
    //SpawnProjectile();   
}
void Weapon::ReleaseFire()
{
    firing_ = 0;
    firing_timer_ = 0.0f;
    node_->SetTransform(Vector3(),Quaternion());
    //kick_rot_ = Quaternion();
    //node_->SetRotation(Quaternion());
}
void Weapon::SpawnProjectile()
{
    //I think that before I make the projectile, I should move the gun, to straighted it, as well as create kick
    Quaternion rot = node_->GetWorldRotation();
    Vector3 pos = node_->GetWorldPosition();

    //initlal rotation of fire_direction
    Vector3 rotoff = rot*fire_off_;
    Vector3 offpos = pos+rotoff;
    Vector3 dir = rotoff.Normalized()*Vector3(1.0f,1.0f,0.0f);//make sure its stays on plane

    //get rotation axis
    //Vector3 rotaxis = dir.CrossProduct(Vector3(0.0f,1.0f,0.0f));//local to the gun
    Vector3 rotaxis = Vector3(0.0f,1.0f,0.0f);//local to the gun
    kick_rot_ = Quaternion(Random(12.0f),rotaxis);
    //node_->Rotate(kick_rot_,TS_WORLD);
    kick_off_ = Vector3(Random(0.3f),Random(0.3f),Random(0.3f));
    //node_->Translate(kick_off_,TS_WORLD);

    node_->SetTransform(kick_off_,kick_rot_);

    //SetLeftHandOffset();

    //GetSubsystem<DebugHud>()->SetAppStats("gun_pos:", String(pos) );
    //GetSubsystem<DebugHud>()->SetAppStats("gun_rot:", String(rot) );

    Node* projectileNode_ = node_->GetScene()->CreateChild("projectile");
    projectileNode_->SetPosition(offpos);

    Projectile* projectile_ = projectileNode_->CreateComponent<Projectile>();
    projectile_->Setup(dir);
    //projectileNode_.position = node.worldPosition+aprojectile_offset_[0];
    //Projectile@ node_script_ = cast<Projectile>(projectile_.CreateScriptObject(scriptFile, ctype_, LOCAL));
    //node_script_.set_parmameters(dir,fire_velocity_,isenemy_,hit); 
    //i need to get the position and the rotation of the weapon to determine the location and roation to spawn at
}

Vector3 Weapon::GetLeftHandTarget()
{
    //get the updated world position to update target positions for IK
    Matrix3x4 updated_trans = node_->GetWorldTransform();
    //GetSubsystem<DebugHud>()->SetAppStats("gun_pos:", updated_trans*lefthand_off_ );
    return updated_trans * lefthand_off_ ;
}