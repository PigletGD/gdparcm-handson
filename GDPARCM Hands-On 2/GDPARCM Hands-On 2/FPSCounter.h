#pragma once
#include "AGameObject.h"
class FPSCounter :    public AGameObject
{
	public:
		FPSCounter();
		~FPSCounter();
		void initialize() override;
		void processInput(sf::Event event) override;
		void update(sf::Time deltaTime) override;
		void draw(sf::RenderWindow* targetWindow) override;
	
	private:
		sf::Clock updateClock;
		sf::Time updateTime;
		sf::Text* statsText;
		int executionCount = 0;
		int framesPassed = 0;
		const float FPS_DISPLAY_DELAY = 1.0f;

		void updateFPS(sf::Time elapsedTime);
		
};

