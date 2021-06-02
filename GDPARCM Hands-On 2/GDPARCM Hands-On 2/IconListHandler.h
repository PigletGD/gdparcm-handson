#pragma once
#include "AGameObject.h"
//#include "SearcherThread.h"
//#include "InserterThread.h"
//#include "DeleterThread.h"

class SearcherThread;
class InserterThread;
class DeleterThread;

#include <semaphore>

const static int BUFFER_MAX = 10;

typedef std::binary_semaphore Mutex;
typedef std::counting_semaphore<BUFFER_MAX> BufferSemaphore;
typedef std::counting_semaphore<2> RoomSemaphore;

class IconListHandler : public AGameObject
{
public:
	IconListHandler();
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

private:
	int numSearchers = 4;
	int numInserters = 2;
	int numDeleters = 1;

	int searcherCount = 0;
	int inserterCount = 0;

	std::vector<SearcherThread*> searchers;
	std::vector<InserterThread*> inserters;
	DeleterThread* deleter;

	Mutex searcherMEMutex = Mutex(1);
	Mutex inserterMEMutex = Mutex(1);
	Mutex deleterMEMutex = Mutex(1);
	BufferSemaphore inserterBufSem = BufferSemaphore(BUFFER_MAX);
	BufferSemaphore deleterBufSem = BufferSemaphore(0);
	RoomSemaphore roomEmpty = RoomSemaphore(2);
};