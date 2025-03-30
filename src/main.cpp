#include <iostream>
#include <vector>
#include <chrono> // Include chrono for timing
#include "sorting/simpleMergeSort.hpp"
#include "sorting/parallelMergeSort.hpp"

int main(int argc, char *argv[])
{
    const int ARRAY_SIZE = 10000000;
    const int MAX_RANDOM_VALUE = 10000000;
    
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
    auto standardSortStart = std::chrono::high_resolution_clock::now();
    standardSorter->sort();
    auto standardSortEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> standardSortDuration = standardSortEnd - standardSortStart;

    std::cout << "Standard MergeSort time: " << standardSortDuration.count() << " seconds" << std::endl;

    delete standardSorter;

    // Measure parallel merge sort performance
    ParallelMergeSort *parallelSorter = new ParallelMergeSort(&parallelSortArray);
    auto parallelSortStart = std::chrono::high_resolution_clock::now();
    parallelSorter->sort();
    auto parallelSortEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> parallelSortDuration = parallelSortEnd - parallelSortStart;

    std::cout << "Parallel MergeSort time: " << parallelSortDuration.count() << " seconds" << std::endl;

    delete parallelSorter;

    return 0;
}