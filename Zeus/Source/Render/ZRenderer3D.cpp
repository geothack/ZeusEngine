#include "Core/CoreLibrary.h"
#include "ZRenderer3D.h"
#include "Windows/ZWindow.h"

ZRenderer3D::ZRenderer3D()
{
	glEnable(GL_DEPTH_TEST);
    z_Shader.Attach();
    z_Shader.SetInt("depthMap", 0);
}

ZRenderer3D::~ZRenderer3D()
{
}

void ZRenderer3D::Update(ZLevel& level, ZCamera& activeCamera, ZSkybox& skyBox)
{
	glClearColor(0.33, 0.33, 0.33, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glViewport(0, 0, 2000, 2000);
    //z_DepthBuffer.Attach();
    //glClear(GL_DEPTH_BUFFER_BIT);

    //glm::mat4 lightProjection, lightView;
    //glm::mat4 lightSpaceMatrix;
    //float near_plane = 1.0f, far_plane = 7.5f;
    //lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    //lightView = glm::lookAt(Vec3(-2.0f, 12.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    //lightSpaceMatrix = lightProjection * lightView;

    //{
    //    auto view = level.GetRegister().view<ZTransform, ZModel, ZShader>();

    //    for (auto [entity, transform, model, shader] : view.each())
    //    {
    //        z_LightShader.Attach();
    //        z_LightShader.SetMat4("lightSpaceMatrix", lightSpaceMatrix);
    //        //shader.BindLighting(activeCamera);
    //        /*if (shader.GetTextures().size() > 0)
    //        {
    //            shader.GetTextures()[0].Attach();
    //            glBindTextureUnit(0, shader.GetTextures()[0].GetHandle());
    //        }
    //        if (shader.SetSky)
    //        {
    //            shader.SetInt("skybox", 1);
    //            glBindTextureUnit(1, skyBox.GetHandle());
    //        }*/
    //        model.Render(z_LightShader, activeCamera,transform,true);
    //    }
    //}

    //z_DepthBuffer.Detach();
    //glViewport(0, 0, ZWindow::GetSize().Width, ZWindow::GetSize().Height);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    {
        auto view = level.GetRegister().view<ZTransform, ZModel, ZShader>();

        for (auto [entity, transform, model, shader] : view.each())
        {
            shader.Attach();
            //shader.SetVec3("viewPos", activeCamera.GetPos());
            //shader.SetVec3("lightPos", Vec3(-2.0f, 12.0f, -1.0f));
            //shader.SetMat4("lightSpaceMatrix", lightSpaceMatrix);
            //shader.SetInt("diffuseTexture", 0);
            //glBindTextureUnit(0, z_Wood.GetHandle());
            //shader.SetInt("shadowMap", 1);
            //glBindTextureUnit(1, z_DepthBuffer.GetTexture());
            shader.BindLighting(activeCamera);
            if (shader.GetTextures().size() > 0)
            {
                shader.GetTextures()[0].Attach();
                glBindTextureUnit(0, shader.GetTextures()[0].GetHandle());
            }
            if (shader.SetSky)
            {
                shader.SetInt("skybox", 1);
                glBindTextureUnit(1, skyBox.GetHandle());
            }
            model.Render(shader, activeCamera, transform);
        }
    }


   //z_Shader.Attach();
   //z_Shader.SetFloat("near_plane", 1.0);
   //z_Shader.SetFloat("far_plane", 7.5);
   //z_DepthBuffer.Render(false);
}
