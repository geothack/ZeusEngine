#pragma once

#include "Windows/ZWindow.h"
#include "Render/ZShader.h"

class ZApplication
{
public:
	ZApplication();
	virtual ~ZApplication();

	void Update();

private:

	ZShader z_BasicShader{}; 
};


ZApplication* CreateZApplication();