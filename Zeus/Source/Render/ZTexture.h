#pragma once


class ZTexture
{
public:
	ZTexture() = default;
	ZTexture(std::string_view samplerName, const std::filesystem::path& path, bool flip = false);
	ZTexture(const std::filesystem::path& directory, const std::filesystem::path& path, aiTextureType type);

	void Attach() const;

	void Load(const std::filesystem::path& path, bool flip = false);

	uint32_t GetHandle() const { return z_Handle; }

	std::string& GetName() { return z_SamplerName; }

	std::filesystem::path& GetPath() { return z_Path; }
	std::filesystem::path& GetDirectory() { return z_Dir; }

	aiTextureType GetType() { return z_Type; }

private:
	aiTextureType z_Type;

	std::filesystem::path z_Path;
	std::filesystem::path z_Dir;

private:
	uint32_t z_Handle = 0;

	std::string z_SamplerName = "";

	int z_Width;
	int z_Height;
	int z_Channels;
};

