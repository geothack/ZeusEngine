#include "Core/CoreLibrary.h"
#include "ZTerrian.h"
#include "Core/Error.h"

ZTerrian::ZTerrian(const std::filesystem::path& path, bool flip)
{
    z_TerrianShader = ZTessellationShader("Zeus/Resource/Shaders/Terrian/Terrian.vert", "Zeus/Resource/Shaders/Terrian/Terrian.frag", "Zeus/Resource/Shaders/Terrian/Terrian.tcs", "Zeus/Resource/Shaders/Terrian/Terrian.tes");
    Init(path, flip);
}

void ZTerrian::Render(ZCamera* camera)
{
    glActiveTexture(GL_TEXTURE0);


    z_TerrianShader.Attach();
    z_TerrianShader.SetInt("heightMap", 0);
    z_TerrianTexture.Attach();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1200 / (float)800, 0.1f, 100000.0f);
    glm::mat4 view = camera->GetViewMatrix();
    z_TerrianShader.SetMat4("projection", projection);
    z_TerrianShader.SetMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0, -50, 0));
    model = glm::scale(model, glm::vec3(0.25));
    z_TerrianShader.SetMat4("model", model);

    glBindVertexArray(z_VAO);
    glDrawArrays(GL_PATCHES, 0, 4 * z_Rez * z_Rez);
}

void ZTerrian::Init(const std::filesystem::path& path, bool flip)
{
    z_TerrianTexture = ZTexture("", path);

    std::vector<float> vertices;

    for (unsigned i = 0; i <= z_Rez - 1; i++)
    {
        for (unsigned j = 0; j <= z_Rez - 1; j++)
        {
            vertices.push_back(-z_TerrianTexture.GetWidth() / 2.0f + z_TerrianTexture.GetWidth() * i / (float)z_Rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-z_TerrianTexture.GetHeight() / 2.0f + z_TerrianTexture.GetHeight() * j / (float)z_Rez); // v.z
            vertices.push_back(i / (float)z_Rez); // u
            vertices.push_back(j / (float)z_Rez); // v

            vertices.push_back(-z_TerrianTexture.GetWidth() / 2.0f + z_TerrianTexture.GetWidth() * (i + 1) / (float)z_Rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-z_TerrianTexture.GetHeight() / 2.0f + z_TerrianTexture.GetHeight() * j / (float)z_Rez); // v.z
            vertices.push_back((i + 1) / (float)z_Rez); // u
            vertices.push_back(j / (float)z_Rez); // v

            vertices.push_back(-z_TerrianTexture.GetWidth() / 2.0f + z_TerrianTexture.GetWidth() * i / (float)z_Rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-z_TerrianTexture.GetHeight() / 2.0f + z_TerrianTexture.GetHeight() * (j + 1) / (float)z_Rez); // v.z
            vertices.push_back(i / (float)z_Rez); // u
            vertices.push_back((j + 1) / (float)z_Rez); // v

            vertices.push_back(-z_TerrianTexture.GetWidth() / 2.0f + z_TerrianTexture.GetWidth() * (i + 1) / (float)z_Rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-z_TerrianTexture.GetHeight() / 2.0f + z_TerrianTexture.GetHeight() * (j + 1) / (float)z_Rez); // v.z
            vertices.push_back((i + 1) / (float)z_Rez); // u
            vertices.push_back((j + 1) / (float)z_Rez); // v
        }
    }


    glGenVertexArrays(1, &z_VAO);
    glBindVertexArray(z_VAO);

    glGenBuffers(1, &z_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, z_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glPatchParameteri(GL_PATCH_VERTICES, 4);
}

