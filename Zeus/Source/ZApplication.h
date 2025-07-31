#pragma once

#include "Windows/ZWindow.h"
#include "Render/Models/ZBox.h"
#include "Render/Models/ZCube.h"
#include "Render/Models/ZPlane.h"
#include "Render/Models/ZSphere.h"
#include "Render/ZCamera.h"
#include "Render/ZRenderer2D.h"
#include "Render/ZRenderer3D.h"
#include "Render/ZShader.h"
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

	double z_TimeStep{};
	double z_LastFrame{};

	ZCamera z_GameCamera{};

	ZShader z_BoxesShader{};
	ZBox z_Boxes{};


	ZLevel z_MainLevel{};
	ZEntity z_Sprite{};
	ZEntity z_Text{};

	ZEntity z_Ship{};
	ZEntity z_Cube{};
	ZEntity z_Plane{};
	ZEntity z_Sphere{};

	ZRenderer2D z_Renderer2D{};
	ZRenderer3D z_Renderer3D{};
};


ZApplication* CreateZApplication();