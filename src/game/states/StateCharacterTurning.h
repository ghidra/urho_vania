#ifndef STATECHARACTERTURNING_H
#define STATECHARACTERTURNING_H

#pragma once

#include "StateCharacterGrounded.h"

class StateCharacterTurning : public StateCharacterGrounded
{
    URHO3D_OBJECT(StateCharacterTurning,StateCharacterGrounded);

public:
    /// Construct.
    StateCharacterTurning(Context* context);
    ~StateCharacterTurning();

    virtual State* HandleInput(Controls& ctrl);
    virtual void Enter(Pawn* pawn);
    virtual void Update(float timeStep = 0.0);

private:
	
	float speed_;//the initial speed that we enter the state in
	bool flipped_;

};
#endif