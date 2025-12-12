#include "Core/CoreLibrary.h"
#include "Demon.h"

Demon::~Demon()
{
}

void Demon::Start()
{
	z_DemonSitting = ZAnimation("Zeus/Resource/Models/Demon/Demon.dae", &GetComponent<ZModel>());
	z_Animator = ZAnimator(&z_DemonSitting);
}

void Demon::FixedUpdate()
{

}

void Demon::Update()
{
	z_Animator.UpdateAnimation(ZTime.DeltaTime);
	GetComponent<ZShader>().Attach();
	auto transforms = z_Animator.GetFinalBoneMatrices();

	//for (int i = 0; i < transforms.size(); ++i)
		//GetComponent<ZShader>().SetMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

	//glm::mat4 arr[100];
	//std::copy(transforms.begin(), transforms.end(), arr);


	glUniformMatrix4fv(glGetUniformLocation(GetComponent<ZShader>().GetHandle(), "finalBonesMatrices[0]"), transforms.size(), GL_FALSE, glm::value_ptr(transforms[0]));

}
