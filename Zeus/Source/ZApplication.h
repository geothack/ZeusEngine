#pragma once

#include "Windows/ZWindow.h"
#include "Render/Models/ZCube.h"
#include "Render/ZShader.h"
#include "World/ZTransform.h"

class ZApplication
{
public:
	ZApplication();
	virtual ~ZApplication();

	void Update();

private:

	ZShader z_BasicShader{}; 
	ZCube z_BasicCube{};

	ZShader z_TrollShader{};
	ZModel z_Troll{};

};


ZApplication* CreateZApplication();