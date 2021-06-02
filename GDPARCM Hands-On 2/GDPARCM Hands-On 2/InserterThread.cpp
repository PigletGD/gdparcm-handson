#include "InserterThread.h"
#include <iostream>

InserterThread::InserterThread (int _ID,IconListHandler* _ILH, Indicator* _indicator, int* _numInserters, Mutex* _inserterMEMutex, Mutex* _deleterMEMutex,
	BufferSemaphore* _inserterBufSem, BufferSemaphore* _deleterBufSem, RoomSemaphore* _roomEmpty, int rand) : IETThread(), ID(_ID), ILH(_ILH), indicator(_indicator),
	numInserters(_numInserters), inserterMEMutex(_inserterMEMutex), deleterMEMutex(_deleterMEMutex), inserterBufSem(_inserterBufSem),
	deleterBufSem(_deleterBufSem), roomEmpty(_roomEmpty), seed(rand)
{
	
}

void InserterThread::run() {
	srand(seed);
	
	while (true) {
		inserterBufSem->acquire();

		deleterMEMutex->acquire();
		(*numInserters)++;
		ILH->logPrintMessage("INSERTER " + std::to_string(ID) +
			": Inserter Started, Inserter Count: " + std::to_string(*numInserters));
		if (*numInserters == 1) {
			roomEmpty->acquire();
		}
		deleterMEMutex->release();

		inserterMEMutex->acquire();
		/*CRITICAL SECTION*/
		insertIconToDisplay();
		
		(*numInserters)--;
		ILH->logPrintMessage("INSERTER " + std::to_string(ID) +
			": Inserter Finished, Inserter Count: " + std::to_string(*numInserters));
		
		if (*numInserters == 0) {
			roomEmpty->release();
		}
		/*CRITICAL SECTION*/
		inserterMEMutex->release();
		
		deleterBufSem->release();

		sleep(205);
		// TOTAL SLEEP DURATION: 305
	}
}

void InserterThread::insertIconToDisplay() {
	std::vector<IconObject*>* iconList = ILH->getIconList();
	std::vector<IconObject*>* iconBank = ILH->getIconBank();

	int randIndex;
	do {
		randIndex = rand() % (*iconList).size();
	} while ((*iconList)[randIndex] != nullptr);

	(*iconList)[randIndex] = (*iconBank)[0];
	iconBank->erase(iconBank->begin());
	(*iconList)[randIndex]->setPosition((randIndex * 100) + 50, 100);
	ILH->updateIndicators(indicator, randIndex);

	ILH->logPrintMessage("INSERTER " + std::to_string(ID) + ": Inserted Icon \"" + (*iconList)[randIndex]->getName()
		+ "\" to display index " + std::to_string(randIndex));

	sleep(100);
}