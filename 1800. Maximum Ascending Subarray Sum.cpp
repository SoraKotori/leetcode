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