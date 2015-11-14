#ifndef STATECHARACTERTURNING_H
#define STATECHARACTERTURNING_H

#pragma once

#include "StateCharacterGrounded.h"
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

class StateCharacterTurning : public StateCharacterGrounded
{
    URHO3D_OBJECT(StateCharacterTurning,StateCharacterGrounded);

public:
    /// Construct.
    StateCharacterTurning(Context* context);
    ~StateCharacterTurning();

    virtual State* HandleInput(Controls& ctrl);
    virtual void Enter(Pawn* pawn);
    virtual void Update();

private:
	
	float speed_;//the initial speed that we enter the state in
	bool flipped_;

};
#endif