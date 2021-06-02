#pragma once
#include "IconObject.h"
class Indicator : public IconObject
{
public:
	Indicator(String name, int index);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

	void setAssignedIndex(int index);
	int getAssignedIndex();

private:
	int assignedIndex = 0;
};
