#include "parallelMergeSort.hpp"

#include <algorithm>

#include <cmath>

#include <iostream>

ParallelMergeSort::ParallelMergeSort(std::vector<int> &arrayToSort) : arrayToSort(arrayToSort), tempBuffer(arrayToSort.size())
{
    unsigned int hardwareThreads =
        std::thread::hardware_concurrency();

    if (hardwareThreads == 0)
    {
        hardwareThreads = 2;
    }

    maxDepth = std::log2(hardwareThreads);
}

void ParallelMergeSort::merge(int startIndex,int midIndex,int endIndex)
{
    int left = startIndex;
    int right = midIndex + 1;
    int mergedIndex = startIndex;

    while (left <= midIndex && right <= endIndex)
    {
        if (arrayToSort[left] <= arrayToSort[right])
        {
            tempBuffer[mergedIndex++] = arrayToSort[left++];
        }
        else
        {
            tempBuffer[mergedIndex++] = arrayToSort[right++];
        }
    }
    while (left <= midIndex)
    {
        tempBuffer[mergedIndex++] = arrayToSort[left++];
    }
    while (right <= endIndex)
    {
        tempBuffer[mergedIndex++] = arrayToSort[right++];
    }
    for (int i = startIndex; i <= endIndex; ++i)
    {
        arrayToSort[i] = tempBuffer[i];
    }
}

void ParallelMergeSort::recursiveSort(int startIndex, int endIndex,unsigned int currentDepth)
{
    const int SIZE_THRESHOLD = 5000;

    if (startIndex >= endIndex)
    {
        return;
    }
    if (endIndex - startIndex < SIZE_THRESHOLD)
    {
        std::sort(arrayToSort.begin() + startIndex, 
        arrayToSort.begin() + endIndex + 1);
        return;
    }
    int midIndex = startIndex + (endIndex - startIndex) / 2;

    // Parallel only if under max depth
    if (currentDepth < maxDepth)
    {
        std::thread leftThread(&ParallelMergeSort::recursiveSort,
                               this,
                               startIndex,
                               midIndex,
                               currentDepth + 1);

        std::thread rightThread(&ParallelMergeSort::recursiveSort,
                                this,
                                midIndex + 1,
                                endIndex,
                                currentDepth + 1);

        leftThread.join();
        rightThread.join();
    }
    else
    {
        recursiveSort(startIndex, midIndex, currentDepth + 1);
        recursiveSort(midIndex + 1, endIndex, currentDepth + 1);
    }
    merge(startIndex, midIndex, endIndex);
}
void ParallelMergeSort::sort()
{
    if (arrayToSort.empty())
    {
        throw std::invalid_argument("Array is empty");
    }
    recursiveSort(0, arrayToSort.size() - 1, 0);
}