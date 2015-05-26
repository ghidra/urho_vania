#include <Urho3D/Urho3D.h>

#include <Urho3D/Core/Context.h>

#include <Urho3D/UI/UI.h>
#include <Urho3D/Input/Input.h>

#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>

#include "CameraLogic.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>

CameraLogic::CameraLogic(Context* context) :
    LogicComponent(context),
    cameraDistanceMin_(1.0f),
    cameraDistanceMax_(5.0f),
    cameraDistanceIni_(20.0f),
    outDirection_(Vector3(0.0f,0.0f,-1.0f)),
    cameraRelativeOrientation_(Quaternion(30.0f,0.0f,0.0f)),
    cameraDistance_(20.0f),
    cameraType_(String("default"))
{
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    //context->RegisterFactory<CameraLogic>();
    SetUpdateEventMask(USE_FIXEDUPDATE);
}

void CameraLogic::RegisterObject(Context* context)
{
    context->RegisterFactory<CameraLogic>();

}
void CameraLogic::SetCameraParameters(const float distance, const float distance_min, const float distance_max, const Quaternion orientation)
{
    cameraDistance_ = distance;
    cameraDistanceMin_ = distance_min;
    cameraDistanceMax_ = distance_max;
    cameraDistanceIni_ = distance;
    cameraRelativeOrientation_ = orientation;
}

void CameraLogic::FixedUpdate(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    if (GetSubsystem<UI>()->GetFocusElement())
        return;

    Input* input = GetSubsystem<Input>();

    // Movement speed as world units per second
    const float MOVE_SPEED = 20.0f;
    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;

    if(cameraType_ == String("default"))
    {
        //this is the default "debug" behavior of the camera
        // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
        IntVector2 mouseMove = input->GetMouseMove();
        yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
        pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
        pitch_ = Clamp(pitch_, -90.0f, 90.0f);

        // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
        node_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));

        // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
        if (input->GetKeyDown('W'))
            node_->Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
        if (input->GetKeyDown('S'))
            node_->Translate(Vector3::BACK * MOVE_SPEED * timeStep);
        if (input->GetKeyDown('A'))
            node_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
        if (input->GetKeyDown('D'))
            node_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);
    }
    else if(cameraType_ == String("sidescrolling"))
    {
        if(target_)//this will only work if I have a target
        {
            //i need the targets position, orientation, to get my cameras position and orientation
            Vector3 target_position = target_->GetWorldPosition();
            Quaternion target_orientation = target_->GetWorldRotation();//i may or may not need this at the moment

            Vector3 rotated_origin = cameraRelativeOrientation_*outDirection_*cameraDistance_;
            Vector3 target_offset_position = rotated_origin + target_position;
            node_->SetPosition(target_offset_position);
        }
    }

    // Toggle debug geometry with space
    //if (input->GetKeyPress(KEY_SPACE))
    //    drawDebug_ = !drawDebug_;
    
    //LOGINFO("updating i guess");
}
