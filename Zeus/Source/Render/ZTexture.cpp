#include "Core/CoreLibrary.h"
#include "ZTexture.h"
#include "Core/Error.h"

ZTexture::ZTexture(std::string_view samplerName, const std::filesystem::path& path, bool flip) : z_SamplerName(samplerName.data()), z_Path(path)
{
	glGenTextures(1, &z_Handle);
	Load(path, flip);
}

ZTexture::ZTexture(const std::filesystem::path& directory, const std::filesystem::path& path, aiTextureType type) : z_Dir(directory), z_Path(path), z_Type(type)
{
	glGenTextures(1, &z_Handle);
	Load((z_Dir.string() + "/" + path.string()).c_str());
}

void ZTexture::Attach() const
{
	glBindTexture(GL_TEXTURE_2D, z_Handle);
}

void ZTexture::Load(const std::filesystem::path& path, bool flip)
{
    stbi_set_flip_vertically_on_load(flip);

    auto pathString = path.string();
    unsigned char* data = stbi_load(pathString.c_str(), &z_Width, &z_Height, &z_Channels, 0);
    if (data)
    {
        uint32_t format;
        if (z_Channels == 1)
        {
            format = GL_RED;
        }
        else if (z_Channels == 3)
        {
            format = GL_RGB;
        }
        else if (z_Channels == 4)
        {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, z_Handle);
        glTexImage2D(GL_TEXTURE_2D, 0, format, z_Width, z_Height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::string string = std::format("Failed to load texture at {}", pathString);
        Error error(string);
        stbi_image_free(data);
    }
}
