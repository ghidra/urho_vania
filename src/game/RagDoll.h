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

    virtual void Setup(Pawn* pawn);//maybe also pass in the number of "bones" to hold for memory allocation

    virtual void Bone(const String start, const String stop, const unsigned type, Vector3 size);
    virtual void Bone(const String start, const float length, const unsigned type, Vector3 size);

private:
    void SetShape(CollisionShape* cs, const unsigned type, const Vector3 size);
    //const String states_[50];
    SharedPtr<Pawn> pawn_; 
    Vector< SharedPtr<Node> > boneNode_;//the root node of the rigid components .Push() and .Size()
};
#endif