#ifndef STATECHARACTERSTOPPING_H
#define STATECHARACTERSTOPPING_H

#pragma once

#include "StateCharacterGrounded.h"

class StateCharacterStopping : public StateCharacterGrounded
{
    URHO3D_OBJECT(StateCharacterStopping,StateCharacterGrounded);

public:
    /// Construct.
    StateCharacterStopping(Context* context);
    ~StateCharacterStopping();

    virtual State* HandleInput(Controls& ctrl);
    virtual void Enter(Pawn* pawn);
    virtual void Update();

};
#endif