#ifndef PU_WEAPON_H
#define PU_WEAPON_H

#pragma once

#include "../game/PickUp.h"

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

using namespace Urho3D;

class PU_Weapon : public PickUp
{

    OBJECT(PU_Weapon);

public:

    PU_Weapon(Context* context);

    static void RegisterObject(Context* context);

    virtual void Start();
    virtual void FixedUpdate(float timeStep);
    virtual void Setup();

protected:
	//virtual void FixedUpdate(float timeStep);
    //SharedPtr<Scene> scene_;
    //SharedPtr<Node> cameraNode_;
   
};
#endif