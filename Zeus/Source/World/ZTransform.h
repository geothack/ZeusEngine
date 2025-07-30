#pragma once


class ZTransform
{
public:
	ZTransform(Vec3 position = Vec3(0.0), Vec3 rotation = Vec3(0.0), Vec3 scale = Vec3(1.0));
	ZTransform(const ZTransform& transform);
	~ZTransform();


public:
	glm::vec3& GetPosition() { return z_Position; }
	glm::vec3& GetRotation() { return z_Rotation; }
	glm::vec3& GetScale() { return z_Scale; }

	void SetPosition(const glm::vec3& position) { z_Position = position; }
	void SetRotation(const glm::vec3& rotation) { z_Rotation = rotation; }
	void SetScale(const glm::vec3& scale) { z_Scale = scale; }

private:
	glm::vec3 z_Position;
	glm::vec3 z_Rotation;
	glm::vec3 z_Scale;
};

