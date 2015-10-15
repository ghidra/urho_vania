#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Context.h>
//#include <Urho3D/Scene/Scene.h>

#include <Urho3D/Graphics/AnimatedModel.h>

//#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Physics/CollisionShape.h>

/*#include <Urho3D/Input/Controls.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Core/ProcessUtils.h>*/
#include <Urho3D/Input/Input.h>

//#include <Urho3D/IO/FileSystem.h>
//#include <Urho3D/Resource/ResourceCache.h>
//#include <Urho3D/Graphics/Material.h>

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

#include "../core/IK.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>

Character::Character(Context* context) :
    Pawn(context),
    turning(false)
    //yaw_(0.0f),
    //pitch_(0.0f),
    //touchEnabled_(false),
    //screenJoystickIndex_(M_MAX_UNSIGNED),
    //screenJoystickSettingsIndex_(M_MAX_UNSIGNED),
    //paused_(false)
{
    //CameraLogic::RegisterObject(context);
    SetUpdateEventMask(USE_FIXEDUPDATE);
    mesh_ = String("Man/MAN.mdl");
    state_ = State_Idle;//set the initial state
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
    SubscribeToEvent(E_SCENEDRAWABLEUPDATEFINISHED, HANDLER(Character, HandleSceneDrawableUpdateFinished));

}
void Character::Setup()
{
    /*ResourceCache* cache = GetSubsystem<ResourceCache>();

    //scene_ does not exists?
    //Node* objectNode = scene->CreateChild("Jack");
    node_->SetPosition(Vector3(0.0f, 1.0f, 0.0f));//objectNode

    // Create the rendering component + animation controller
    AnimatedModel* object = node_->CreateComponent<AnimatedModel>();
    object->SetModel(cache->GetResource<Model>("Models/"+mesh_));
    //object->SetMaterial(cache->GetResource<Material>("Materials/Jack.xml"));
    object->SetCastShadows(true);
    node_->CreateComponent<AnimationController>();

    // Set the head bone for manual control
    //object->GetSkeleton().GetBone("Bip01_Head")->animated_ = false;

    // Create rigidbody, and set non-zero mass so that the body becomes dynamic
    RigidBody* body = node_->CreateComponent<RigidBody>();
    body->SetCollisionLayer(collision_layer_);
    body->SetCollisionMask(collision_mask_);
    body->SetMass(1.0f);

    // Set zero angular factor so that physics doesn't turn the character on its own.
    // Instead we will control the character yaw manually
    body->SetAngularFactor(Vector3::ZERO);

    // Set the rigidbody to signal collision also when in rest, so that we get ground collisions properly
    body->SetCollisionEventMode(COLLISION_ALWAYS);
    */
    // Set a capsule shape for collision
    Pawn::Setup();//do the basic set up with stored and set values
    //scale it down
    //node_->SetScale(0.5);
    //rotate it to face the right direction
    AnimatedModel* model = GetComponent<AnimatedModel>();
    Skeleton& skeleton = model->GetSkeleton();
    skeleton.GetBone(String("root"))->animated_ = false;

    leftArmIK_ = node_->CreateComponent<IK>();//
    leftArmIK_->CreateChain(String("wrist.L"));
    //leftArmIK_->ToggleDebug();
    rightArmIK_ = node_->CreateComponent<IK>();//
    rightArmIK_->CreateChain(String("wrist.R"));
    //rightArmIK_->ToggleDebug();
    //node_->Rotate(Quaternion(0.0f,90.0f,0.0f));
    //then setup the collision shape
    CollisionShape* shape = node_->CreateComponent<CollisionShape>();
    shape->SetCapsule(3.0f, 10.0f, Vector3(0.0f, 5.0f, 0.0f));

    RigidBody* body = node_->GetComponent<RigidBody>();
    body->SetMass(1.0f);


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
            switch(state_)
            {
                case State_Idle:
                    break;
                case State_Walking:
                    break;
                case State_Running:
                    break;
                case State_Jumping:
                    break;
                case State_Firing:
                    break;
            }
            //we are possessed by the application controller
            Controls& ctrl = applicationInput_->controls_;
            AnimationController* animCtrl = GetComponent<AnimationController>();
            RigidBody* body = GetComponent<RigidBody>();

            Input* input = GetSubsystem<Input>();

            // Update the in air timer. Reset if grounded
            if (!onGround_)
                inAirTimer_ += timeStep;
            else
                inAirTimer_ = 0.0f;
            // When character has been in air less than 1/10 second, it's still interpreted as being on ground
            bool softGrounded = inAirTimer_ < inAirThresholdTime_;

            // Update movement & animation
            const Quaternion& rot = node_->GetRotation();
            Vector3 moveDir = Vector3::ZERO;
            const Vector3& velocity = body->GetLinearVelocity();
            // Velocity on the XZ plane
            Vector3 planeVelocity(velocity.x_, 0.0f, velocity.z_);
            Vector3 jumpVelocity(0.0f, velocity.y_, 0.0f);
            
            if (ctrl.IsDown(CTRL_UP))
                moveDir += Vector3::FORWARD;
            if (ctrl.IsDown(CTRL_DOWN))
                moveDir += Vector3::BACK;
            if (ctrl.IsDown(CTRL_LEFT))
                moveDir += Vector3::LEFT;
            if (ctrl.IsDown(CTRL_RIGHT))
                moveDir += Vector3::RIGHT;

            if(weapon_ != NULL)
            {
                //if(input->GetMouseButtonDown(MOUSEB_LEFT) || input->GetMouseButtonDown(MOUSEB_RIGHT))
                if(ctrl.IsDown(CTRL_FIRE))
                    weapon_->Fire(timeStep);
                else
                    weapon_->ReleaseFire();
                

            }

            // Normalize move vector so that diagonal strafing is not faster
            if (moveDir.LengthSquared() > 0.0f)
            {
                moveDir*=Vector3(1.0f,1.0f,0.0f);//flatten movement out to a plane
                moveDir.Normalize();
            }
            // If in air, allow control, but slower than when on ground
            //body->ApplyImpulse(rot * moveDir * 0.3);
            //body->ApplyImpulse(rot * moveDir * moveForce_);
            body->ApplyImpulse(rot * moveDir * (softGrounded ? moveForce_ : inAirMoveForce_));
            //body->SetLinearVelocity(rot * moveDir * (softGrounded ? moveForce_ : inAirMoveForce_));
    

            //now control animation
            // Play walk animation if moving on ground, otherwise fade it out
            /*if (!moveDir.Equals(Vector3::ZERO))
                animCtrl->PlayExclusive("Models/Man/MAN_RunningGunning.ani", 0, true, 0.2f);
            else
                animCtrl->Stop("Models/Man/MAN_RunningGunning.ani", 0.2f);
            // Set walk animation speed proportional to velocity
            animCtrl->SetSpeed("Models/Man/MAN_RunningGunning.ani", planeVelocity.Length() * 0.3f);
            */
            if (softGrounded)
            {
                // When on ground, apply a braking force to limit maximum ground velocity
                Vector3 brakeForce = -planeVelocity * brakeForce_;
                body->ApplyImpulse(brakeForce);
                
                // Jump. Must release jump control inbetween jumps
                if (applicationInput_->controls_.IsDown(CTRL_JUMP))
                {
                    if (okToJump_)
                    {
                        body->ApplyImpulse(Vector3::UP * jumpForce_);
                        okToJump_ = false;
                    }
                }
                else
                    okToJump_ = true;
            }else{
                //we are in the air and we need a downforce applied so its not like jumping on the moon
                //if( Vector3(0.0f,-1.0f,0.0f).DotProduct(jumpVelocity.Normalized())>=0.0 )
                //{
                //    body->ApplyImpulse(Vector3(0.0f,-1.0f,0.0f)*jumpDownForce_);
                //}
            }
            /////////
            // deal with the orientation of the character
            /////////
            Node* root = node_->GetChild(String("root"),true);
            float dp = planeVelocity.Normalized().DotProduct(Vector3::LEFT);
            
            //String debugHover = String( dp );
            //GetSubsystem<DebugHud>()->SetAppStats("direction dot product:", debugHover);

            if(dp>=0.99)
            {
                root->SetRotation(Quaternion(0.0f,-90.0f,0.0f));
                if(turning)
                {
                    animCtrl->Play("Models/Man/MAN_TurnSkidGunningFlipped.ani", false, 0.0f);
                    turning=false;
                }
                //GetSubsystem<DebugHud>()->SetAppStats("direction:", String("left"));

            }else if(dp<=-0.99)
            {
                root->SetRotation(Quaternion(0.0f,90.0f,0.0f));
                if(turning)
                {
                    animCtrl->Play("Models/Man/MAN_TurnSkidGunningFlipped.ani", false, 0.0f);
                    turning=false;
                }
                //GetSubsystem<DebugHud>()->SetAppStats("direction:", String("right"));
            }

            /////////
            /////////
            // deal with the anmation asepect
            /////////
            /////////

            // Play walk animation if moving on ground, otherwise fade it out
            if (softGrounded && !moveDir.Equals(Vector3::ZERO) )//!moveDir.Equals(Vector3::ZERO) //moveDir.Length()>0.0001
            {
                float dp2 = planeVelocity.Normalized().DotProduct(moveDir);//we are moving in the opposite direction we are trying to go
                if( dp2<0.0f )
                {
                    body->ApplyImpulse(rot * -moveDir * 0.9f * moveForce_);//i ned to make it turn around slower

                    GetSubsystem<DebugHud>()->SetAppStats("animtion:", String("pivot") );
                    float skid = body->GetLinearVelocity().Length();
                    float skidTime_a = Fit( skid,moveForce_,0.0f,0.0f,animCtrl->GetLength("Models/Man/MAN_TurnSkidGunning.ani") );
                    GetSubsystem<DebugHud>()->SetAppStats("animtion speed:", skidTime_a );

                    //animCtrl->Stop("Models/Man/MAN_StandingIdleGun.ani", 0.1f);
                    //animCtrl->Stop("Models/Man/MAN_RunningGunning.ani", 0.5f);
                    //animCtrl->Stop("Models/Man/MAN_Jumping.ani", 0.1f);
                    
                    animCtrl->PlayExclusive("Models/Man/MAN_TurnSkidGunning.ani", false, 0.1f);
                    //animCtrl->SetWeight("Models/Man/MAN_TurnSkidGunning.ani",0.1f);
                    //animCtrl->SetTime("Models/Man/MAN_TurnSkidGunning.ani",skidTime_a);
                    turning = true;
                }
                else
                {
                    GetSubsystem<DebugHud>()->SetAppStats("animtion:", String("run and gun") );
                    //animCtrl->Stop("Models/Man/MAN_StandingIdleGun.ani", 0.1f);
                    //animCtrl->Stop("Models/Man/MAN_Jumping.ani", 0.1f);
                    //animCtrl->Stop("Models/Man/MAN_TurnSkidGunning.ani", 0.1f);
                    //animCtrl->Play("Models/Man/MAN_Jumping.ani", false, 0.1f);

                    animCtrl->PlayExclusive("Models/Man/MAN_RunningGunning.ani", 0, true, 0.2f);
                    // Set walk animation speed proportional to velocity
                    animCtrl->SetSpeed("Models/Man/MAN_RunningGunning.ani", planeVelocity.Length() * 0.04f);
                }
            }
            //otherwise we are in the air, ornot moving: lets play the jump animation, o idle 
            else
            {
                //GetSubsystem<DebugHud>()->SetAppStats("jumpvel:", String( velocity.y_ ) );
                if(!okToJump_)//we are jumping
                {
                    GetSubsystem<DebugHud>()->SetAppStats("animtion:", String("jump") );
                    float jumpTime = 0.0f;
                    if(velocity.y_>0.0f)
                    {
                        jumpTime = Fit(velocity.y_,jumpForce_,0.0f,0.0f,0.5f);
                    }
                    else
                    {
                        jumpTime = Fit(velocity.y_,0.0f,-jumpForce_,0.5f,1.0f);
                    }
                    //animCtrl->Stop("Models/Man/MAN_StandingIdleGun.ani", 0.1f);
                    //animCtrl->Stop("Models/Man/MAN_RunningGunning.ani", 0.5f);
                    //animCtrl->Stop("Models/Man/MAN_TurnSkidGunning.ani", 0.1f);
                    
                    animCtrl->PlayExclusive("Models/Man/MAN_Jumping.ani", 0,false, 0.1f);
                    animCtrl->SetTime("Models/Man/MAN_Jumping.ani",jumpTime);
                }
                else//we are idle
                {
                    
                    if( planeVelocity.Length()>0.1f )
                    {
                        GetSubsystem<DebugHud>()->SetAppStats("animtion:", String("stop") );
            
                        float skid = planeVelocity.Length();
                        float skidTime = Fit(skid,moveForce_,0.0f,0.0f,0.03f);

                        GetSubsystem<DebugHud>()->SetAppStats("animtion speed:", skidTime );
                        //animCtrl->Stop("Models/Man/MAN_StandingIdleGun.ani", 0.1f);
                        //animCtrl->Stop("Models/Man/MAN_RunningGunning.ani", 0.5f);
                        //animCtrl->Stop("Models/Man/MAN_Jumping.ani", 0.1f);

                        animCtrl->PlayExclusive("Models/Man/MAN_TurnSkidGunning.ani", 0,false, 0.2f);
                        animCtrl->SetTime("Models/Man/MAN_TurnSkidGunning.ani",skidTime);
            
                    }
                    else
                    {
                        GetSubsystem<DebugHud>()->SetAppStats("animtion:", String("idle") );
                        //animCtrl->Stop("Models/Man/MAN_StandingIdleGun.ani", 0.1f);
                        //animCtrl->Stop("Models/Man/MAN_RunningGunning.ani", 0.5f);
                        //animCtrl->Stop("Models/Man/MAN_Jumping.ani", 0.1f);
                        //animCtrl->Stop("Models/Man/MAN_TurnSkidGunning.ani", 0.1f);
                        if(ctrl.IsDown(CTRL_FIRE))
                        {
                            animCtrl->PlayExclusive("Models/Man/MAN_StandingShooting.ani", 0,true, 0.1f);
                        }
                        else
                        {
                            animCtrl->PlayExclusive("Models/Man/MAN_StandingIdleGun.ani", 0,true, 0.5f);
                        }
                    }
                }



                /*if(velocity.y_>0.0f)
                {
                    animCtrl->Play("Models/Man/MAN_Jumping.ani", false, 0.1f);    
                }
                else
                {
                    animCtrl->Play("Models/Man/MAN_StandingIdleGun.ani", true, 0.5f);
                }*/
            }
            
            // Reset grounded flag for next frame
            onGround_ = false;
            //onGround_ = true;
            

        }
    }
    
    //body->ApplyImpulse(Vector3::FORWARD);
}

void Character::HandleSceneDrawableUpdateFinished(StringHash eventType, VariantMap& eventData)
{
    //UPDATE IK TARGETS?
    if(weapon_ != NULL)
    {
        //i need to put the target position in local space relative to the character
        //leftArmIK_->SetTarget(node_->WorldToLocal(weapon_->GetLeftHandTarget()));
        //GetSubsystem<DebugHud>()->SetAppStats("gun_pos:", node_->WorldToLocal(weapon_->GetLeftHandTarget()) );
        
        rightArmIK_->SetTarget(weapon_->GetNode()->GetWorldPosition());
        leftArmIK_->SetTarget(weapon_->GetLeftHandTarget());

    }
}
