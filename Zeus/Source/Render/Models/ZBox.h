#pragma once


#include "Core/CoreLibrary.h"

#include "World/ZTransform.h"
#include "Render/ZCamera.h"
#include "Render/ZShader.h"
#include "Windows/ZWindow.h"
#include "Core/VertexMemory.h"

class ZBox
{
public:
    ZBox()
    {

    }

    void Init()
    {
        z_Vertices =
        {
            // position             x   y   z   i
             0.5f,  0.5f,  0.5f, // +   +   +   0
            -0.5f,  0.5f,  0.5f, // -   +   +   1
            -0.5f, -0.5f,  0.5f, // -   -   +   2
             0.5f, -0.5f,  0.5f, // +   -   +   3
             0.5f,  0.5f, -0.5f, // +   +   -   4
            -0.5f,  0.5f, -0.5f, // -   +   -   5
            -0.5f, -0.5f, -0.5f, // -   -   -   6
             0.5f, -0.5f, -0.5f  // +   -   -   7
        };

        z_Indices =
        { // 12 lines
            // front face (+ve z)
            0, 1,
            1, 2,
            2, 3,
            3, 0,
            // back face (-ve z)
            4, 5,
            5, 6,
            6, 7,
            7, 4,
            // right face (+ve x)
            0, 4,
            3, 7,
            // left face (-ve x)
            1, 5,
            2, 6
        };

        z_ArrayObject.Generate();
        z_ArrayObject.Attach();

        z_ArrayObject["VBO"] = ZBufferObject(GL_ARRAY_BUFFER);
        z_ArrayObject["VBO"].Generate();
        z_ArrayObject["VBO"].Attach();
        z_ArrayObject["VBO"].SetData<float>(z_Vertices.size(), &z_Vertices[0], GL_STATIC_DRAW);
        z_ArrayObject["VBO"].SetAttPointer<GLfloat>(0, 3, GL_FLOAT, 3, 0);

        z_ArrayObject["OVBO"] = ZBufferObject(GL_ARRAY_BUFFER);
        z_ArrayObject["OVBO"].Generate();
        z_ArrayObject["OVBO"].Attach();
        z_ArrayObject["OVBO"].SetData<float>(300, NULL, GL_DYNAMIC_DRAW);
        z_ArrayObject["OVBO"].SetAttPointer<Vec3>(1, 3, GL_FLOAT, 1, 0);

        z_ArrayObject["EBO"] = ZBufferObject(GL_ELEMENT_ARRAY_BUFFER);
        z_ArrayObject["EBO"].Generate();
        z_ArrayObject["EBO"].Attach();
        z_ArrayObject["EBO"].SetData<uint32_t>(z_Indices.size(), &z_Indices[0], GL_STATIC_DRAW);

        z_ArrayObject["SVBO"] = ZBufferObject(GL_ARRAY_BUFFER);
        z_ArrayObject["SVBO"].Generate();
        z_ArrayObject["SVBO"].Attach();
        z_ArrayObject["SVBO"].SetData<float>(300, NULL, GL_DYNAMIC_DRAW);
        z_ArrayObject["SVBO"].SetAttPointer<Vec3>(2, 3, GL_FLOAT, 1, 0);
        z_ArrayObject["SVBO"].Detach();

        ZArrayObject::Detach;


        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glVertexAttribDivisor(1, 1); // Reset third attrib every 1 instance
        glVertexAttribDivisor(2, 1);

        glBindVertexArray(0);
    }


    void Render(ZShader& shader, ZCamera& activeCamera)
    {
        Mat4 view = activeCamera.GetViewMatrix();
        Mat4 projection = glm::perspective(glm::radians(45.0f), (float)ZWindow::GetSize().Width / (float)ZWindow::GetSize().Height, 0.1f, 100.0f);

        shader.Attach();
        shader.SetMat4("Model", Mat4(1.0));
        shader.SetMat4("View", view);
        shader.SetMat4("Projection", projection);

        auto size = std::min(100, static_cast<int>(z_Positions.size()));

        if (size != 0)
        {
            z_ArrayObject["OVBO"].Attach();
            z_ArrayObject["OVBO"].UpdateData<Vec3>(0, size, &z_Positions[0]);

            z_ArrayObject["SVBO"].Attach();
            z_ArrayObject["SVBO"].UpdateData<Vec3>(0, size, &z_Scales[0]);

            z_ArrayObject["SVBO"].Detach();
        }


        z_ArrayObject.Attach();
        z_ArrayObject.Render(GL_LINES, z_Indices.size(), GL_UNSIGNED_INT, 0, size);
        z_ArrayObject.Detach();
    }

    void Free()
    {
        z_ArrayObject.Free();
    }

    std::vector<Vec3>& GetPositions() { return z_Positions; }
    std::vector<Vec3>& GetScales() { return z_Scales; }

private:
    ZArrayObject z_ArrayObject;

    std::vector<float> z_Vertices;
    std::vector<uint32_t> z_Indices;

    std::vector<Vec3> z_Positions;
    std::vector<Vec3> z_Scales;

};

class BoxCollider
{
public:
    /*BoxCollider(BoundTypes type, Box& boxes, const glm::vec3& position, const glm::vec3& scale)
    {
        mBounds = BoundingRegion(type);
        mBounds.SetMin(glm::vec3(-5.0f));
        mBounds.SetMax(glm::vec3(5.0f));
        boxes.AddInstance(mBounds, position, scale);
    }*/


private:
    //BoundingRegion mBounds;

};