#pragma once
// Third Party Libraries
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <entt/entt.hpp>

#include <freetype/freetype.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <sndfile.h>

#include <box2d/box2d.h>

// Standard Libraries
#include <string_view>
#include <print>
#include <format>
#include <stacktrace>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <memory>
#include <unordered_map>
#include <map>
#include <vector>

// Created Classes
#include "Core/Log.h"
#include "Core/Core.h"
#include "stb_image.h"
#include "Input/Input.h"
#include "Core/Time.h"
#include "Output/Output.h"
#include "World/ZEntity.h"
#include "Core/RuntimeCache.h"
#include "Core/ResourceCache.h"

