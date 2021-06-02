#include "Indicator.h"

Indicator::Indicator(String name, int index) : IconObject(name, index) {
	assignedIndex = -1;
}

void Indicator::initialize() {

}

void Indicator::processInput(sf::Event event) {

}

void Indicator::update(sf::Time deltaTime) {

}

void Indicator::setAssignedIndex(int index) {
	assignedIndex = index;
}

int Indicator::getAssignedIndex() {
	return assignedIndex;
}