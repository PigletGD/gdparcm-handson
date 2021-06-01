#include "FPSCounter.h"
#include <iostream>
#include "BaseRunner.h"

FPSCounter::FPSCounter(): AGameObject("FPSCounter")
{
}

FPSCounter::~FPSCounter()
{
	delete this->statsText->getFont();
	delete this->statsText;
	AGameObject::~AGameObject();
}

void FPSCounter::initialize()
{
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Sansation.ttf");

	this->statsText = new sf::Text();
	this->statsText->setFont(*font);
	this->statsText->setPosition(BaseRunner::WINDOW_WIDTH - 150, BaseRunner::WINDOW_HEIGHT - 70);
	this->statsText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->statsText->setOutlineThickness(2.5f);
	this->statsText->setCharacterSize(35);

	this->updateTime = sf::Time::Zero;
	this->framesPassed = 0;
	this->statsText->setString("FPS: --");
}

void FPSCounter::processInput(sf::Event event)
{
}

void FPSCounter::update(sf::Time deltaTime)
{
	this->updateFPS(deltaTime);
}

void FPSCounter::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if(this->statsText != nullptr)
		targetWindow->draw(*this->statsText);
}

void FPSCounter::updateFPS(sf::Time elapsedTime)
{
	updateTime += elapsedTime;
	this->executionCount += 1;

	// Displays frames counted based on specified fps display delay
	if (updateTime.asSeconds() >= FPS_DISPLAY_DELAY) {
		// Gets FPS by dividing 1 by the average elapsed time based on function execution count
		int fps = 1 / (this->updateTime.asSeconds() / this->executionCount);
		this->statsText->setString("FPS: " + std::to_string(fps));
		this->updateTime = sf::Time(sf::seconds(0));
		this->executionCount = 0;
	}
}
