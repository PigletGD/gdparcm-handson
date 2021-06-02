#include "DeleterThread.h"
#include <iostream>

DeleterThread::DeleterThread(int _ID, IconListHandler* _ILH, Indicator* _indicator, Mutex* _deleterMEMutex, BufferSemaphore* _inserterBufSem,
	BufferSemaphore* _deleterBufSem, RoomSemaphore* _roomEmpty, int rand) : IETThread(), ID(_ID), ILH(_ILH), indicator(_indicator),
	deleterMEMutex(_deleterMEMutex), inserterBufSem(_inserterBufSem), deleterBufSem(_deleterBufSem), roomEmpty(_roomEmpty), seed(rand)
{
	
}

void DeleterThread::run() {
	srand(seed);
	
	while (true) {
		deleterBufSem->acquire();
		deleterMEMutex->acquire();
		for (int i = 0; i < 2; i++) {
			roomEmpty->acquire();
		}
		ILH->logPrintMessage("DELETER  " + std::to_string(ID) + ": Deleter Started");

		/*CRITICAL SECTION*/
		removeIconFromDisplayList();
		/*CRITICAL SECTION*/

		ILH->logPrintMessage("DELETER  " + std::to_string(ID) + ": Deleter Ended");
		for (int i = 0; i < 2; i++) {
			roomEmpty->release();
		}
		deleterMEMutex->release();

		inserterBufSem->release();

		sleep(200);
		// TOTAL SLEEP DURATION: 300
	}
}

void DeleterThread::removeIconFromDisplayList() {
	std::vector<IconObject*>* iconList = ILH->getIconList();
	std::vector<IconObject*>* iconBank = ILH->getIconBank();

	int randIndex;
	do {
		randIndex = rand() % (*iconList).size();
	} while ((*iconList)[randIndex] == nullptr);

	IconObject* holder = (*iconList)[randIndex];
	(*iconList)[randIndex]->setPosition(-9999, -9999);
	iconBank->push_back((*iconList)[randIndex]);
	(*iconList)[randIndex] = nullptr;
	ILH->updateIndicators(indicator, randIndex);

	ILH->logPrintMessage("DELETER  " + std::to_string(ID) + ": Deleted Icon \"" + holder->getName()
		+ "\" from Display Index " + std::to_string(randIndex));

	sleep(100);
}