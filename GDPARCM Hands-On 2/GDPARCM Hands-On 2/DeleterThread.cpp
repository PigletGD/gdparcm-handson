#include "DeleterThread.h"
#include <iostream>

DeleterThread::DeleterThread(IconListHandler* _ILH, Indicator* _indicator, Mutex* _deleterMEMutex, BufferSemaphore* _inserterBufSem,
	BufferSemaphore* _deleterBufSem, RoomSemaphore* _roomEmpty, int rand) : IETThread(), ILH(_ILH), indicator(_indicator),
	deleterMEMutex(_deleterMEMutex), inserterBufSem(_inserterBufSem), deleterBufSem(_deleterBufSem), roomEmpty(_roomEmpty), seed(rand)
{
	
}

void DeleterThread::run() {
	srand(seed);
	
	while (true) {
		std::cout << "DELETER: GOING TO ASK TO EMPTY ROOM\n";
		deleterBufSem->acquire();
		std::cout << "DELETER: ACQUIRED PERMIT\n";
		deleterMEMutex->acquire();
		std::cout << "DELETER: ACQUIRED PERMIT TWO\n";
		for (int i = 0; i < 2; i++) {
			roomEmpty->acquire();
			std::cout << "DELETER: ROOM EMPTY PERMIT ACQUIRED\n";
		}
		std::cout << "DELETER: ENTERED CRITICAL SECTION\n";

		/*DO SOMETHING*/
		std::vector<IconObject*>* iconList = ILH->getIconList(); // returns IconObject**
		std::vector<IconObject*>* iconBank = ILH->getIconBank();

		if (!iconList->empty()) {
			int randIndex;
			do {
				randIndex = rand() % (*iconList).size();
			} while ((*iconList)[randIndex] == nullptr);

			(*iconList)[randIndex]->setPosition(-9999, -9999);
			iconBank->push_back((*iconList)[randIndex]);
			(*iconList)[randIndex] = nullptr;
			ILH->updateIndicators(indicator, randIndex);
		}
		
		//if ((*iconList)[randIndex] == nullptr)std::cout << "Its null: " << std::endl;

		
		//ILH->updateIndicators()

		std::cout << "DELETER: LEAVING CRITICAL SECTION\n";

		for (int i = 0; i < 2; i++) {
			roomEmpty->release();
		}
		deleterMEMutex->release();

		inserterBufSem->release();

		sleep(1500);
	}
}