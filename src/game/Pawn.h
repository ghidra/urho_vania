#ifndef PAWN_H
#define PAWN_H

#pragma once

#include "Actor.h"
#include "../core/ApplicationInput.h"
#include "../game/Weapon.h"

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

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

protected:

    virtual void Setup();

    virtual void HandleNodeCollision(StringHash eventType, VariantMap& eventData);

    ApplicationInput* applicationInput_ = NULL;
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

    //bool onGround_;//already in the actor class

    bool okToJump_;
    float inAirTimer_;    /// In air timer. Due to possible physics inaccuracy, character can be off ground for max. 1/10 second and still be allowed to move.
   
};
#endif