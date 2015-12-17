#ifndef PROJECTILE01_H
#define PROJECTILE01_H

#pragma once

#include "../framework/src/Projectile.h"

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

using namespace Urho3D;

class Projectile01 : public Projectile
{

    URHO3D_OBJECT(Projectile01,Projectile);

public:

    Projectile01(Context* context);
    ~Projectile01();
    
    static void RegisterObject(Context* context);

    virtual void Start();
    //virtual void FixedUpdate(float timeStep);
    virtual void Setup(const Vector3 direction);

protected:
    virtual void HandleNodeCollision(StringHash eventType, VariantMap& eventData);
   
};
#endif