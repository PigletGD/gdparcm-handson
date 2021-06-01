#include "ThreadPool.h"
#include "PoolWorkerThread.h"

ThreadPool::ThreadPool(String name, int numWorkers)
{
	this->name = name;
	this->numWorkers = numWorkers;

	for (int i = 0; i < this->numWorkers; i++)
		this->inactiveThreads.push(new PoolWorkerThread(i, this));
}

ThreadPool::~ThreadPool()
{

}

void ThreadPool::startScheduler()
{
	this->running = true;
	this->start();
}

void ThreadPool::stopScheduler()
{
	this->running = false;
}

void ThreadPool::scheduleTask(IWorkerAction* action)
{
	this->pendingActions.push(action);
}

void ThreadPool::run() {
	while (this->running) {
		if (this->pendingActions.empty() == false) {
			if (this->inactiveThreads.empty() == false) {
				
				//schedule task
				PoolWorkerThread* workerThread = this->inactiveThreads.front();
				this->inactiveThreads.pop();
				this->activeThreads[workerThread->getThreadID()] = workerThread;

				workerThread->assignTask(this->pendingActions.front());
				workerThread->start();

				std::cout << "[ThreadPool " << this->name << "] Scheduled task on ID " << workerThread->getThreadID() << std::endl;

				this->pendingActions.pop();
			}
			//else std::cout << "[ThreadPool " << this->name << "] No more available worker thread" << std::endl;
		}
		//else std::cout << "[ThreadPool " << this->name << "] No actions scheduled" << std::endl;
	}
}

void ThreadPool::onFinished(int threadID)
{
	if (this->activeThreads[threadID] != nullptr) {
		// create a fresh instance of a thread worker after execution
		delete this->activeThreads[threadID];
		this->activeThreads.erase(threadID);

		this->inactiveThreads.push(new PoolWorkerThread(threadID, this));

		std::cout << "[ThreadPool " << this->name << "] Task ended on ID " << threadID << std::endl;
	}
}