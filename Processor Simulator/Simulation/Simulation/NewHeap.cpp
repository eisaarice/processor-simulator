//NewHeap.cpp

#include "NewHeap.h"

// Constructor: Builds a heap from an input array of size cap
NewHeap::NewHeap(int cap) {

    heapSize = 0;
    capacity = cap;
    heapArray = new Job[cap];
}

// Function to insert a new job key
void NewHeap::InsertKey(Job k) {

    if (heapSize == capacity) {

        cout << endl << "Overflow: Could not insertKey" << endl;
        return;
    }

    // First insert the new key at the end
    heapSize++;
    int i = heapSize - 1;
    heapArray[i] = k;

    // If min heap found
    while (i != 0 && (heapArray[ParentNode(i)].processingTime > heapArray[i].processingTime || heapArray[i].jobType == 'D')) {
        SwapHeap(&heapArray[i], &heapArray[ParentNode(i)]);
        i = ParentNode(i);
    }

    // If element isn't swapped out, this executes
    if (i == 0) {

        if (heapSize > 1 && (heapArray[1].processingTime < heapArray[0].processingTime || heapArray[1].jobType == 'D')) {

            SwapHeap(&heapArray[1], &heapArray[0]);
        }

        if (heapSize > 2 && (heapArray[2].processingTime < heapArray[0].processingTime || heapArray[2].jobType == 'D')) {

            SwapHeap(&heapArray[2], &heapArray[0]);
        }
    }
}

// Function to check whether the heap is empty
bool NewHeap::IsHeapEmpty() {

    if (heapSize == 0) {

        return true;
    }

    else {

        return false;
    }
}

// Swaps two elements in the heap
void NewHeap::SwapHeap(Job* heapOne, Job* heapTwo) {

    Job temp = *heapOne;
    *heapOne = *heapTwo;
    *heapTwo = temp;

}

// Prints out the objects in the Heap, starting at the root
void NewHeap::PrintHeap() {

    for (int arr_i = 0; arr_i < heapSize; arr_i++) {

        cout << "Type " << heapArray[arr_i].jobType << "   ";
        cout << "Arrival Time " << heapArray[arr_i].arrivalTime << "   ";
        cout << "Job Number " << heapArray[arr_i].jobNumber << "   ";
        cout << "Type Number " << heapArray[arr_i].typeNumber << "   ";
        cout << "Processing Time " << heapArray[arr_i].processingTime << endl;
    }
}

//Increases the wait time in all job objects in the queue
void NewHeap::AddHeapWaitTime() {

    if (heapSize > 0) {

        for (int arr_i = 0; arr_i < heapSize; arr_i++) {

            heapArray[arr_i].waitTime++;
        }
    }

}

//Returns the sum of the wait times of all job objects
int NewHeap::GetRemainingWaitTime() {

    int totalWait = 0;
    if (heapSize > 0) {

        for (int arr_i = 0; arr_i < heapSize; arr_i++) {

            totalWait = totalWait + heapArray[arr_i].waitTime;
        }
    }
    return totalWait;
}

// Method to remove minimum element (or root) from min heap
Job NewHeap::PullMinElement() {

    if (heapSize <= 0) {

        return { '\0',0,0,0,0 };
    }

    if (heapSize == 1) {

        heapSize--;
        return heapArray[0];
    }

    // Store the minimum value, and remove it from heap
    Job root = heapArray[0];
    heapArray[0] = heapArray[heapSize - 1];
    heapSize--;
    MinHeapify(0);

    return root;
}

// Recursive function to heapify a subtree with root at given index
void NewHeap::MinHeapify(int i) {

    int l = LeftNode(i);
    int r = RightNode(i);
    int smallest = i;
    if (l < heapSize && heapArray[l].processingTime < heapArray[i].processingTime) {

        smallest = l;
    }

    if (r < heapSize && heapArray[r].processingTime < heapArray[smallest].processingTime) {

        smallest = r;
    }
    if (smallest != i) {

        SwapHeap(&heapArray[i], &heapArray[smallest]);
        MinHeapify(smallest);
    }
}