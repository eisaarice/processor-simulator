//Main.cpp

#include "jobStack.h"
#include "NewHeap.h"
#include <random>
#include "Processor.h"
#include <fstream>
#include <iostream>
using namespace std;

// Used to create the job stack
void CreateJobStack(JobStack& inputJobs) {

    JobStack tempJobs;
    int jobArrived = 0;

    Job temp = { '\0', 0,0,0,0, 0 };

    fstream jobFile("org.dat", ios::in | ios::ate | ios::binary); //org.dat is the organized file from the other program

    if (!jobFile)
    {
        cerr << "org.dat could not be opened" << endl;
    }

    jobFile.seekg(0, ios::end);

    //add jobs from org.dat to stack
    for (int i = 0; i < 5570; i++)
    {
        static int jobNum = 1; //jobNumber in the file generator != jobNumber here
        temp = { '\0', 0, 0, jobNum, 0, 0 }; //reset for next

        jobFile.seekg((static_cast<std::basic_istream<char, std::char_traits<char>>::off_type>(i) * jobSize), ios::beg);
        jobFile.read((char*)&temp, jobSize);

        tempJobs.PushJobStack(temp);
        jobArrived++;
    }

    while (tempJobs.IsJobEmpty() != true) {

        inputJobs.PushJobStack(tempJobs.RemoveJobStack());
    }

    jobFile.close();
}

