#include "IconListHandler.h"

#include "SearcherThread.h"
#include "InserterThread.h"
#include "DeleterThread.h"

IconListHandler::IconListHandler() : AGameObject("Icon List Handler") {
	for (int i = 0; i < numSearchers; i++) {
		searchers.push_back(new SearcherThread(&searcherCount, &searcherMEMutex,
			&deleterMEMutex, &deleterBufSem, &roomEmpty));

		searchers[i]->start();
	}
	
	for (int i = 0; i < numInserters; i++) {
		inserters.push_back(new InserterThread(&inserterCount, &inserterMEMutex,
			&deleterMEMutex, &inserterBufSem, &deleterBufSem, &roomEmpty));

		inserters[i]->start();
	}

	deleter = new DeleterThread(&deleterMEMutex, &inserterBufSem, &deleterBufSem, &roomEmpty);
	deleter->start();
}

void IconListHandler::initialize() {

}

void IconListHandler::processInput(sf::Event event) {

}

void IconListHandler::update(sf::Time deltaTime) {

}