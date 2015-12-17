#ifndef STAGE1_H
#define STAGE1_H

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

class Stage1 : public Object
{

    URHO3D_OBJECT(Stage1,Object);

public:

    Stage1(Context* context);

    virtual void Setup(SharedPtr<Scene> scene, SharedPtr<Node> cameraNode);

protected:

    SharedPtr<Scene> scene_;
    SharedPtr<Node> cameraNode_;

    const String states_[50];
    const Vector3 positions_[50];
    
};
#endif