#include "Core/CoreLibrary.h"
#include "ZSkybox.h"
#include "Windows/ZWindow.h"

ZSkybox::ZSkybox(const std::vector<std::string_view>& faces) : z_Faces(faces)
{
    if (z_Faces.size() == 0)
    {
        z_Faces = 
        {
            "Zeus/Resource/Textures/Desert/SkyboxDesert_E.png",
            "Zeus/Resource/Textures/Desert/SkyboxDesert_W.png",
            "Zeus/Resource/Textures/Desert/SkyboxDesert_U.png",
            "Zeus/Resource/Textures/Desert/SkyboxDesert_D.png",
            "Zeus/Resource/Textures/Desert/SkyboxDesert_N.png",
            "Zeus/Resource/Textures/Desert/SkyboxDesert_S.png"
        };
    }
    Init(z_Faces);
}

ZSkybox::~ZSkybox()
{
}

void ZSkybox::Init(const std::vector<std::string_view>& faces)
{
    z_Shader = ZShader("Zeus/Resource/Shaders/Skybox/Skybox.vert", "Zeus/Resource/Shaders/Skybox/Skybox.frag");

    float skyboxVertices[] =
    {
        // positions          
        -100.0f,  100.0f, -100.0f,
        -100.0f, -100.0f, -100.0f,
         100.0f, -100.0f, -100.0f,
         100.0f, -100.0f, -100.0f,
         100.0f,  100.0f, -100.0f,
        -100.0f,  100.0f, -100.0f,

        -100.0f, -100.0f,  100.0f,
        -100.0f, -100.0f, -100.0f,
        -100.0f,  100.0f, -100.0f,
        -100.0f,  100.0f, -100.0f,
        -100.0f,  100.0f,  100.0f,
        -100.0f, -100.0f,  100.0f,

         100.0f, -100.0f, -100.0f,
         100.0f, -100.0f,  100.0f,
         100.0f,  100.0f,  100.0f,
         100.0f,  100.0f,  100.0f,
         100.0f,  100.0f, -100.0f,
         100.0f, -100.0f, -100.0f,

        -100.0f, -100.0f,  100.0f,
        -100.0f,  100.0f,  100.0f,
         100.0f,  100.0f,  100.0f,
         100.0f,  100.0f,  100.0f,
         100.0f, -100.0f,  100.0f,
        -100.0f, -100.0f,  100.0f,

        -100.0f,  100.0f, -100.0f,
         100.0f,  100.0f, -100.0f,
         100.0f,  100.0f,  100.0f,
         100.0f,  100.0f,  100.0f,
        -100.0f,  100.0f,  100.0f,
        -100.0f,  100.0f, -100.0f,

        -100.0f, -100.0f, -100.0f,
        -100.0f, -100.0f,  100.0f,
         100.0f, -100.0f, -100.0f,
         100.0f, -100.0f, -100.0f,
        -100.0f, -100.0f,  100.0f,
         100.0f, -100.0f,  100.0f
    };

    z_ArrayObject.Generate();
    z_ArrayObject.Attach();

    z_ArrayObject["VBO"] = ZBufferObject(GL_ARRAY_BUFFER);
    z_ArrayObject["VBO"].Generate();
    z_ArrayObject["VBO"].Attach();
    z_ArrayObject["VBO"].SetDataS(skyboxVertices, &skyboxVertices, GL_STATIC_DRAW);
    z_ArrayObject["VBO"].SetAttPointer<float>(0, 3, GL_FLOAT, 3, 0);

    z_CubeMapTexture = Load(faces);

    z_Shader.Attach();
    z_Shader.SetInt("skybox", 0);
}

void ZSkybox::Render(ZCamera& activeCamera)
{
    glDepthFunc(GL_LEQUAL);
    z_Shader.Attach();
    Mat4 view = activeCamera.GetViewMatrix(); 
    Mat4 projection = glm::perspective(glm::radians(45.0f), (float)ZWindow::GetSize().Width / (float)ZWindow::GetSize().Height, 0.1f, 100.0f);
    z_Shader.SetMat4("View", view);
    z_Shader.SetMat4("Projection", projection);

    z_ArrayObject.Attach();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, z_CubeMapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    ZArrayObject::Detach();
    glDepthFunc(GL_LESS); 
}

uint32_t ZSkybox::Load(const std::vector<std::string_view>& faces)
{
    uint32_t textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrComponents;

    //stbi_set_flip_vertically_on_load(true);

    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].data(), &width, &height, &nrComponents, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            ZLog.Error("Cubemap texture failed to load at path");
            ZLog.Error(faces[i].data());
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
