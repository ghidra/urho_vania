#ifndef WEAPON_H
#define WEAPON_H

#pragma once

#include <Urho3D/Input/Controls.h>
#include "../game/Actor.h"

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

using namespace Urho3D;

class Weapon : public Actor
{

    URHO3D_OBJECT(Weapon,Actor);

public:

    Weapon(Context* context);
    ~Weapon();

    //virtual void FixedUpdate(float timeStep);
    virtual void Update(Controls& ctrl, float timeStep);
    virtual void Setup();
    //virtual void Attach(Node* bone);
    virtual void Fire(float timestep);
    virtual void ReleaseFire();
    virtual void SetFireRate(float fireRate);
    //virtual unsigned GetFiring(){return firing_;};
    //virtual Vector3 GetFireOffset(return fire_offset_);
    virtual Vector3 GetLeftHandTarget();
    //virtual Vector3 GetLeftHandTarget(){return lefthand_target_;};

protected:

    
    virtual void HandleNodeCollision(StringHash eventType, VariantMap& eventData);
    //virtual void HandleSceneDrawableUpdateFinished(StringHash eventType, VariantMap& eventData);

    
    //virtual void FireLogic(float timeStep);
    virtual void SpawnProjectile();

    //virtual void SetLeftHandOffset();//set the offest. sets itself on fire. needs to always be set

    //bool collected_;
	unsigned firing_;
	float fire_velocity_;
	float firing_timer_;
	float firing_interval_;//the rate of fire

    Vector3 fire_off_;//the vector offset of the position releative to where projectiles should spawn
    Quaternion kick_rot_;
    Vector3 kick_off_;

    Vector3 lefthand_off_;//the constant offset of the IK position

private:
    SharedPtr<Node> lefthand_grip_;//node that is the grip of the weapons for the left had
    //Vector3 lefthand_target_;
    //Vector3 lefthand_target_;//the updated target position for IK
};
#endif