#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Scene.h>//will not complie without this?

#include "RagDoll.h"

#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/RigidBody.h>

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>

RagDoll::RagDoll(Context* context):
    Object(context)
{
}
RagDoll::~RagDoll(){}

void RagDoll::Setup(Pawn* pawn)
{
	pawn_ = pawn;
}

void RagDoll::Bone(const String start, const String stop, const unsigned type, Vector3 size)
{

	Node* joint = pawn_->GetNode()->GetChild(start,true);
	Node* jointend = pawn_->GetNode()->GetChild(stop,true);

	Vector3 begin = joint->GetWorldPosition();
	Vector3 end = jointend->GetWorldPosition();

	Vector3 vec = begin-end;
	float length = vec.Length();
	size+=Vector3(0.0f,length,0.0f);;

	//----make the components
	RigidBody* rb = joint->CreateComponent<RigidBody>();
	CollisionShape* cs = joint->CreateComponent<CollisionShape>();

	SetShape(cs,type,size);
	boneNode_.Push(SharedPtr<Node>(joint));
	rb->SetTrigger(true);
}
void RagDoll::Bone(const String start, const float length, const unsigned type, Vector3 size)
{
	Node* joint = pawn_->GetNode()->GetChild(start,true);
	size+=Vector3(0.0f,length,0.0f);
	//----make the components
	RigidBody* rb = joint->CreateComponent<RigidBody>();
	CollisionShape* cs = joint->CreateComponent<CollisionShape>();
	SetShape(cs,type,size);
	boneNode_.Push(SharedPtr<Node>(joint));
	rb->SetTrigger(true);
}
//private
//-----
void RagDoll::SetShape(CollisionShape* cs, const unsigned type, const Vector3 size)
{
	switch(type)
	{
		case 0:
			cs->SetCapsule(size.x_,size.y_,Vector3(0.0f,size.y_/2.0f,0.0f));
			break;
		case 1:
			cs->SetBox(size,Vector3(0.0f,size.y_/2.0f,0.0f));
			break;
	}
}