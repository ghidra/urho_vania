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

private:

    //SharedPtr<Node> cameraNode_;
    /// Camera yaw angle.
    float yaw_;
    /// Camera pitch angle.
    float pitch_;
};

#endif
