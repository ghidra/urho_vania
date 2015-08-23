#ifndef IK_H
#define IK_H

#pragma once

#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

/*namespace Urho3D
{

class Node;
class Scene;

}*/

class IK : public LogicComponent
{
    OBJECT(IK);
    
public:
    IK(Context* context);
    ~IK();

    static void RegisterObject(Context* context);

    //virtual void Update(float timeStep);
    virtual void CreateChain(const String bone);
    virtual void SetTarget(Vector3 targetPos);
    
private:

    void HandleSceneDrawableUpdateFinished(StringHash eventType, VariantMap& eventData);
    void Solve(Vector3 targetPos);

    float FindD(const float a, const float b, const float c);
    float FindE(const float a, const float d);
    void DefineM(const Vector3 p, const Vector3 d);
    Vector3 Rot(const Matrix3 M, Vector3 src);
    bool Perlin(const float A, const float B, const Vector3 P, const Vector3 D );

    Matrix3 Minv;
    Matrix3 Mfwd;

    String boneName_;//leftFootName
    //String rightFootName;
    Vector3 axis_;//legAxis
    float unevenThreshold_; // Set this threshold according to the delta between feet height in idle position/animation
    bool doIK_; // Allow to disable Foot IK, which is only relevant when the character is grounded

    Node* effector_;//leftFoot
    //Node* rightFoot;
    //Node* rootBone;
    //float length_;//leftLegLength
    //float rightLegLength;
    //float originalRootHeight;
    //Quaternion initialRot_;//leftFootInitialRot
    Vector3 targetPos_;//set with function
    //Quaternion rightFootInitialRot;
    
};
#endif