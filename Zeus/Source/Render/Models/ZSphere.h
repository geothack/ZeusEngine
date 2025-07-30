#pragma once

#include "Core/CoreLibrary.h"
#include "World/ZModel.h"
#include "World/ZTransform.h"

class ZSphere : public ZModel
{
public:
	ZSphere() = default;
	ZSphere(const ZTransform& transform) : ZModel(transform)
	{

	}

	void Init()
	{
		Load("Zeus/Resource/Models/Sphere", "scene.gltf");
	}

	void Render(ZShader& shader, ZCamera& activeCamera)
	{
		ZModel::Render(shader, activeCamera);
	}
};