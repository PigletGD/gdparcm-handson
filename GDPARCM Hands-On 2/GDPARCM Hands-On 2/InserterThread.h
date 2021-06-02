#pragma once
#include "IETThread.h"
#include "IconListHandler.h"

class InserterThread : public IETThread
{
public:
	InserterThread(IconListHandler*, Indicator*, int*, Mutex*, Mutex*, BufferSemaphore*, BufferSemaphore*, RoomSemaphore*, int);
private:
	void run() override;

	int seed;

	IconListHandler* ILH;

	Indicator* indicator;

	int* numInserters;

	Mutex* inserterMEMutex;
	Mutex* deleterMEMutex;
	BufferSemaphore* inserterBufSem;
	BufferSemaphore* deleterBufSem;
	RoomSemaphore* roomEmpty;
};