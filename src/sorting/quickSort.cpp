/**
 * @file quickSort.cpp
 * @brief Implementation of the QuickSort class for integer vectors
 */

#include "quickSort.hpp"
#include <algorithm> // For std::swap

/**
 * @brief Constructor for QuickSort
 * @param nums Pointer to the vector to be sorted
 */
QuickSort::QuickSort(std::vector<int> *nums) {
    this->nums = nums;
}

/**
 * @brief Destructor for QuickSort
 */
QuickSort::~QuickSort() {}

/**
 * @brief Partitions the subarray around a pivot element
 * @param low The starting index of the subarray
 * @param high The ending index of the subarray
 * @return The index of the pivot element after partitioning
 * 
 * This implementation uses the last element as the pivot.
 */
int QuickSort::partition(int low, int high) {
    int pivot = (*nums)[high]; // Choose the last element as pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if ((*nums)[j] <= pivot) {
            i++; // Increment index of smaller element
            std::swap((*nums)[i], (*nums)[j]);
        }
    }
    std::swap((*nums)[i + 1], (*nums)[high]);
    return (i + 1);
}

/**
 * @brief Performs recursive quick sort on a subarray
 * @param low The starting index of the subarray
 * @param high The ending index of the subarray
 */
void QuickSort::recursiveQuickSort(int low, int high) {
    if (low < high) {
        // pi is partitioning index, (*nums)[pi] is now at right place
        int pi = partition(low, high);

        // Separately sort elements before partition and after partition
        recursiveQuickSort(low, pi - 1);
        recursiveQuickSort(pi + 1, high);
    }
}

/**
 * @brief Initiates the sorting process on the entire array
 */
void QuickSort::sort() {
    if (nums == nullptr || (*nums).empty()) {
        return; // Or handle error appropriately
    }
    recursiveQuickSort(0, (*nums).size() - 1);
}
