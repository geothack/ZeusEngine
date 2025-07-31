#pragma once

#include "Render/ZCamera.h"
#include "Render/ZShader.h"

class ZSkybox
{
public:
	ZSkybox(const std::vector<std::string_view>& faces = {});
	~ZSkybox();

	void Init(const std::vector<std::string_view>& faces = {});
	void Render(ZCamera& activeCamera);

	uint32_t GetHandle () { return z_CubeMapTexture; }
private:
	uint32_t Load(const std::vector<std::string_view>& faces);

private:
	ZArrayObject z_ArrayObject{};
	uint32_t z_CubeMapTexture;

	ZShader z_Shader;

	std::vector<std::string_view> z_Faces{};

};

