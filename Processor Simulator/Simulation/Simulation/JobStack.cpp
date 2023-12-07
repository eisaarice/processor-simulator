//JobStack.cpp

#include "JobStack.h"

JobStack::JobStack() {
    jobArrived = 0;
}

// This function adds a new job to the top of the stack
void JobStack::PushJobStack(Job inputJob) {
    jobArrived++;
    jobArray[jobArrived - 1] = inputJob;
}

// Function to remove the job on the top of the stack and return it to the main function
Job JobStack::RemoveJobStack() {
    Job tempJob;
    tempJob = jobArray[jobArrived - 1];
    jobArray[jobArrived - 1] = { '\0',0, 0, 0, 0 };
    jobArrived--;
    return tempJob;
}

// Function to determine if the job stack is empty
bool JobStack::IsJobEmpty() {

    if (jobArrived == 0) {

        return true;
    }

    else {

        return false;
    }
}

// Function to determine if the job stack is full
bool JobStack::IsJobFull() {

    if (jobArrived == 5570) {

        return true;
    }

    else {

        return false;
    }
}

// Function to print out all jobs within the stack
void JobStack::PrintJobs() {

    for (int stackArr = jobArrived - 1; stackArr >= 0; stackArr--) {

        cout << "Type " << jobArray[stackArr].jobType << "   ";
        cout << "Arrival Time " << jobArray[stackArr].arrivalTime << "   ";
        cout << "Job Number " << jobArray[stackArr].jobNumber << "   ";
        cout << "Type Number " << jobArray[stackArr].typeNumber << "   ";
        cout << "Processing Time " << jobArray[stackArr].processingTime << endl;
    }
}

// Function that returns to main the arrival time of the job on the top of the stack
int JobStack::PeekJobArrivalTime() {

    return jobArray[jobArrived - 1].arrivalTime;
}