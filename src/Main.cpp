#include <Urho3D/Urho3D.h>

//#include <Urho3D/Core/Context.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Engine/Console.h>
#include <Urho3D/UI/Cursor.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Core/Timer.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/Resource/XMLFile.h>


#include <Urho3D/Core/CoreEvents.h>
//#include <Urho3D/Engine/Engine.h>
#include <Urho3D/UI/Font.h>
//#include <Urho3D/Input/Input.h>
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/UI/Text.h>
//#include <Urho3D/UI/UI.h>

#include "Main.h"
#include "core/CameraLogic.h" 
#include "core/Character.h"
#include "stages/VaniaDebugEnv.h"
//#include "core/ApplicationInput.h"


#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>

#include <iostream>

// Expands to this example's entry-point
DEFINE_APPLICATION_MAIN(Main)

Main::Main(Context* context) :
    ApplicationHandler(context)
    //yaw_(0.0f),
    //pitch_(0.0f),
    //touchEnabled_(false),
    //screenJoystickIndex_(M_MAX_UNSIGNED),
    //screenJoystickSettingsIndex_(M_MAX_UNSIGNED),
    //paused_(false)
{
    CameraLogic::RegisterObject(context);
    Character::RegisterObject(context);
}

//-------------------
//-------------------
void Main::Start()
{
    // Execute base class startup
    ApplicationHandler::Start();

    applicationInput_ = new ApplicationInput(context_);
    SetApplicationInput(applicationInput_);//this also set up the basic camera
    applicationInput_->SetCameraType(String("sidescrolling"));
    
    VariantMap camParms;
    camParms["targetOffset"] = Vector3(0.0f,6.0f,0.0f);

    applicationInput_->SetCameraParameters(camParms);
    //I can set parameters here if I want for the camera, for now, let the defaults deal with it

    // Create "Hello World" Text
    //CreateText();

    stage_ = new VaniaDebugEnv(context_);
    stage_->Setup(scene_, cameraNode_);

    characterNode_ = scene_->CreateChild("Jack");
    Character* character_ = characterNode_->CreateComponent<Character>();

    //character_ = new Character(context_);
    character_->Setup(scene_, cameraNode_);
    character_->Possess(applicationInput_);

    applicationInput_->SetCameraTarget(characterNode_);

    // Finally subscribe to the update event. Note that by subscribing events at this point we have already missed some events
    // like the ScreenMode event sent by the Graphics subsystem when opening the application window. To catch those as well we
    // could subscribe in the constructor instead.
    //SubscribeToEvents();
}



/*void HelloWorld::CreateText()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    // Construct new Text object
    SharedPtr<Text> helloText(new Text(context_));

    // Set String to display
    helloText->SetText("Hello World from Urho3D!");

    // Set font and text color
    helloText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 30);
    helloText->SetColor(Color(0.0f, 1.0f, 0.0f));

    // Align Text center-screen
    helloText->SetHorizontalAlignment(HA_CENTER);
    helloText->SetVerticalAlignment(VA_CENTER);

    // Add Text instance to the UI root element
    
    //std::cout << helloText->GetText() << std::endl;
    //LOGDEBUG(helloText->GetText());

    GetSubsystem<UI>()->GetRoot()->AddChild(helloText);
}*/

/*void Main::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, HANDLER(Main, HandleUpdate));
}*/

/*void Main::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    //applicationInput_->HandleUpdate(eventType, eventData);
    // Do nothing for now, could be extended to eg. animate the display
}*/