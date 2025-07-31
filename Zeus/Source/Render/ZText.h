#pragma once

#include "Core/VertexMemory.h"
#include "Render/ZShader.h"
#include "World/ZTransform.h"


struct Character
{
	uint32_t TextureID;
	glm::ivec2   Size;
	glm::ivec2   Bearing;
	uint32_t Advance;
};

class ZText
{
public:
	ZText() = default;
	ZText(std::string_view message, const int height, const Color& color, const std::filesystem::path& path = "Zeus/Resource/Fonts/Hey Comic.ttf");
	~ZText() = default;

	void LoadFont(const std::filesystem::path& path);
	void RenderFont(ZShader& shader, ZTransform& transform);

	std::string Message = "";

	Color TextColor{};

	std::map<GLchar, Character> Characters;

	GLuint GetVertexArray() { return z_ArrayObject.z_Val; }
	GLuint GetVertexBuffer() { return z_ArrayObject["VBO"].z_Val; }

private:
	Mat4 z_World{};

	ZArrayObject z_ArrayObject{};

	int z_Height{};
};

