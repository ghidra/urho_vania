#ifndef STATECHARACTERIDLE_H
#define STATECHARACTERIDLE_H

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

class StateCharacterIdle : public StateCharacterGrounded
{
    URHO3D_OBJECT(StateCharacterIdle,StateCharacterGrounded);

public:
    /// Construct.
    StateCharacterIdle(Context* context);
    ~StateCharacterIdle();

    virtual State* HandleInput(Controls& ctrl, Input* input);
    virtual void Enter(Pawn* pawn);
    virtual void Update();
    virtual void Exit();

};
#endif