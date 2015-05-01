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
    
    /// Set motion parameters: forward movement speed, rotation speed, and movement boundaries.
    //void SetParameters(float moveSpeed, float rotateSpeed, const BoundingBox& bounds);
    /// Handle scene update. Called by LogicComponent base class.
    virtual void Update(float timeStep);
    
    /// Return forward movement speed.
    //void Move(float timeStep);

private:

    //SharedPtr<Node> cameraNode_;
    /// Camera yaw angle.
    float yaw_;
    /// Camera pitch angle.
    float pitch_;
};
