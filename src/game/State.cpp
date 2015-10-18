#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?

#include "State.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>

State::State(Context* context):
    Object(context),
    name_(String("unknown"))
{
}
State::~State(){}

State* State::HandleInput(Pawn* pawn, Input* input)
{
    return new State(context_);
}
void State::Update(Pawn* pawn)
{
}
void State::Debug(){
    GetSubsystem<DebugHud>()->SetAppStats("state:", name_ );
}