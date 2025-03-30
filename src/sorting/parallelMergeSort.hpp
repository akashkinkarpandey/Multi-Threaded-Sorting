/**
 * @file parallelMergeSort.hpp
 * @brief Provides a class for parallel merge sort implementation on integer vectors
 * 
 * This header defines the ParallelMergeSort class which implements a multi-threaded
 * version of the merge sort algorithm for improved performance on multi-core systems.
 */

#ifndef PARALLELMERGESORT_H
#define PARALLELMERGESORT_H

#include <vector>
#include <thread>
#include <iostream>

/**
 * @class ParallelMergeSort
 * @brief Implements a parallel version of the merge sort algorithm for integer vectors
 * 
 * This class provides functionality to sort a vector of integers using a parallel
 * implementation of the merge sort algorithm, which divides the work among multiple
 * threads to achieve better performance on multi-core systems.
 */
class ParallelMergeSort
{
private:
    std::vector<int> *arrayToSort; /**< Pointer to the vector to be sorted */
public:
    /**
     * @brief Constructor for ParallelMergeSort
     * @param arrayToSort Pointer to the vector to be sorted
     * 
     * Stores a pointer to the original vector to allow in-place sorting
     * without creating unnecessary copies.
     */
    ParallelMergeSort(std::vector<int> *arrayToSort);
    
    /**
     * @brief Destructor for ParallelMergeSort
     * 
     * No dynamic memory allocation was performed by this class,
     * so the destructor is empty.
     */
    ~ParallelMergeSort();
    
    /**
     * @brief Initiates the parallel sorting process
     * 
     * Creates multiple threads to sort different segments of the array
     * in parallel, then merges the results.
     */
    void sort();
    
    /**
     * @brief Performs recursive merge sort on a subarray, potentially in parallel
     * @param startIndex The starting index of the subarray
     * @param endIndex The ending index of the subarray
     * 
     * This method may spawn new threads for sorting subarrays if the
     * subarray size is large enough to benefit from parallelization.
     */
    void recursiveSort(int startIndex, int endIndex);
};

#endif