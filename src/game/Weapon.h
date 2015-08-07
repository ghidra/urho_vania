#ifndef WEAPON_H
#define WEAPON_H

#pragma once

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

    OBJECT(Weapon);

public:

    Weapon(Context* context);
    ~Weapon();

    virtual void FixedUpdate(float timeStep);
    virtual void Setup();
    //virtual void Attach(Node* bone);
    virtual void Fire(float timestep);
    virtual void SetFireRate(float fireRate);


protected:

    
    virtual void HandleNodeCollision(StringHash eventType, VariantMap& eventData);

    virtual void ReleaseFire();
    //virtual void FireLogic(float timeStep);
    virtual void SpawnProjectile();

    //bool collected_;
	unsigned firing_;
	float fire_velocity_;
	float firing_timer_;
	float firing_interval_;//the rate of fire

   
};
#endif