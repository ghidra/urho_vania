#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Context.h>
//#include <Urho3D/Scene/Scene.h>

#include <Urho3D/Graphics/AnimatedModel.h>

//#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Physics/CollisionShape.h>

/*#include <Urho3D/Input/Controls.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/Input/Input.h>*/

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

#include "Character.h"
#include "../core/ApplicationInput.h"//i need this for the control constants

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>

Character::Character(Context* context) :
    Actor(context)
    //yaw_(0.0f),
    //pitch_(0.0f),
    //touchEnabled_(false),
    //screenJoystickIndex_(M_MAX_UNSIGNED),
    //screenJoystickSettingsIndex_(M_MAX_UNSIGNED),
    //paused_(false)
{
    //CameraLogic::RegisterObject(context);
    //SetUpdateEventMask(USE_FIXEDUPDATE);
}

//-------------------
//-------------------
void Character::RegisterObject(Context* context)
{
    context->RegisterFactory<Character>();

}

void Character::Start()
{
    // Execute base class startup
    //ApplicationHandler::Start();
    //LOGINFO("Character start");
    SubscribeToEvent(GetNode(), E_NODECOLLISION, HANDLER(Character, HandleNodeCollision));

}
void Character::Setup(SharedPtr<Scene> scene, SharedPtr<Node> cameraNode)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    //scene_ does not exists?
    //Node* objectNode = scene->CreateChild("Jack");
    node_->SetPosition(Vector3(0.0f, 1.0f, 0.0f));//objectNode

    // Create the rendering component + animation controller
    AnimatedModel* object = node_->CreateComponent<AnimatedModel>();
    object->SetModel(cache->GetResource<Model>("Models/Man/MAN.mdl"));
    //object->SetMaterial(cache->GetResource<Material>("Materials/Jack.xml"));
    object->SetCastShadows(true);
    node_->CreateComponent<AnimationController>();

    // Set the head bone for manual control
    //object->GetSkeleton().GetBone("Bip01_Head")->animated_ = false;

    // Create rigidbody, and set non-zero mass so that the body becomes dynamic
    RigidBody* body = node_->CreateComponent<RigidBody>();
    body->SetCollisionLayer(1);
    body->SetMass(1.0f);

    // Set zero angular factor so that physics doesn't turn the character on its own.
    // Instead we will control the character yaw manually
    body->SetAngularFactor(Vector3::ZERO);

    // Set the rigidbody to signal collision also when in rest, so that we get ground collisions properly
    body->SetCollisionEventMode(COLLISION_ALWAYS);

    // Set a capsule shape for collision
    CollisionShape* shape = node_->CreateComponent<CollisionShape>();
    shape->SetCapsule(0.7f, 1.8f, Vector3(0.0f, 0.9f, 0.0f));

    // Create the character logic component, which takes care of steering the rigidbody
    // Remember it so that we can set the controls. Use a WeakPtr because the scene hierarchy already owns it
    // and keeps it alive as long as it's not removed from the hierarchy
    //character_ = objectNode->CreateComponent<Character>();

}

/*void Character::Control(Controls* controls)
{
    if(controls->IsDown(CTRL_UP))
    {
        LOGINFO("controls from in character");
        //im not sure moving rigid bides here are right
        //RigidBody* body = GetComponent<RigidBody>();
        //body->ApplyImpulse(Vector3::FORWARD);
    }
}*/

void Character::FixedUpdate(float timeStep)
{
    if(applicationInput_)
    {
        if(!applicationInput_->IsDebugCamera())//if we are not in debug camera mode
        {
            //we are possessed by the application controller
            Controls& ctrl = applicationInput_->controls_;

            AnimationController* animCtrl = GetComponent<AnimationController>();

            //LOGINFO("MOVE ME");
            RigidBody* body = GetComponent<RigidBody>();
            // Update movement & animation
            const Quaternion& rot = node_->GetRotation();
            Vector3 moveDir = Vector3::ZERO;
            const Vector3& velocity = body->GetLinearVelocity();
            // Velocity on the XZ plane
            Vector3 planeVelocity(velocity.x_, 0.0f, velocity.z_);
            
            if (ctrl.IsDown(CTRL_UP))
                moveDir += Vector3::FORWARD;
            if (applicationInput_->controls_.IsDown(CTRL_DOWN))
                moveDir += Vector3::BACK;
            if (applicationInput_->controls_.IsDown(CTRL_LEFT))
                moveDir += Vector3::LEFT;
            if (applicationInput_->controls_.IsDown(CTRL_RIGHT))
                moveDir += Vector3::RIGHT;
            
            // Normalize move vector so that diagonal strafing is not faster
            if (moveDir.LengthSquared() > 0.0f)
                moveDir.Normalize();
            
            // If in air, allow control, but slower than when on ground
            body->ApplyImpulse(rot * moveDir * 0.3);

            //now control animation
            // Play walk animation if moving on ground, otherwise fade it out
            if (!moveDir.Equals(Vector3::ZERO))
                animCtrl->PlayExclusive("Models/Man/MAN_RunningGunning.ani", 0, true, 0.2f);
            else
                animCtrl->Stop("Models/Man/MAN_RunningGunning.ani", 0.2f);
            // Set walk animation speed proportional to velocity
            animCtrl->SetSpeed("Models/Man/MAN_RunningGunning.ani", planeVelocity.Length() * 0.3f);
    

        }
    }
    
    //body->ApplyImpulse(Vector3::FORWARD);
}
