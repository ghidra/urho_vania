#ifndef IK_H
#define IK_H

#pragma once

#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

class IK : public LogicComponent
{
    OBJECT(IK);
    
public:
    IK(Context* context);
    ~IK();

    virtual void Update(float timeStep);
    
private:

    String leftFootName;
    String rightFootName;
    Vector3 legAxis;
    float unevenThreshold; // Set this threshold according to the delta between feet height in idle position/animation
    bool doIK; // Allow to disable Foot IK, which is only relevant when the character is grounded

    Node* leftFoot;
    Node* rightFoot;
    Node* rootBone;
    float leftLegLength;
    float rightLegLength;
    float originalRootHeight;
    Quaternion leftFootInitialRot;
    Quaternion rightFootInitialRot;
    
};
#endif