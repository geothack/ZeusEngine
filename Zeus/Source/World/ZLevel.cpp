#include "Core/CoreLibrary.h"
#include "ZLevel.h"
#include "World/ZEntity.h"

ZEntity ZLevel::CreateEntity(const ZTransform& transform)
{
	auto entity = ZEntity(z_Registry.create(), *this);
	entity.AddComponent<ZTransform>(transform);
	return entity;
}

ZEntity ZLevel::Create3DMeshEntity(const ZTransform& transform, const ZModel& model, const ZShader& shader)
{
	auto entity = ZEntity(z_Registry.create(), *this);
	entity.AddComponent<ZTransform>(transform);
	entity.AddComponent<ZModel>(model);
	entity.AddComponent<ZShader>(shader);
	return entity;
}

ZEntity ZLevel::CreateUiTextEntity(const ZTransform& transform, const ZText& text, const ZShader& shader)
{
	auto entity = ZEntity(z_Registry.create(), *this);
	entity.AddComponent<ZTransform>(transform);
	entity.AddComponent<ZText>(text);
	entity.AddComponent<ZShader>(shader);
	return entity;
}

ZEntity ZLevel::CreateUiSpriteEntity(const ZTransform& transform, const ZSprite& sprite, const ZShader& shader)
{
	auto entity = ZEntity(z_Registry.create(), *this);
	entity.AddComponent<ZTransform>(transform);
	entity.AddComponent<ZSprite>(sprite);
	entity.AddComponent<ZShader>(shader);
	return entity;
}
