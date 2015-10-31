#ifndef STATECHARACTERGROUNDED_H
#define STATECHARACTERGROUNDED_H

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

class StateCharacterGrounded : public State
{
    OBJECT(StateCharacterGrounded);

public:
    /// Construct.
    StateCharacterGrounded(Context* context);
    ~StateCharacterGrounded();

    virtual State* HandleInput(Controls& ctrl, Input* input);
    virtual void Update();

protected:
	bool TestTurn();//check if we need to turn around
	void Turn();//do the actual rotation of the root node
	Vector3 moveDir_;
};
#endif