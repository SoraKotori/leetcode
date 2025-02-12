#include "header.h"

class Solution {
public:
    int maximumSum(vector<int>& nums) {
        unordered_map<int, priority_queue<int>> map;

        for (auto num : nums)
        {
            int sum = 0;
            auto str = to_string(num);
            for (auto digit : str)
                sum += digit - '0';

            map[sum].emplace(num);
        }

        int maximux = -1;
        for (auto& [sum, queue] : map)
        {
            if (size(queue) < 2)
                continue;
            auto pair_sum = queue.top();
            queue.pop();
            pair_sum += queue.top();
            maximux = max(maximux, pair_sum);
        }

        return maximux;
    }
};

class Solution_1 {
public:
    int maximumSum(vector<int>& nums) {
        unordered_map<int, pair<int, int>> map;

        for (auto num : nums)
        {
            int sum = 0;
            for (auto digit = num; digit;)
            {
                sum += digit % 10;
                digit /= 10;
            }

            auto& second_max = map[sum].first < map[sum].second ? map[sum].first : map[sum].second;
            if (second_max < num)
                second_max = num;
        }

        int maximux = -1;
        for (auto& [sum, pair] : map)
            if (pair.first && pair.second)
                maximux = max(maximux, pair.first + pair.second);

        return maximux;
    }
};

class Solution_2 {
public:
    int maximumSum(vector<int>& nums) {

        int maximux = -1;
        array<int, 82> map{};

        for (auto num : nums)
        {
            int digit_sum = 0;
            for (auto digit = num; digit; digit /= 10)
                digit_sum += digit % 10;

            if (map[digit_sum])
                maximux = max(maximux, num + map[digit_sum]);

            map[digit_sum] = max(map[digit_sum], num);
        }

        return maximux;
    }
};

int main()
{
    Solution_2 sol;

    vector nums1 = {18, 43, 36, 13, 7};
    cout << "Result1: " << sol.maximumSum(nums1) << endl;

    vector nums2 = {10, 12, 19, 14};
    cout << "Result2: " << sol.maximumSum(nums2) << endl;

    vector nums3 = {4, 6, 10, 6};
    cout << "Result3: " << sol.maximumSum(nums3) << endl;

    vector nums4 = {229,398,269,317,420,464,491,218,439,153,482,169,411,93,147,50,347,210,251,366,401};
    cout << "Result4: " << sol.maximumSum(nums4) << endl;
}

// Example 1:

// Input: nums = [18,43,36,13,7]
// Output: 54
// Explanation: The pairs (i, j) that satisfy the conditions are:
// - (0, 2), both numbers have a sum of digits equal to 9, and their sum is 18 + 36 = 54.
// - (1, 4), both numbers have a sum of digits equal to 7, and their sum is 43 + 7 = 50.
// So the maximum sum that we can obtain is 54.
// Example 2:

// Input: nums = [10,12,19,14]
// Output: -1
// Explanation: There are no two numbers that satisfy the conditions, so we return -1.
