//Processor.cpp

#include "Processor.h"

// Processor Constructor
Processor::Processor() {
    currentJob = { '\0', 0, 0, 0, 0 ,0 };
    jobArrived = 0;
}


// Function to add a job to the Processor Stack
void Processor::PushProcessor(Job inputJob) {

    if (jobArrived == 0) {

        currentJob = inputJob;
        jobArrived++;
    }
}

// Function to remove an item from the Processor stack
Job Processor::RemoveProcessor() {


    Job tempJob = currentJob;
    currentJob = {};
    jobArrived--;
    return tempJob;

}

// Function to check whether the Processor stack is empty
bool Processor::IsEmpty() {

    if (jobArrived == 0) {

        return true;
    }

    else {

        return false;
    }
}

// Function to check whether the Processor stack is full
bool Processor::IsFull() {

    if (jobArrived == 1) {

        return true;
    }

    else {

        return false;
    }
}


// Function to check when the processor has no time remaining in the stack, else not complete.
bool Processor::IsComplete() {

    if (currentJob.processingTime == 0) {

        return true;
    }

    else {

        return false;
    }
}

//Decreases the processing time in an active job in a processor
void Processor::ProcessJobOne() {

    currentJob.processingTime--;
}