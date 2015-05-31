#ifndef ACTOR_H
#define ACTOR_H

#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include "../core/ApplicationInput.h"
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

    //static void RegisterObject(Context* context);

    //virtual void Start();
    virtual void FixedUpdate(float timeStep);
    //virtual void Possess(ApplicationInput* applicationInput);
    //virtual void Control(Controls* controls);
    
protected:

    
    //virtual bool Damage(Actor * origin, float amount);
    //virtual bool Heal(float amount);
    //virtual void PlaySound(const String& soundName);
    virtual void HandleNodeCollision(StringHash eventType, VariantMap& eventData);
    //virtual void WorldCollision(VariantMap& eventData);

    //Controls* controls_ = NULL;
    ApplicationInput* applicationInput_ = NULL;

    String mesh_;
    String mesh_convex_;
    String material_;
  
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

    //character collision masks as default
    uint collision_layer_;//=1;
    uint collision_mask_;//=60;
};
#endif