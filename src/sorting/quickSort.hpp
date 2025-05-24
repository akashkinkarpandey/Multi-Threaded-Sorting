/**
 * @file quickSort.hpp
 * @brief Provides a class for quick sort implementation on integer vectors
 */

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>

/**
 * @class QuickSort
 * @brief Implements the quick sort algorithm for integer vectors
 * 
 * This class provides functionality to sort a vector of integers
 * using the quick sort algorithm.
 */
class QuickSort {
private:
    std::vector<int> *nums; /**< Pointer to the vector to be sorted */

    /**
     * @brief Performs recursive quick sort on a subarray
     * @param low The starting index of the subarray
     * @param high The ending index of the subarray
     */
    void recursiveQuickSort(int low, int high);

    /**
     * @brief Partitions the subarray around a pivot element
     * @param low The starting index of the subarray
     * @param high The ending index of the subarray
     * @return The index of the pivot element after partitioning
     */
    int partition(int low, int high);

public:
    /**
     * @brief Constructor for QuickSort
     * @param nums Pointer to the vector to be sorted
     */
    QuickSort(std::vector<int> *nums);
    
    /**
     * @brief Destructor for QuickSort
     */
    ~QuickSort();
    
    /**
     * @brief Initiates the sorting process
     */
    void sort();
};

#endif
