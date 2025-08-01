#include "Core/CoreLibrary.h"
#include "ZRenderer3D.h"

ZRenderer3D::ZRenderer3D()
{
	glEnable(GL_DEPTH_TEST);
}

ZRenderer3D::~ZRenderer3D()
{
}

void ZRenderer3D::Update(ZLevel& level, ZCamera& activeCamera, ZSkybox& skyBox)
{
	glClearColor(0.33, 0.33, 0.33, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    {
        auto view = level.GetRegister().view<ZTransform, ZModel, ZShader>();

        for (auto [entity, transform, model, shader] : view.each())
        {
            shader.Attach();
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
            model.Render(shader, activeCamera,transform);
        }
    }
}
