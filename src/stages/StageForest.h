#ifndef STAGEFOREST_H
#define STAGEFOREST_H

#pragma once

//#include <string>
#include <Urho3D/Core/Object.h>
//#include "../piece/Character.h"

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

using namespace Urho3D;

class StageForest : public Object
{

    URHO3D_OBJECT(StageForest,Object);

public:

    StageForest(Context* context);
    virtual void Setup(SharedPtr<Scene> scene, SharedPtr<Node> cameraNode);

protected:

    SharedPtr<Scene> scene_;
    SharedPtr<Node> cameraNode_;

    //SharedPtr<Character> character_;
   
};
#endif