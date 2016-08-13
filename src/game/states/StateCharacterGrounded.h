#ifndef STATECHARACTERGROUNDED_H
#define STATECHARACTERGROUNDED_H

#pragma once

#include "../../framework/src/State.h"

class StateCharacterGrounded : public State
{
    URHO3D_OBJECT(StateCharacterGrounded,State);

public:
    /// Construct.
    StateCharacterGrounded(Context* context);
    ~StateCharacterGrounded();

    virtual State* HandleInput(Controls& ctrl);
    virtual void Update(float timeStep = 0.0);

protected:
	bool TestTurn();//check if we need to turn around
	void Turn();//do the actual rotation of the root node
	Vector3 moveDir_;
};
#endif