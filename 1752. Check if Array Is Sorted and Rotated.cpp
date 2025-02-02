#include "header.h"

class Solution {
public:
    bool check(vector<int>& nums) {

        auto it = ranges::is_sorted_until(nums);
        if (it == end(nums))
            return true;

        auto sorted = ranges::is_sorted(it, end(nums));
        return sorted && nums.back() <= nums.front();
    }
};

class Solution_1 {
public:
    bool check(vector<int>& nums) {

        int count = 0;
        for (int i = 1; i <= size(nums); i++)
            if (nums[i - 1] > nums[i % size(nums)])
                count++;

        return count <= 1;
    }
};

int main() {
    Solution_1 solution;

    vector<int> nums1 = {3, 4, 5, 1, 2};
    cout << "Example 1: " << solution.check(nums1) << endl; // Output: true

    vector<int> nums2 = {2, 1, 3, 4};
    cout << "Example 2: " << solution.check(nums2) << endl; // Output: false

    vector<int> nums3 = {1, 2, 3};
    cout << "Example 3: " << solution.check(nums3) << endl; // Output: true

    return 0;
}