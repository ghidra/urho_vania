#ifndef CHARACTER_H
#define CHARACTER_H

#pragma once

//#include <Urho3D/Input/Controls.h>
//#include <string>
#include "../game/Pawn.h"
#include "../game/State.h"
#include "../core/IK.h"

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

using namespace Urho3D;

class Character : public Pawn
{

    OBJECT(Character);

public:

    Character(Context* context);

    static void RegisterObject(Context* context);

    virtual void Start();
    virtual void FixedUpdate(float timeStep);
    virtual void Setup();
    
    //virtual void Control(Controls* controls);

protected:
	//virtual void FixedUpdate(float timeStep);
    //SharedPtr<Scene> scene_;
    //SharedPtr<Node> cameraNode_;

private:

    State* state_;
    
    void HandleSceneDrawableUpdateFinished(StringHash eventType, VariantMap& eventData);
    bool turning;

    IK* leftArmIK_;
    IK* rightArmIK_;
   
};
#endif
