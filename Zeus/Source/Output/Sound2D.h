#pragma once


class ZSound2D
{
public:
    ZSound2D();
    ~ZSound2D();

    void Init();
    void Load(std::string_view name, const std::filesystem::path& filePath);
    void Play(std::string_view name);
    void Stop(std::string_view name);
    void Free();

private:
    struct SoundData
    {
        ALuint Buffer;
        ALuint Source;
    };

    std::map<std::string, SoundData> z_SoundMap;

    void CheckOpenALError(std::string_view message);

    ALCdevice* z_Device;
    ALCcontext* z_Context;
};

