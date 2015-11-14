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
//#include "../game/State.h"
#include "states/StateCharacterIdle.h"
#include "states/StateCharacterFalling.h"//force it into falling first

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>

Character::Character(Context* context) :
    Pawn(context)
    //yaw_(0.0f),
    //pitch_(0.0f),
    //touchEnabled_(false),
    //screenJoystickIndex_(M_MAX_UNSIGNED),
    //screenJoystickSettingsIndex_(M_MAX_UNSIGNED),
    //paused_(false)
{
    SetUpdateEventMask(USE_FIXEDUPDATE);
    mesh_ = String("Man/MAN.mdl");
    rootName_ = String("root");
    facingDirection_=false;
}

//-------------------
//-------------------
void Character::RegisterObject(Context* context)
{
    context->RegisterFactory<Character>();

}

void Character::Start()
{
    SubscribeToEvent(GetNode(), E_NODECOLLISION, URHO3D_HANDLER(Character, HandleNodeCollision));
    SubscribeToEvent(E_SCENEDRAWABLEUPDATEFINISHED, URHO3D_HANDLER(Character, HandleSceneDrawableUpdateFinished));
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
    SetState( new StateCharacterFalling(context_) );
    //state_= new StateCharacterIdle(context_);
    //state_->Enter(static_cast<Pawn*>(this));
}
//--------
void Character::FixedUpdate(float timeStep)
{
    Pawn::FixedUpdate(timeStep);

    if(applicationInput_)
    {
        if(!applicationInput_->IsDebugCamera())//if we are not in debug camera mode
        {
            //we are possessed by the application controller
            Controls& ctrl = applicationInput_->controls_;
            //AnimationController* animCtrl = GetComponent<AnimationController>();
            //Input* input = GetSubsystem<Input>();

            //--------------------------------------------------
            //--------------------------------------------------
            ///state stuff
            if(state_ != NULL)
            {
                State* state = state_->HandleInput(ctrl);
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
                //state_->Debug();
            }

            if(weapon_ != NULL)
            {
                weapon_->Update(ctrl,timeStep);
            }
            
            // Reset grounded flag for next frame
            onGround_ = false;//i might not really need this anymore
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
        
        //turn these off for the moment
        //rightArmIK_->SetTarget(weapon_->GetNode()->GetWorldPosition());
        //leftArmIK_->SetTarget(weapon_->GetLeftHandTarget());

    }
}
