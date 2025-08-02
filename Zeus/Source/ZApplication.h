#pragma once

#include "Core/LevelCache.h"
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
	void Update(ZLevel& level, ZCamera& activeCamera);

private:

	ZWindow z_GameWindow = ZWindow("ZeusEngine", 800, 600);

	CameraData z_CameraData{};

	double z_TimeStep{};
	double z_LastFrame{};


	ZBox z_Boxes{};

	ZSkybox z_Skybox{};

	

	ZRenderer2D z_Renderer2D{};
	ZRenderer3D z_Renderer3D{};
};


ZApplication* CreateZApplication();