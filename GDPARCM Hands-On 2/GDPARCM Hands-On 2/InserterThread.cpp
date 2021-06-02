#include "InserterThread.h"
#include <iostream>

InserterThread::InserterThread (int* _numInserters, Mutex* _inserterMEMutex, Mutex* _deleterMEMutex, BufferSemaphore* _inserterBufSem,
	BufferSemaphore* _deleterBufSem, RoomSemaphore* _roomEmpty) : IETThread(), numInserters(_numInserters), inserterMEMutex(_inserterMEMutex),
	deleterMEMutex(_deleterMEMutex), inserterBufSem(_inserterBufSem), deleterBufSem(_deleterBufSem), roomEmpty(_roomEmpty)
{

}

void InserterThread::run() {
	while (true) {
		inserterBufSem->acquire();

		deleterMEMutex->acquire();
		(*numInserters)++;
		std::cout << "INSERTERS: Entering Critical Section, Count: " << std::to_string(*numInserters) << std::endl;
		if (*numInserters == 1) {
			roomEmpty->acquire();
		}
		deleterMEMutex->release();

		inserterMEMutex->acquire();
		/*CRITICAL SECTION*/
		sleep(300);
		(*numInserters)--;
		inserterMEMutex->release();

		if (*numInserters == 0) {
			roomEmpty->release();
		}
		
		std::cout << "INSERTERS: Exiting Critical Section, Count: " << std::to_string(*numInserters) << std::endl;
		deleterBufSem->release();

		sleep(500);
	}
}