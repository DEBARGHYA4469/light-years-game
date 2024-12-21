#include "framework/MathUtil.h"
#include "math.h"

const float PI = std::acos(-1.0);

sf::Vector2f ly::RotationToVector(float rotation)
{
	float radians = DegreeToRadians(rotation);
	return sf::Vector2f(std::cos(radians), std::sin(radians));
}

// PI radians = 180 degrees
float ly::DegreeToRadians(float degrees)
{
	return degrees * PI / 180.f;
}

float ly::RadiansToDegrees(float radians)
{
	return radians * 180.f / PI;
}
