#pragma once


#include "World/ZEntity.h"

class RuntimeCache
{
public:
	static RuntimeCache& Get()
	{
		if (!z_RuntimeCache)
		{
			z_RuntimeCache = new RuntimeCache();
		}

		return *z_RuntimeCache;
	}

	template<class T>
	void Add(T& object)
	{
		auto* entity = static_cast<Entity&>(object);
		z_EntityCache.emplace_back(entity);
	}

	void Add(ZEntity& entity)
	{
		z_EntityCache.emplace_back(&entity);
	}

	void FixedUpdate()
	{
		for (auto* entity : z_EntityCache)
		{
			if (entity)
			{
				entity->FixedUpdate();
			}
		}
	}

	void Update()
	{
		for (auto* entity : z_EntityCache)
		{
			if (!entity->HasStartedPlay)
			{
				entity->Start();
				entity->HasStartedPlay = true;
			}
			if (entity)
			{
				entity->Update();
			}
		}
	}

	void Free(const int handle)
	{
		for (auto it = z_EntityCache.begin(); it != z_EntityCache.end(); )
		{
			if ((*it)->GetHandle() == 500)
			{
				it = z_EntityCache.erase(it);
				//delete* it;
			}
			else
			{
				it++;
			}
		}
	}

	void Free()
	{
		z_EntityCache.clear();
		delete z_RuntimeCache;
	}

private:
	std::vector<ZEntity*> z_EntityCache;

	inline static RuntimeCache* z_RuntimeCache = nullptr;
};

