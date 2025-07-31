#pragma once

#include "Core/CoreLibrary.h"
#include "World/ZModel.h"
#include "World/ZTransform.h"

class ZPlane : public ZModel
{
public:
	ZPlane() : ZModel()
	{
		Init();
	}

	void Init()
	{
        int numOfVertices = 6;

		float vertices[] =
		{
			// positions            // texcoords  // normals
			 25.0f, -0.5f,  25.0f,  25.0f,  0.0f, 0.0f, 1.0f, 0.0f,
			-25.0f, -0.5f,  25.0f,   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
			-25.0f, -0.5f, -25.0f,   0.0f, 25.0f, 0.0f, 1.0f, 0.0f,

			 25.0f, -0.5f,  25.0f,  25.0f,  0.0f, 0.0f, 1.0f, 0.0f,
			-25.0f, -0.5f, -25.0f,   0.0f, 25.0f, 0.0f, 1.0f, 0.0f,
			 25.0f, -0.5f, -25.0f,  25.0f, 25.0f, 0.0f, 1.0f, 0.0f,
		};

        std::vector<uint32_t> indices(numOfVertices);

        for (uint32_t i = 0; i < numOfVertices; i++)
        {
            indices[i] = i;
        }


        z_Meshes.emplace_back(ZMesh(Vertex::GenerateList(vertices, numOfVertices), indices));
	}

	void Render(ZShader& shader, ZCamera& activeCamera, ZTransform& transform)
	{
		ZModel::Render(shader, activeCamera, transform);
	}

};