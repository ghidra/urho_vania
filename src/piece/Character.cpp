#include <Urho3D/Urho3D.h>

#include <Urho3D/Core/Context.h>
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>

#include "Character.h"
#include "../core/ApplicationInput.h"//i need this for the control constants
#include "../core/IK.h"
#include "states/StateCharacterIdle.h"

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
    SetUpdateEventMask(USE_FIXEDUPDATE);
    mesh_ = String("Man/MAN.mdl");
}

//-------------------
//-------------------
void Character::RegisterObject(Context* context)
{
    context->RegisterFactory<Character>();

}

void Character::Start()
{
    SubscribeToEvent(GetNode(), E_NODECOLLISION, HANDLER(Character, HandleNodeCollision));
    SubscribeToEvent(E_SCENEDRAWABLEUPDATEFINISHED, HANDLER(Character, HandleSceneDrawableUpdateFinished));
}

void Character::Setup()
{
    Pawn::Setup();//do the basic set up with stored and set values

    AnimatedModel* model = GetComponent<AnimatedModel>();
    Skeleton& skeleton = model->GetSkeleton();
    skeleton.GetBone(String("root"))->animated_ = false;

    leftArmIK_ = node_->CreateComponent<IK>();//
    leftArmIK_->CreateChain(String("wrist.L"));
    //leftArmIK_->ToggleDebug();
    rightArmIK_ = node_->CreateComponent<IK>();//
    rightArmIK_->CreateChain(String("wrist.R"));
    //rightArmIK_->ToggleDebug();

    shape_ = node_->CreateComponent<CollisionShape>();
    shape_->SetCapsule(3.0f, 10.0f, Vector3(0.0f, 5.0f, 0.0f));
    body_->SetMass(1.0f);

    //set initial state
    state_= new StateCharacterIdle(context_);
    state_->Enter(static_cast<Pawn*>(this));
}

void Character::FixedUpdate(float timeStep)
{
    Pawn::FixedUpdate(timeStep);

    if(applicationInput_)
    {
        if(!applicationInput_->IsDebugCamera())//if we are not in debug camera mode
        {
            //we are possessed by the application controller
            Controls& ctrl = applicationInput_->controls_;
            AnimationController* animCtrl = GetComponent<AnimationController>();
            Input* input = GetSubsystem<Input>();

            //--------------------------------------------------
            //--------------------------------------------------
            ///state stuff
            State* state = state_->HandleInput(ctrl, input);
            if (state != NULL)
            {
                //do exit state before removing state
                state_->Exit();
                delete state_;
                state_ = state;
                //we are entering the new state
                state_->Enter(static_cast<Pawn*>(this));
            }
            state_->Update();
            state_->Debug();

            if(stateArms_ != NULL)
            {
                State* stateArms = stateArms_->HandleInput(ctrl, input);
                if (stateArms != NULL)
                {
                    //do exit state before removing state
                    stateArms_->Exit();
                    delete stateArms_;
                    stateArms_ = stateArms;
                    //we are entering the new state
                    stateArms_->Enter(static_cast<Pawn*>(this));
                }
                stateArms_->Update();
                stateArms_->Debug();
            }
            //--------------------------------------------------
            //--------------------------------------------------

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
            /*const Vector3& velocity = body_->GetLinearVelocity();
            // Velocity on the XZ plane
            Vector3 planeVelocity(velocity.x_, 0.0f, velocity.z_);
            Vector3 jumpVelocity(0.0f, velocity.y_, 0.0f);
            */

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
            body_->ApplyImpulse(rot * moveDir * (softGrounded ? moveForce_ : inAirMoveForce_));
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
                Vector3 brakeForce = -planeVelocity_ * brakeForce_;
                body_->ApplyImpulse(brakeForce);
                
                // Jump. Must release jump control inbetween jumps
                if (applicationInput_->controls_.IsDown(CTRL_JUMP))
                {
                    if (okToJump_)
                    {
                        body_->ApplyImpulse(Vector3::UP * jumpForce_);
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
            float dp = planeVelocity_.Normalized().DotProduct(Vector3::LEFT);
            
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
                float dp2 = planeVelocity_.Normalized().DotProduct(moveDir);//we are moving in the opposite direction we are trying to go
                if( dp2<0.0f )
                {
                    body_->ApplyImpulse(rot * -moveDir * 0.9f * moveForce_);//i ned to make it turn around slower

                    GetSubsystem<DebugHud>()->SetAppStats("animtion:", String("pivot") );
                    float skid = body_->GetLinearVelocity().Length();
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
                    animCtrl->SetSpeed("Models/Man/MAN_RunningGunning.ani", planeVelocity_.Length() * 0.04f);
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
                    if(velocity_.y_>0.0f)
                    {
                        jumpTime = Fit(velocity_.y_,jumpForce_,0.0f,0.0f,0.5f);
                    }
                    else
                    {
                        jumpTime = Fit(velocity_.y_,0.0f,-jumpForce_,0.5f,1.0f);
                    }
                    //animCtrl->Stop("Models/Man/MAN_StandingIdleGun.ani", 0.1f);
                    //animCtrl->Stop("Models/Man/MAN_RunningGunning.ani", 0.5f);
                    //animCtrl->Stop("Models/Man/MAN_TurnSkidGunning.ani", 0.1f);
                    
                    animCtrl->PlayExclusive("Models/Man/MAN_Jumping.ani", 0,false, 0.1f);
                    animCtrl->SetTime("Models/Man/MAN_Jumping.ani",jumpTime);
                }
                else//we are idle
                {
                    
                    if( planeVelocity_.Length()>0.1f )
                    {
                        GetSubsystem<DebugHud>()->SetAppStats("animtion:", String("stop") );
            
                        float skid = planeVelocity_.Length();
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
