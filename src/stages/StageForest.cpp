//#include <string>

#include <Urho3D/Urho3D.h>

#include <Urho3D/Graphics/Camera.h>
//#include <Urho3D/Engine/Engine.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Resource/XMLFile.h>

#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Physics/CollisionShape.h>

#include <Urho3D/Graphics/Animation.h>
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/AnimationState.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/Graphics/Zone.h>

#include "StageForest.h"
//#include "../core/CameraLogic.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>


StageForest::StageForest(Context* context) :
    Object(context)
{
}

//-------------------
//-------------------
void StageForest::Setup(SharedPtr<Scene> scene, SharedPtr<Node> cameraNode)
{

	scene_ = scene;
	cameraNode_ = cameraNode;

	ResourceCache* cache = GetSubsystem<ResourceCache>();

    // Create a Zone component for ambient lighting & fog control
    Node* zoneNode = scene_->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.5f, 0.5f, 0.7f));
    zone->SetFogStart(100.0f);
    zone->SetFogEnd(300.0f);

    Node* stageNode = scene_->CreateChild("Stage");

    SharedPtr<File> file = cache->GetFile("Scenes/StageForest.xml");
    //stageNode->LoadXML(*file);
    scene_->InstantiateXML(*file,Vector3(0.0f,-10.0f,0.0f),Quaternion());

    cameraNode_->SetPosition(Vector3(0.0f, 5.0f, 0.0f));

}