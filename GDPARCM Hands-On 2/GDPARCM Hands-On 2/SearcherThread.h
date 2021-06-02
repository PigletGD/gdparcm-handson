#pragma once
#include "IETThread.h"
#include "IconListHandler.h"

class SearcherThread : public IETThread
{
public:
	SearcherThread(IconListHandler*, Indicator*, int*, Mutex*, Mutex*, BufferSemaphore*, RoomSemaphore*, int rand);
private:
	void run() override;

	int seed;

	IconListHandler* ILH;

	Indicator* indicator;
	
	int* numSearchers;

	Mutex* searcherMEMutex;
	Mutex* deleterMEMutex;
	BufferSemaphore* deleterBufSem;
	RoomSemaphore* roomEmpty;
};