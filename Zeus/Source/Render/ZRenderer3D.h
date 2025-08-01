#pragma once

#include "Render/ZCamera.h"
#include "Render/ZFramebuffer.h"
#include "Render/ZShader.h"
#include "Render/ZSkybox.h"
#include "World/ZLevel.h"

class ZRenderer3D
{
public:
	ZRenderer3D();
	~ZRenderer3D();

	void Update(ZLevel& level, ZCamera& activeCamera, ZSkybox& skybox);

private:
	ZFramebuffer z_DepthBuffer{};
	ZShader z_Shader = ZShader("Zeus/Resource/Shaders/Shadows/Depth.vert", "Zeus/Resource/Shaders/Shadows/Depth.frag");
	ZShader z_LightShader = ZShader("Zeus/Resource/Shaders/Shadows/SimpleDepth.vert", "Zeus/Resource/Shaders/Shadows/SimpleDepth.frag");
	ZTexture z_Wood = ZTexture("diffues0", "Zeus/Resource/Textures/Wood.png");
};

