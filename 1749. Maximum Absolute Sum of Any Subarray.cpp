#include "header.h"

// You are given an integer array nums. The absolute sum of a subarray [numsl, numsl+1, ..., numsr-1, numsr] is abs(numsl + numsl+1 + ... + numsr-1 + numsr).

// Return the maximum absolute sum of any (possibly empty) subarray of nums.

// Note that abs(x) is defined as follows:

// If x is a negative integer, then abs(x) = -x.
// If x is a non-negative integer, then abs(x) = x.

// Example 1:
// Input: nums = [1,-3,2,3,-4]
// Output: 5
// Explanation: The subarray [2,3] has absolute sum = abs(2+3) = abs(5) = 5.

// Example 2:
// Input: nums = [2,-5,1,-4,3,-2]
// Output: 8
// Explanation: The subarray [-5,1,-4] has absolute sum = abs(-5+1-4) = abs(-8) = 8.

// Constraints:
// 1 <= nums.length <= 10^5
// -10^4 <= nums[i] <= 10^4

class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {

        int best_max = numeric_limits<int>::min();
        int current_sum = 0;

        for (auto num : nums)
        {
            current_sum = max(current_sum + num, num);
            best_max = max(best_max, current_sum);
        }

        int best_min = numeric_limits<int>::max();
        current_sum = 0;

        for (auto num : nums)
        {
            current_sum = min(current_sum + num, num);
            best_min = min(best_min, current_sum);
        }

        return max(best_max, -best_min);
    }
};

int main()
{
    Solution sol;

    {
        vector<int> nums = {1,-3,2,3,-4};
        cout << sol.maxAbsoluteSum(nums) << endl; // 5
    }
    {
        vector<int> nums = {2,-5,1,-4,3,-2};
        cout << sol.maxAbsoluteSum(nums) << endl; // 8
    }
    {
        vector<int> nums = {-3,-5,-3,-2,-6,3,10,-10,-8,-3,0,10,3,-5,8,7,-9,-9,5,-8};
        cout << sol.maxAbsoluteSum(nums) << endl; // 27
    }
    {
        vector<int> nums = {-2,-9,4,-10,6,-3,-8,3,-9,-5,-10,-1,0,8,0,-2,5,-1,6,5}; 
        cout << sol.maxAbsoluteSum(nums) << endl; // 44
    }
    {
        vector<int> nums = {2,-1}; 
        cout << sol.maxAbsoluteSum(nums) << endl; // 2
    }
}
