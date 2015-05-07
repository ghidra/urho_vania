//#include <string>

#include <Urho3D/Urho3D.h>

#include <Urho3D/Graphics/Camera.h>
//#include <Urho3D/Engine/Engine.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Resource/XMLFile.h>

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

#include "Stage1.h"
#include "core/CameraLogic.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>


Stage1::Stage1(Context* context) :
    Object(context)
{
    const String states_[50]=
    {
        "state_1.001.mdl",
        "state_2.001.mdl",
        "state_3.001.mdl",
        "state_4.001.mdl",
        "state_5.001.mdl",
        "state_6.001.mdl",
        "state_7.001.mdl",
        "state_8.001.mdl",
        "state_9.001.mdl",
        "state_10.001.mdl",
        "state_11.001.mdl",
        "state_12.001.mdl",
        "state_13.001.mdl",
        "state_14.001.mdl",
        "state_15.001.mdl",
        "state_16.001.mdl",
        "state_17.001.mdl",
        "state_18.001.mdl",
        "state_19.001.mdl",
        "state_20.001.mdl",
        "state_21.001.mdl",
        "state_22.001.mdl",
        "state_23.001.mdl",
        "state_24.001.mdl",
        "state_25.001.mdl",
        "state_26.001.mdl",
        "state_27.001.mdl",
        "state_28.001.mdl",
        "state_29.001.mdl",
        "state_30.001.mdl",
        "state_31.001.mdl",
        "state_32.001.mdl",
        "state_33.001.mdl",
        "state_34.001.mdl",
        "state_35.001.mdl",
        "state_36.001.mdl",
        "state_37.001.mdl",
        "state_38.001.mdl",
        "state_39.001.mdl",
        "state_40.001.mdl",
        "state_41.001.mdl",
        "state_42.001.mdl",
        "state_43.001.mdl",
        "state_44.001.mdl",
        "state_45.001.mdl",
        "state_46.001.mdl",
        "state_47.001.mdl",
        "state_48.001.mdl",
        "state_49.001.mdl",
        "state_50.001.mdl"
    };

    const Vector3 positions_[50]=
    {
        Vector3(0.21888011694,0.0156500004232,2.09723997116),
        Vector3(2.54229521751,-0.00904999952763,1.75292992592),
        Vector3(2.41885995865,-0.00999999977648,1.90676009655),
        Vector3(0.673485100269,0.0166000016034,2.30860519409),
        Vector3(0.369050145149,0.0175500009209,1.11237001419),
        Vector3(0.516425132751,0.0185000002384,0.181779891253),
        Vector3(0.423860132694,0.0185000002384,0.481095075607),
        Vector3(0.577625155449,0.0185000002384,1.04367494583),
        Vector3(0.837990105152,0.0185000002384,1.52935504913),
        Vector3(0.935640096664,0.0185000002384,1.02947998047),
        Vector3(0.837135195732,0.0185000002384,0.446817427874),
        Vector3(1.17873501778,0.0185000002384,0.342575073242),
        Vector3(1.26694011688,0.0185000002384,0.743340015411),
        Vector3(1.27813506126,0.0185000002384,1.56136512756),
        Vector3(1.73834013939,0.0175500009209,1.89084005356),
        Vector3(1.36196017265,0.0185000002384,1.13154006004),
        Vector3(1.85952007771,0.0185000002384,1.51079499722),
        Vector3(1.88827514648,0.000450000166893,1.21628499031),
        Vector3(1.77227497101,0.0175500009209,0.656964957714),
        Vector3(1.77993512154,-0.00144999939948,0.365104973316),
        Vector3(2.22174501419,-0.0052499989979,0.468360185623),
        Vector3(2.69981503487,-0.0052499989979,0.614735066891),
        Vector3(2.4618601799,-0.0052499989979,0.627650141716),
        Vector3(2.53034496307,-0.00810000021011,1.0825150013),
        Vector3(2.75453519821,-0.00714999902993,1.07339000702),
        Vector3(2.99251008034,-0.00714999902993,0.980669975281),
        Vector3(3.74992036819,-0.00810000021011,0.702120065689),
        Vector3(3.66952991486,-0.00619999971241,0.732804954052),
        Vector3(3.72557497025,-0.00619999971241,0.641584992409),
        Vector3(3.53317499161,-0.00904999952763,1.00545012951),
        Vector3(3.5650601387,-0.00619999971241,0.886059999466),
        Vector3(3.40220499039,-0.00429999921471,1.02564501762),
        Vector3(3.82462024689,-0.00239999918267,0.349364906549),
        Vector3(3.70352506638,-0.0052499989979,0.491724967957),
        Vector3(3.60558986664,-0.0052499989979,0.511260032654),
        Vector3(3.44979000092,-0.00429999921471,0.630430102348),
        Vector3(3.3455851078,-0.0052499989979,0.875915110111),
        Vector3(2.3500752449,-0.0052499989979,1.56273007393),
        Vector3(3.1991353035,-0.00144999939948,1.08977997303),
        Vector3(3.26395010948,-0.00144999939948,1.17536497116),
        Vector3(2.79603528976,-0.00714999902993,1.73529994488),
        Vector3(2.81455516815,-0.00144999939948,1.42764496803),
        Vector3(3.25786995888,-0.00144999939948,1.38491988182),
        Vector3(3.21765995026,-0.00619999971241,1.58336496353),
        Vector3(3.04369020462,-0.00429999921471,1.68953490257),
        Vector3(3.07175517082,-0.00999999977648,2.11033010483),
        Vector3(1.79783010483,0.0185000002384,0.926185011864),
        Vector3(2.24017524719,-0.00619999971241,0.882490038872),
        Vector3(2.32092523575,-0.0052499989979,1.23307991028),
        Vector3(2.81634521484,-0.00429999921471,1.25435996056)
    };
}

