#ifndef PAWN_H
#define PAWN_H

#pragma once

#include "Actor.h"
#include "../core/ApplicationInput.h"
#include "../game/Weapon.h"

#include <Urho3D/Graphics/AnimationController.h>

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

class State;

class Pawn : public Actor
{

    OBJECT(Pawn);

public:

    Pawn(Context* context);
    ~Pawn();

    //static void RegisterObject(Context* context);
    //virtual void Start();

    virtual void FixedUpdate(float timeStep);
    virtual void Possess(ApplicationInput* applicationInput);
    virtual void EquipWeapon(Weapon* weapon);
    //virtual void Setup(SharedPtr<Scene> scene, SharedPtr<Node> cameraNode);

    float GetMoveForce(){return moveForce_;};
    float GetJumpForce(){return jumpForce_;};
    float GetBrakeForce(){return brakeForce_;};

    Vector3 GetVelocity(){return velocity_;};
    Vector3 GetPlaneVelocity(){return planeVelocity_;};
    Vector3 GetJumpVelocity(){return jumpVelocity_;};

    AnimationController* GetAnimationController(){return animationController_;};
    String GetRootName(){return rootName_;};
    bool GetFacingDirection(){return facingDirection_;};
    void SetFacingDirection(bool d){facingDirection_=d;}

    void SetState(State* state);
    //void SetArmsState(State* state);

protected:

    virtual void Setup();

    virtual void HandleNodeCollision(StringHash eventType, VariantMap& eventData);

    //ApplicationInput* applicationInput_ = NULL;
    Weapon* weapon_ = NULL;
  
    float health_;
    float maxHealth_;
    int lastDamageSide_;
    uint lastDamageCreatorID_;

    float moveForce_;
    float inAirMoveForce_;
    float brakeForce_;
    float jumpForce_;
    //float jumpDownForce_;
    float yawSensitivity_;
    float inAirThresholdTime_;

    Vector3 velocity_;
    Vector3 planeVelocity_;
    Vector3 jumpVelocity_;

    //bool onGround_;//already in the actor class

    bool okToJump_;
    float inAirTimer_;    /// In air timer. Due to possible physics inaccuracy, character can be off ground for max. 1/10 second and still be allowed to move.

    AnimationController* animationController_;

    String rootName_;//the name of the root node, to grab for world transforms
    bool facingDirection_;//the direction I am facing. left=0 or right=1;
    
    State* state_ = NULL;
    //State* stateArms_ = NULL;
   
};
#endif