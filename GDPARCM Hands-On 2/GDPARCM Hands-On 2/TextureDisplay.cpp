#include "TextureDisplay.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "IconObject.h"
#include "IETThread.h"

TextureDisplay::TextureDisplay(): AGameObject("TextureDisplay")
{
	
}

void TextureDisplay::initialize()
{

}

void TextureDisplay::processInput(sf::Event event)
{
	
}

void TextureDisplay::update(sf::Time deltaTime)
{
	this->ticks += deltaTime.asMicroseconds() * 0.001f;

	if (streamingType == StreamingType::BATCH_LOAD && !this->startedStreaming && this->ticks > this->STREAMING_LOAD_DELAY && this->numIconsLoaded < this->MAX_ICONS) {
		this->startedStreaming = true;
		this->ticks = 0.0f;
		TextureManager::getInstance()->loadStreamingAssets();
	}
	else if (streamingType == StreamingType::SINGLE_STREAM && this->ticks > this->STREAMING_LOAD_DELAY && this->currentIconIndex < this->MAX_ICONS) {
		this->ticks = 0.0f;
		TextureManager::getInstance()->loadSingleStreamAsset(this->currentIconIndex++, this);
	}
}

void TextureDisplay::onFinishedExecution() {
	this->spawnObject();
	this->numIconsLoaded++;
}

void TextureDisplay::spawnObject()
{
	if (this->iconList.size() >= TextureManager::getInstance()->getStreamingAssetsCount())
		return;

	String objectName = "Icon_" + to_string(this->iconList.size());

	//TextureManager::getInstance()->loadSingleStreamAsset(this->iconList.size());
	IconObject* iconObj = new IconObject(objectName, this->iconList.size());
	this->iconList.push_back(iconObj);

	//set position
	int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
	float x = this->columnGrid * IMG_WIDTH;
	float y = this->rowGrid * IMG_HEIGHT;
	iconObj->setPosition(x, y);

	std::cout << "Set position: " << x << " " << y << std::endl;

	this->columnGrid++;
	if(this->columnGrid == this->MAX_COLUMN)
	{
		this->columnGrid = 0;
		this->rowGrid++;
	}

	GameObjectManager::getInstance()->addObject(iconObj);
}
