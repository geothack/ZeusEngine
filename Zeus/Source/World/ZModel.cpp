#include "Core/CoreLibrary.h"
#include "ZModel.h"

ZModel::ZModel()
{
}

void ZModel::Init()
{
}

void ZModel::Render(ZShader& shader)
{
	for (auto& zMesh : z_Meshes)
	{
		zMesh.Render(shader);
	}
}

void ZModel::Free()
{
	for (auto& zMesh : z_Meshes)
	{
		zMesh.Free();
	}
}
