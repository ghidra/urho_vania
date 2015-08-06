#ifndef PROJECTILE_H
#define PROJECTILE_H

#pragma once

#include "../game/Actor.h"

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

using namespace Urho3D;

class Projectile : public Actor
{

    OBJECT(Projectile);

public:

    Projectile(Context* context);
    ~Projectile();

    virtual void FixedUpdate(float timeStep);
    virtual void Setup();
    //virtual void Attach(Node* bone);

protected:

    
    virtual void HandleNodeCollision(StringHash eventType, VariantMap& eventData);

    Vector3 pos_born_;//the position this projectile was born
  	Vector3 hit_;//this is if we want this projectile to aim at a specific position
  	float range_;//how far this projectile can travel
  	float damage_;//how much damage this projectile can do

    //bool collected_;
   
};
#endif