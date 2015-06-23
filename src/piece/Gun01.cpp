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

#include "Gun01.h"

#include "../game/Weapon.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>

Gun01::Gun01(Context* context) :
    Weapon(context)
{
    //CameraLogic::RegisterObject(context);
    //SetUpdateEventMask(USE_FIXEDUPDATE);
    //collision_layer_ = 4;
    //collision_mask_ = 33;
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
    // Execute base class startup
    //ApplicationHandler::Start();
    //LOGINFO("Character start");
    SubscribeToEvent(GetNode(), E_NODECOLLISION, HANDLER(Gun01, HandleNodeCollision));

}
void Gun01::Setup()
{
    Weapon::Setup();
    // Set a capsule shape for collision
    //CollisionShape* shape = node_->CreateComponent<CollisionShape>();
    //shape->SetCapsule(0.7f, 1.8f, Vector3(0.0f, 0.9f, 0.0f));

    // Create the character logic component, which takes care of steering the rigidbody
    // Remember it so that we can set the controls. Use a WeakPtr because the scene hierarchy already owns it
    // and keeps it alive as long as it's not removed from the hierarchy
    //character_ = objectNode->CreateComponent<Character>();

}

void Gun01::FixedUpdate(float timeStep)
{
    
    //body->ApplyImpulse(Vector3::FORWARD);
}void Gun01::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeCollision;

    Weapon::HandleNodeCollision(eventType, eventData);
    
    /*if(collected_)
    {
        //LOGINFO("collected");
        Node* otherNode = static_cast<Node*>(eventData[P_OTHERNODE].GetPtr());
        Node* boneNode = otherNode->GetChild(String("wrist.R"), true);//get the bone that holds the gun

        if(!boneNode)
        {
            LOGWARNING("Could not find bone " + String("Gun") );
        }else{
            String debugHover = String( boneNode->GetName() );
            GetSubsystem<DebugHud>()->SetAppStats("boneNode:", debugHover);
        }
        //now I need to equip the pickup
        Node* gunNode = boneNode->CreateChild("weapon");
        Weapon* weapon_ = gunNode->CreateComponent<Weapon>();
        //weapon_->Setup();

        //remove the pickup after everything is given
        node_->Remove();
        //delete this;
    }*/
    //
}


