#pragma once
#include "IETThread.h"
#include "IconListHandler.h"

class DeleterThread : public IETThread
{
public:
	DeleterThread(IconListHandler*, Indicator*, Mutex*, BufferSemaphore*, BufferSemaphore*, RoomSemaphore*, int rand);

private:
	void run() override;

	int seed;

	IconListHandler* ILH;

	Indicator* indicator;

	Mutex* deleterMEMutex;
	BufferSemaphore* inserterBufSem;
	BufferSemaphore* deleterBufSem;
	RoomSemaphore* roomEmpty;
};