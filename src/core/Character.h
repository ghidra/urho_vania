#ifndef CHARACTER_H
#define CHARACTER_H

#pragma once

#include <Urho3D/Input/Controls.h>
//#include <string>
#include "Actor.h"

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

using namespace Urho3D;

class Character : public Actor
{

    OBJECT(Character);

public:

    Character(Context* context);

    //static void RegisterObject(Context* context);

    virtual void Start();
    virtual void Setup(SharedPtr<Scene> scene, SharedPtr<Node> cameraNode);
    virtual void FixedUpdate(float timeStep);

protected:

    //SharedPtr<Scene> scene_;
    //SharedPtr<Node> cameraNode_;
   
};
#endif