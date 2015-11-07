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

#include "PU_Gun01.h"

#include "Gun01.h"

#include "Character.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>

PU_Gun01::PU_Gun01(Context* context) :
    PickUp(context)
    //yaw_(0.0f),
    //pitch_(0.0f),
    //touchEnabled_(false),
    //screenJoystickIndex_(M_MAX_UNSIGNED),
    //screenJoystickSettingsIndex_(M_MAX_UNSIGNED),
    //paused_(false)
{
    //CameraLogic::RegisterObject(context);
    //SetUpdateEventMask(USE_FIXEDUPDATE);
    collision_layer_ = 4;
    collision_mask_ = 33;
    mesh_ = String("Man/MAN_gun.mdl");
}
PU_Gun01::~PU_Gun01(){}
//-------------------
//-------------------
void PU_Gun01::RegisterObject(Context* context)
{
    context->RegisterFactory<PU_Gun01>();

}

void PU_Gun01::Start()
{
    // Execute base class startup
    //ApplicationHandler::Start();
    //LOGINFO("Character start");
    SubscribeToEvent(GetNode(), E_NODECOLLISION, URHO3D_HANDLER(PU_Gun01, HandleNodeCollision));

}
void PU_Gun01::Setup()
{
    PickUp::Setup();
    // Set a capsule shape for collision
    //CollisionShape* shape = node_->CreateComponent<CollisionShape>();
    //shape->SetCapsule(0.7f, 1.8f, Vector3(0.0f, 0.9f, 0.0f));
    shape_ = node_->CreateComponent<CollisionShape>();
    shape_->SetBox(Vector3(2.0f, 1.0f, 4.0f));

    node_->SetPosition(Vector3(4.0f, 8.0f, 0.0f));//objectNode
    node_->SetRotation(Quaternion(33.0f,78.0f,24.0f));

    // Create the character logic component, which takes care of steering the rigidbody
    // Remember it so that we can set the controls. Use a WeakPtr because the scene hierarchy already owns it
    // and keeps it alive as long as it's not removed from the hierarchy
    //character_ = objectNode->CreateComponent<Character>();

}

void PU_Gun01::FixedUpdate(float timeStep)
{
    
    //body->ApplyImpulse(Vector3::FORWARD);
}void PU_Gun01::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeCollision;

    PickUp::HandleNodeCollision(eventType, eventData);
    
    if(collected_)
    {
        //LOGINFO("collected");
        Node* otherNode = static_cast<Node*>(eventData[P_OTHERNODE].GetPtr());
        Node* boneNode = otherNode->GetChild(String("gun"), true);//get the bone that holds the gun

        if(!boneNode)
        {
            //LOGWARNING("Could not find bone " + String("Gun") );
        }
        else
        {
            String debugHover = String( boneNode->GetName() );
            GetSubsystem<DebugHud>()->SetAppStats("boneNode:", debugHover);

            Node* gunNode = boneNode->CreateChild("gun_01");
            Gun01* weapon = gunNode->CreateComponent<Gun01>();
            weapon->Setup();

            //we need to give the weapon to the character
            Character* character =  otherNode->GetComponent<Character>();
            if(character != NULL)
            {
                character->EquipWeapon(weapon);
                //GetSubsystem<DebugHud>()->SetAppStats("pickup:", String("we have a character") );
            }
        }
        //now I need to equip the pickup
        
        //weapon_->Setup();

        //remove the pickup after everything is given
        node_->Remove();
        //delete this;
    }
    //
}


