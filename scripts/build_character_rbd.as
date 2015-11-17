//abs - neck (body)
//neck - MANUAL (head)

//X2
//armupper.R -armlower.R (right upper arm)
//armlower.R-wrist.R (right lower arm)

//X2
//legupper.R - leglower.R (right thigh)
//leglower.R - foot.R (right calf)

uint shapes_ = 10;//number of rbds to make
float margin_ = 0.0f;

Array<String> bones_ = {
	String("abs"), String("neck"),
	String("neck"), String("MANUAL"),
	String("armupper.R"), String("armlower.R"),
	String("armlower.R"), String("wrist.R"),
	String("legupper.R"), String("leglower.R"),
	String("leglower.R"), String("foot.R"),
	String("armupper.L"), String("armlower.L"),
	String("armlower.L"), String("wrist.L"),
	String("legupper.L"), String("leglower.L"),
	String("leglower.L"), String("foot.L")
};

Array<float> manual_length_ = {
	1.5f
};

//0 capsule
//1 box
Array<uint> type_ = {
	1,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

//body should be a box 2,calc,0.85
Array<Vector3> size_ = {
	Vector3(2.0f,0.0f,0.85f),
	Vector3(1.0f,0.0f,0.0f),
	Vector3(0.35f,0.0f,0.0f),
	Vector3(0.25f,0.0f,0.0f),
	Vector3(0.5f,0.0f,0.0f),
	Vector3(0.5f,0.0f,0.0f),
	Vector3(0.35f,0.0f,0.0f),
	Vector3(0.25f,0.0f,0.0f),
	Vector3(0.5f,0.0f,0.0f),
	Vector3(0.5f,0.0f,0.0f)
};


Node@ char = scene.CreateChild("character");

AnimatedModel@ charmdl = char.CreateComponent("AnimatedModel");
charmdl.model = cache.GetResource("Model", "Models/Man/MAN.mdl");

//make a thing
uint manual_count_=0;
//loop by the amount set in shapes_
for(uint i=0;i<shapes_;i++){
	//first make sure that the String are not "MANUAL" if manual, I need to grab the size
	String boneroot = bones_[i*2];
	String bonetip = bones_[(i*2)+1];

	if(boneroot != "MANUAL" && bonetip != "MANUAL"){

		Node@ joint = char.GetChild(boneroot,true);
		Node@ jointend = char.GetChild(bonetip,true);

		Vector3 begin = joint.worldPosition;
		Vector3 end = jointend.worldPosition;

		Vector3 vec = begin-end;
		float len = vec.length;

		//----make the components
		RigidBody@ rb = joint.CreateComponent("RigidBody");
		CollisionShape@ cs = joint.CreateComponent("CollisionShape");
		switch(type_[i]){
			case 0:
				cs.SetCapsule(size_[i].x,len,Vector3(0.0f,len/2.0f,0.0f));
				break;
			case 1:
				cs.SetBox(Vector3(size_[i].x,len,size_[i].z),Vector3(0.0f,len/2.0f,0.0f));
				break;
		}
		////
	}else if(bonetip == "MANUAL"){
		Node@ joint = char.GetChild(boneroot,true);

		//----make the components
		RigidBody@ rb = joint.CreateComponent("RigidBody");
		CollisionShape@ cs = joint.CreateComponent("CollisionShape");
		switch(type_[i]){
			case 0:
				cs.SetCapsule(size_[i].x,manual_length_[manual_count_],Vector3(0.0f,manual_length_[manual_count_]/2.0f,0.0f));
				break;
			case 1:
				cs.SetBox(Vector3(size_[i].x,manual_length_[manual_count_],size_[i].z),Vector3(0.0f,manual_length_[manual_count_]/2.0f,0.0f));
				break;
		}
		manual_count_+=1;
	}
	//not dealing with a boneroot is null case yet, cause I dont know what I want to do in that situation
}