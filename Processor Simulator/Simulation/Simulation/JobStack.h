//JobStack.h

#pragma once

#include <iostream>

using namespace std;

struct Job {

    char jobType;
    int processingTime;
    int typeNumber;
    int jobNumber;
    int arrivalTime;
    int waitTime = 0;
};
const int jobSize = sizeof(Job); //24

class JobStack {

private:
    Job jobArray[5570];
    int jobArrived;
public:
    JobStack();

    void PushJobStack(Job inputJob);
    Job RemoveJobStack();

    bool IsJobEmpty();
    bool IsJobFull();
    void PrintJobs();
    int PeekJobArrivalTime();
    int GetJobArrived() { return jobArrived; }     // Inline GetCount Function that returns jobArrived to main
};