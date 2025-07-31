#pragma once

#include "Core/Error.h"
#include "World/ZLevel.h"
#include "World/ZTransform.h"

class ZEntity
{
public:
	ZEntity() = default;

	ZEntity(const ZEntity& other) = default;

	ZEntity(entt::entity entity, ZLevel& level);

	virtual ~ZEntity() {};

	virtual void Start() {};

	virtual void FixedUpdate() {};

	virtual void Update() {};

	bool HasStartedPlay = false;

	void Destroy();

	template<typename T>
	bool HasComponent()
	{
		return z_Level->GetRegister().any_of<T>(z_Handle);
	}

	template<typename T, typename ... Args>
	T& AddComponent(Args&& ... args)
	{
		if (HasComponent<T>())
		{
			Error error{ "Entity already has component" };
		}
		return z_Level->GetRegister().emplace<T>(z_Handle, std::forward<Args>(args)...);
	}

	template<typename T>
	T& GetComponent()
	{
		if (!HasComponent<T>())
		{
			Error error{ "Entity does not have component" };
		}

		return z_Level->GetRegister().get<T>(z_Handle);
	}

	template<typename T>
	void RemoveComponent()
	{
		if (!HasComponent<T>())
		{
			Error error{ "Entity does not have component" };
		}

		z_Level->GetRegister().erase<T>(z_Handle);
	}

	template<typename T, typename ... Args>
	void UpdateComponent(Args&& ... args)
	{
		if (!HasComponent<T>())
		{
			Error error{ "Entity does not have component" };
		}

		z_Level->GetRegister().replace<T>(z_Handle, std::forward<Args>(args)...);
	}

	ZTransform& GetZTransform()
	{
		if (!HasComponent<ZTransform>())
		{
			Error error{ "Entity does not have ZTransform component" };
		}

		return GetComponent<ZTransform>();
	}

	void SetZTransform(ZTransform& transform)
	{
		if (!HasComponent<ZTransform>())
		{
			Error error{ "Entity does not have ZTransform component" };
		}

		UpdateComponent<ZTransform>(transform);
	}

	Vec3 GetPosition()
	{
		if (!HasComponent<ZTransform>())
		{
			Error error{ "Entity does not have ZTransform component" };
		}

		return GetComponent<ZTransform>().GetPosition();
	}

	void SetPosition(Vec3 position)
	{
		if (!HasComponent<ZTransform>())
		{
			Error error{ "Entity does not have ZTransform component" };
		}

		GetComponent<ZTransform>().SetPosition(position);
	}

	Vec3 GetRotation()
	{
		if (!HasComponent<ZTransform>())
		{
			Error error{ "Entity does not have ZTransform component" };
		}

		return GetComponent<ZTransform>().GetRotation();
	}

	void SetRotation(Vec3 rotation)
	{
		if (!HasComponent<ZTransform>())
		{
			Error error{ "Entity does not have ZTransform component" };
		}

		GetComponent<ZTransform>().SetPosition(rotation);
	}

	Vec3 GetScale()
	{
		if (!HasComponent<ZTransform>())
		{
			Error error{ "Entity does not have ZTransform component" };
		}

		return GetComponent<ZTransform>().GetScale();
	}

	void SetScale(Vec3 scale)
	{
		if (!HasComponent<ZTransform>())
		{
			Error error{ "Entity does not have ZTransform component" };
		}

		GetComponent<ZTransform>().SetScale(scale);
	}

	int GetHandle() const { return z_DestroyHandle; }

private:
	entt::entity z_Handle;

	ZLevel* z_Level;

	int z_DestroyHandle = 0;
};