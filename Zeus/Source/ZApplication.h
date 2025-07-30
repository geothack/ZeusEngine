#pragma once

#include "Windows/ZWindow.h"
#include "Render/Models/ZCube.h"
#include "Render/Models/ZPlane.h"
#include "Render/Models/ZSphere.h"
#include "Render/ZCamera.h"
#include "Render/ZShader.h"
#include "World/ZTransform.h"

class ZApplication
{
public:
	ZApplication();
	virtual ~ZApplication();

	void Update();

private:

	double z_DeltaTime{};
	double z_LastFrame{};

	ZCamera z_GameCamera{};

	ZShader z_BasicShader{}; 
	ZCube z_BasicCube{};

	ZShader z_LightShader{};
	ZSphere z_Sphere{};

	ZPlane z_Plane{};

	ZShader z_TrollShader{};
	ZModel z_Troll{};

	ZShader z_ShipShader{};
	ZModel z_Ship{};

};


ZApplication* CreateZApplication();