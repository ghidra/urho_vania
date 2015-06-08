#ifndef PAWN_H
#define PAWN_H

#pragma once

#include "Actor.h"
#include "../core/ApplicationInput.h"

using namespace Urho3D;

namespace Urho3D
{

class Node;
class Scene;

}

class Pawn : public Actor
{

    OBJECT(Pawn);

public:

    Pawn(Context* context);
    ~Pawn();

    //static void RegisterObject(Context* context);
    //virtual void Start();

    virtual void FixedUpdate(float timeStep);
    virtual void Possess(ApplicationInput* applicationInput);
    //virtual void Setup(SharedPtr<Scene> scene, SharedPtr<Node> cameraNode);

protected:

    virtual void Setup();

    virtual void HandleNodeCollision(StringHash eventType, VariantMap& eventData);

    ApplicationInput* applicationInput_ = NULL;
  
    float health_;
    float maxHealth_;
    int lastDamageSide_;
    uint lastDamageCreatorID_;
   
};
#endif