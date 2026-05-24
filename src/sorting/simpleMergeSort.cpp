#include "simpleMergeSort.hpp"

#include <algorithm>
#include <stdexcept>

MergeSort::MergeSort(std::vector<int> &nums)
    : nums(nums)
{
}

void MergeSort::recursiveSort(int startIndex, int endIndex)
{
    if (startIndex >= endIndex)
    {
        return;
    }

    int midIndex = startIndex + (endIndex - startIndex) / 2;

    recursiveSort(startIndex, midIndex);
    recursiveSort(midIndex + 1, endIndex);

    std::inplace_merge( nums.begin() + startIndex,
        nums.begin() + midIndex + 1,
        nums.begin() + endIndex + 1);
}

void MergeSort::sort()
{
    if (nums.empty())
    {
        throw std::invalid_argument(
            "Array is empty");
    }

    recursiveSort(0, nums.size() - 1);
}