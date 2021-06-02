#pragma once
#include "IETThread.h"
#include "IconListHandler.h"

class DeleterThread : public IETThread
{
public:
	DeleterThread(int, IconListHandler*, Indicator*, Mutex*, BufferSemaphore*, BufferSemaphore*, RoomSemaphore*, int);

private:
	void run() override;

	void removeIconFromDisplayList();

	int ID;
	int seed;

	IconListHandler* ILH;

	Indicator* indicator;

	Mutex* deleterMEMutex;
	BufferSemaphore* inserterBufSem;
	BufferSemaphore* deleterBufSem;
	RoomSemaphore* roomEmpty;
};