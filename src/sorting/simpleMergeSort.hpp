#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>

class MergeSort
{
private:
    std::vector<int> &nums;

    void recursiveSort(int startIndex, int endIndex);

public:
    MergeSort(std::vector<int> &nums);

    void sort();
};

#endif