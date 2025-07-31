#pragma once

#include "Render/ZShader.h"
#include "Render/ZSprite.h"
#include "Render/ZText.h"
#include "World/ZTransform.h"

class ZEntity;

class ZLevel
{
public:
	ZLevel() = default;

	ZEntity CreateEntity(const ZTransform& transform);
	ZEntity CreateUiTextEntity(const ZTransform& transform, const ZText& text, const ZShader& shader);
	ZEntity CreateUiSpriteEntity(const ZTransform& transform, const ZSprite& sprite, const ZShader& shader);

	entt::registry& GetRegister() { return z_Registry; }

private:
	entt::registry z_Registry;

	friend class ZEntity;
};

