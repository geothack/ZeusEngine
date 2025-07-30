#pragma once

#include "Core/CoreLibrary.h"
#include "World/ZModel.h"
#include "World/ZTransform.h"

class ZCube : public ZModel
{
public:
    ZCube() = default;
	ZCube(const ZTransform& transform) : z_Transform(transform)
	{

	}

	void Init()
	{
		int numOfVertices = 36;

        float vertices[] =
        {
            -1.0f, -1.0f, -1.0f,    0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
             1.0f,  1.0f, -1.0f,    1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
             1.0f, -1.0f, -1.0f,    1.0f, 0.0f,   0.0f,  0.0f, -1.0f,
             1.0f,  1.0f, -1.0f,    1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,    0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,    0.0f, 1.0f,   0.0f,  0.0f, -1.0f,
            // front face                      
            -1.0f, -1.0f,  1.0f,   0.0f, 0.0f,    0.0f,  0.0f,  1.0f,
             1.0f, -1.0f,  1.0f,   1.0f, 0.0f,    0.0f,  0.0f,  1.0f,
             1.0f,  1.0f,  1.0f,   1.0f, 1.0f,    0.0f,  0.0f,  1.0f,
             1.0f,  1.0f,  1.0f,   1.0f, 1.0f,    0.0f,  0.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,   0.0f, 1.0f,    0.0f,  0.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,   0.0f, 0.0f,    0.0f,  0.0f,  1.0f,
            // left face                       
            -1.0f,  1.0f,  1.0f,   1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,
            -1.0f,  1.0f, -1.0f,   1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
            -1.0f, -1.0f, -1.0f,   0.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
            -1.0f, -1.0f, -1.0f,   0.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
            -1.0f, -1.0f,  1.0f,   0.0f, 0.0f,   -1.0f,  0.0f,  0.0f,
            -1.0f,  1.0f,  1.0f,   1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,
            // right face                      
             1.0f,  1.0f,  1.0f,   1.0f, 0.0f,    1.0f,  0.0f,  0.0f,
             1.0f, -1.0f, -1.0f,   0.0f, 1.0f,    1.0f,  0.0f,  0.0f,
             1.0f,  1.0f, -1.0f,   1.0f, 1.0f,    1.0f,  0.0f,  0.0f,
             1.0f, -1.0f, -1.0f,   0.0f, 1.0f,    1.0f,  0.0f,  0.0f,
             1.0f,  1.0f,  1.0f,   1.0f, 0.0f,    1.0f,  0.0f,  0.0f,
             1.0f, -1.0f,  1.0f,   0.0f, 0.0f,    1.0f,  0.0f,  0.0f,
             // bottom face                     
             -1.0f, -1.0f, -1.0f,   0.0f, 1.0f,    0.0f, -1.0f,  0.0f,
              1.0f, -1.0f, -1.0f,   1.0f, 1.0f,    0.0f, -1.0f,  0.0f,
              1.0f, -1.0f,  1.0f,   1.0f, 0.0f,    0.0f, -1.0f,  0.0f,
              1.0f, -1.0f,  1.0f,   1.0f, 0.0f,    0.0f, -1.0f,  0.0f,
             -1.0f, -1.0f,  1.0f,   0.0f, 0.0f,    0.0f, -1.0f,  0.0f,
             -1.0f, -1.0f, -1.0f,   0.0f, 1.0f,    0.0f, -1.0f,  0.0f,
             // top face                        
             -1.0f,  1.0f, -1.0f,   0.0f, 1.0f,     0.0f,  1.0f,  0.0f,
              1.0f,  1.0f , 1.0f,   1.0f, 0.0f,     0.0f,  1.0f,  0.0f,
              1.0f,  1.0f, -1.0f,   1.0f, 1.0f,     0.0f,  1.0f,  0.0f,
              1.0f,  1.0f,  1.0f,   1.0f, 0.0f,     0.0f,  1.0f,  0.0f,
             -1.0f,  1.0f, -1.0f,   0.0f, 1.0f,     0.0f,  1.0f,  0.0f,
             -1.0f,  1.0f,  1.0f,   0.0f, 0.0f,     0.0f,  1.0f,  0.0f
        };

        std::vector<uint32_t> indices(numOfVertices);

        for (uint32_t i = 0; i < numOfVertices; i++)
        {
            indices[i] = i;
        }


        z_Meshes.emplace_back(ZMesh(Vertex::GenerateList(vertices, numOfVertices), indices));
	}

	void Render(ZShader& shader)
	{
        Mat4 model = Mat4(1.0);

        model = glm::translate(model, z_Transform.GetPosition());
        model = glm::rotate(model, static_cast<float>(45.0f * glfwGetTime() * 0.01), Vec3(1, 1, 0));
        model = glm::scale(model, z_Transform.GetScale());

        shader.Attach();
        shader.SetMat4("Model", model);

        ZModel::Render(shader);
	}

private:
	ZTransform z_Transform;
};
