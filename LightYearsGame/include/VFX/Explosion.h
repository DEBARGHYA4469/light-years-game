#pragma once 
#include "SFML/Graphics.hpp"
#include "framework/Core.h"
#include "string"

namespace ly {
	class World;
	class Explosion {
	public:
		Explosion(int mParticleAmt = 20,
			float mDuration = 5.f,
			float mLifeTimeMin = 0.5f,
			float mLifeTimeMax = 1.5f,
			float mSizeMin = 1,
			float mSizeMax = 3,
			float mSpeedMin = 200,
			float mSpeedMax = 400,
			const List<std::string> mParticleImgPath = {
				"SpaceShooterRedux/PNG/Effects/star1.png",
				"SpaceShooterRedux/PNG/Effects/star2.png",
				"SpaceShooterRedux/PNG/Effects/star3.png"
			},
			const sf::Color& mParticleColor = sf::Color(255, 128, 0, 255)
		);

		void SpawnExplosion(World* world, const sf::Vector2f& actorLocation);
	private:
		int mParticleAmt;
		float mDuration;
		float mLifeTimeMin, mLifeTimeMax;
		float mSizeMin, mSizeMax;
		float mSpeedMin, mSpeedMax;
		List<std::string> mParticleImgPath;
		sf::Color mParticleColor;
	};
};