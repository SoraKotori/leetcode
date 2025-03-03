#include "header.h"

#include <ranges>
class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        vector<int> result(size(nums));
        auto first = begin(result);
        for (auto num : nums)
            if (num < pivot)
                *first++ = num;
        auto last = end(result) - 1;
        for (auto num : nums | views::reverse)
            if (num > pivot)
                *last-- = num;
        while (first <= last)
            *first++ = pivot;
        return result;
    }
};

int main()
{
    Solution sol;

    {
        vector<int> nums = {9,12,5,10,14,3,10};
        print_1D(sol.pivotArray(nums, 10));
    }
    {
        vector<int> nums = {-3,4,3,2};
        print_1D(sol.pivotArray(nums, 2));
    }
}