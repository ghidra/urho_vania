#ifndef PU_GUN01_H
#define PU_GUN01_H

#pragma once

#include "../game/PickUp.h"

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

using namespace Urho3D;

class PU_Gun01 : public PickUp
{

    URHO3D_OBJECT(PU_Gun01,PickUp);

public:

    PU_Gun01(Context* context);
    ~PU_Gun01();
    
    static void RegisterObject(Context* context);

    virtual void Start();
    virtual void FixedUpdate(float timeStep);
    virtual void Setup();

protected:
	//virtual void FixedUpdate(float timeStep);
    //SharedPtr<Scene> scene_;
    //SharedPtr<Node> cameraNode_;
    virtual void HandleNodeCollision(StringHash eventType, VariantMap& eventData);
   
};
#endif