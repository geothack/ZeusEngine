#pragma once

#include "Windows/ZWindow.h"

class ZApplication
{
public:
	ZApplication();
	virtual ~ZApplication();

	void Update();

private:
};


ZApplication* CreateZApplication();