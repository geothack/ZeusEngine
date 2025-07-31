#pragma once


class Log
{
public:
	static Log& Get();

	template<typename T>
	void Info(T var)
	{
		std::println("Info | {}", var);
	}

	template<typename T>
	void Debug(T var)
	{
		std::println("Debug | {}", var);
	}

	template<typename T>
	void Warning(T var)
	{
		std::println("Warning | {}", var);
	}

	template<typename T>
	void Error(T var)
	{
		std::println("Error | {}", var);
	}

	void Free();

private:
	inline static Log* z_Log = nullptr;
};

