#pragma once

#include "Core/CoreLibrary.h"

class Error
{
public:
	Error(std::string_view message)
	{
		std::println("{}",message);
		throw std::runtime_error(std::format("{}", std::stacktrace::current()));
	}
};