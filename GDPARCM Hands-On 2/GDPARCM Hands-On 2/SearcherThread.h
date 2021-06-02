#pragma once
#include "IETThread.h"
#include "IconListHandler.h"

class SearcherThread : public IETThread
{
public:
	SearcherThread(int, IconListHandler*, Indicator*, int*, Mutex*, Mutex*, BufferSemaphore*, RoomSemaphore*, int);
private:
	void run() override;

	void searchIconList();

	int ID;
	int seed;

	IconListHandler* ILH;

	Indicator* indicator;
	
	int* numSearchers;
	int currentIndex;

	Mutex* searcherMEMutex;
	Mutex* deleterMEMutex;
	BufferSemaphore* deleterBufSem;
	RoomSemaphore* roomEmpty;
};