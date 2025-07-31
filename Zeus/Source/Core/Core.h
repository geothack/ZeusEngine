#pragma once

using Mat4 = glm::mat4; // 64 bytes must be passed by reference
using Mat3 = glm::mat3; // 36 bytes must be passed by reference
using Vec4 = glm::vec4; // 16 bytes can be passed by value
using Vec3 = glm::vec3; // 12 bytes can be passed by value
using Vec2 = glm::vec2; // 8 bytes can be passed by value

#define ZInput Input::Get()
#define ZLog Log::Get()
#define ZTime Time::Get()
#define ZOutput Output::Get()
#define ZRuntime RuntimeCache::Get()
#define ZRuntime RuntimeCache::Get()
#define ZBoxes Box::Get()