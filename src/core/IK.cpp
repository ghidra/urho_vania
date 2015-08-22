#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Scene.h>

/*#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/Input/Controls.h>*/
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/Skeleton.h>
//#include <Urho3D/Graphics/AnimationController.h>

#include "IK.h"
//#include "../core/ApplicationInput.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>


IK::IK(Context* context) :
    LogicComponent(context),
    unevenThreshold_(0.05),
    doIK_(true),
    axis_(Vector3(0.0f,0.0f,-1.0f))
{
    //SetUpdateEventMask(USE_UPDATE);
}
IK::~IK(){}

void IK::RegisterObject(Context* context)
{
    context->RegisterFactory<IK>();
}

void IK::CreateChain(const String bone)
{
	// Set IK chains effectors
	boneName_= bone;
	effector_ = node_->GetChild(bone, true);
	//rightFoot = node.GetChild(rightFootName, true);
	if (!effector_)
	{
		//log.Info("Cannot get feet nodes " + leftFootName + " and/or " + rightFootName);
		return;
	}

	if (!effector_->GetParent() || !effector_->GetParent()->GetParent())
		return;

	// Set variables
	AnimatedModel* model = node_->GetComponent<AnimatedModel>();
	Skeleton skel = model->GetSkeleton();
	//if (!skel) 
	//	return;

	length_ = skel.GetBone(effector_->GetParent()->GetParent()->GetName())->boundingBox_.Size().y_ + skel.GetBone(effector_->GetParent()->GetName())->boundingBox_.Size().y_; // Left thigh length + left calf length
	//rightLegLength = skel.GetBone(rightFoot.parent.parent.name).boundingBox.size.y + skel.GetBone(rightFoot.parent.name).boundingBox.size.y; // Right thigh length + right calf length
	//originalRootHeight = rootBone.worldPosition.y - node.position.y; // Used when no animation is playing

	// Keep track of initial rotation in case no animation is playing
	initialRot_ = skel.GetBone(boneName_)->initialRotation_;
	//rightFootInitialRot = skel.GetBone(rightFootName).initialRotation;

	// Subscribe to the SceneDrawableUpdateFinished event which is triggered after the animations have been updated, so we can apply IK to override them
	//SubscribeToEvent("SceneDrawableUpdateFinished", "HandleSceneDrawableUpdateFinished");
	//SubscribeToEvent(E_SCENEDRAWABLEUPDATEFINISHED, HANDLER(IK, HandleSceneDrawableUpdateFinished));
}

void IK::SetTarget(Vector3 targetPos)
{
	Solve(targetPos);
}

void IK::HandleSceneDrawableUpdateFinished(StringHash eventType, VariantMap& eventData)
{
	using namespace Update;
	if (doIK_)
	{
		//SolveIK( eventData[P_TIMESTEP].GetFloat() );
		Solve( targetPos_ );
		//GetSubsystem<DebugHud>()->SetAppStats("IK:", boneName_+String(":")+String(length_)+String(":")+String(initialRot_) );
	}
}

