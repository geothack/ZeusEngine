#include "Core/CoreLibrary.h"
#include "ZMesh.h"

std::vector<Vertex> Vertex::GenerateList(const float* vertices, const int numOfVertices)
{
	std::vector<Vertex> ret(numOfVertices);

	int stride = sizeof(Vertex) / sizeof(float);

	for (auto i = 0; i < numOfVertices; i++)
	{
		ret[i].Position = glm::vec3
		(
			vertices[i * stride + 0],
			vertices[i * stride + 1],
			vertices[i * stride + 2]
		);

		ret[i].TextureCoordinate = glm::vec2
		(
			vertices[i * stride + 3],
			vertices[i * stride + 4]
		);

		ret[i].Normal = glm::vec3
		(
			vertices[i * stride + 5],
			vertices[i * stride + 6],
			vertices[i * stride + 7]
		);
	}

	return ret;
}

ZMesh::ZMesh()
{
}

ZMesh::ZMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<ZTexture>& textures) : z_Vertices(vertices)
	, z_Indices(indices), z_Textures(textures)
{
	Init();
}

void ZMesh::Render(ZShader& shader)
{
	if (z_Textures.size() >= 1)
	{
		uint32_t diffuse = 0;
		uint32_t specular = 0;
		for (size_t i = 0; i < z_Textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			std::string name;
			switch (z_Textures[i].GetType())
			{
			case aiTextureType_DIFFUSE:
				name = "diffuse" + std::to_string(diffuse++);
				break;

			case aiTextureType_SPECULAR:
				name = "specular" + std::to_string(specular++);
				break;
			}

			shader.SetInt(name, i);
			z_Textures[i].Attach();
		}
	}

	z_ArrayObject.Attach();
	z_ArrayObject.Render(GL_TRIANGLES, static_cast<GLsizei>(z_Indices.size()), GL_UNSIGNED_INT, 0);
	ZArrayObject::Detach();

	glActiveTexture(GL_TEXTURE0);
}

void ZMesh::Free()
{
	z_ArrayObject.Free();
}

void ZMesh::Init()
{
	z_ArrayObject.Generate();
	z_ArrayObject.Attach();

	z_ArrayObject["EBO"] = ZBufferObject(GL_ELEMENT_ARRAY_BUFFER);
	z_ArrayObject["EBO"].Generate();
	z_ArrayObject["EBO"].Attach();
	z_ArrayObject["EBO"].SetData<uint32_t>(z_Indices.size(), &z_Indices[0], GL_STATIC_DRAW);


	z_ArrayObject["VBO"] = ZBufferObject(GL_ARRAY_BUFFER);
	z_ArrayObject["VBO"].Generate();
	z_ArrayObject["VBO"].Attach();
	z_ArrayObject["VBO"].SetData<Vertex>(z_Vertices.size(), &z_Vertices[0], GL_STATIC_DRAW);


	z_ArrayObject["VBO"].SetAttPointer<GLfloat>(0, 3, GL_FLOAT, 8, 0);
	z_ArrayObject["VBO"].SetAttPointer<GLfloat>(1, 2, GL_FLOAT, 8, 3);
	z_ArrayObject["VBO"].SetAttPointer<GLfloat>(2, 3, GL_FLOAT, 8, 5);

	z_ArrayObject.Detach();

	ZArrayObject::Detach();
}
