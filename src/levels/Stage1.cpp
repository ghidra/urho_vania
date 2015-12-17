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
//#include "../core/CameraLogic.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>


Stage1::Stage1(Context* context) :
    Object(context)
{
}

//-------------------
//-------------------
void Stage1::Setup(SharedPtr<Scene> scene, SharedPtr<Node> cameraNode)
{

    const String states_[50] = 
    {
        String("state_1.001.mdl"),
        String("state_2.001.mdl"),
        String("state_3.001.mdl"),
        String("state_4.001.mdl"),
        String("state_5.001.mdl"),
        String("state_6.001.mdl"),
        String("state_7.001.mdl"),
        String("state_8.001.mdl"),
        String("state_9.001.mdl"),
        String("state_10.001.mdl"),
        String("state_11.001.mdl"),
        String("state_12.001.mdl"),
        String("state_13.001.mdl"),
        String("state_14.001.mdl"),
        String("state_15.001.mdl"),
        String("state_16.001.mdl"),
        String("state_17.001.mdl"),
        String("state_18.001.mdl"),
        String("state_19.001.mdl"),
        String("state_20.001.mdl"),
        String("state_21.001.mdl"),
        String("state_22.001.mdl"),
        String("state_23.001.mdl"),
        String("state_24.001.mdl"),
        String("state_25.001.mdl"),
        String("state_26.001.mdl"),
        String("state_27.001.mdl"),
        String("state_28.001.mdl"),
        String("state_29.001.mdl"),
        String("state_30.001.mdl"),
        String("state_31.001.mdl"),
        String("state_32.001.mdl"),
        String("state_33.001.mdl"),
        String("state_34.001.mdl"),
        String("state_35.001.mdl"),
        String("state_36.001.mdl"),
        String("state_37.001.mdl"),
        String("state_38.001.mdl"),
        String("state_39.001.mdl"),
        String("state_40.001.mdl"),
        String("state_41.001.mdl"),
        String("state_42.001.mdl"),
        String("state_43.001.mdl"),
        String("state_44.001.mdl"),
        String("state_45.001.mdl"),
        String("state_46.001.mdl"),
        String("state_47.001.mdl"),
        String("state_48.001.mdl"),
        String("state_49.001.mdl"),
        String("state_50.001.mdl")
    };
    const Vector3 positions_[50] = 
    {
        Vector3(0.21888011694f,0.0156500004232f,2.09723997116f),
        Vector3(2.54229521751f,-0.00904999952763f,1.75292992592f),
        Vector3(2.41885995865f,-0.00999999977648f,1.90676009655f),
        Vector3(0.673485100269f,0.0166000016034f,2.30860519409f),
        Vector3(0.369050145149f,0.0175500009209f,1.11237001419f),
        Vector3(0.516425132751f,0.0185000002384f,0.181779891253f),
        Vector3(0.423860132694f,0.0185000002384f,0.481095075607f),
        Vector3(0.577625155449f,0.0185000002384f,1.04367494583f),
        Vector3(0.837990105152f,0.0185000002384f,1.52935504913f),
        Vector3(0.935640096664f,0.0185000002384f,1.02947998047f),
        Vector3(0.837135195732f,0.0185000002384f,0.446817427874f),
        Vector3(1.17873501778f,0.0185000002384f,0.342575073242f),
        Vector3(1.26694011688f,0.0185000002384f,0.743340015411f),
        Vector3(1.27813506126f,0.0185000002384f,1.56136512756f),
        Vector3(1.73834013939f,0.0175500009209f,1.89084005356f),
        Vector3(1.36196017265f,0.0185000002384f,1.13154006004f),
        Vector3(1.85952007771f,0.0185000002384f,1.51079499722f),
        Vector3(1.88827514648f,0.000450000166893f,1.21628499031f),
        Vector3(1.77227497101f,0.0175500009209f,0.656964957714f),
        Vector3(1.77993512154f,-0.00144999939948f,0.365104973316f),
        Vector3(2.22174501419f,-0.0052499989979f,0.468360185623f),
        Vector3(2.69981503487f,-0.0052499989979f,0.614735066891f),
        Vector3(2.4618601799f,-0.0052499989979f,0.627650141716f),
        Vector3(2.53034496307f,-0.00810000021011f,1.0825150013f),
        Vector3(2.75453519821f,-0.00714999902993f,1.07339000702f),
        Vector3(2.99251008034f,-0.00714999902993f,0.980669975281f),
        Vector3(3.74992036819f,-0.00810000021011f,0.702120065689f),
        Vector3(3.66952991486f,-0.00619999971241f,0.732804954052f),
        Vector3(3.72557497025f,-0.00619999971241f,0.641584992409f),
        Vector3(3.53317499161f,-0.00904999952763f,1.00545012951f),
        Vector3(3.5650601387f,-0.00619999971241f,0.886059999466f),
        Vector3(3.40220499039f,-0.00429999921471f,1.02564501762f),
        Vector3(3.82462024689f,-0.00239999918267f,0.349364906549f),
        Vector3(3.70352506638f,-0.0052499989979f,0.491724967957f),
        Vector3(3.60558986664f,-0.0052499989979f,0.511260032654f),
        Vector3(3.44979000092f,-0.00429999921471f,0.630430102348f),
        Vector3(3.3455851078f,-0.0052499989979f,0.875915110111f),
        Vector3(2.3500752449f,-0.0052499989979f,1.56273007393f),
        Vector3(3.1991353035f,-0.00144999939948f,1.08977997303f),
        Vector3(3.26395010948f,-0.00144999939948f,1.17536497116f),
        Vector3(2.79603528976f,-0.00714999902993f,1.73529994488f),
        Vector3(2.81455516815f,-0.00144999939948f,1.42764496803f),
        Vector3(3.25786995888f,-0.00144999939948f,1.38491988182f),
        Vector3(3.21765995026f,-0.00619999971241f,1.58336496353f),
        Vector3(3.04369020462f,-0.00429999921471f,1.68953490257f),
        Vector3(3.07175517082f,-0.00999999977648f,2.11033010483f),
        Vector3(1.79783010483f,0.0185000002384f,0.926185011864f),
        Vector3(2.24017524719f,-0.00619999971241f,0.882490038872f),
        Vector3(2.32092523575f,-0.0052499989979f,1.23307991028f),
        Vector3(2.81634521484f,-0.00429999921471f,1.25435996056f)
    };

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

    for (unsigned j=0; j<50; ++j)
    {
        Node* stateNode = scene_->CreateChild("state");
        Vector3 corrected = Vector3(positions_[j].z_,positions_[j].y_,positions_[j].x_)*10.0f;
        stateNode->SetPosition(corrected);
        StaticModel* stateModel = stateNode->CreateComponent<StaticModel>();
        stateModel->SetModel( cache->GetResource<Model>(String("Models/States/")+states_[j]) );
        
        //LOGINFO(positions_[j].ToString());
    }
    /*Node* stateNode = scene_->CreateChild("state");
    stateNode->SetPosition(positions_[0]);
    StaticModel* stateModel = stateNode->CreateComponent<StaticModel>();
    stateModel->SetModel( cache->GetResource<Model>(String("Models/States/")+states_[0]) );*/

    // Create the camera. Limit far clip distance to match the fog
    //cameraNode_ = scene_->CreateChild("Camera");
    //Camera* camera = cameraNode_->CreateComponent<Camera>();
    //camera->SetFarClip(300.0f);

    // Set an initial position for the camera scene node above the plane
    cameraNode_->SetPosition(Vector3(0.0f, 5.0f, 0.0f));

    //give the camera the logic I want
    //CameraLogic* cameralogic = cameraNode_->CreateComponent<CameraLogic>();
}