#include "header.h"

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        for (auto i = begin(numbers), last = end(numbers); i != last; i++)
            if (auto find = lower_bound(i + 1, last, target - *i); find != last && *i + *find == target)
                return {static_cast<int>(distance(begin(numbers), i)) + 1,
                        static_cast<int>(distance(begin(numbers), find)) + 1};

        return {};
    }
};

class Solution_1 {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {

        auto left = begin(numbers);
        auto right = end(numbers) - 1;

        while (left != right)
            if (auto comp = *left + *right <=> target; comp < 0)
                left++;
            else if (comp > 0)
                right--;
            else
                return {static_cast<int>(distance(begin(numbers), left)) + 1,
                        static_cast<int>(distance(begin(numbers), right)) + 1};

        return {};
    }
};

int main() {
    Solution_1 sol1;

    vector<int> numbers1 = {2, 7, 11, 15};
    int target1 = 9;
    vector<int> result1 = sol1.twoSum(numbers1, target1);
    cout << "Example 1: [" << result1[0] << ", " << result1[1] << "]" << endl;

    vector<int> numbers2 = {2, 3, 4};
    int target2 = 6;
    vector<int> result2 = sol1.twoSum(numbers2, target2);
    cout << "Example 2: [" << result2[0] << ", " << result2[1] << "]" << endl;

    vector<int> numbers3 = {-1, 0};
    int target3 = -1;
    vector<int> result3 = sol1.twoSum(numbers3, target3);
    cout << "Example 3: [" << result3[0] << ", " << result3[1] << "]" << endl;

    return 0;
}
