#pragma once

#include "Core/VertexMemory.h"
#include "Render/ZShader.h"
#include "World/ZTransform.h"

class ZSprite
{
public:
    ZSprite();
    ~ZSprite();

    void Init();

    void Render(ZShader& shader, ZTransform& transform);

private:
    ZArrayObject z_ArrayObject;
};

