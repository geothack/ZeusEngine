#pragma once

#include "Render/ZShader.h"
#include "Render/ZTexture.h"

class ZTerrian
{
public:
	ZTerrian() = default;
	ZTerrian(const std::filesystem::path& path = {}, bool flip = false);

	void Render(ZCamera* camera);

private:
	void Init(const std::filesystem::path& path, bool flip);

private:
	ZTessellationShader z_TerrianShader = {};
	ZTexture z_TerrianTexture = {};

	uint32_t z_VAO;
	uint32_t z_VBO;

	int z_Rez = 20;
};