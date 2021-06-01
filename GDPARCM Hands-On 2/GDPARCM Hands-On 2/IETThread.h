#pragma once
#include <iostream>
#include <thread>
#include <semaphore>

/// <summary>
/// Representation of a Java/C# like thread class. The behavior must be inherited by a class that needs to be threaded.
/// By: NeilDG
/// </summary>
class IETThread
{
public:
	IETThread();
	~IETThread();

	void start(); //schedules thread execution
	static void sleep(int ms);

protected:
	const int BUFFER;
	virtual void run() = 0;
};