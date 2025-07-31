#include "Core/CoreLibrary.h"
#include "ZRenderer2D.h"

ZRenderer2D::ZRenderer2D()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

ZRenderer2D::~ZRenderer2D()
{

}

void ZRenderer2D::Update(ZLevel& level)
{
    glDisable(GL_DEPTH_TEST);

    {
        auto view = level.GetRegister().view<ZTransform, ZSprite, ZShader>();

        for (auto [entity, transform, sprite, shader] : view.each())
        {
            shader.Attach();
            sprite.Render(shader, transform);
        }
    }

    {
        auto view = level.GetRegister().view<ZTransform, ZText, ZShader>();

        for (auto [entity, transform, text, shader] : view.each())
        {
            text.RenderFont(shader, transform);
        }
    }

    glEnable(GL_DEPTH_TEST);
}
