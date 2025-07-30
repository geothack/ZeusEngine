#pragma once

#include "Render/ZTexture.h"
#include "Render/ZShader.h"
#include "Core/VertexMemory.h"

struct Vertex
{
	Vec3 Position;
	Vec2 TextureCoordinate;
	Vec3 Normal;

	static std::vector<Vertex> GenerateList(const float* vertices, const int numOfVertices);
};


class ZMesh
{
public:
	ZMesh();
	ZMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<ZTexture>& textures = {});

	void Render(ZShader& shader);

	void Free();


private:
	void Init();

private:
	std::vector<Vertex> z_Vertices;
	std::vector<uint32_t> z_Indices;

	ZArrayObject z_ArrayObject;

	std::vector<ZTexture> z_Textures;
};

