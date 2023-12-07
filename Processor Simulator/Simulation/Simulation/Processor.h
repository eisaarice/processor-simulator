//Processor.h

#pragma once

#include "jobStack.h"

using namespace std;

class Processor {

private:
	Job currentJob;
	int jobArrived;

public:

	Processor();
	void PushProcessor(Job inputJob);
	Job RemoveProcessor();
	bool IsEmpty();
	bool IsFull();
	bool IsComplete();
	void ProcessJobOne();
	Job PeekJob() { return currentJob; } // Inline eekJob Function that returns currentJob to main
};