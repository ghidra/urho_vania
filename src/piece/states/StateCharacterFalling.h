#ifndef STATECHARACTERFALLING_H
#define STATECHARACTERFALLING_H

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

class StateCharacterFalling : public State
{
    OBJECT(StateCharacterFalling);

public:
    /// Construct.
    StateCharacterFalling(Context* context);
    ~StateCharacterFalling();

    virtual State* HandleInput(Controls& ctrl, Input* input);
    virtual void Enter(Pawn* pawn);
    virtual void Update();

};
#endif