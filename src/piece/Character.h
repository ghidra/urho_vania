#ifndef CHARACTER_H
#define CHARACTER_H

#pragma once

#include "../game/Pawn.h"
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

    URHO3D_OBJECT(Character,Pawn);

public:

    Character(Context* context);

    static void RegisterObject(Context* context);

    virtual void Start();
    virtual void FixedUpdate(float timeStep);
    virtual void Setup();

private:
    
    void HandleSceneDrawableUpdateFinished(StringHash eventType, VariantMap& eventData);

    WeakPtr<IK> leftArmIK_;
    WeakPtr<IK> rightArmIK_;

    //SharedPtr<Node> temp_;
   
};
#endif
