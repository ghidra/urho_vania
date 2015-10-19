#ifndef STATECHARACTERJUMPING_H
#define STATECHARACTERJUMPING_H

#pragma once

#include "../../game/State.h"
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

class StateCharacterJumping : public State
{
    OBJECT(StateCharacterJumping);

public:
    /// Construct.
    StateCharacterJumping(Context* context);
    ~StateCharacterJumping();

    virtual State* HandleInput(Pawn* pawn, Controls& ctrl, Input* input);
    virtual void Update(Pawn* pawn);

};
#endif