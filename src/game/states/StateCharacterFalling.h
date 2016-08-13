#ifndef STATECHARACTERFALLING_H
#define STATECHARACTERFALLING_H

#pragma once

#include "../../framework/src/State.h"
#include <Urho3D/Physics/PhysicsWorld.h>//for the raycasting

class StateCharacterFalling : public State
{
    URHO3D_OBJECT(StateCharacterFalling,State);

public:
    /// Construct.
    StateCharacterFalling(Context* context);
    ~StateCharacterFalling();

    virtual State* HandleInput(Controls& ctrl);
    virtual void Enter(Pawn* pawn);
    virtual void Update(float timeStep = 0.0);

private:

	float distanceBottom_;//the initial distnace to the bottom found on enter

	PhysicsRaycastResult FindBottom();//do the raycasting

};
#endif