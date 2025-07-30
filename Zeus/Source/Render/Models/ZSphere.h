#pragma once

#include "Core/CoreLibrary.h"
#include "World/ZModel.h"
#include "World/ZTransform.h"

class ZSphere : public ZModel
{
public:
	ZSphere() = default;
	ZSphere(const ZTransform& transform) : z_Transform(transform)
	{

	}

	void Init()
	{
		Load("Zeus/Resource/Models/Sphere", "scene.gltf");
	}

	void Render(ZShader& shader)
	{
		Mat4 model = Mat4(1.0);

		model = glm::translate(model, z_Transform.GetPosition());
		//model = glm::rotate(model, static_cast<float>(45.0f * glfwGetTime() * 0.01), Vec3(1, 1, 0));
		model = glm::scale(model, z_Transform.GetScale());

		shader.Attach();
		shader.SetMat4("Model", model);

		ZModel::Render(shader);
	}

private:
	ZTransform z_Transform{};
};