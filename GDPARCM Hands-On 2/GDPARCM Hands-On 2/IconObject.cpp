#include "IconObject.h"
#include <iostream>
#include "BaseRunner.h"
#include "TextureManager.h"

IconObject::IconObject(String name, int index = 0): AGameObject(name)
{
	textureIndex = index;

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::TextureManager::getInstance()->getFromTextureMap(name, 0);
	this->sprite->setTexture(*texture);
}

void IconObject::initialize()
{
	
}

void IconObject::processInput(sf::Event event)
{
}

void IconObject::update(sf::Time deltaTime)
{
}

void IconObject::setColor(sf::Color color) {
	this->sprite->setColor(color);
}