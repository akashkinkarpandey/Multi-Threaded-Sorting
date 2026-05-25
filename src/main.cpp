#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include "sorting/parallelMergeSort.hpp"
#include "sorting/simpleMergeSort.hpp"

struct BenchmarkResult
{
    std::string algorithmName;
    double executionTime;
    bool sortedCorrectly;
};

class BenchmarkRunner
{
private:
    static constexpr int MAX_RANDOM_VALUE = 19999999;

    std::mt19937 generator;

public:
    BenchmarkRunner()
    {
        std::random_device rd;
        generator = std::mt19937(rd());
    }

    std::vector<int> generateRandomArray(int size)
    {
        std::uniform_int_distribution<int> distribution(
            0,
            MAX_RANDOM_VALUE);

        std::vector<int> array(size);

        for (int i = 0; i < size; ++i)
        {
            array[i] = distribution(generator);
        }

        return array;
    }

    BenchmarkResult runSequentialMergeSort(
        std::vector<int> array)
    {
        MergeSort sorter(array);

        auto start =
            std::chrono::high_resolution_clock::now();

        sorter.sort();

        auto end =
            std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;

        return {
            "Sequential Merge Sort",
            duration.count(),
            std::is_sorted(array.begin(), array.end())};
    }

    BenchmarkResult runParallelMergeSort(
        std::vector<int> array)
    {
        ParallelMergeSort sorter(array);

        auto start =
            std::chrono::high_resolution_clock::now();

        sorter.sort();

        auto end =
            std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;

        return {
            "Parallel Merge Sort",
            duration.count(),
            std::is_sorted(array.begin(), array.end())};
    }

    BenchmarkResult runSTLSort(
        std::vector<int> array)
    {
        auto start =
            std::chrono::high_resolution_clock::now();

        std::sort(array.begin(), array.end());

        auto end =
            std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;

        return {
            "STL Sort",
            duration.count(),
            std::is_sorted(array.begin(), array.end())};
    }

    void printHeader()
    {
        std::cout << "\n";
        std::cout << "============================================================\n";
        std::cout << "          PARALLEL MERGE SORT BENCHMARK SUITE\n";
        std::cout << "============================================================\n\n";

        std::cout << "Hardware Threads Available : "
                  << std::thread::hardware_concurrency()
                  << "\n\n";
    }

    void printTableHeader()
    {
        std::cout
            << std::left
            << std::setw(15) << "Array Size"
            << std::setw(25) << "Algorithm"
            << std::setw(20) << "Time (sec)"
            << std::setw(15) << "Correct"
            << "\n";

        std::cout
            << std::string(75, '-')
            << "\n";
    }

    void printResult(
        int arraySize,
        const BenchmarkResult &result)
    {
        std::cout
            << std::left
            << std::setw(15) << arraySize
            << std::setw(25) << result.algorithmName
            << std::setw(20) << std::fixed
            << std::setprecision(6)
            << result.executionTime
            << std::setw(15)
            << (result.sortedCorrectly ? "YES" : "NO")
            << "\n";
    }

    void printSpeedup(
        const BenchmarkResult &sequential,
        const BenchmarkResult &parallel,
        const BenchmarkResult &stl)
    {
        double parallelVsSequential =
            sequential.executionTime /
            parallel.executionTime;

        double parallelVsSTL =
            stl.executionTime /
            parallel.executionTime;

        std::cout
            << "\n"
            << "   Parallel vs Sequential Speedup : "
            << std::fixed
            << std::setprecision(2)
            << parallelVsSequential
            << "x\n";

        std::cout
            << "   Parallel vs STL Speedup        : "
            << parallelVsSTL
            << "x\n";

        std::cout
            << std::string(75, '=')
            << "\n\n";
    }
};

int main()
{
    BenchmarkRunner benchmarkRunner;

    benchmarkRunner.printHeader();


    std::vector<int> arraySizes = {
        100000,
        500000,
        1000000,
        5000000,
        10000000};

    for (const int arraySize : arraySizes)
    {
        std::vector<int> originalArray =
            benchmarkRunner.generateRandomArray(arraySize);

        BenchmarkResult sequentialResult =
            benchmarkRunner.runSequentialMergeSort(
                originalArray);

        BenchmarkResult parallelResult =
            benchmarkRunner.runParallelMergeSort(
                originalArray);

        BenchmarkResult stlResult =
            benchmarkRunner.runSTLSort(
                originalArray);

        benchmarkRunner.printTableHeader();

        benchmarkRunner.printResult(
            arraySize,
            sequentialResult);

        benchmarkRunner.printTableHeader();

        benchmarkRunner.printResult(
            arraySize,
            parallelResult);

        benchmarkRunner.printTableHeader();

        benchmarkRunner.printResult(
            arraySize,
            stlResult);

        benchmarkRunner.printSpeedup(
            sequentialResult,
            parallelResult,
            stlResult);
    }

    return 0;
}