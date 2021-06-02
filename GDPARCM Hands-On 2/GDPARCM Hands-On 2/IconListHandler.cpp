#include "IconListHandler.h"

#include "GameObjectManager.h"
#include "TextureManager.h"

#include "SearcherThread.h"
#include "InserterThread.h"
#include "DeleterThread.h"

IconListHandler::IconListHandler() : AGameObject("Icon List Handler") {
	spawnThreads();
	spawnIconObjectsToDisplay();
}

void IconListHandler::initialize() {

}

void IconListHandler::processInput(sf::Event event) {

}

void IconListHandler::update(sf::Time deltaTime) {

}

void IconListHandler::spawnThreads() {
	for (int i = 0; i < numSearchers; i++) {
		searchers.push_back(new SearcherThread(&searcherCount, &searcherMEMutex,
			&deleterMEMutex, &deleterBufSem, &roomEmpty));

		searchers[i]->start();

		searcherIndicators.push_back(new IconObject("indicator", 0));
		searcherIndicators[i]->setPosition(200, 400);
		searcherIndicators[i]->setColor(sf::Color(2, 165, 86, 255));
		GameObjectManager::getInstance()->addObject(searcherIndicators[i]);
	}

	for (int i = 0; i < numInserters; i++) {
		inserters.push_back(new InserterThread(&inserterCount, &inserterMEMutex,
			&deleterMEMutex, &inserterBufSem, &deleterBufSem, &roomEmpty));

		inserters[i]->start();

		inserterIndicators.push_back(new IconObject("indicator", 0));
		inserterIndicators[i]->setPosition(300, 400);
		inserterIndicators[i]->setColor(sf::Color(231, 18, 36, 255));

		GameObjectManager::getInstance()->addObject(inserterIndicators[i]);
	}

	deleter = new DeleterThread(&deleterMEMutex, &inserterBufSem, &deleterBufSem, &roomEmpty);
	deleter->start();

	deleterIndicator = new IconObject("indicator", 0);
	deleterIndicator->setPosition(100, 400);
	deleterIndicator->setColor(sf::Color(246, 99, 12, 255));

	GameObjectManager::getInstance()->addObject(deleterIndicator);
}

void IconListHandler::spawnIconObjectsToDisplay() {
	std::string number = "";

	for (int i = 0; i < 10; i++) {
		if (i < 10) number = "00" + std::to_string(i);
		else if (i < 100) number = "0" + std::to_string(i);
		else number = std::to_string(i);

		iconBufferList[i] = new IconObject("tile" + number, 0);
		iconBufferList[i]->setPosition((i * 100) + 50, 200);
		
		GameObjectManager::getInstance()->addObject(iconBufferList[i]);
	}
}

void IconListHandler::spawnIconObjectBank() {

}