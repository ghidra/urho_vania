#ifndef STATECHARACTERJUMPING_H
#define STATECHARACTERJUMPING_H

#pragma once

#include "../../framework/src/State.h"

class StateCharacterJumping : public State
{
    URHO3D_OBJECT(StateCharacterJumping,State);

public:
    /// Construct.
    StateCharacterJumping(Context* context);
    ~StateCharacterJumping();

    virtual State* HandleInput(Controls& ctrl);
    virtual void Enter(Pawn* pawn);
    virtual void Update(float timeStep = 0.0);

private:
	bool jumping_;
};
#endif