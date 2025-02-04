#include "header.h"

class Solution {
public:
    int maxAscendingSum(vector<int>& nums) {
        int current = nums[0];
        int max_value = current;

        for (int i = 1; i < size(nums); i++)
        {
            current = nums[i - 1] < nums[i] ? current + nums[i] : nums[i];
            max_value = max(max_value, current);
        }

        return max_value;
    }
};

int main() {
    Solution solution;

    vector<int> nums1 = {10, 20, 30, 5, 10, 50};
    cout << "Example 1: " << solution.maxAscendingSum(nums1) << endl; // Output: 65

    vector<int> nums2 = {10, 20, 30, 40, 50};
    cout << "Example 2: " << solution.maxAscendingSum(nums2) << endl; // Output: 150

    vector<int> nums3 = {12, 17, 15, 13, 10, 11, 12};
    cout << "Example 3: " << solution.maxAscendingSum(nums3) << endl; // Output: 33

    return 0;
}
