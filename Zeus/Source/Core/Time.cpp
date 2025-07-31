#include "Core/CoreLibrary.h"
#include "Time.h"

Time& Time::Get()
{
	if (!z_Time)
	{
		z_Time = new Time();
	}

	return *z_Time;
}

void Time::Free()
{
	delete z_Time;
}
