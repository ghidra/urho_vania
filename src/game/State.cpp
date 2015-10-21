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

State* State::HandleInput(Controls& ctrl, Input* input)
{
    return NULL;
}
void State::Enter(Pawn* pawn)
{
	pawn_  = pawn;
}
void State::Update()
{
}
void State::Exit()
{
}
void State::Debug(){
    GetSubsystem<DebugHud>()->SetAppStats("state:", name_ );
}