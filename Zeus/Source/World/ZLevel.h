#pragma once

#include "Render/ZShader.h"
#include "Render/ZSprite.h"
#include "Render/ZText.h"
#include "World/ZModel.h"
#include "World/ZTransform.h"

class ZEntity;

class ZLevel
{
public:
	ZLevel() = default;

	ZEntity CreateEntity(const ZTransform& transform);

	ZEntity Create3DMeshEntity(const ZTransform& transform, const ZModel& model, const ZShader& shader);

	template<class T>
	ZEntity Create3DMeshEntity(const ZTransform& transform, T& model, const ZShader& shader)
	{
		auto* baseModel = static_cast<ZModel&>(model);
		Create3DMeshEntity(transform, &baseModel, shader);
	}

	ZEntity CreateUiTextEntity(const ZTransform& transform, const ZText& text, const ZShader& shader);
	ZEntity CreateUiSpriteEntity(const ZTransform& transform, const ZSprite& sprite, const ZShader& shader);

	entt::registry& GetRegister() { return z_Registry; }

private:
	entt::registry z_Registry;

	friend class ZEntity;
};

