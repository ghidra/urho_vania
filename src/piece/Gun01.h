#ifndef GUN01_H
#define GUN01_H

#pragma once

#include "../game/Weapon.h"

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

using namespace Urho3D;

class Gun01 : public Weapon
{

    URHO3D_OBJECT(Gun01,Weapon);

public:

    Gun01(Context* context);
    ~Gun01();
    
    static void RegisterObject(Context* context);

    virtual void Start();
    virtual void FixedUpdate(float timeStep);
    virtual void Setup();

protected:
    virtual void HandleNodeCollision(StringHash eventType, VariantMap& eventData);
    virtual void SpawnProjectile();
   
};
#endif