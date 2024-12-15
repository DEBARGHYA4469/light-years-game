#pragma once 
#include "string"

std::string GetResourceDir() {
#ifdef NDEBUG // DEBUG MODE
	return "C:/Users/kdeb4/source/repos/LightYears/LightYearsGame/assets/";
#else // RELEASE MODE
	return "assets/";
#endif // NDEBUG
}