//-------------------
//-------------------
void Stage1::Setup(SharedPtr<Scene> scene, SharedPtr<Node> cameraNode)
{
	scene_ = scene;
	cameraNode_ = cameraNode;

	ResourceCache* cache = GetSubsystem<ResourceCache>();

    // Create scene node & StaticModel component for showing a static plane
    Node* planeNode = scene_->CreateChild("Plane");
    planeNode->SetScale(Vector3(100.0f, 1.0f, 100.0f));
    StaticModel* planeObject = planeNode->CreateComponent<StaticModel>();
    planeObject->SetModel(cache->GetResource<Model>("Models/Plane.mdl"));
    planeObject->SetMaterial(cache->GetResource<Material>("Materials/StoneTiled.xml"));

    // Create a Zone component for ambient lighting & fog control
    Node* zoneNode = scene_->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.5f, 0.5f, 0.7f));
    zone->SetFogStart(100.0f);
    zone->SetFogEnd(300.0f);

    // Create a directional light to the world. Enable cascaded shadows on it
    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
    // Set cascade splits at 10, 50 and 200 world units, fade shadows out at 80% of maximum shadow distance
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));

    // Create animated models
    const unsigned NUM_MODELS = 100;
    const float MODEL_MOVE_SPEED = 2.0f;
    const float MODEL_ROTATE_SPEED = 100.0f;
    const BoundingBox bounds(Vector3(-47.0f, 0.0f, -47.0f), Vector3(47.0f, 0.0f, 47.0f));

    for (unsigned i = 0; i < NUM_MODELS; ++i)
    {
        Node* modelNode = scene_->CreateChild("Jack");
        modelNode->SetPosition(Vector3(Random(90.0f) - 45.0f, 0.0f, Random(90.0f) - 45.0f));
        modelNode->SetRotation(Quaternion(0.0f, Random(360.0f), 0.0f));
        AnimatedModel* modelObject = modelNode->CreateComponent<AnimatedModel>();
        modelObject->SetModel(cache->GetResource<Model>("Models/Jack.mdl"));
        modelObject->SetMaterial(cache->GetResource<Material>("Materials/Jack.xml"));
        modelObject->SetCastShadows(true);

        // Create an AnimationState for a walk animation. Its time position will need to be manually updated to advance the
        // animation, The alternative would be to use an AnimationController component which updates the animation automatically,
        // but we need to update the model's position manually in any case
        Animation* walkAnimation = cache->GetResource<Animation>("Models/Jack_Walk.ani");
        AnimationState* state = modelObject->AddAnimationState(walkAnimation);
        // The state would fail to create (return null) if the animation was not found
        if (state)
        {
            // Enable full blending weight and looping
            state->SetWeight(1.0f);
            state->SetLooped(true);
        }

        // Create our custom Mover component that will move & animate the model during each frame's update
        //Mover* mover = modelNode->CreateComponent<Mover>();
        //mover->SetParameters(MODEL_MOVE_SPEED, MODEL_ROTATE_SPEED, bounds);
    }

    /*for (unsigned j=0; j<50; ++j)
    {
        Node* stateNode = scene_->CreateChild("state");
        stateNode->SetPosition(positions_[j]);
        StaticModel* stateModel = stateNode->CreateComponent<StaticModel>();
        stateModel->SetModel( cache->GetResource<Model>("Models/States/"+states_[j]) );
    }*/
    Node* stateNode = scene_->CreateChild("state");
    stateNode->SetPosition(positions_[0]);
    StaticModel* stateModel = stateNode->CreateComponent<StaticModel>();
    stateModel->SetModel( cache->GetResource<Model>(String("Models/States/")+states_[0]) );

    // Create the camera. Limit far clip distance to match the fog
    //cameraNode_ = scene_->CreateChild("Camera");
    //Camera* camera = cameraNode_->CreateComponent<Camera>();
    //camera->SetFarClip(300.0f);

    // Set an initial position for the camera scene node above the plane
    cameraNode_->SetPosition(Vector3(0.0f, 5.0f, 0.0f));

    //give the camera the logic I want
    CameraLogic* cameralogic = cameraNode_->CreateComponent<CameraLogic>();
}