#include "BaseRunner.h"
#include  "GameObjectManager.h"
#include "BGObject.h"
#include "TextureManager.h"
#include "TextureDisplay.h"
#include "FPSCounter.h"

/// <summary>
/// This demonstrates a running parallax background where after X seconds, a batch of assets will be streamed and loaded.
/// </summary>
const float FRAME_RATE = 60.0f;
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / FRAME_RATE);
BaseRunner* BaseRunner::sharedInstance = NULL;

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "HO: Entity Component", sf::Style::Close) {	
	sharedInstance = this;
	
	//load initial textures
	TextureManager::getInstance()->loadFromAssetList();

	//load objects
	BGObject* bgObject = new BGObject("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);
}

void BaseRunner::run() {
	sf::Clock clock;
	
	while (this->window.isOpen())
	{
		// Stays in loop until elapsed time reaches fixed time step
		while (clock.getElapsedTime() < TIME_PER_FRAME);

		sf::Time elapsedTime = clock.restart();

		processEvents();
		update(elapsedTime);
		render();
	}
}

BaseRunner* BaseRunner::getInstance()
{
	return sharedInstance;
}

float BaseRunner::getFPS()
{
	return this->fps;
}

void BaseRunner::processEvents()
{
	sf::Event event;
	if (this->window.pollEvent(event)) {
		switch (event.type) {
		
		default: GameObjectManager::getInstance()->processInput(event); break;
		case sf::Event::Closed:
			this->window.close();
			break;

		}
	}
}

void BaseRunner::update(sf::Time elapsedTime) {
	GameObjectManager::getInstance()->update(elapsedTime);
}

void BaseRunner::render() {
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}