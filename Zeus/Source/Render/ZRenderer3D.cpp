#include "Core/CoreLibrary.h"
#include "ZRenderer3D.h"
#include "Windows/ZWindow.h"

ZRenderer3D::ZRenderer3D()
{
	glEnable(GL_DEPTH_TEST);
}

ZRenderer3D::~ZRenderer3D()
{
}

void ZRenderer3D::Update(ZLevel& level, ZCamera& activeCamera)
{
	glClearColor(0.33, 0.33, 0.33, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    {
        auto view = level.GetRegister().view<ZTransform, ZModel, ZShader>();

        for (auto [entity, transform, model, shader] : view.each())
        {
            if (level.GetRegister().any_of<ZBoxCollider>(entity))
            {
                level.GetRegister().get<ZBoxCollider>(entity).SetPosition(transform.GetPosition());
            }

            shader.Attach();
            shader.BindLighting(activeCamera);
            if (shader.GetTextures().size() > 0)
            {
                shader.GetTextures()[0].Attach();
                glBindTextureUnit(0, shader.GetTextures()[0].GetHandle());
            }

           /* if (level.GetRegister().any_of<ZSkybox>(entity))
            {
                if (shader.SetSky)
                {
                    shader.SetInt("skybox", 1);
                    glBindTextureUnit(1, level.GetRegister().get<ZSkybox>(entity).GetHandle());
                }
            }*/
            
            model.Render(shader, activeCamera,transform);
        }
    }

    {
        auto view = level.GetRegister().view<ZSkybox>();

        for (auto [entity, skybox] : view.each())
        {
            skybox.Render(activeCamera);
        }
    }

    {
        auto view = level.GetRegister().view<ZTerrian>();

        for (auto [entity, terrian] : view.each())
        {
            terrian.Render(&activeCamera);
        }
    }

    if (RenderColliders)
    {
        if (Boxes.GetPositions().size() > 0)
        {
            Boxes.Render(z_BoxesShader, activeCamera);
        }
    }

}
