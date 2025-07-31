#include "Core/CoreLibrary.h"
#include "Sound2D.h"
#include "Core/Error.h"

ZSound2D::ZSound2D()
{
    Init();
}

ZSound2D::~ZSound2D()
{

}

void ZSound2D::Init()
{
    z_Device = alcOpenDevice(nullptr);
    if (!z_Device)
    {
        Error error("Failed to open OpenAL device");
    }

    z_Context = alcCreateContext(z_Device, nullptr);
    if (!z_Context || !alcMakeContextCurrent(z_Context))
    {
        Error error("Failed to create or set OpenAL context");
    }
}

void ZSound2D::Load(std::string_view name, const std::filesystem::path& filePath)
{
    auto path = filePath.string();

    SF_INFO sfInfo;
    SNDFILE* sndFile = sf_open(path.c_str(), SFM_READ, &sfInfo);
    if (!sndFile)
    {
        Error error("Failed to load sound file: " + path);
    }

    ALenum format;
    if (sfInfo.channels == 1)
    {
        format = AL_FORMAT_MONO16;
    }
    else if (sfInfo.channels == 2)
    {
        format = AL_FORMAT_STEREO16;
    }
    else
    {
        ZLog.Error("Unsupported channel count");
        sf_close(sndFile);
        Error error("Failed to indentify file format");
    }


    // Read audio data
    std::vector<short> samples(sfInfo.frames * sfInfo.channels);
    sf_count_t numFrames = sf_readf_short(sndFile, samples.data(), sfInfo.frames);
    sf_close(sndFile);

    if (numFrames < 1)
    {
        Error error("Failed to read audio data from file| " + path);
    }

    // Create OpenAL buffer and source
    ALuint buffer;
    ALuint source;
    alGenBuffers(1, &buffer);
    CheckOpenALError("Failed to generate OpenAL buffer");
    alBufferData(buffer, format, samples.data(), samples.size() * sizeof(short), sfInfo.samplerate);
    CheckOpenALError("Failed to buffer audio data");

    alGenSources(1, &source);
    CheckOpenALError("Failed to generate OpenAL source");
    alSourcei(source, AL_BUFFER, buffer);

    // Store in map
    z_SoundMap[name.data()] = { buffer, source };
}

void ZSound2D::Play(std::string_view name)
{
    auto it = z_SoundMap.find(name.data());
    auto string = static_cast<std::string>(name);
    if (it == z_SoundMap.end())
    {
        Error error("Sound not found| " + string);
    }
    alSourcePlay(it->second.Source);
    CheckOpenALError("Failed to play sound");
}

void ZSound2D::Stop(std::string_view name)
{
    auto it = z_SoundMap.find(name.data());
    auto string = static_cast<std::string>(name);
    if (it == z_SoundMap.end())
    {
        Error error("Sound not found| " + string);
    }
    alSourceStop(it->second.Source);
    CheckOpenALError("Failed to stop sound");
}

void ZSound2D::Free()
{
    for (auto& pair : z_SoundMap)
    {
        alDeleteSources(1, &pair.second.Source);
        alDeleteBuffers(1, &pair.second.Buffer);
    }
    if (z_Context)
    {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(z_Context);
    }
    if (z_Device)
    {
        alcCloseDevice(z_Device);
    }
}

void ZSound2D::CheckOpenALError(std::string_view message)
{
    ALenum alError = alGetError();
    auto string = static_cast<std::string>(message);

    if (alError != AL_NO_ERROR)
    {
        Error error(string + " (OpenAL error: " + std::to_string(alError) + ")");
    }
}
