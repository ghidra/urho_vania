#ifndef ACTOR_H
#define ACTOR_H

#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include "../core/ApplicationInput.h"

#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Physics/CollisionShape.h>
//#include <Urho3D/Input/Controls.h>

using namespace Urho3D;

const int SIDE_NEUTRAL = 0;
const int SIDE_PLAYER = 1;
const int SIDE_ENEMY = 2;

//these need to match what is in applicationinput
/*const int CTRL_UP = 1;
const int CTRL_DOWN = 2;
const int CTRL_LEFT = 4;
const int CTRL_RIGHT = 8;
const int CTRL_JUMP = 16;

const float MOVE_FORCE = 0.8f;
const float INAIR_MOVE_FORCE = 0.02f;
const float BRAKE_FORCE = 0.2f;
const float JUMP_FORCE = 7.0f;
const float YAW_SENSITIVITY = 0.1f;
const float INAIR_THRESHOLD_TIME = 0.1f;*/

/// Custom logic component for moving the animated model and rotating at area edges.
class Actor : public LogicComponent
{
    OBJECT(Actor);
    
public:
    Actor(Context* context);
    ~Actor();

    //static void RegisterObject(Context* context);

    //virtual void Start();
    virtual void FixedUpdate(float timeStep);
    //virtual void Possess(ApplicationInput* applicationInput);
    //virtual void Control(Controls* controls);
    Node* GetNode(){return node_;};
    RigidBody* GetBody(){return body_;};
    
    Vector3 GetVelocity(){return velocity_;};
    Vector3 GetPlaneVelocity(){return planeVelocity_;};
    Vector3 GetJumpVelocity(){return jumpVelocity_;};
    
protected:

    
    //virtual bool Damage(Actor * origin, float amount);
    //virtual bool Heal(float amount);
    //virtual void PlaySound(const String& soundName);
    virtual void HandleNodeCollision(StringHash eventType, VariantMap& eventData);
    float Fit(float v, float l1, float h1, float l2, float h2);
    //virtual void WorldCollision(VariantMap& eventData);

    //Controls* controls_ = NULL;
    ApplicationInput* applicationInput_ = NULL;

    String mesh_;
    String mesh_convex_;
    String material_;

    //bool readyForUpdate_;//this is to make sure that we are totally initialized before calling fixedupdate. for physcs objects
  
    bool onGround_;
    bool isSliding_;
    float duration_;
    //float health_;
    //float maxHealth_;
    int side_;
    //int lastDamageSide_;
    //uint lastDamageCreatorID_;
    uint creatorID_;

    float speed_;
    float sensitivity_;

    float timeIncrement_;

    RigidBody* body_;
    CollisionShape* shape_;

    Vector3 velocity_;
    Vector3 planeVelocity_;
    Vector3 jumpVelocity_;

    //character collision masks as default
    uint collision_layer_;//=1;
    uint collision_mask_;//=60;

    //collision data
    Vector3 contactPosition_;
    Vector3 contactNormal_;
    float contactDistance_;
    float contactImpulse_;
/*
COLLISION LAYERS AND MASKS
--------------------------------
layers:                        masks:
000001 = (1)character          111100 (60)
000010 = (2)character bullets  111000 (56)
000100 = (4)pickups            100001 (33)
001000 = (8)enemy bullets      100001 (33)
010000 = (16)enemies           100011 (35) 110011 (51)(collide with other enemies)
100000 = (32)env               111111 (63)
---------------------------------
*/

};
#endif