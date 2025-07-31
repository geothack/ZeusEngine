#include "Core/CoreLibrary.h"
#include "Output.h"

Output& Output::Get()
{
	if (!z_Output)
	{
		z_Output = new Output();
	}

	return *z_Output;
}

void Output::Load(std::string_view name, const std::filesystem::path& filePath)
{
	z_Sound2D.Load(name, filePath);
}

void Output::Play(std::string_view name)
{
	z_Sound2D.Play(name);
}

void Output::Stop(std::string_view name)
{
	z_Sound2D.Stop(name);
}

void Output::Free()
{
	z_Sound2D.Free();
	delete z_Output;
}
