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

protected:

    
    virtual void HandleNodeCollision(StringHash eventType, VariantMap& eventData);

    //bool collected_;
   
};
#endif