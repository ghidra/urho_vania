#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#pragma once

#include "core/ApplicationHandler.h"
#include "core/ApplicationInput.h"

class HelloWorld : public ApplicationHandler
{
    OBJECT(HelloWorld);

public:
    /// Construct.
    HelloWorld(Context* context);

    virtual void Start();

private:
    /// Construct a new Text instance, containing the 'Hello World' String, and add it to the UI root element.
    void CreateText();
    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);

    ApplicationInput * applicationInput_;

};
#endif