#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <thread>
#include <random>

#include "sorting/simpleMergeSort.hpp"
#include "sorting/parallelMergeSort.hpp"

int main()
{
    const int ARRAY_SIZE = 10000000;
    const int MAX_RANDOM_VALUE = 19999999;

    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_int_distribution<int> distribution(0, MAX_RANDOM_VALUE);

    std::vector<int> standardSortArray(ARRAY_SIZE);
    std::vector<int> parallelSortArray(ARRAY_SIZE);

    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        standardSortArray[i] = distribution(generator);

        parallelSortArray[i] = standardSortArray[i];
    }

    std::cout << "\n========== SYSTEM INFO ==========\n";

    std::cout<< "Hardware Threads Available: "<< std::thread::hardware_concurrency()
        << "\n";

    std::cout<< "Array Size: " << ARRAY_SIZE << "\n";

    std::cout << "\n========== STANDARD MERGE SORT ==========\n";

    MergeSort standardSorter(standardSortArray);

    auto standardStart =
        std::chrono::high_resolution_clock::now();

    standardSorter.sort();

    auto standardEnd =
        std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> standardDuration =
        standardEnd - standardStart;

    bool standardCorrect =
        std::is_sorted(
            standardSortArray.begin(),
            standardSortArray.end());

    std::cout
        << "Execution Time: "
        << standardDuration.count()
        << " seconds\n";

    std::cout
        << "Sorted Correctly: "
        << (standardCorrect ? "YES" : "NO")
        << "\n";

    std::cout << "\n========== PARALLEL MERGE SORT ==========\n";

    ParallelMergeSort parallelSorter(parallelSortArray);

    auto parallelStart = std::chrono::high_resolution_clock::now();

    parallelSorter.sort();

    auto parallelEnd = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> parallelDuration =
        parallelEnd - parallelStart;

    bool parallelCorrect =
        std::is_sorted(
            parallelSortArray.begin(),
            parallelSortArray.end());

    std::cout
        << "Execution Time: "
        << parallelDuration.count()
        << " seconds\n";

    std::cout
        << "Sorted Correctly: "
        << (parallelCorrect ? "YES" : "NO")
        << "\n";

    double speedup =standardDuration.count() / parallelDuration.count();

    std::cout << "\n========== PERFORMANCE METRICS ==========\n";

    std::cout<< "Speedup Ratio: " << speedup << "x\n";

    return 0;
}