#ifndef STATE_H
#define STATE_H

#pragma once

#include <Urho3D/Core/Object.h>
#include <Urho3D/Input/Controls.h>
#include "../core/ApplicationInput.h"//for the control constants
#include <Urho3D/Input/Input.h>
#include "Pawn.h"

//using namespace Urho3D;
namespace Urho3D
{

class Node;
class Scene;

}

class Pawn;

class State : public Object
{
    OBJECT(State);
    
public:
    State(Context* context);
    ~State();

    virtual State* HandleInput(Controls& ctrl, Input* input);
    virtual void Enter(Pawn* pawn);
    virtual void Update();
    virtual void Exit();

    virtual void Debug();

protected:

    String name_;
    Pawn* pawn_;
  
};
#endif