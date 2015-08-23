#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Scene.h>
//#include <math.h>

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
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Math/Sphere.h>


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
	//AnimatedModel* model = node_->GetComponent<AnimatedModel>();
	//Skeleton skel = model->GetSkeleton();
	//if (!skel) 
	//	return;

	//length_ = skel.GetBone(effector_->GetParent()->GetParent()->GetName())->boundingBox_.Size().y_ + skel.GetBone(effector_->GetParent()->GetName())->boundingBox_.Size().y_; // Left thigh length + left calf length
	//rightLegLength = skel.GetBone(rightFoot.parent.parent.name).boundingBox.size.y + skel.GetBone(rightFoot.parent.name).boundingBox.size.y; // Right thigh length + right calf length
	//originalRootHeight = rootBone.worldPosition.y - node.position.y; // Used when no animation is playing

	// Keep track of initial rotation in case no animation is playing
	//initialRot_ = skel.GetBone(boneName_)->initialRotation_;
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
float IK::FindD(const float a, const float b, const float c)
{
	return Max(0.0f, Min(a, (c + (a*a-b*b)/c) / 2.0f));
}
float IK::FindE(const float a, const float d)
{
	return sqrtf(a*a-d*d);
}
void IK::DefineM(const Vector3 p, const Vector3 d)
{
	Vector3 mX,mY,mZ;

	// Minv defines a coordinate system whose x axis contains P, so X = unit(P).
	mX = p.Normalized();

	// The y axis of Minv is perpendicular to P, so Y = unit( D - X(D·X) ).

    float  dDOTx = d.DotProduct(mX);
   	mY.x_ = d.x_ - dDOTx * mX.x_;
   	mY.y_ = d.y_ - dDOTx * mX.y_;
   	mY.z_ = d.z_ - dDOTx * mX.z_;
    mY.Normalize();

	// The z axis of Minv is perpendicular to both X and Y, so Z = X×Y.

    mZ=mX.CrossProduct(mY);

    Minv = Matrix3(mX.x_,mX.y_,mX.z_,mY.x_,mY.y_,mY.z_,mZ.x_,mZ.y_,mZ.z_);
    //Minv = Minv.Transpose();
    Mfwd = Minv.Transpose();
	// Mfwd = (Minv)T, since transposing inverts a rotation matrix.

}
void IK::Solve(Vector3 targetPos)
{
	//http://mrl.nyu.edu/~perlin/gdc/ik/ik.java.html

	// Get current world position for the 3 joints of the IK chain
	Vector3 startJointPos = effector_->GetParent()->GetParent()->GetWorldPosition(); // Thigh pos (hip joint)
	Vector3 midJointPos = effector_->GetParent()->GetWorldPosition(); // Calf pos (knee joint)
	Vector3 effectorPos = effector_->GetWorldPosition(); // Foot pos (ankle joint)

	// Direction vectors
	Vector3 thighDir = midJointPos - startJointPos; // Thigh direction
	Vector3 calfDir = effectorPos - midJointPos; // Calf direction
	Vector3 targetDir = targetPos - startJointPos; // Leg direction

	Vector3 bendAxis = Vector3(effectorPos-startJointPos).Normalized().CrossProduct(targetDir.Normalized());


	// Vectors lengths
	float length1 = thighDir.Length();
	float length2 = calfDir.Length();
	float limbLength = length1 + length2;
	float lengthH = targetDir.Length();

	//PERLINS STUFF
	bool test = Perlin(length1,length2, effector_->GetParent()->GetParent()->WorldToLocal(targetPos),effector_->GetParent()->GetParent()->WorldToLocal(midJointPos));
	GetSubsystem<DebugHud>()->SetAppStats("ik:", String(test) );
	//------

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

	//get the next angle? http://www.ryanjuckett.com/programming/analytic-two-bone-ik-in-2d/
	/*float sinAngle = Sin(theta);
	float triAdjacent = length1 + length2*cos_theta;
    float triOpposite = length2*sinAngle;

    //rotate by axis, and flatten to 2d
    Quaternion flatten = Quaternion();
    flatten.FromRotationTo(bendAxis.Normalized(),Vector3(0.0,0.0,1.0));
    Vector3 flat = flatten * targetPos;
  
  	float tanY = flat.y_*triAdjacent - flat.x_*triOpposite;
    float tanX = flat.x_*triAdjacent + flat.y_*triOpposite;
    //float tanY = targetY*triAdjacent - targetX*triOpposite;
    //float tanX = targetX*triAdjacent + targetY*triOpposite;
  
    // Note that it is safe to call Atan2(0,0) which will happen if targetX and
    // targetY are zero
    float theta1 = Atan2( tanY, tanX );*/

	//DEBUG
	/*DebugRenderer* dbg = effector_->GetScene()->GetComponent<DebugRenderer>();
	dbg->AddSphere(Sphere(startJointPos,0.2f),Color(1.0f,0.0f,0.0f),false);
	dbg->AddLine(startJointPos,startJointPos+thighDir,Color(1.0f,0.0f,0.0f),false);

	dbg->AddSphere(Sphere(midJointPos,0.2f),Color(0.0f,1.0f,0.0f),false);
	dbg->AddLine(midJointPos,midJointPos+calfDir,Color(0.0f,1.0f,0.0f),false);

	dbg->AddSphere(Sphere(effectorPos,0.2f),Color(0.0f,0.0f,1.0f),false);

	dbg->AddSphere(Sphere(targetPos,0.2f),Color(1.0f,1.0f,0.0f),false);*/

	// Quaternions for knee and hip joints
	if (Abs(theta - kneeAngle) > 0.001)
	{
		//Vector3 kneeAxis = thighDir.CrossProduct(calfDir);
		//Vector3 bendAxis = Vector3(effectorPos-startJointPos).Normalized().CrossProduct(targetDir.Normalized());
		
		//dbg->AddLine(startJointPos+(bendAxis.Normalized()*1.0f),startJointPos+(bendAxis.Normalized()*2.0f),Color(1.0f,1.0f,1.0f),false);
		
		Quaternion deltaKnee = Quaternion((theta - kneeAngle) , bendAxis.Normalized());
		Quaternion deltaHip = Quaternion(-(theta - kneeAngle) * 0.5, bendAxis.Normalized());
		//Quaternion deltaKnee = Quaternion((theta - kneeAngle) * 0.5, Vector3(1.0f,0.0f,0.0f));
		//Quaternion deltaHip = Quaternion(-(theta - kneeAngle) * 0.5, Vector3(0.0f,0.0f,-1.0f));
		
		// Apply rotations
		/*Vector3 newHip = startJointPos+(deltaHip*thighDir);
		dbg->AddLine(startJointPos,newHip,Color(1.0f,0.5f,0.5f),false);
		dbg->AddSphere(Sphere(newHip,0.2f),Color(0.5f,1.0f,0.5f),false);
		
		Vector3 newKnee = newHip+(deltaHip*calfDir);
		dbg->AddLine(newHip,newKnee,Color(0.5f,1.0f,0.5f),false);
		dbg->AddSphere(Sphere(newKnee,0.2f),Color(0.5f,0.5f,1.0f),false);*/
		
		//effector_->GetParent()->SetRotation(effector_->GetParent()->GetRotation() * deltaKnee);
		//effector_->GetParent()->GetParent()->SetRotation(effector_->GetParent()->GetParent()->GetRotation() * deltaHip);
		//effector_->GetParent()->SetWorldRotation(effector_->GetParent()->GetWorldRotation() * deltaKnee);
		//effector_->GetParent()->GetParent()->SetWorldRotation(effector_->GetParent()->GetParent()->GetWorldRotation() * deltaHip);
	}
	//effector_->SetWorldPosition(targetPos);//This is a Brute force way to put this thing in place

}
bool IK::Perlin(const float A, const float B, const Vector3 P, const Vector3 D )
{
	//A is length of hip to knee
	//B is length of knee to foot
	//P is target
	//D is pre bent elbow
	Vector3 R;
	DefineM(P,D);
	R = Rot(Minv,P);
    float d = FindD(A,B,R.Length());
    float e = FindE(A,d);
    Vector3 S = Vector3(d,e,0.0f);
    Vector3 Q = Rot(Mfwd,S);

    //R*=Vector3(-1.0,-1.0,1.0);
    //S*=Vector3(-1.0,-1.0,1.0);

    DebugRenderer* dbg = effector_->GetScene()->GetComponent<DebugRenderer>();

    dbg->AddSphere(Sphere(Vector3(),0.2f),Color(0.0f,0.0f,0.0f),false);//origin
    dbg->AddSphere(Sphere(D,0.2f),Color(0.1f,0.0f,0.0f),false);//old elbow
    dbg->AddSphere(Sphere(P,0.2f),Color(0.0f,1.0f,0.0f),false);//target
    dbg->AddLine(Vector3(),P,Color(0.1f,0.1f,0.1f),false);

    dbg->AddSphere(Sphere(Q,0.2f),Color(1.0f,0.0f,0.0f),false);
	dbg->AddLine(Vector3(),Q,Color(1.0f,0.0f,0.0f),false);
	dbg->AddLine(Q,P,Color(1.0f,0.0f,0.0f),false);

	Vector3 to = effector_->GetParent()->GetParent()->LocalToWorld(Vector3());
	Vector3 tq = effector_->GetParent()->GetParent()->LocalToWorld(Q);
	Vector3 tp = effector_->GetParent()->GetParent()->LocalToWorld(P);
	dbg->AddSphere(Sphere(tq,0.2f),Color(1.0f,0.0f,0.0f),false);
	dbg->AddSphere(Sphere(tp,0.2f),Color(0.0f,1.0f,0.0f),false);
	dbg->AddLine(to,tq,Color(1.0f,0.0f,0.0f),false);
	dbg->AddLine(tq,tp,Color(1.0f,0.0f,0.0f),false);
	//dbg->AddSphere(Sphere(effector_->GetParent()->GetParent()->LocalToWorld(S),0.2f),Color(0.0f,1.0f,0.0f),false);
	//dbg->AddLine(startJointPos,startJointPos+thighDir,Color(1.0f,0.0f,0.0f),false);
	
	//dbg->AddSphere(Sphere(S,0.2f),Color(0.0f,1.0f,0.0f),false);
	//dbg->AddSphere(Sphere(effector_->GetParent()->GetParent()->LocalToWorld(P),0.2f),Color(0.0f,0.0f,1.0f),false);
	

	//dbg->AddSphere(Sphere(midJointPos,0.2f),Color(0.0f,1.0f,0.0f),false);
	//dbg->AddLine(midJointPos,midJointPos+calfDir,Color(0.0f,1.0f,0.0f),false);

    return d > 0.0f && d < A;

}
Vector3 IK::Rot(const Matrix3 M, Vector3 src)
{
	Vector3 dst;
    dst.x_ = Vector3(M.m00_,M.m01_,M.m02_).DotProduct(src);
   	dst.y_ = Vector3(M.m10_,M.m11_,M.m12_).DotProduct(src);
   	dst.z_ = Vector3(M.m20_,M.m21_,M.m22_).DotProduct(src);
   	return dst;
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