/**
 * @file simpleMergeSort.cpp
 * @brief Implementation of the MergeSort class for integer vectors
 */

#include "simpleMergeSort.hpp"

/**
 * @brief Constructor for MergeSort
 * @param nums Pointer to the vector to be sorted
 * 
 * Stores a pointer to the original vector to allow in-place sorting
 * without creating unnecessary copies.
 */
MergeSort::MergeSort(std::vector<int> *nums)
{
    this->nums = nums;
}

/**
 * @brief Destructor for MergeSort
 * 
 * No dynamic memory allocation was performed by this class,
 * so the destructor is empty.
 */
MergeSort::~MergeSort() {}

/**
 * @brief Performs recursive merge sort on a subarray
 * @param startIndex The starting index of the subarray
 * @param endIndex The ending index of the subarray
 * 
 * This is the core of the merge sort algorithm that:
 * 1. Divides the array into two halves
 * 2. Recursively sorts each half
 * 3. Merges the sorted halves back together
 */
void MergeSort::recursiveSort(int startIndex, int endIndex)
{
    // Base case: if the subarray has 0 or 1 elements, it's already sorted
    if (startIndex >= endIndex)
    {
        return;
    }
    
    // Calculate middle point, avoiding overflow with this formula
    int midIndex = startIndex + (endIndex - startIndex) / 2;

    // Recursively sort the left half
    recursiveSort(startIndex, midIndex);
    
    // Recursively sort the right half
    recursiveSort(midIndex + 1, endIndex);

    // Temporary array to hold merged results
    std::vector<int> tempMergedArray;
    int leftArrayIndex = startIndex;
    int rightArrayIndex = midIndex + 1;

    // Merge the two sorted subarrays into tempMergedArray
    while (leftArrayIndex <= midIndex && rightArrayIndex <= endIndex)
    {
        if ((*nums)[leftArrayIndex] <= (*nums)[rightArrayIndex])
        {
            tempMergedArray.push_back((*nums)[leftArrayIndex]);
            leftArrayIndex++;
        }
        else
        {
            tempMergedArray.push_back((*nums)[rightArrayIndex]);
            rightArrayIndex++;
        }
    }

    // If any elements remain in the left subarray, add them
    while (leftArrayIndex <= midIndex)
    {
        tempMergedArray.push_back((*nums)[leftArrayIndex]);
        leftArrayIndex++;
    }

    // If any elements remain in the right subarray, add them
    while (rightArrayIndex <= endIndex)
    {
        tempMergedArray.push_back((*nums)[rightArrayIndex]);
        rightArrayIndex++;
    }

    // Copy the merged elements back to the original array
    for (int mergedArrayIndex = 0; mergedArrayIndex < tempMergedArray.size(); mergedArrayIndex++)
    {
        (*nums)[startIndex + mergedArrayIndex] = tempMergedArray[mergedArrayIndex];
    }
}

/**
 * @brief Initiates the sorting process on the entire array
 * 
 * Validates the input vector and starts the recursive merge sort
 * from the beginning to the end of the array.
 */
void MergeSort::sort()
{
    // Handle empty vector case
    if ((*nums).size() == 0)
    {
        exit(1);  // Exit with error code
    }
    
    // Start the recursive sorting process
    recursiveSort(0, (*nums).size() - 1);
}