int main() {
    JobStack inputJobs;
    NewHeap jobHeap(5570);

    ofstream logFile;
    logFile.open("log.txt");

    long double heapAvg = 0;
    int maxQueue = 0;
    long int idleCount = 0;
    int jobsCompleted = 0;
    int aCompleted = 0, bCompleted = 0, cCompleted = 0, dCompleted = 0;
    int aArrived = 0, bArrived = 0, cArrived = 0, dArrived = 0;
    int activeCycle = 0;
    int totalProcessingTime = 0;
    int totalWaitTime = 0;
    float averageWaitTime = 0;
    int userCPU;

    CreateJobStack(inputJobs);
    //inputJobs.PrintJobs();            //Take out comment bars to see jobs printed

    cout << "Welcome to Jesus', Zawad's, and Matt's Test Processor Program!" << endl << endl;

    fstream jobFile("org.dat", ios::in | ios::ate | ios::binary); //org.dat is the organized file from the other program

    if (!jobFile)
    {
        cerr << "org.dat could not be opened" << endl;
        return -1;
    }

    do {

        cout << "How many processors would you like to use in this test?" << endl;
        cin >> userCPU;

        if (userCPU < 0) {

            cout << "Invalid Input" << endl;
        }
    } while (userCPU < 1);


    Processor* CPU = new Processor[userCPU];

    // Main loop
    for (int time = 1; time <= 10000; time++) //500 + 9500 = 10000
    {
        //report time
        logFile << "Time " << time << ": ";

        // Finishes a job and outputs completion status
        for (int cpuNum = 0; cpuNum < userCPU; cpuNum++) {
            if (CPU[cpuNum].IsComplete() && CPU[cpuNum].IsFull()) {

                Job tempJob;
                tempJob = CPU[cpuNum].RemoveProcessor();

                logFile << "Job " << tempJob.jobType << " " << tempJob.typeNumber << " Completed; ";
                jobsCompleted++;  

                if (tempJob.jobType == 'A') {

                    aCompleted++;
                }

                if (tempJob.jobType == 'B') {

                    bCompleted++;
                }

                if (tempJob.jobType == 'C') {

                    cCompleted++;
                }

                if (tempJob.jobType == 'D') {

                    dCompleted++;
                }
                
            }
        }

        // Adds items to the heap
        while (inputJobs.PeekJobArrivalTime() == time) {

            Job tempJob = inputJobs.RemoveJobStack();

            jobHeap.InsertKey(tempJob);

            logFile << "Arrival Job " << tempJob.jobType << ": Overall Job " << tempJob.jobNumber
                << ", Job " << tempJob.jobType << " " << tempJob.typeNumber
                << ", Processing Time " << tempJob.processingTime << "; ";


            // Counts each type of job in each run
            if (tempJob.jobType == 'A') {

                aArrived++;
            }

            if (tempJob.jobType == 'B') {

                bArrived++;
            }

            if (tempJob.jobType == 'C') {

                cArrived++;
            }

            if (tempJob.jobType == 'D') {

                dArrived++;
            }            
        }


        // Removes a job D from the stack for a more priority job
        for (int cpuNum = 0; cpuNum < userCPU; cpuNum++) {

            if (CPU[cpuNum].IsEmpty() || jobHeap.SizeOfHeap() == 0) {

                continue;
            }

            Job temp = jobHeap.GetMinHeap();

            if (temp.jobType == 'D') {

                Job interruptedJob;
                Job Djob;
                interruptedJob = CPU[cpuNum].RemoveProcessor();
                Djob = jobHeap.PullMinElement();
                CPU[cpuNum].PushProcessor(Djob);
                jobHeap.InsertKey(interruptedJob);
            }
            else {
                break;
            }
        }

        // Processes a new cpu in stack and adds to processing time
        for (int cpuNum = 0; cpuNum < userCPU; cpuNum++) {

            if (jobHeap.IsHeapEmpty()) 
            {
                logFile << "Queue: Empty; ";
                
                break;
            }
            
            else if (CPU[cpuNum].IsEmpty()) 
            {
                Job tempJob = jobHeap.PullMinElement();
                totalWaitTime = totalWaitTime + tempJob.waitTime;
                tempJob.waitTime = 0; // Resets job wait time 
                CPU[cpuNum].PushProcessor(tempJob);
              
                logFile << "Begin Processing Job " << tempJob.jobType << " " << tempJob.typeNumber
                    << " in CPU " << cpuNum + 1 << " , End Time " << time + tempJob.processingTime << "; ";
            }
        }

        //Process
        bool activeJob = false;

        for (int cpuNum = 0; cpuNum < userCPU; cpuNum++) {

            if (CPU[cpuNum].IsEmpty()) {                             

                logFile << " CPU " << cpuNum + 1 << ": Idle Time ";
                idleCount++;
                
            }

            else {

                Job tempJob = CPU[cpuNum].PeekJob();
                CPU[cpuNum].ProcessJobOne();
                activeJob = true;

                logFile << "CPU " << cpuNum + 1 << ": Job " << tempJob.jobType << " " << tempJob.jobNumber << "; ";
                totalProcessingTime++;
                
            }
        }

        jobHeap.AddHeapWaitTime();

        if (activeJob == true)
        { 
            activeCycle++;
        }
            
        

            heapAvg = heapAvg + (jobHeap.SizeOfHeap() - heapAvg) / time;

            if (jobHeap.SizeOfHeap() > maxQueue)

                maxQueue = jobHeap.SizeOfHeap();
                
            logFile << endl;
        

        //Initial Metrics Analysis
        if (time == 500)
        {
            int totalJobsArrived = aArrived + bArrived + cArrived + dArrived;
            totalWaitTime = totalWaitTime + jobHeap.GetRemainingWaitTime();
            averageWaitTime = totalWaitTime / totalJobsArrived;

            logFile << endl << "INITIAL REPORT METRICS" << endl;
            logFile << "Number of processor(s) being used: " << userCPU << endl;
            logFile << "Current Queue Size: " << jobHeap.SizeOfHeap() << endl;
            logFile << "Average queue size: " << heapAvg << endl;
            logFile << "Maximum jobs in queue: " << maxQueue << endl;
            logFile << "Total time jobs were in queue: " << totalWaitTime << " time units." << endl;
            logFile << "Average time jobs are in queue: " << averageWaitTime << " time units" << endl;
            logFile << "Total number of jobs A arrived: " << aArrived << endl;
            logFile << "Total number of jobs A completed: " << aCompleted << endl;
            logFile << "Total number of jobs B arrived: " << bArrived << endl;
            logFile << "Total number of jobs B completed: " << bCompleted << endl;
            logFile << "Total number of jobs C arrived: " << cArrived << endl;
            logFile << "Total number of jobs C completed: " << cCompleted << endl;
            logFile << "Total number of jobs D arrived: " << dArrived << endl;
            logFile << "Total number of jobs D completed: " << dCompleted << endl;
            logFile << "Total jobs arrived: " << totalJobsArrived << endl;
            logFile << "Total jobs completed: " << jobsCompleted << endl;
            logFile << "Total time CPU(s) were processing: " << totalProcessingTime << " time units" << endl;
            logFile << "Total time CPU(s) were idle: " << idleCount << " time units." << endl << endl;


            cout << endl << "INITIAL REPORT METRICS" << endl;
            cout << "Number of processor(s) being used: " << userCPU << endl;
            cout << "Current Queue Size: " << jobHeap.SizeOfHeap() << endl;
            cout << "Average queue size: " << heapAvg << endl;
            cout << "Maximum jobs in queue: " << maxQueue << endl;
            cout << "Total time jobs were in queue: " << totalWaitTime << " time units." << endl;
            cout << "Average time jobs are in queue: " << averageWaitTime << " time units" << endl;
            cout << "Total number of jobs A arrived: " << aArrived << endl;
            cout << "Total number of jobs A completed: " << aCompleted << endl;
            cout << "Total number of jobs B arrived: " << bArrived << endl;
            cout << "Total number of jobs B completed: " << bCompleted << endl;
            cout << "Total number of jobs C arrived: " << cArrived << endl;
            cout << "Total number of jobs C completed: " << cCompleted << endl;
            cout << "Total number of jobs D arrived: " << dArrived << endl;
            cout << "Total number of jobs D completed: " << dCompleted << endl;
            cout << "Total jobs arrived: " << totalJobsArrived << endl;
            cout << "Total jobs completed: " << jobsCompleted << endl;
            cout << "Total time CPU(s) were processing: " << totalProcessingTime << " time units" << endl;
            cout << "Total time CPU(s) were idle: " << idleCount << " time units." << endl << endl;
        }
    }

    // Metrics for final analysis
    int totalJobsArrived = aArrived + bArrived + cArrived + dArrived;
    totalWaitTime = totalWaitTime + jobHeap.GetRemainingWaitTime();
    averageWaitTime = totalWaitTime / totalJobsArrived;

    logFile << endl << "FINAL REPORT METRICS" << endl;
    logFile << "Number of processor(s) being used: " << userCPU << endl;
    logFile << "Final Queue Size: " << jobHeap.SizeOfHeap() << endl;
    logFile << "Average queue size: " << heapAvg << endl;
    logFile << "Maximum jobs in queue: " << maxQueue << endl;
    logFile << "Total time jobs were in queue: " << totalWaitTime << " time units." << endl;
    logFile << "Average time jobs are in queue: " << averageWaitTime << " time units" << endl;
    logFile << "Total number of jobs A arrived: " << aArrived << endl;
    logFile << "Total number of jobs A completed: " << aCompleted << endl;
    logFile << "Total number of jobs B arrived: " << bArrived << endl;
    logFile << "Total number of jobs B completed: " << bCompleted << endl;
    logFile << "Total number of jobs C arrived: " << cArrived << endl;
    logFile << "Total number of jobs C completed: " << cCompleted << endl;
    logFile << "Total number of jobs D arrived: " << dArrived << endl;
    logFile << "Total number of jobs D completed: " << dCompleted << endl;
    logFile << "Total jobs arrived: " << totalJobsArrived << endl;
    logFile << "Total jobs completed: " << jobsCompleted << endl;
    logFile << "Total time CPU(s) were processing: " << totalProcessingTime << " time units" << endl;
    logFile << "Total time CPU(s) were idle: " << idleCount << " time units." << endl << endl;
    
    
    cout << endl << "FINAL REPORT METRICS" << endl;
    cout << "Number of processor(s) being used: " << userCPU << endl;
    cout << "Final Queue Size: " << jobHeap.SizeOfHeap() << endl;
    cout << "Average queue size: " << heapAvg << endl;
    cout << "Maximum jobs in queue: " << maxQueue << endl;
    cout << "Total time jobs were in queue: " << totalWaitTime << " time units." << endl;
    cout << "Average time jobs are in queue: " << averageWaitTime << " time units" << endl;
    cout << "Total number of jobs A arrived: " << aArrived << endl;
    cout << "Total number of jobs A completed: " << aCompleted << endl;
    cout << "Total number of jobs B arrived: " << bArrived << endl;
    cout << "Total number of jobs B completed: " << bCompleted << endl;
    cout << "Total number of jobs C arrived: " << cArrived << endl;
    cout << "Total number of jobs C completed: " << cCompleted << endl;
    cout << "Total number of jobs D arrived: " << dArrived << endl;
    cout << "Total number of jobs D completed: " << dCompleted << endl;
    cout << "Total jobs arrived: " << totalJobsArrived << endl;
    cout << "Total jobs completed: " << jobsCompleted << endl;
    cout << "Total time CPU(s) were processing: " << totalProcessingTime << " time units" << endl;
    cout << "Total time CPU(s) were idle: " << idleCount << " time units." << endl << endl;

    logFile.close();
    jobFile.close();

    cout << "Report information is in the file log.txt" << endl;

    return 0;
}