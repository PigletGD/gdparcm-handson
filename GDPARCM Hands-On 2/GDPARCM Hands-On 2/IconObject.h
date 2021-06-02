#pragma once
#include "AGameObject.h"
class IconObject :    public AGameObject
{
public:
	IconObject(String name, int index);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

	void setColor(sf::Color color);

private:
	int textureIndex = 0;
};

