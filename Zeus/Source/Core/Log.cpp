#include "Core/CoreLibrary.h"
#include "Log.h"

Log& Log::Get()
{
	if (!z_Log)
	{
		z_Log = new Log();
	}

	return *z_Log;
}

void Log::Free()
{
	delete z_Log;
}
