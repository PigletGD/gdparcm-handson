#include "SearcherThread.h"

SearcherThread::SearcherThread(IconListHandler* _ILH, Indicator* _indicator, int* _numSearchers, Mutex* _searcherMEMutex,
	Mutex* _deleterMEMutex, BufferSemaphore* _deleterBufSem, RoomSemaphore* _roomEmpty, int rand) : IETThread(), ILH(_ILH),
	indicator(_indicator), numSearchers(_numSearchers), searcherMEMutex(_searcherMEMutex), deleterMEMutex(_deleterMEMutex),
	deleterBufSem(_deleterBufSem), roomEmpty(_roomEmpty), seed(rand) {

}

void SearcherThread::run() {
	srand(seed);

	while (true) {
		deleterMEMutex->acquire();
		searcherMEMutex->acquire();
		(*numSearchers)++;
		std::cout << "SEARCHERS: Entering Critical Section, Count: " 
		<< std::to_string(*numSearchers) << std::endl;
		if (*numSearchers == 1) {
			roomEmpty->acquire();
		}
		searcherMEMutex->release();
		deleterMEMutex->release();

		/*DOES SOMETHING*/
		std::vector<IconObject*>* iconList = ILH->getIconList(); // returns IconObject**
		std::vector<IconObject*>* iconBank = ILH->getIconBank();

		if (!iconList->empty()) {
			int randIndex;
			do {
				randIndex = rand() % (*iconList).size();
			} while ((*iconList)[randIndex] == nullptr);

			ILH->updateIndicators(indicator, randIndex);
		}

		searcherMEMutex->acquire();
		(*numSearchers)--;
		if (*numSearchers == 0) {
			roomEmpty->release();
		}
		std::cout << "SEARCHERS: Exiting Critical Section, Count: " 
			<< std::to_string(*numSearchers) << std::endl;
		searcherMEMutex->release();

		sleep(1000);
	}
}