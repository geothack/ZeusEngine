#include "Core/CoreLibrary.h"
#include "ZRenderer3D.h"

ZRenderer3D::ZRenderer3D()
{
	glEnable(GL_DEPTH_TEST);
}

ZRenderer3D::~ZRenderer3D()
{
}

void ZRenderer3D::Update(ZLevel& level)
{
	glClearColor(0.33, 0.33, 0.33, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
