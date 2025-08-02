#pragma once
#include "Core/CoreLibrary.h"
#include "Core/Error.h"
#include "World/ZLevel.h"

class LevelCache
{
public:
	LevelCache() = default;

	void Add(std::string_view handle, ZLevel* level)
	{
		if (z_LevelCache.find(handle.data()) != z_LevelCache.end())
		{
			Error error("ZLevel already exists");
		}

		z_LevelCache[handle.data()] = { level };
	}

	ZLevel& Fetch(std::string_view handle)
	{
		if (z_LevelCache.find(handle.data()) == z_LevelCache.end())
		{
			Error error("ZLevel not found");
		}

		return *z_LevelCache[handle.data()];
	}

	void Free(std::string_view handle)
	{
		if (z_LevelCache.find(handle.data()) == z_LevelCache.end())
		{
			Error error("ZLevel not found");
		}

		z_LevelCache.erase(handle.data());
	}

	void Free()
	{
		z_LevelCache.clear();
	}

private:
	std::unordered_map<std::string, ZLevel*> z_LevelCache{};

};