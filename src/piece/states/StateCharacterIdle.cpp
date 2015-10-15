#include <Urho3D/Urho3D.h>

#include <Urho3D/Input/Controls.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Graphics/Renderer.h>

#include <Urho3D/Engine/Application.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Engine/Console.h>
#include <Urho3D/UI/Cursor.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Core/Timer.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/Resource/XMLFile.h>

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Graphics/DebugRenderer.h>


#include <Urho3D/Input/Input.h>
#include "../../game/Pawn.h"

#include "StateCharacterIdle.h"

StateCharacterIdle::StateCharacterIdle(Context* context):
    State(context)
{
}
StateCharacterIdle::~StateCharacterIdle(){}

void StateCharacterIdle::HandleInput(Pawn& pawn, Input* input)
{
}
void StateCharacterIdle::Update(Pawn& pawn)
{
}