#include "SearcherThread.h"

SearcherThread::SearcherThread(int* _numSearchers, Mutex* _searcherMEMutex, Mutex* _deleterMEMutex, BufferSemaphore* _deleterBufSem, RoomSemaphore* _roomEmpty) :
	IETThread(), numSearchers(_numSearchers), searcherMEMutex(_searcherMEMutex), deleterMEMutex(_deleterMEMutex), deleterBufSem(_deleterBufSem), roomEmpty(_roomEmpty) {
	
}

void SearcherThread::run() {
	while (true) {
		deleterMEMutex->acquire();
		(*numSearchers)++;
		std::cout << "SEARCHERS: Entering Critical Section, Count: " 
			<< std::to_string(*numSearchers) << std::endl;
		if (*numSearchers == 1) {
			roomEmpty->acquire();
		}
		deleterMEMutex->release();

		/*DOES SOMETHING*/
		sleep(1000);

		searcherMEMutex->acquire();
		(*numSearchers)--;
		if (*numSearchers == 0) {
			roomEmpty->release();
		}
		std::cout << "SEARCHERS: Exiting Critical Section, Count: " 
			<< std::to_string(*numSearchers) << std::endl;
		searcherMEMutex->release();

		sleep(500);
	}
}