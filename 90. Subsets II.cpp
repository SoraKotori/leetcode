#include "header.h"

// Given an integer array nums that may contain duplicates, return all possible 
// subsets (the power set).

// The solution set must not contain duplicate subsets. Return the solution in any order.

// Example 1:
// Input: nums = [1,2,2]
// Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]

// Example 2:
// Input: nums = [0]
// Output: [[],[0]]

// Constraints:

// 1 <= nums.length <= 10
// -10 <= nums[i] <= 10

class Solution {
    void gen(vector<vector<int>>& result, const vector<int>& nums, vector<int> vec, int start)
    {
        result.push_back(vec);

        vec.resize(size(vec) + 1);
        for (int i = start; i < size(nums);)
        {
            vec.back() = nums[i];
            gen(result, nums, vec, i + 1);
            while (++i < size(nums) && vec.back() == nums[i]);
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>&& nums) {
        vector<vector<int>> result;
        sort(begin(nums), end(nums));
        gen(result, nums, {}, 0);
        return result;
    }
};

int main()
{
    Solution sol;

    print_2D_line(sol.subsetsWithDup({1,2,2}));
    print_2D_line(sol.subsetsWithDup({0}));
    print_2D_line(sol.subsetsWithDup({4,4,4,1,4}));
}