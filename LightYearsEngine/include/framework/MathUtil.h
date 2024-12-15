#pragma once 
#include "SFML/Graphics.hpp"
#include <math.h>
#include "framework/Core.h"

namespace ly {
	sf::Vector2f RotationToVector(float rotation);
	float DegreeToRadians(float degrees);
	float RadiansToDegrees(float radians);

	template <typename T> 
	float GetVectorLength(sf::Vector2<T>& vec) {
		return std::sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	template <typename T>
	sf::Vector2<T>& ScaleVector(sf::Vector2<T>& vectorToScale, float amt) {
		vectorToScale.x *= amt;
		vectorToScale.y *= amt;
		return vectorToScale;
	}

	template <typename T>
	sf::Vector2<T>& Normalize(sf::Vector2<T>& vector) {
		float VectorLength = GetVectorLength<T>(vector);
		if(VectorLength == 0.f) return sf::Vector2<T>{};
		ScaleVector(vector, 1.f / VectorLength);
		return vector;
	}
};