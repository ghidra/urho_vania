#include <Urho3D/Urho3D.h>

#include <Urho3D/Core/Context.h>
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Scene/SceneEvents.h>

#include "Character.h"
#include "states/StateCharacterFalling.h"//force it into falling first

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>

Character::Character(Context* context) :
    PawnAnimated(context)
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
    PawnAnimated::Setup();//do the basic set up with stored and set values

    //DEBUG
    /*ResourceCache* cache = GetSubsystem<ResourceCache>();
    temp_ = node_->GetScene()->CreateChild("temp");
    StaticModel* object = temp_->CreateComponent<StaticModel>();
    object->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    object->SetMaterial(cache->GetResource<Material>("Materials/Jack.xml"));
    */
    //----

    AnimatedModel* model = GetComponent<AnimatedModel>();
    Skeleton& skeleton = model->GetSkeleton();
    skeleton.GetBone(String("root"))->animated_ = false;

    leftArmIK_ = node_->CreateComponent<IK>();//
    leftArmIK_->CreateChain(String("wrist.L"));
    //leftArmIK_->ToggleDebug();
    rightArmIK_ = node_->CreateComponent<IK>();//
    rightArmIK_->CreateChain(String("wrist.R"));
    //rightArmIK_->ToggleDebug();

    //this is the controller rigidbody
    shape_ = node_->CreateComponent<CollisionShape>();
    shape_->SetCapsule(3.0f, 10.0f, Vector3(0.0f, 5.0f, 0.0f));
    ///

    //state_= new StateCharacterIdle(context_);
    //state_->Enter(static_cast<Pawn*>(this));

    //build the ragdoll rigid bodies that this thing will need
    ragdoll_->Bone("abs","neck", SHAPE_CAPSULE, Vector3(2.0f,0.0f,0.85f) );
    ragdoll_->Bone("neck",1.5f, SHAPE_CAPSULE, Vector3(1.0f,0.0f,0.0f) );
    ragdoll_->Bone("armupper.R","armlower.R", SHAPE_CAPSULE, Vector3(0.35f,0.0f,0.0f) );
    ragdoll_->Bone("armlower.R","wrist.R", SHAPE_CAPSULE, Vector3(0.25f,0.0f,0.0f) );
    ragdoll_->Bone("legupper.R","leglower.R", SHAPE_CAPSULE, Vector3(0.5f,0.0f,0.0f) );
    ragdoll_->Bone("leglower.R","foot.R", SHAPE_CAPSULE, Vector3(0.5f,0.0f,0.0f) );
    ragdoll_->Bone("foot.R",0.75f, SHAPE_CAPSULE, Vector3(0.5f,0.0f,0.0f) );
    ragdoll_->Bone("armupper.L","armlower.L", SHAPE_CAPSULE, Vector3(0.35f,0.0f,0.0f) );
    ragdoll_->Bone("armlower.L","wrist.L", SHAPE_CAPSULE, Vector3(0.25f,0.0f,0.0f) );
    ragdoll_->Bone("legupper.L","leglower.L", SHAPE_CAPSULE, Vector3(0.5f,0.0f,0.0f) );
    ragdoll_->Bone("leglower.L","foot.L", SHAPE_CAPSULE, Vector3(0.5f,0.0f,0.0f) );
    ragdoll_->Bone("foot.L",0.75f, SHAPE_CAPSULE, Vector3(0.5f,0.0f,0.0f) );

    //contraint info
    //http://urho3d.github.io/documentation/HEAD/_physics.html
    
    //ragdoll_->Constrain("abs", "root", CONSTRAINT_CONETWIST, Vector3::BACK, Vector3::FORWARD, Vector2(45.0f, 45.0f), Vector2::ZERO);
    ragdoll_->Constrain("neck", "abs", CONSTRAINT_CONETWIST, Vector3::BACK, Vector3::FORWARD, Vector2(45.0f, 45.0f), Vector2::ZERO);
    ragdoll_->Constrain("armupper.R", "abs", CONSTRAINT_CONETWIST, Vector3::BACK, Vector3::FORWARD, Vector2(45.0f, 45.0f), Vector2::ZERO);
    ragdoll_->Constrain("armlower.R", "armupper.R", CONSTRAINT_HINGE, Vector3::BACK, Vector3::FORWARD, Vector2(45.0f, 45.0f), Vector2::ZERO);
    ragdoll_->Constrain("legupper.R", "abs", CONSTRAINT_HINGE, Vector3::BACK, Vector3::FORWARD, Vector2(45.0f, 45.0f), Vector2::ZERO);
    ragdoll_->Constrain("leglower.R", "legupper.R", CONSTRAINT_HINGE, Vector3::BACK, Vector3::FORWARD, Vector2(45.0f, 45.0f), Vector2::ZERO);
    ragdoll_->Constrain("foot.R", "leglower.R", CONSTRAINT_HINGE, Vector3::BACK, Vector3::FORWARD, Vector2(45.0f, 45.0f), Vector2::ZERO);
    ragdoll_->Constrain("armupper.L", "abs", CONSTRAINT_CONETWIST, Vector3::BACK, Vector3::FORWARD, Vector2(45.0f, 45.0f), Vector2::ZERO);
    ragdoll_->Constrain("armlower.L", "armupper.L", CONSTRAINT_HINGE, Vector3::BACK, Vector3::FORWARD, Vector2(45.0f, 45.0f), Vector2::ZERO);
    ragdoll_->Constrain("legupper.L", "abs", CONSTRAINT_HINGE, Vector3::BACK, Vector3::FORWARD, Vector2(45.0f, 45.0f), Vector2::ZERO);
    ragdoll_->Constrain("leglower.L", "legupper.L", CONSTRAINT_HINGE, Vector3::BACK, Vector3::FORWARD, Vector2(45.0f, 45.0f), Vector2::ZERO);
    ragdoll_->Constrain("foot.L", "leglower.L", CONSTRAINT_HINGE, Vector3::BACK, Vector3::FORWARD, Vector2(45.0f, 45.0f), Vector2::ZERO);
    

    //set initial state
    SetState( new StateCharacterFalling(context_) );
}
//--------
void Character::FixedUpdate(float timeStep)
{
    PawnAnimated::FixedUpdate(timeStep);

    if(controller_)
    {
        Controls& ctrl = controller_->controls_;
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
        
        // Reset grounded flag for next frame //might be obsolete
        onGround_ = false;//i might not really need this anymore
        
    }
}

void Character::HandleSceneDrawableUpdateFinished(StringHash eventType, VariantMap& eventData)
{
    //solve for ik
    if(weapon_ != NULL)
    {       
        rightArmIK_->SetTarget(weapon_->GetNode()->GetWorldPosition());
        leftArmIK_->SetTarget(weapon_->GetLeftHandTarget());
    }
}
