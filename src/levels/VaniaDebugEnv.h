#ifndef VANIADEBUGENV_H
#define VANIADEBUGENV_H

#pragma once

//#include <string>
#include <Urho3D/Core/Object.h>
#include "../game/Character.h"

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

using namespace Urho3D;

class VaniaDebugEnv : public Object
{

    URHO3D_OBJECT(VaniaDebugEnv,Object);

public:

    VaniaDebugEnv(Context* context);

    virtual void Setup(SharedPtr<Scene> scene, SharedPtr<Node> cameraNode);

protected:

    SharedPtr<Scene> scene_;
    SharedPtr<Node> cameraNode_;

    SharedPtr<Character> character_;
   
};
#endif