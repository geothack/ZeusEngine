#pragma once

#include "Output/Sound2D.h"

class Output
{
public:
	static Output& Get();

	void Load(std::string_view name, const std::filesystem::path& filePath);
	void Play(std::string_view name);
	void Stop(std::string_view name);

	void Free();

private:
	inline static Output* z_Output = nullptr;

	ZSound2D z_Sound2D{};
};

