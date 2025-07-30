#include "Core/CoreLibrary.h"
#include "ZTransform.h"

ZTransform::ZTransform(Vec3 position, Vec3 rotation, Vec3 scale) : z_Position(position), z_Rotation(rotation), z_Scale(scale)
{
}

ZTransform::ZTransform(const ZTransform& transform) : z_Position(transform.z_Position), z_Rotation(transform.z_Rotation), z_Scale(transform.z_Scale)
{
	
}

ZTransform::~ZTransform()
{
}
