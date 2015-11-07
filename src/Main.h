#ifndef MAIN_H
#define MAIN_H

#pragma once

#include "core/ApplicationHandler.h"
#include "stages/StageForest.h"
#include "stages/VaniaDebugEnv.h"
//#include "core/ApplicationInput.h"
namespace Urho3D
{

class Node;
class Scene;

}

class CameraLogic;


class Main : public ApplicationHandler
{
    URHO3D_OBJECT(Main,ApplicationHandler);

public:
    /// Construct.
    Main(Context* context);
    ~Main();

    virtual void Start();

private:
    /// Construct a new Text instance, containing the 'Hello World' String, and add it to the UI root element.
    //void CreateText();
    /// Subscribe to application-wide logic update events.
    //void SubscribeToEvents();
    /// Handle the logic update event.
    //void HandleUpdate(StringHash eventType, VariantMap& eventData);

    //ApplicationInput * applicationInput_ = NULL;
    StageForest* stage_ = NULL;
    //VaniaDebugEnv* stage_ = NULL;

    SharedPtr<Node> characterNode_;
    //Character* character_;

};
#endif