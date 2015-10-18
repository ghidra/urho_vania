#ifndef STATECHARACTERIDLE_H
#define STATECHARACTERIDLE_H

#pragma once

#include "../../game/State.h"
#include <Urho3D/Input/Input.h>
#include "../../game/Pawn.h"

//using namespace Urho3D;
namespace Urho3D
{

class Node;
class Scene;

}

class StateCharacterIdle : public State
{
    OBJECT(StateCharacterIdle);

public:
    /// Construct.
    StateCharacterIdle(Context* context);
    ~StateCharacterIdle();

    virtual State* HandleInput(Pawn* pawn, Input* input);
    virtual void Update(Pawn* pawn);

};
#endif