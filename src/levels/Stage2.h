#ifndef STAGE2_H
#define STAGE2_H

#pragma once

//#include <string>
#include <Urho3D/Core/Object.h>

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

using namespace Urho3D;

class Stage2 : public Object
{

    URHO3D_OBJECT(Stage2,Object);

public:

    Stage2(Context* context);

    virtual void Setup(SharedPtr<Scene> scene, SharedPtr<Node> cameraNode);

protected:

    SharedPtr<Scene> scene_;
    SharedPtr<Node> cameraNode_;

    const String states_[50];
    const Vector3 positions_[50];
    
};
#endif