void IK::Solve(Vector3 targetPos)
{
	// Get current world position for the 3 joints of the IK chain
	Vector3 startJointPos = effector_->GetParent()->GetParent()->GetWorldPosition(); // Thigh pos (hip joint)
	Vector3 midJointPos = effector_->GetParent()->GetWorldPosition(); // Calf pos (knee joint)
	Vector3 effectorPos = effector_->GetWorldPosition(); // Foot pos (ankle joint)

	// Direction vectors
	Vector3 thighDir = midJointPos - startJointPos; // Thigh direction
	Vector3 calfDir = effectorPos - midJointPos; // Calf direction
	Vector3 targetDir = targetPos - startJointPos; // Leg direction

	// Vectors lengths
	float length1 = thighDir.Length();
	float length2 = calfDir.Length();
	float limbLength = length1 + length2;
	float lengthH = targetDir.Length();
	if (lengthH > limbLength)
	{
		targetDir = targetDir * (limbLength / lengthH) * 0.999; // Do not overshoot if target unreachable
		lengthH = targetDir.Length();
	}
	float lengthHsquared = targetDir.LengthSquared();

	// Current knee angle (from animation keyframe)
	float kneeAngle = thighDir.Angle(calfDir);

	// New knee angle
	float cos_theta = (lengthHsquared - thighDir.LengthSquared() - calfDir.LengthSquared()) / (2 * length1 * length2);
	if (cos_theta > 1) 
		cos_theta = 1; 
	else if (cos_theta < -1) 
		cos_theta = -1;
	float theta = Acos(cos_theta);

	// Quaternions for knee and hip joints
	if (Abs(theta - kneeAngle) > 0.01)
	{
		Vector3 kneeAxis = thighDir.CrossProduct(calfDir);
		Vector3 hipAxis = Vector3(startJointPos-effectorPos).Normalized().CrossProduct(Vector3(startJointPos-targetPos).Normalized());
		Quaternion deltaKnee = Quaternion((theta - kneeAngle), kneeAxis.Normalized());
		Quaternion deltaHip = Quaternion(-(theta - kneeAngle) * 0.5, hipAxis);

		// Apply rotations
		effector_->GetParent()->SetRotation(effector_->GetParent()->GetRotation() * deltaKnee);
		effector_->GetParent()->GetParent()->SetRotation(effector_->GetParent()->GetParent()->GetRotation() * deltaHip);
	}

}
/*void CreateIKChains()//renamed to CreateChain
{
	// Set IK chains effectors
	leftFoot = node.GetChild(leftFootName, true);
	rightFoot = node.GetChild(rightFootName, true);
	if (leftFoot is null || rightFoot is null)
	{
		//log.Info("Cannot get feet nodes " + leftFootName + " and/or " + rightFootName);
		return;
	}

	if (leftFoot.parent is null || leftFoot.parent.parent is null || rightFoot.parent is null || rightFoot.parent.parent is null)
		return;

	// Set variables
	AnimatedModel@ model = node.GetComponent("AnimatedModel");
	Skeleton@ skel = model.skeleton;
	if (skel is null) return;
		rootBone = node.GetChild(skel.rootBone.name, true); // Get root bone of the skeleton as we will move its node up/down to match IK targets

	leftLegLength = skel.GetBone(leftFoot.parent.parent.name).boundingBox.size.y + skel.GetBone(leftFoot.parent.name).boundingBox.size.y; // Left thigh length + left calf length
	rightLegLength = skel.GetBone(rightFoot.parent.parent.name).boundingBox.size.y + skel.GetBone(rightFoot.parent.name).boundingBox.size.y; // Right thigh length + right calf length
	originalRootHeight = rootBone.worldPosition.y - node.position.y; // Used when no animation is playing

	// Keep track of initial rotation in case no animation is playing
	leftFootInitialRot = skel.GetBone(leftFootName).initialRotation;
	rightFootInitialRot = skel.GetBone(rightFootName).initialRotation;

	// Subscribe to the SceneDrawableUpdateFinished event which is triggered after the animations have been updated, so we can apply IK to override them
	//SubscribeToEvent("SceneDrawableUpdateFinished", "HandleSceneDrawableUpdateFinished");
	SubscribeToEvent(GetNode(), E_SCENEDRAWABLEUPDATEFINISHED, HANDLER(IK, HandleSceneDrawableUpdateFinished));
}





void SolveIKUrho(Node* effectorNode, Vector3 targetPos)
{
	// Get current world position for the 3 joints of the IK chain
	Vector3 startJointPos = effectorNode.parent.parent.worldPosition; // Thigh pos (hip joint)
	Vector3 midJointPos = effectorNode.parent.worldPosition; // Calf pos (knee joint)
	Vector3 effectorPos = effectorNode.worldPosition; // Foot pos (ankle joint)

	// Direction vectors
	Vector3 thighDir = midJointPos - startJointPos; // Thigh direction
	Vector3 calfDir = effectorPos - midJointPos; // Calf direction
	Vector3 targetDir = targetPos - startJointPos; // Leg direction

	// Vectors lengths
	float length1 = thighDir.length;
	float length2 = calfDir.length;
	float limbLength = length1 + length2;
	float lengthH = targetDir.length;
	if (lengthH > limbLength)
	{
		targetDir = targetDir * (limbLength / lengthH) * 0.999; // Do not overshoot if target unreachable
		lengthH = targetDir.length;
	}
	float lengthHsquared = targetDir.lengthSquared;

	// Current knee angle (from animation keyframe)
	float kneeAngle = thighDir.Angle(calfDir);

	// New knee angle
	float cos_theta = (lengthHsquared - thighDir.lengthSquared - calfDir.lengthSquared) / (2 * length1 * length2);
	if (cos_theta > 1) 
		cos_theta = 1; 
	else if (cos_theta < -1) 
		cos_theta = -1;
	float theta = Acos(cos_theta);

	// Quaternions for knee and hip joints
	if (Abs(theta - kneeAngle) > 0.01)
	{
		Quaternion deltaKnee = Quaternion((theta - kneeAngle), legAxis);
		Quaternion deltaHip = Quaternion(-(theta - kneeAngle) * 0.5, legAxis);

		// Apply rotations
		effectorNode.parent.rotation = effectorNode.parent.rotation * deltaKnee;
		effectorNode.parent.parent.rotation = effectorNode.parent.parent.rotation * deltaHip;
	}
}


void SolveLegIK(float timeStep)
{
	// ONLY IF NO ANIMATION playing: reset rootBone height
	AnimationController@ animCtrl = node.GetComponent("AnimationController");
	if (node.name == "Jack" && !animCtrl.IsPlaying("Models/Jack_Walk.ani"))
	rootBone.worldPosition = Vector3(rootBone.worldPosition.x, node.position.y + originalRootHeight, rootBone.worldPosition.z);

	// Root bone and feet height from animation keyframe and character node position
	float footHeightL = leftFoot.worldPosition.y - node.position.y;
	float footHeightR = rightFoot.worldPosition.y - node.position.y;

	// Current feet position from animation keyframe
	Vector3 leftGround = leftFoot.worldPosition;
	Vector3 rightGround = rightFoot.worldPosition;

	Octree@ octree = scene.octree;
	float leftHeightDiff = 0; // Distance from left foot to ground, while preserving animation's foot offset from ground
	float rightHeightDiff = 0; // Distance from right foot to ground, while preserving animation's foot offset from ground
	Vector3 leftNormal = Vector3(0, 0, 0);
	Vector3 rightNormal = Vector3(0, 0, 0);

	// Left Foot (NB: ray cast is performed from a position above the foot, but not higher than the character so that we get an accurate result when foot is currently underground)
	RayQueryResult result = octree.RaycastSingle(Ray(leftGround + Vector3(0, leftLegLength, 0), Vector3(0, -1, 0)), RAY_TRIANGLE, 10, DRAWABLE_GEOMETRY, 63); // NB: skip last 2 view mask layers that contain self, foot effects, cutouts...
	if (result.drawable !is null)
	{
	leftGround = result.position;
	leftHeightDiff = leftFoot.worldPosition.y - (leftGround.y + footHeightL); // Distance from foot to ground, while preserving animation's foot offset from ground
	leftNormal = result.normal; // Used to make foot to face along the ground normal
	}

	// Right Foot (NB: ray cast is performed from a position above the foot, but not higher than the character so that we get an accurate result when foot is currently underground)
	RayQueryResult result2 = octree.RaycastSingle(Ray(rightGround + Vector3(0, rightLegLength, 0), Vector3(0, -1, 0)), RAY_TRIANGLE, 10, DRAWABLE_GEOMETRY, 63); // NB: skip last 2 view mask layers that contain self, foot effects, cutouts...
	if (result2.drawable !is null)
	{
	rightGround = result2.position;
	rightHeightDiff = rightFoot.worldPosition.y - (rightGround.y + footHeightR); // Distance from foot to ground, while preserving animation's foot offset from ground
	rightNormal = result2.normal; // Used to make foot to face along the ground normal
	}

	// Feet are facing ground normal
	if (node.name == "Jack" && !animCtrl.IsPlaying("Models/Jack_Walk.ani")) // When no animation is playing, manually reset rotation (when an animation is playing, rotation is reset by the keyframe)
	{
	leftFoot.rotation = leftFootInitialRot;
	rightFoot.rotation = rightFootInitialRot;
	}
	leftFoot.worldRotation = Quaternion(Vector3(0, 1, 0), leftNormal) * leftFoot.worldRotation;
	rightFoot.worldRotation = Quaternion(Vector3(0, 1, 0), rightNormal) * rightFoot.worldRotation;

	// Skip grounding if flat ground
	if(Abs(rightHeightDiff - leftHeightDiff) < 0.001) return;

	// From animation keyframe, determine which foot should be grounded
	bool leftDown = false;
	bool rightDown = false;
	if (leftGround.y < rightGround.y - unevenThreshold) leftDown = true;
	else if (rightGround.y < leftGround.y - unevenThreshold) rightDown = true;

	// If feet are at even level in animation, ground at lowest ray cast level
	if (!leftDown && !rightDown)
	{
	if (leftGround.y < rightGround.y) leftDown = true; else rightDown = true;
	}

	// Set root bone offset to reach grounded foot target position. Also update non grounded foot from this offset
	float heightDiff = 0;
	if (leftDown)
	{
	heightDiff = leftHeightDiff;
	rightGround = rightGround + Vector3(0, heightDiff, 0);
	}
	else if (rightDown)
	{
	heightDiff = rightHeightDiff;
	leftGround = leftGround + Vector3(0, heightDiff, 0);
	}

	// Move the root bone (NB: node has already been 'moved' by its physics collider)
	rootBone.worldPosition = rootBone.worldPosition - Vector3(0, heightDiff, 0);

	// Selectively solve IK
	if (!leftDown) SolveIKUrho(leftFoot, leftGround);
	if (!rightDown) SolveIKUrho(rightFoot, rightGround);
	}

}*/