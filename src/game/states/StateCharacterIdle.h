#ifndef STATECHARACTERIDLE_H
#define STATECHARACTERIDLE_H

#pragma once

#include "StateCharacterGrounded.h"

class StateCharacterIdle : public StateCharacterGrounded
{
    URHO3D_OBJECT(StateCharacterIdle,StateCharacterGrounded);

public:
    /// Construct.
    StateCharacterIdle(Context* context);
    ~StateCharacterIdle();

    virtual State* HandleInput(Controls& ctrl);
    virtual void Enter(Pawn* pawn);
    virtual void Update(float timeStep = 0.0);
    virtual void Exit();
private:
	bool firing_;
};
#endif