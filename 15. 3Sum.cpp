#include "header.h"

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        ranges::sort(nums);
        vector<vector<int>> result;

        for (auto i = begin(nums); i != end(nums); i++)
        {
            if (i != begin(nums) && *i == *(i - 1))
                continue;

            auto left = i + 1;
            auto right = end(nums) - 1;

            while (left < right)
                if (auto comp = *i + *left + *right; comp > 0)
                    right--;
                else if (comp < 0)
                    left++;
                else
                {
                    result.push_back({*i, *left, *right});
                    for (auto temp_left = *left; left < right && temp_left == *++left;);
                    for (auto temp_right = *right; left < right && temp_right == *--right;);
                }
        }

        return result;
    }
};

void printResult(const vector<vector<int>>& result) {
    cout << "[";
    for (const auto& triplet : result) {
        cout << "[";
        for (const auto& num : triplet) {
            cout << num << ",";
        }
        cout << "],";
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;

    vector<int> nums1 = {-1, 0, 1, 2, -1, -4};
    printResult(sol.threeSum(nums1));

    vector<int> nums2 = {0, 1, 1};
    printResult(sol.threeSum(nums2));

    vector<int> nums3 = {0, 0, 0};
    printResult(sol.threeSum(nums3));

    return 0;
}