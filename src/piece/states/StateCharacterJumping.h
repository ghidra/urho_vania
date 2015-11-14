#ifndef STATECHARACTERJUMPING_H
#define STATECHARACTERJUMPING_H

#pragma once

#include "../../game/State.h"
#include <Urho3D/Input/Controls.h>
#include "../../core/ApplicationInput.h"
//#include <Urho3D/Input/Input.h>
#include "../../game/Pawn.h"

//using namespace Urho3D;
namespace Urho3D
{

class Node;
class Scene;

}

class StateCharacterJumping : public State
{
    URHO3D_OBJECT(StateCharacterJumping,State);

public:
    /// Construct.
    StateCharacterJumping(Context* context);
    ~StateCharacterJumping();

    virtual State* HandleInput(Controls& ctrl);
    virtual void Enter(Pawn* pawn);
    virtual void Update();

private:
	bool jumping_;
};
#endif