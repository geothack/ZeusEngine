#include "Core/CoreLibrary.h"
#include "ZFramebuffer.h"
#include "Core/Error.h"
#include "Windows/ZWindow.h"

ZFramebuffer::ZFramebuffer()
{
	glGenFramebuffers(1, &z_Framebuffer);
    glGenTextures(1, &z_Texture);
    Init();
}

void ZFramebuffer::Init()
{
    float quadVertices[] = 
    {
        // positions        // texture Coords
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };

    z_ArrayObject.Generate();
    z_ArrayObject.Attach();
    z_ArrayObject["VBO"] = ZBufferObject(GL_ARRAY_BUFFER);
    z_ArrayObject["VBO"].Generate();
    z_ArrayObject["VBO"].Attach();
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    z_ArrayObject["VBO"].SetAttPointer<float>(0, 3, GL_FLOAT, 5, 0);
    z_ArrayObject["VBO"].SetAttPointer<float>(1, 2, GL_FLOAT, 5, 3);

    
    glBindTexture(GL_TEXTURE_2D, z_Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 2000, 2000, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_FRAMEBUFFER, z_Framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, z_Texture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);


    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        Error error("Failed to complete framebuffer");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ZFramebuffer::Attach() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, z_Framebuffer);
}

void ZFramebuffer::Detach() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ZFramebuffer::Render(bool doRender)
{
    glBindTextureUnit(0, z_Texture);
    if (doRender)
    {
        z_ArrayObject.Attach();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        ZArrayObject::Detach();
    }
}
