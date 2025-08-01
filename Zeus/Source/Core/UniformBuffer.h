#pragma once

struct CameraData
{
    alignas(16) Mat4 View;
    alignas(16) Mat4 Projection;
};

class UniformBuffer
{
public:
    static UniformBuffer& Get();

    void Create(std::string_view handle, size_t size, GLuint bindingPoint);
    void Update(std::string_view handle, size_t offset, const void* data, size_t dataSize);
    void Attach(std::string_view handle, GLuint shaderID, std::string_view uboName);

    void Free(); 

private:
    UniformBuffer() = default;
    ~UniformBuffer() = default;
    UniformBuffer(const UniformBuffer&) = delete;
    UniformBuffer& operator=(const UniformBuffer&) = delete;

    struct Data
    {
        GLuint bufferID;
        size_t bufferSize;
        GLuint bindingPoint;
    };

    std::unordered_map<std::string, Data> z_UniformCache{};

    inline static UniformBuffer* z_UniformBuffer = nullptr;
};
