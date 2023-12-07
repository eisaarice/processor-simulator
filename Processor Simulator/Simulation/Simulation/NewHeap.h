//NewHeap.h

#pragma once

#include <iostream>
#include "jobStack.h"

using namespace std;

class NewHeap {

    Job* heapArray;
    int capacity;
    int heapSize;

public:
    // Constructor
    NewHeap(int capacity);

    void MinHeapify(int);

    // In line function to return index of parent of node at index i
    int ParentNode(int i) { return (i - 1) / 2; }

    // In line function to return index of left child of node at index i
    int LeftNode(int i) { return (2 * i + 1); }

    // In line function to return index of right child of node at index i
    int RightNode(int i) { return (2 * i + 2); }

    // Function to extract the minimum element of heap
    Job PullMinElement();

    // Function that returns the minimum heap
    Job GetMinHeap() { return heapArray[0]; }

    void InsertKey(Job k);

    bool IsHeapEmpty();

    void SwapHeap(Job* heapOne, Job* heapTwo);

    void PrintHeap();

    // Inline function to return heap size to main
    int SizeOfHeap() { return heapSize; }

    void AddHeapWaitTime();

    int GetRemainingWaitTime();
};