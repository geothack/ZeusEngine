#pragma once

#include "Core/UniformBuffer.h"
#include "Gameplay/ZFPSController.h"
#include "Render/Models/ZBox.h"
#include "Render/Models/ZCube.h"
#include "Render/Models/ZPlane.h"
#include "Render/Models/ZSphere.h"
#include "Render/ZCamera.h"
#include "Render/ZRenderer2D.h"
#include "Render/ZRenderer3D.h"
#include "Render/ZShader.h"
#include "Render/ZSkybox.h"
#include "Windows/ZWindow.h"
#include "World/ZEntity.h"
#include "World/ZLevel.h"
#include "World/ZTransform.h"

class ZApplication
{
public:
	ZApplication();
	virtual ~ZApplication();

	void FixedUpdate();
	void Update();

private:

	ZWindow z_GameWindow = ZWindow("ZeusEngine", 800, 600);

	CameraData z_CameraData{};

	double z_TimeStep{};
	double z_LastFrame{};

	ZCamera z_GameCamera{};

	ZBox z_Boxes{};

	ZShader z_EMapping = ZShader("Zeus/Resource/Shaders/Skybox/eMapping.vert", "Zeus/Resource/Shaders/Skybox/eMapping.frag");
	ZShader z_TEMapping = ZShader("Zeus/Resource/Shaders/Lighting/TEADS.vert", "Zeus/Resource/Shaders/Lighting/TEADS.frag");

	ZTexture z_Wood = ZTexture("diffues0","Zeus/Resource/Textures/Wood.png");

	ZSkybox z_Skybox{};

	ZLevel z_MainLevel{};
	ZEntity z_Sprite{};
	ZEntity z_Text{};

	ZEntity z_Ship{};
	ZEntity z_Cube{};
	ZEntity z_Cube2{};
	ZEntity z_Plane{};
	ZEntity z_Sphere{};

	ZRenderer2D z_Renderer2D{};
	ZRenderer3D z_Renderer3D{};

	ZFPSController z_FPSController{};
};


ZApplication* CreateZApplication();