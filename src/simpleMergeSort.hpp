/**
 * @file simpleMergeSort.hpp
 * @brief Provides a class for merge sort implementation on integer vectors
 */

#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>

/**
 * @class MergeSort
 * @brief Implements the merge sort algorithm for integer vectors
 * 
 * This class provides functionality to sort a vector of integers
 * using the merge sort algorithm, which has O(n log n) time complexity.
 */
class MergeSort {
private:
    std::vector<int> *nums; /**< Pointer to the vector to be sorted */

public:
    /**
     * @brief Constructor for MergeSort
     * @param nums Pointer to the vector to be sorted
     */
    MergeSort(std::vector<int> *nums);
    
    /**
     * @brief Destructor for MergeSort
     */
    ~MergeSort();
    
    /**
     * @brief Initiates the sorting process
     */
    void sort();
    
    /**
     * @brief Performs recursive merge sort on a subarray
     * @param left The starting index of the subarray
     * @param right The ending index of the subarray
     */
    void recursiveSort(int left, int right);
};

#endif