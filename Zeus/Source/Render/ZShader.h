#pragma once

#include "Render/ZCamera.h"
#include "Render/ZTexture.h"

struct Color
{
    double Red;
    double Green;
    double Blue;
};

class ZShader
{
public:
    ZShader() = default;

    ZShader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragShaderPath, const Color& color = {-1,-1,-1}, const std::filesystem::path& geoShaderPath = "", const std::vector<ZTexture>& textures = {}, bool setSky = false);

    void MakeShader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragShaderPath, const std::filesystem::path& geoShaderPath = "");

    void Attach() const;

    void BindLighting(ZCamera& activeCamera) const;

public:
    void SetVec3(std::string_view name, Vec3 value) const;

    void SetMat4(std::string_view name, const Mat4& value) const;

    void SetInt(std::string_view name, int value) const;

    void SetFloat(std::string_view name, float value) const;

    bool SetSky = false;

public:
    inline uint32_t GetHandle() const { return z_Program; }

    std::vector<ZTexture>& GetTextures() { return z_Textures; }

private:
    void Create(uint32_t& shader, const char* path, uint32_t type);

    void LinkShader();

private:
    uint32_t z_Program{};
    uint32_t z_Vertex{};
    uint32_t z_Fragment{};
    uint32_t z_Geometry{};

    int z_Success{};
    char z_InfoLog[512]{};

    std::unordered_map<std::string, uint32_t> z_UniformCache{};

    std::vector<ZTexture> z_Textures{};

    Color z_Color{};
};


class ZTessellationShader
{
public:
    ZTessellationShader() = default;

    ZTessellationShader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragShaderPath, const std::filesystem::path& tscShaderPath, const std::filesystem::path& tesShaderPath);

    void MakeShader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragShaderPath, const std::filesystem::path& tscShaderPath, const std::filesystem::path& tesShaderPath);

    void Attach() const;

public:
    void SetVec3(std::string_view name, Vec3 value) const;

    void SetMat4(std::string_view name, const Mat4& value) const;

    void SetInt(std::string_view name, int value) const;

    void SetFloat(std::string_view name, float value) const;

public:
    inline uint32_t GetHandle() const { return z_Program; }


private:
    void Create(uint32_t& shader, const char* path, uint32_t type);

    void LinkShader();

private:
    uint32_t z_Program{};
    uint32_t z_Vertex{};
    uint32_t z_Fragment{};
    uint32_t z_TessellationControl{};
    uint32_t z_TesselationEvaluation{};

    int z_Success{};
    char z_InfoLog[512]{};

    std::unordered_map<std::string, uint32_t> z_UniformCache{};
};