#ifndef STATECHARACTERRUNNING_H
#define STATECHARACTERRUNNING_H

#pragma once

#include "StateCharacterGrounded.h"

class StateCharacterRunning : public StateCharacterGrounded
{
    URHO3D_OBJECT(StateCharacterRunning,StateCharacterGrounded);

public:
    /// Construct.
    StateCharacterRunning(Context* context);
    ~StateCharacterRunning();

    virtual State* HandleInput(Controls& ctrl);
    virtual void Update();

};
#endif