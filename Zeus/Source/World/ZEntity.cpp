#include "Core/CoreLibrary.h"
#include "ZEntity.h"

ZEntity::ZEntity(entt::entity entity, ZLevel& level) : z_Handle(entity), z_Level(&level)
{
}

void ZEntity::Destroy()
{
	z_DestroyHandle = 500;
}
