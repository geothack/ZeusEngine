#pragma once

#include "Render/ZShader.h"
#include "World/ZMesh.h"


class ZModel
{
public:
	ZModel();

	void Init();

	void Render(ZShader& shader);

	void Free();

protected:
	std::vector<ZMesh> z_Meshes;

};

