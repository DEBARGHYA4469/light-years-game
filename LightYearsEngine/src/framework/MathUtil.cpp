#include "framework/MathUtil.h"
#include "math.h"
#include <random>
#include <cassert>

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

sf::Color ly::LerpColor(const sf::Color& a, const sf::Color& b, float alpha)
{
	int LerpR = LerpFloat(a.r, b.r, alpha);
	int LerpG = LerpFloat(a.g, b.g, alpha);
	int LerpB = LerpFloat(a.b, b.b, alpha);
	int LerpA = LerpFloat(a.a, b.a, alpha);
	return sf::Color(LerpR, LerpG, LerpB, LerpA);

}

float ly::LerpFloat(float a, float b, float alpha)
{
	//assert(a <= b);
	if (alpha > 1) alpha = 1;
	if (alpha < 0) alpha = 0;
	return a + (b - a) * alpha;
}

sf::Vector2f ly::LerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float alpha)
{
	float lerpX = LerpFloat(a.x, b.x, alpha);
	float lerpY = LerpFloat(a.y, b.y, alpha);
	return sf::Vector2f(lerpX, lerpY);
}

float ly::RandomRange(float min, float max)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(gen);
}

sf::Vector2f ly::RandomUnitVector()
{
	float Rx = RandomRange(-1, 1);
	float Ry = RandomRange(-1, 1);
	sf::Vector2f randVec {Rx, Ry };
	Normalize(randVec);
	return randVec;
}
