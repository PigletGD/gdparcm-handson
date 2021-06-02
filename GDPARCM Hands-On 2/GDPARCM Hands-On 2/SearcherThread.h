#pragma once
#include "IETThread.h"
#include "IconListHandler.h"

class SearcherThread : public IETThread
{
public:
	SearcherThread(int*, Mutex*, Mutex*, BufferSemaphore*, RoomSemaphore*);
private:
	void run() override;

	int* numSearchers;

	Mutex* searcherMEMutex;
	Mutex* deleterMEMutex;
	BufferSemaphore* deleterBufSem;
	RoomSemaphore* roomEmpty;
};