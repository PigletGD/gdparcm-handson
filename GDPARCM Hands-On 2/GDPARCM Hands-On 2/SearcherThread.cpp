#include "SearcherThread.h"

SearcherThread::SearcherThread(int _ID, IconListHandler* _ILH, Indicator* _indicator, int* _numSearchers, Mutex* _searcherMEMutex,
	Mutex* _deleterMEMutex, BufferSemaphore* _deleterBufSem, RoomSemaphore* _roomEmpty, int rand) : IETThread(), ID(_ID), ILH(_ILH),
	indicator(_indicator), numSearchers(_numSearchers), searcherMEMutex(_searcherMEMutex), deleterMEMutex(_deleterMEMutex),
	deleterBufSem(_deleterBufSem), roomEmpty(_roomEmpty), seed(rand) {
	currentIndex = 0;
}

void SearcherThread::run() {
	srand(seed);

	while (true) {
		deleterMEMutex->acquire();
		searcherMEMutex->acquire();
		(*numSearchers)++;
		if (*numSearchers == 1) {
			roomEmpty->acquire();
		}
		searcherMEMutex->release();
		deleterMEMutex->release();

		/*CRITICAL SECTION*/
		searchIconList();
		/*CRITICAL SECTION*/

		searcherMEMutex->acquire();
		(*numSearchers)--;
		if (*numSearchers == 0) {
			roomEmpty->release();
		}
		searcherMEMutex->release();

		sleep(100);
		// TOTAL SLEEP DURATION: 100 + (25 * Number of Elements Moved)
	}
}

void SearcherThread::searchIconList() {
	std::vector<IconObject*>* iconList = ILH->getIconList();
	std::vector<IconObject*>* iconBank = ILH->getIconBank();

	int randIndex;
	do {
		randIndex = rand() % (*iconList).size();
	} while ((*iconList)[randIndex] == nullptr);

	do {
		currentIndex++;
		if (currentIndex >= 10)
			currentIndex = 0;

		ILH->updateIndicators(indicator, currentIndex);
		sleep(25);
	} while (currentIndex != randIndex);

	ILH->updateIndicators(indicator, randIndex);
}