#ifndef APPLICATIONINPUT_H
#define APPLICATIONINPUT_H

#pragma once

#include <Urho3D/Core/Object.h>
#include "ApplicationHandler.h"

using namespace Urho3D;

namespace Urho3D
{
    class Controls;
    class Engine;
}

//const float CAMERA_MIN_DIST = 1.0f;
//const float CAMERA_INITIAL_DIST = 5.0f;
//const float CAMERA_MAX_DIST = 20.0f;
//const float TOUCH_SENSITIVITY = 2.0f;

class ApplicationInput : public Object
{
    OBJECT(ApplicationInput);

public:
    /// Construct.
    ApplicationInput(Context* context);

private:
    /// Construct a new Text instance, containing the 'Hello World' String, and add it to the UI root element.
    //void CreateText();
    void SetParameters(SharedPtr<Engine>& engine);
    /// Subscribe to application-wide logic update events.
    void InitTouchInput();
    /// Handle the logic update event.
    void HandleKeyDown(StringHash eventType, VariantMap& eventData);
    //
    void HandleTouchBegin(StringHash eventType, VariantMap& eventData);

    virtual String GetScreenJoystickPatchString() const { return String::EMPTY; }

    bool touchEnabled_;
    /// Screen joystick index for navigational controls (mobile platforms only).
    unsigned screenJoystickIndex_;
    /// Screen joystick index for settings (mobile platforms only).
    unsigned screenJoystickSettingsIndex_;

    bool paused_;

    /// Touch sensitivity.
    float touchSensitivity_;
    /// Current camera zoom distance.
    float cameraDistance_;
    float cameraDistanceMin_;
    float cameraDistanceMax_;
    float cameraDistanceIni_;
    /// Zoom flag.
    bool zoom_;
    /// Gyroscope on/off flag.
    bool useGyroscope_;

    SharedPtr<Engine> engine_;
    ApplicationHandler* applicationHandler_;


};
#endif