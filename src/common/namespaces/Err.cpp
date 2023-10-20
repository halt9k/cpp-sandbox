#pragma once
#include "Err.h"

#include <iostream>

void Log::Warning(std::string msg)
	{
	std::cout << "WARNING: " << msg << std::endl;
	}
