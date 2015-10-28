#ifndef STATECHARACTERSTOPPING_H
#define STATECHARACTERSTOPPING_H

#pragma once

#include "StateCharacterGrounded.h"
#include <Urho3D/Input/Controls.h>
#include "../../core/ApplicationInput.h"
#include <Urho3D/Input/Input.h>
#include "../../game/Pawn.h"

//using namespace Urho3D;
namespace Urho3D
{

class Node;
class Scene;

}

class StateCharacterStopping : public StateCharacterGrounded
{
    OBJECT(StateCharacterStopping);

public:
    /// Construct.
    StateCharacterStopping(Context* context);
    ~StateCharacterStopping();

    virtual State* HandleInput(Controls& ctrl, Input* input);
    virtual void Update();

};
#endif