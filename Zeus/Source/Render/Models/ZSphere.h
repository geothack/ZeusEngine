#pragma once

#include "Core/CoreLibrary.h"
#include "World/ZModel.h"
#include "World/ZTransform.h"

class ZSphere : public ZModel
{
public:
	ZSphere() : ZModel("Zeus/Resource/Models/Sphere", "scene.gltf")
	{
		Init();
	}

	void Init()
	{
	}

	void Render(ZShader& shader, ZCamera& activeCamera, ZTransform& transform)
	{
		ZModel::Render(shader, activeCamera, transform);
	}
};