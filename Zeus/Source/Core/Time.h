#pragma once


class Time
{
public:
	static Time& Get();

	double DeltaTime{};

	void Free();

private:
	inline static Time* z_Time = nullptr;
};

