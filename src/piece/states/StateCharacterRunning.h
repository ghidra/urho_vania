#ifndef STATECHARACTERRUNNING_H
#define STATECHARACTERRUNNING_H

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