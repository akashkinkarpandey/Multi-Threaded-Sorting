/**
 * @file parallelMergeSort.cpp
 * @brief Implementation of the ParallelMergeSort class for integer vectors
 * 
 * This file contains the implementation of a parallel merge sort algorithm
 * that uses multiple threads to improve performance on multi-core systems.
 */

#include "parallelMergeSort.hpp"
#include <algorithm>

/**
 * @brief Constructor for ParallelMergeSort
 * @param arrayToSort Pointer to the vector to be sorted
 * 
 * Uses initialization list to store the pointer to the original vector,
 * which allows sorting in-place without creating unnecessary copies.
 */
ParallelMergeSort::ParallelMergeSort(std::vector<int> *arrayToSort)
    : arrayToSort(arrayToSort)
{
}

/**
 * @brief Destructor for ParallelMergeSort
 * 
 * No dynamic memory allocation was performed by this class,
 * so the destructor is empty.
 */
ParallelMergeSort::~ParallelMergeSort() {}

/**
 * @brief Performs recursive merge sort on a subarray, potentially in parallel
 * @param startIndex The starting index of the subarray
 * @param endIndex The ending index of the subarray
 * 
 * This method uses a threshold to determine whether to use std::sort for small
 * subarrays (more efficient) or to continue with the parallel merge sort algorithm
 * for larger subarrays.
 */
void ParallelMergeSort::recursiveSort(int startIndex, int endIndex)
{
    // Define threshold for switching to std::sort
    // Below this size, the overhead of threading and merging outweighs the benefits
    const int SIZE_THRESHOLD = 5000;

    // Use std::sort for small arrays (more efficient than recursive mergesort)
    if (endIndex - startIndex < SIZE_THRESHOLD)
    {
        std::sort(arrayToSort->begin() + startIndex, arrayToSort->begin() + endIndex + 1);
        return;
    }

    // Base case: if the subarray has 0 or 1 elements, it's already sorted
    if (startIndex >= endIndex)
    {
        return;
    }

    // Calculate middle point, avoiding potential overflow
    int midIndex = startIndex + (endIndex - startIndex) / 2;

    // Create two threads to sort the left and right halves in parallel
    std::thread leftSortThread([this, startIndex, midIndex]
                         { this->recursiveSort(startIndex, midIndex); });
    std::thread rightSortThread([this, midIndex, endIndex]
                         { this->recursiveSort(midIndex + 1, endIndex); });
    
    // Wait for both threads to complete before merging
    leftSortThread.join();
    rightSortThread.join();

    // Temporary array to hold merged results
    std::vector<int> tempMergedArray;
    int leftArrayIndex = startIndex;        // Index for left subarray
    int rightArrayIndex = midIndex + 1;     // Index for right subarray

    // Merge the two sorted subarrays
    while (leftArrayIndex <= midIndex && rightArrayIndex <= endIndex)
    {
        if ((*arrayToSort)[leftArrayIndex] <= (*arrayToSort)[rightArrayIndex])
        {
            tempMergedArray.push_back((*arrayToSort)[leftArrayIndex]);
            leftArrayIndex++;
        }
        else
        {
            tempMergedArray.push_back((*arrayToSort)[rightArrayIndex]);
            rightArrayIndex++;
        }
    }

    // Copy any remaining elements from the left subarray
    while (leftArrayIndex <= midIndex)
    {
        tempMergedArray.push_back((*arrayToSort)[leftArrayIndex]);
        leftArrayIndex++;
    }

    // Copy any remaining elements from the right subarray
    while (rightArrayIndex <= endIndex)
    {
        tempMergedArray.push_back((*arrayToSort)[rightArrayIndex]);
        rightArrayIndex++;
    }

    // Copy the merged results back to the original array
    for (int mergedArrayIndex = 0; mergedArrayIndex < tempMergedArray.size(); mergedArrayIndex++)
    {
        (*arrayToSort)[startIndex + mergedArrayIndex] = tempMergedArray[mergedArrayIndex];
    }
}

/**
 * @brief Initiates the parallel sorting process
 * 
 * Validates the input vector and starts the recursive merge sort
 * in a separate thread to allow the main thread to continue execution.
 */
void ParallelMergeSort::sort()
{
    // Handle empty vector case
    if (arrayToSort->size() == 0)
    {
        exit(1);  // Exit with error code
    }

    // Create a thread to perform the sorting
    std::thread mainSortThread([this]
                         { this->recursiveSort(0, arrayToSort->size() - 1); });
    
    // Wait for the sorting thread to complete
    mainSortThread.join();
}