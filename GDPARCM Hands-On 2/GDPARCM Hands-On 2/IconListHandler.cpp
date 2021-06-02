#include "IconListHandler.h"

#include "GameObjectManager.h"
#include "TextureManager.h"

#include "SearcherThread.h"
#include "InserterThread.h"
#include "DeleterThread.h"

IconListHandler::IconListHandler() : AGameObject("Icon List Handler") {
	fileOut.open("output.txt");

	srand(time(NULL));

	spawnThreads();
	spawnIconObjectsToDisplay();
	spawnIconObjectBank();

	runThreads();
}

IconListHandler::~IconListHandler() {
	fileOut.close();
}

void IconListHandler::initialize() {

}

void IconListHandler::processInput(sf::Event event) {

}

void IconListHandler::update(sf::Time deltaTime) {

}

std::vector<IconObject*>* IconListHandler::getIconList() {
	return &iconBufferList;
}

std::vector<IconObject*>* IconListHandler::getIconBank() {
	return &iconObjectBank;
}

void IconListHandler::spawnThreads() {
	for (int i = 0; i < numSearchers; i++) {
		searcherIndicators.push_back(new Indicator("indicator", 0));
		searcherIndicators[i]->setPosition(-9999, -9999);
		searcherIndicators[i]->setColor(sf::Color(2, 165, 86, 255));

		GameObjectManager::getInstance()->addObject(searcherIndicators[i]);

		searchers.push_back(new SearcherThread(i, this, searcherIndicators[i], &searcherCount,
			&searcherMEMutex, &deleterMEMutex, &deleterBufSem, &roomEmpty, rand()));
	}

	for (int i = 0; i < numInserters; i++) {
		inserterIndicators.push_back(new Indicator("indicator", 0));
		inserterIndicators[i]->setPosition(-9999, -9999);
		inserterIndicators[i]->setColor(sf::Color(246, 99, 12, 255));

		GameObjectManager::getInstance()->addObject(inserterIndicators[i]);

		inserters.push_back(new InserterThread(i, this, inserterIndicators[i], &inserterCount, &inserterMEMutex,
			&deleterMEMutex, &inserterBufSem, &deleterBufSem, &roomEmpty, rand()));
	}

	for (int i = 0; i < numDeleters; i++) {
		deleterIndicators.push_back(new Indicator("indicator", 0));
		deleterIndicators[i]->setPosition(-9999, -9999);
		deleterIndicators[i]->setColor(sf::Color(231, 18, 36, 255));

		GameObjectManager::getInstance()->addObject(deleterIndicators[i]);

		deleters.push_back(new DeleterThread(i, this, deleterIndicators[i], &deleterMEMutex,
			&inserterBufSem, &deleterBufSem, &roomEmpty, rand()));
	}
}

void IconListHandler::runThreads() {
	for (int i = 0; i < numSearchers; i++) {
		searchers[i]->start();
	}

	for (int i = 0; i < numInserters; i++) {
		inserters[i]->start();
	}

	for (int i = 0; i < numDeleters; i++) {
		deleters[i]->start();
	}
}

void IconListHandler::spawnIconObjectsToDisplay() {
	std::string number = "";

	for (int i = 0; i < 10; i++) {
		if (i < 10) number = "00" + std::to_string(i);
		else if (i < 100) number = "0" + std::to_string(i);
		else number = std::to_string(i);

		iconBufferList.push_back(new IconObject("tile" + number, 0));
		iconBufferList[i]->setPosition((i * 100) + 50, 100);
		
		GameObjectManager::getInstance()->addObject(iconBufferList[i]);
	}
}

void IconListHandler::spawnIconObjectBank() {
	std::string number = "";

	for (int i = 10; i < 20; i++) {
		if (i < 10) number = "00" + std::to_string(i);
		else if (i < 100) number = "0" + std::to_string(i);
		else number = std::to_string(i);

		iconObjectBank.push_back(new IconObject("tile" + number, 0));
		iconObjectBank[i-10]->setPosition(-9999, -9999);

		GameObjectManager::getInstance()->addObject(iconObjectBank[i-10]);
	}
}

void IconListHandler::updateIndicators(Indicator* indicator, int randIndex) {
	syncMEMutex.acquire();

	indicator->setAssignedIndex(randIndex);

	int occupyingIndex[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int currentIndex;
	for (int i = 0; i < numSearchers; i++) {
		currentIndex = searcherIndicators[i]->getAssignedIndex();
		if (currentIndex == -1) continue;

		searcherIndicators[i]->setPosition((currentIndex * 100) + 50, (occupyingIndex[currentIndex] * 80) + 180);

		occupyingIndex[currentIndex]++;
	}

	for (int i = 0; i < numInserters; i++) {
		currentIndex = inserterIndicators[i]->getAssignedIndex();
		if (currentIndex == -1) continue;

		inserterIndicators[i]->setPosition((currentIndex * 100) + 50, (occupyingIndex[currentIndex] * 80) + 180);

		occupyingIndex[currentIndex]++;
	}

	for (int i = 0; i < numDeleters; i++) {
		currentIndex = deleterIndicators[i]->getAssignedIndex();
		if (currentIndex == -1) continue;

		deleterIndicators[i]->setPosition((currentIndex * 100) + 50, (occupyingIndex[currentIndex] * 80) + 180);

		occupyingIndex[currentIndex]++;
	}

	syncMEMutex.release();
}

void IconListHandler::logPrintMessage(std::string msg) {
	fileOut << msg << std::endl;
	std::cout << msg << std::endl;
}