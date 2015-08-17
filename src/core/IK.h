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

    //virtual void Update(float timeStep);
    virtual void CreateChain(const String bone);
    
private:

    String boneName_;//leftFootName
    //String rightFootName;
    Vector3 axis_;//legAxis
    float unevenThreshold_; // Set this threshold according to the delta between feet height in idle position/animation
    bool doIK_; // Allow to disable Foot IK, which is only relevant when the character is grounded

    Node* effector_;//leftFoot
    //Node* rightFoot;
    //Node* rootBone;
    float length_;//leftLegLength
    //float rightLegLength;
    //float originalRootHeight;
    Quaternion initialRot_;//leftFootInitialRot
    //Quaternion rightFootInitialRot;
    
};
#endif