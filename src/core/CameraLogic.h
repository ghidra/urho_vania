#ifndef CAMERALOGIC_H
#define CAMERALOGIC_H

#pragma once

#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

/// Custom logic component for moving the animated model and rotating at area edges.
class CameraLogic : public LogicComponent
{
    OBJECT(CameraLogic);
    
public:
    /// Construct.
    CameraLogic(Context* context);

    static void RegisterObject(Context* context);
    virtual void FixedUpdate(float timeStep);

    //setters
    virtual void SetCameraType(const String& cameraType){ cameraType_ = cameraType; }
    virtual void SetCameraTarget(SharedPtr<Node> target){  target_ = target; }
    virtual void SetCameraParameters(const float distance, const float distance_min = 1.0f, const float distance_max = 20.0f, const Quaternion orientation = Quaternion(0.0f,0.0f,0.0f,1.0f) );


private:

    //SharedPtr<Node> cameraNode_;
    /// Camera yaw angle.
    float yaw_;
    /// Camera pitch angle.
    float pitch_;

    String cameraType_;
    SharedPtr<Node> target_;

    float cameraDistance_;
    float cameraDistanceMin_;
    float cameraDistanceMax_;
    float cameraDistanceIni_;
    Vector3 outDirection_;
    Quaternion cameraRelativeOrientation_;
};

#endif
