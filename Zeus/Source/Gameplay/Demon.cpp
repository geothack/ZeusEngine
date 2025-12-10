#include "Core/CoreLibrary.h"
#include "Demon.h"

Demon::~Demon()
{
}

void Demon::Start()
{
	z_DemonSitting = Animation("Zeus/Resource/Models/Demon/Demon.dae", &GetComponent<ZModel>());
	z_Animator = Animator(&z_DemonSitting);
}

void Demon::FixedUpdate()
{
	
}

void Demon::Update()
{
	z_Animator.UpdateAnimation(ZTime.DeltaTime);
	GetComponent<ZShader>().Attach();
	auto transforms = z_Animator.GetFinalBoneMatrices();
	for (int i = 0; i < transforms.size(); ++i)
		GetComponent<ZShader>().SetMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
}
