#pragma once

#include "Windows/ZWindow.h"
#include "World/ZLevel.h"

class ZRenderer2D
{
public:
	ZRenderer2D();
	~ZRenderer2D();

	void Update(ZLevel& level);

};

