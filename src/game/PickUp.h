#ifndef PICKUP_H
#define PICKUP_H

#pragma once

#include "../game/Actor.h"

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

using namespace Urho3D;

class PickUp : public Actor
{

    OBJECT(PickUp);

public:

    PickUp(Context* context);

    virtual void FixedUpdate(float timeStep);

protected:

    virtual void HandleNodeCollision(StringHash eventType, VariantMap& eventData);
   
};
#endif