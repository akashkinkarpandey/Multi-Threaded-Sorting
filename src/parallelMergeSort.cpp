#include "parallelMergeSort.hpp"
#include "algorithm"

ParallelMergeSort::ParallelMergeSort(std::vector<int> *arrayToSort)
    : arrayToSort(arrayToSort)
{
}

ParallelMergeSort::~ParallelMergeSort() {}

void ParallelMergeSort::recursiveSort(int left, int right)
{

    const int THRESHOLD = 5000;

    if (right - left < THRESHOLD)
    {
        std::sort(arrayToSort->begin() + left, arrayToSort->begin() + right + 1);
        return;
    }

    if (left >= right)
    {
        return;
    }
    int mid = left + (right - left) / 2;

    std::thread thread_1([this, left, mid]
                         { this->recursiveSort(left, mid); });
    std::thread thread_2([this, mid, right]
                         { this->recursiveSort(mid + 1, right); });
    thread_1.join();
    thread_2.join();

    std::vector<int> result;
    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right)
    {
        if ((*arrayToSort)[i] <= (*arrayToSort)[j])
        {
            result.push_back((*arrayToSort)[i]);
            i++;
        }
        else
        {
            result.push_back((*arrayToSort)[j]);
            j++;
        }
    }

    while (i <= mid)
    {
        result.push_back((*arrayToSort)[i]);
        i++;
    }

    while (j <= right)
    {
        result.push_back((*arrayToSort)[j]);
        j++;
    }

    for (int k = 0; k < result.size(); k++)
    {
        (*arrayToSort)[left + k] = result[k];
    }
}

void ParallelMergeSort::sort()
{
    if ((*arrayToSort).size() == 0)
    {
        exit(1);
    }

    std::thread thread_1([this]
                         { this->recursiveSort(0, (*arrayToSort).size() - 1); });
    thread_1.join();
}