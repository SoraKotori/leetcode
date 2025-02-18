#include "header.h"

// Given an array nums of distinct integers, return all the possible 
// permutations
// . You can return the answer in any order.

// Example 1:
// Input: nums = [1,2,3]
// Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

// Example 2:
// Input: nums = [0,1]
// Output: [[0,1],[1,0]]
// Example 3:

// Input: nums = [1]
// Output: [[1]]

// Constraints:

// 1 <= nums.length <= 6
// -10 <= nums[i] <= 10
// All the integers of nums are unique.

class Solution {
    void gen(vector<vector<int>>& result, vector<int> nums, vector<int> vec)
    {
        if (size(nums) == 0)
        {
            result.push_back(vec);
            return;
        }

        for (int i = 0; i < size(nums); i++)
        {
            auto new_vec = vec;
            auto new_nums = nums;

            new_vec.push_back(nums[i]);
            new_nums.erase(begin(new_nums) + i);

            gen(result, new_nums, new_vec);
        }
    }
public:
    vector<vector<int>> permute(const vector<int>& nums) {
        vector<vector<int>> result;
        gen(result, nums, {});
        return result;
    }
};

class Solution_1 {
    void gen(vector<vector<int>>& result, vector<int>& vec, int vec_i)
    {
        if (size(vec) == vec_i)
        {
            result.push_back(vec);
            return;
        }

        for (int i = vec_i; i < size(vec); i++)
        {
            swap(vec[vec_i], vec[i]);
            gen(result, vec, vec_i + 1);
            swap(vec[vec_i], vec[i]);
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        gen(result, nums, 0);
        return result;
    }
};

class Solution_2 {

public:
    vector<vector<int>> permute(vector<int>& nums) 
    {
        auto factorial = [](int n)
        {
            std::function<int(int)> fac = [&](int n) { return (n < 2) ? 1 : n * fac(n - 1); };
            return fac(n);
        };

        std::sort(nums.begin(), nums.end());
        vector<vector<int>> result(factorial(nums.size()));
        int i = 0;
        do
        {
            result[i] = nums;
            i++;
        }
        while (std::next_permutation(nums.begin(), nums.end()));
        
        return result;
    }
};

int main()
{
    Solution_2 sol;

    vector<int> vec = {1,2,3};
    print_2D_line(sol.permute(vec));

    vec = {0,1};
    print_2D_line(sol.permute(vec));

    vec = {1};
    print_2D_line(sol.permute(vec));
}