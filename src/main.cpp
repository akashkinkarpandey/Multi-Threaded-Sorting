/**
 * @file main.cpp
 * @brief Performance comparison between standard and parallel merge sort algorithms
 * 
 * This program compares the execution time of a standard sequential merge sort
 * algorithm against a parallel implementation. It generates a large array of
 * random integers, creates identical copies, and measures the time each
 * algorithm takes to sort the data.
 */

#include <iostream>
#include <vector>
#include <chrono> 
#include "sorting/simpleMergeSort.hpp"
#include "sorting/parallelMergeSort.hpp"

/**
 * @brief Main program entry point
 * @param argc Number of command line arguments
 * @param argv Array of command line arguments
 * @return 0 on successful execution
 */
int main(int argc, char *argv[])
{
    // Configuration constants
    const int ARRAY_SIZE = 10000000;       // Size of the test arrays
    const int MAX_RANDOM_VALUE = 10000000; // Maximum random value generated
    
    // Create two identical arrays of random integers
    std::vector<int> standardSortArray(ARRAY_SIZE);
    std::vector<int> parallelSortArray(ARRAY_SIZE);
    
    // Fill arrays with the same random values
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        standardSortArray[i] = rand() % MAX_RANDOM_VALUE;
        parallelSortArray[i] = standardSortArray[i];
    }

    // Measure standard merge sort performance
    MergeSort *standardSorter = new MergeSort(&standardSortArray);
    auto standardSortStart = std::chrono::high_resolution_clock::now();  // Start timer
    standardSorter->sort();                                              // Execute sort
    auto standardSortEnd = std::chrono::high_resolution_clock::now();    // Stop timer
    std::chrono::duration<double> standardSortDuration = standardSortEnd - standardSortStart;

    // Output standard sort performance results
    std::cout << "Standard MergeSort time: " << standardSortDuration.count() << " seconds" << std::endl;

    // Free memory allocated for standard sorter
    delete standardSorter;

    // Measure parallel merge sort performance
    ParallelMergeSort *parallelSorter = new ParallelMergeSort(&parallelSortArray);
    auto parallelSortStart = std::chrono::high_resolution_clock::now();  // Start timer
    parallelSorter->sort();                                              // Execute sort
    auto parallelSortEnd = std::chrono::high_resolution_clock::now();    // Stop timer
    std::chrono::duration<double> parallelSortDuration = parallelSortEnd - parallelSortStart;

    // Output parallel sort performance results
    std::cout << "Parallel MergeSort time: " << parallelSortDuration.count() << " seconds" << std::endl;

    // Free memory allocated for parallel sorter
    delete parallelSorter;

    return 0;
}