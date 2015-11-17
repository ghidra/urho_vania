#ifndef RAGDOLL_H
#define RAGDOLL_H

#pragma once

#include <Urho3D/Core/Object.h>
#include "Pawn.h"

//using namespace Urho3D;
namespace Urho3D
{

class Node;
class Scene;

}

class Pawn;

class RagDoll : public Object
{
    URHO3D_OBJECT(RagDoll,Object);
    
public:
    RagDoll(Context* context);
    ~RagDoll();

    virtual void Setup(Pawn* pawn);
};
#endif