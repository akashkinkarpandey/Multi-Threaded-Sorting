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
    std::vector<int> stlSortArray(ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        standardSortArray[i] = distribution(generator);

        parallelSortArray[i] = standardSortArray[i];

        stlSortArray[i] = standardSortArray[i];
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

    std::cout << "\n========== STL SORT ==========\n";

    auto stlStart = std::chrono::high_resolution_clock::now();

    std::sort(stlSortArray.begin(),stlSortArray.end());

    auto stlEnd = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> stlDuration = stlEnd - stlStart;

    bool stlCorrect =std::is_sorted(stlSortArray.begin(),stlSortArray.end());

    std::cout<< "Execution Time: "<< stlDuration.count()<< " seconds\n";

    std::cout<< "Sorted Correctly: "<< (stlCorrect ? "YES" : "NO") << "\n";

    std::cout << "\n========== COMPARISON ==========\n";

    std::cout
        << "Parallel vs Sequential Speedup: "
        << standardDuration.count() / parallelDuration.count()
        << "x\n";

    std::cout
        << "Parallel vs STL Speedup: "
        << stlDuration.count() / parallelDuration.count()
        << "x\n";

    return 0;
}