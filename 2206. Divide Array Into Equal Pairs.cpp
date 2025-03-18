#include "header.h"
#include <bitset>

// You are given an integer array nums consisting of 2 * n integers.

// You need to divide nums into n pairs such that:

// Each element belongs to exactly one pair.
// The elements present in a pair are equal.
// Return true if nums can be divided into n pairs, otherwise return false.

// Example 1:
// Input: nums = [3,2,3,2,2,2]
// Output: true
// Explanation: 
// There are 6 elements in nums, so they should be divided into 6 / 2 = 3 pairs.
// If nums is divided into the pairs (2, 2), (3, 3), and (2, 2), it will satisfy all the conditions.

// Example 2:
// Input: nums = [1,2,3,4]
// Output: false
// Explanation: 
// There is no way to divide nums into 4 / 2 = 2 pairs such that the pairs satisfy every condition.

// Constraints:
// nums.length == 2 * n
// 1 <= n <= 500
// 1 <= nums[i] <= 500

class Solution_1 {
public:
    bool divideArray(vector<int>& nums) {
        sort(begin(nums), end(nums));

        int n = size(nums);
        for (int i = 0; i < n; i += 2)
            if (nums[i] != nums[i + 1])
                return false;

        return true;
    }
};

class Solution {
public:
    bool divideArray(vector<int>& nums) {
        bitset<501> map{};

        int n = size(nums);

        for (auto num : nums)
            if (map[num].flip() == false)
                n -= 2;

        return n == 0;
    }
};

int main()
{
    Solution sol;

    {
        vector<int> nums = {3,2,3,2,2,2};
        cout << sol.divideArray(nums) << endl;
    }
    {
        vector<int> nums = {1,2,3,4};
        cout << sol.divideArray(nums) << endl;
    }
}
