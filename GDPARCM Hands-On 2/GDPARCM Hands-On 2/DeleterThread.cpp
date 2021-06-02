#include "DeleterThread.h"
#include <iostream>

DeleterThread::DeleterThread(Mutex* _deleterMEMutex, BufferSemaphore* _inserterBufSem, BufferSemaphore* _deleterBufSem, RoomSemaphore* _roomEmpty) :
	IETThread(), deleterMEMutex(_deleterMEMutex), inserterBufSem(_inserterBufSem), deleterBufSem(_deleterBufSem), roomEmpty(_roomEmpty)
{

}

void DeleterThread::run() {
	while (true) {
		deleterBufSem->acquire();

		deleterMEMutex->acquire();
		for (int i = 0; i < 2; i++) {
			roomEmpty->acquire();
		}

		/*DO SOMETHING*/
		std::cout << "DELETER: Doing Something" << std::endl;
		
		for (int i = 0; i < 2; i++) {
			roomEmpty->release();
		}
		deleterMEMutex->release();

		inserterBufSem->release();

		sleep(500);
	}
}