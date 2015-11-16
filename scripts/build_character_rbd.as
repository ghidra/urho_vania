//abs - neck (body)
//neck - MANUAL (head)

//X2
//armupper.R -armlower.R (right upper arm)
//armlower.R-wrist.R (right lower arm)

//X2
//legupper.R - leglower.R (right thigh)
//leglower.R - foot.R (right calf)


Node@ char = scene.CreateChild("character");

AnimatedModel@ charmdl = char.CreateComponent("AnimatedModel");
charmdl.model = cache.GetResource("Model", "Models/Man/MAN.mdl");

//make a thing
Node@ joint = char.GetChild("armupper.R",true);
Node@ jointend = char.GetChild("armlower.R",true);

Vector3 begin = joint.worldPosition;
Vector3 end = jointend.worldPosition;

Vector3 vec = begin-end;
float len = vec.length;

//----make the components
RigidBody@ rb = joint.CreateComponent("RigidBody");
CollisionShape@ cs = joint.CreateComponent("CollisionShape");
cs.SetCapsule(1.0f,len,Vector3(0.0f,len/2.0f,0.0f));
////