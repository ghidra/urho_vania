#ifndef STATECHARACTERJUMPING_H
#define STATECHARACTERJUMPING_H

#pragma once

#include "../../game/State.h"

class StateCharacterJumping : public State
{
    URHO3D_OBJECT(StateCharacterJumping,State);

public:
    /// Construct.
    StateCharacterJumping(Context* context);
    ~StateCharacterJumping();

    virtual State* HandleInput(Controls& ctrl);
    virtual void Enter(Pawn* pawn);
    virtual void Update();

private:
	bool jumping_;
};
#endif