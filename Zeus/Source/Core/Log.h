#pragma once


class Log
{
public:

	template<typename T>
	static void Info(T var)
	{
		std::println("Info | {}", var);
	}

	template<typename T>
	static void Debug(T var)
	{
		std::println("Debug | {}", var);
	}

	template<typename T>
	static void Warning(T var)
	{
		std::println("Warning | {}", var);
	}

	template<typename T>
	static void Error(T var)
	{
		std::println("Error | {}", var);
	}
};

