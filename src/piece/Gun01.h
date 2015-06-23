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

    OBJECT(Gun01);

public:

    Gun01(Context* context);
    ~Gun01();
    
    static void RegisterObject(Context* context);

    virtual void Start();
    virtual void FixedUpdate(float timeStep);
    virtual void Setup();

protected:
    virtual void HandleNodeCollision(StringHash eventType, VariantMap& eventData);
   
};
#endif