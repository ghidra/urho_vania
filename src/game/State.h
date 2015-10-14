#ifndef STATE_H
#define STATE_H

#pragma once

#include <Urho3D/Core/Object.h>
#include <Urho3D/Input/Input.h>
#include "Pawn.h"

using namespace Urho3D;

class State : public Object
{
    OBJECT(State);
    
public:
    State(Context* context);
    ~State();

    virtual void HandleInput(Pawn& pawn, Input* input);
    virtual void Update(Pawn& pawn);
  
};
#endif