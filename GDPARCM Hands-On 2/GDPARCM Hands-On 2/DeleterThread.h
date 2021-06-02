#pragma once
#include "IETThread.h"
#include "IconListHandler.h"

class DeleterThread : public IETThread
{
public:
	DeleterThread(Mutex*, BufferSemaphore*, BufferSemaphore*, RoomSemaphore*);
private:
	void run() override;

	Mutex* deleterMEMutex;
	BufferSemaphore* inserterBufSem;
	BufferSemaphore* deleterBufSem;
	RoomSemaphore* roomEmpty;
};