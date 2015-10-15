#ifndef STATECHARACTERIDLE_H
#define STATECHARACTERIDLE_H

#pragma once

#include <Urho3D/Input/Input.h>
#include "../../game/State.h"
#include "../../game/Pawn.h"

using namespace Urho3D;

class StateCharacterIdle : public State
{
    OBJECT(StateCharacterIdle);

public:
    /// Construct.
    StateCharacterIdle(Context* context);
    ~StateCharacterIdle();

    virtual void HandleInput(Pawn& pawn, Input* input);
    virtual void Update(Pawn& pawn);

};
#endif