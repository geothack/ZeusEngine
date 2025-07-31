#pragma once

template<class ... T>
class ResourceCache
{
public:
	static ResourceCache& Get()
	{
		if (!z_Cache)
		{
			z_Cache = new ZResourceCache();
		}

		return *z_Cache;
	}


	template<class U, class ... Args>
	U& Add(const std::string& handle, Args && ... args)
	{
		auto& map = std::get<std::unordered_map<std::string, U>>(z_ResourceCache);

		if (map.contains(handle))
		{
			throw new std::runtime_error("Resource pool already contains resource called " + handle);
		}

		const auto [iter, inserted] = map.emplace(std::make_pair(handle, U{ std::forward<Args>(args) ... }));

		return iter->second;
	}


	template<class U>
	U& Fetch(const std::string& handle)
	{
		auto& map = std::get<std::unordered_map<std::string, U>>(z_ResourceCache);

		if (!map.contains(handle))
		{
			throw new std::runtime_error("Resource pool does not contain resource called " + handle);
		}

		const auto object = map.find(handle);

		return object->second;
	}

	template<class U>
	void Free(const std::string& handle)
	{
		auto& map = std::get<std::unordered_map<std::string, U>>(z_ResourceCache);

		if (!map.contains(handle))
		{
			throw new std::runtime_error("Resource pool does not contain resource called " + handle);
		}

		map.erase(handle);

	}

	template<class U>
	std::unordered_map<std::string, U>& FetchCache()
	{
		auto& map = std::get<std::unordered_map<std::string, U>>(z_ResourceCache);
		return map;
	}

	void Free()
	{
		std::apply([](auto&... map) {(map.clear(), ...); }, z_ResourceCache);
		delete z_Cache;
	}


private:
	std::tuple<std::unordered_map<std::string, T> ... > z_ResourceCache;

	inline static ZResourceCache* z_Cache = nullptr;
};