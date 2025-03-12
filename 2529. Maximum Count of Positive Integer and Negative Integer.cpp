#include "header.h"

// Given an array nums sorted in non-decreasing order, return the maximum between the number of positive integers and the number of negative integers.

// In other words, if the number of positive integers in nums is pos and the number of negative integers is neg, then return the maximum of pos and neg.
// Note that 0 is neither positive nor negative.

// Example 1:
// Input: nums = [-2,-1,-1,1,2,3]
// Output: 3
// Explanation: There are 3 positive integers and 3 negative integers. The maximum count among them is 3.

// Example 2:
// Input: nums = [-3,-2,-1,0,0,1,2]
// Output: 3
// Explanation: There are 2 positive integers and 3 negative integers. The maximum count among them is 3.

// Example 3:
// Input: nums = [5,20,66,1314]
// Output: 4
// Explanation: There are 4 positive integers and 0 negative integers. The maximum count among them is 4.
 
// Constraints:
// 1 <= nums.length <= 2000
// -2000 <= nums[i] <= 2000
// nums is sorted in a non-decreasing order.

// Follow up: Can you solve the problem in O(log(n)) time complexity?

class Solution_1 {
public:
    int maximumCount(vector<int>& nums) {
        int positive = 0;
        int negative = 0;

        for (auto num : nums)
        {
            if (num > 0)
                positive++;
            if (num < 0)
                negative++;
        }
        return max(positive, negative);
    }
};

class Solution_2 {
public:
    int maximumCount(vector<int>& nums) {

        auto negative = distance(begin(nums), lower_bound(begin(nums), end(nums), 0));
        auto positive = distance(upper_bound(begin(nums), end(nums), 0), end(nums));

        return max(positive, negative);
    }
};

class Solution {
public:
    int maximumCount(vector<int>& nums) {

        auto [first, last] = std::equal_range(begin(nums), end(nums), 0);
        auto negative = distance(begin(nums), first);
        auto positive = distance(last, end(nums));

        return max(positive, negative);
    }
};

int main()
{
    Solution sol;
    {
        vector<int> nums = {-2,-1,-1,1,2,3};
        cout << sol.maximumCount(nums) << endl;
    }
    {
        vector<int> nums = {-3,-2,-1,0,0,1,2};
        cout << sol.maximumCount(nums) << endl;
    }
    {
        vector<int> nums = {5,20,66,1314};
        cout << sol.maximumCount(nums) << endl;
    }
}