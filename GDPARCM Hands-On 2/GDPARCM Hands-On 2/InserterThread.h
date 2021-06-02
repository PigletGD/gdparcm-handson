#pragma once
#include "IETThread.h"
#include "IconListHandler.h"

class InserterThread : public IETThread
{
public:
	InserterThread(int*, Mutex*, Mutex*, BufferSemaphore*, BufferSemaphore*, RoomSemaphore*);
private:
	void run() override;

	int* numInserters;

	Mutex* inserterMEMutex;
	Mutex* deleterMEMutex;
	BufferSemaphore* inserterBufSem;
	BufferSemaphore* deleterBufSem;
	RoomSemaphore* roomEmpty;
};