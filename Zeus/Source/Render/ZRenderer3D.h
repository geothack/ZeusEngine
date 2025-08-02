#pragma once

#include "Render/Models/ZBox.h"
#include "Render/ZCamera.h"
#include "Render/ZShader.h"
#include "Render/ZSkybox.h"
#include "World/ZLevel.h"

class ZRenderer3D
{
public:
	ZRenderer3D();
	~ZRenderer3D();

	void Update(ZLevel& level, ZCamera& activeCamera, ZSkybox* skybox = nullptr);

	inline static bool RenderColliders = false;

private:
	ZShader z_BoxesShader = ZShader("Zeus/Resource/Shaders/Box.vert", "Zeus/Resource/Shaders/Box.frag");
	ZShader z_RedBoxesShader = ZShader("Zeus/Resource/Shaders/RBox.vert", "Zeus/Resource/Shaders/RBox.frag");
};

