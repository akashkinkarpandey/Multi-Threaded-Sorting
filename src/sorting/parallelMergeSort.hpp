#ifndef PARALLELMERGESORT_H
#define PARALLELMERGESORT_H

#include <vector>
#include <thread>
#include <atomic>

class ParallelMergeSort
{
private:
    std::vector<int> &arrayToSort;
    std::vector<int> tempBuffer;

    unsigned int maxDepth;

    void recursiveSort(
        int startIndex,
        int endIndex,
        unsigned int currentDepth);

    void merge(
        int startIndex,
        int midIndex,
        int endIndex);

public:
    ParallelMergeSort(std::vector<int> &arrayToSort);

    void sort();
};

#endif