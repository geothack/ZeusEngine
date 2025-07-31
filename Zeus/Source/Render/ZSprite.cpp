#include "Core/CoreLibrary.h"
#include "ZSprite.h"
#include "Windows/ZWindow.h"

ZSprite::ZSprite()
{
    Init();
}

ZSprite::~ZSprite()
{
}

void ZSprite::Init()
{
    z_ArrayObject.Generate();

    z_ArrayObject["VBO"] = ZBufferObject(GL_ARRAY_BUFFER);
    z_ArrayObject["VBO"].Generate();

    float vertices[] =
    {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };


    z_ArrayObject["VBO"].Attach();
    z_ArrayObject["VBO"].SetData(vertices, GL_STATIC_DRAW);

    z_ArrayObject.Attach();
    z_ArrayObject["VBO"].SetAttPointer<GLfloat>(0, 4, GL_FLOAT, 4, 0);
    z_ArrayObject["VBO"].Detach();
    ZArrayObject::Detach();


    //Mat4 projection = glm::ortho(0.0f, static_cast<float>(ZWindow::GetSize().Width), static_cast<float>(ZWindow::GetSize().Height), 0.0f, -1.0f, 1.0f);



}

void ZSprite::Render(ZShader& shader, ZTransform& transform)
{
    shader.Attach();
    Mat4 model = Mat4(1.0f);
    model = glm::translate(model, Vec3(transform.GetPosition()));

    model = glm::translate(model, Vec3(0.5f * transform.GetScale().x, 0.5f * transform.GetScale().y, 0.0f));
    model = glm::rotate(model, glm::radians(transform.GetRotation().x), Vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, Vec3(-0.5f * transform.GetScale().x, -0.5f * transform.GetScale().y, 0.0f));

    model = glm::scale(model, Vec3(transform.GetScale()));

    shader.SetMat4("Model", model);

    Mat4 projection = glm::ortho(0.0f, static_cast<float>(ZWindow::GetSize().Width), static_cast<float>(ZWindow::GetSize().Height), 0.0f, -1.0f, 1.0f);

    shader.SetMat4("Projection", projection);

    /*if (material.GetTextures().size() >= 1)
    {
        material.AttachTextures();
    }*/

    z_ArrayObject.Attach();
    z_ArrayObject.Render(GL_TRIANGLES, 0, 6);
    ZArrayObject::Detach();
}
