#include "header.h"

// Given an integer array nums of unique elements, return all possible 
// subsets (the power set).

// The solution set must not contain duplicate subsets. Return the solution in any order.

// Example 1:
// Input: nums = [1,2,3]
// Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

// Example 2:
// Input: nums = [0]
// Output: [[],[0]]

// Constraints:

// 1 <= nums.length <= 10
// -10 <= nums[i] <= 10
// All the numbers of nums are unique.

class Solution {
    void gen(vector<vector<int>>& result, const vector<int>& nums, vector<int> vec, int num_i)
    {
        result.push_back(vec);

        vec.resize(vec.size() + 1);
        for (int i = num_i; i < std::size(nums); i++)
        {
            vec.back() = nums[i];
            gen(result, nums, vec, i + 1);
        }
    }
public:
    vector<vector<int>> subsets(const vector<int>& nums) {
        vector<vector<int>> result;
        gen(result, nums, {}, 0);
        return result;
    }
};

// class Solution {
// public:
//     vector<vector<int>> subsets(vector<int>& nums) {
//         vector<vector<int>> output;
//         output.push_back({});
//         for (int num : nums) {
//             vector<vector<int>> newSubsets;
//             for (vector<int> curr : output) {
//                 vector<int> temp = curr;
//                 temp.push_back(num);
//                 newSubsets.push_back(temp);
//             }
//             for (vector<int> curr : newSubsets) {
//                 output.push_back(curr);
//             }
//         }
//         return output;
//     }
// };

// class Solution {
// public:
//     vector<vector<int>> output;
//     int n;
    
//     void backtrack(int first, vector<int> curr, vector<int>& nums) {
//         // Add the current combination to the output
//         output.push_back(curr);
        
//         // Explore further combinations
//         for (int i = first; i < n; ++i) {
//             // Add the next element to the current combination
//             curr.push_back(nums[i]);
//             // Recurse to form the next combination
//             backtrack(i + 1, curr, nums);
//             // Backtrack and remove the last element
//             curr.pop_back();
//         }
//     }
    
//     vector<vector<int>> subsets(vector<int>& nums) {
//         n = nums.size();
//         vector<int> curr;
//         backtrack(0, curr, nums); // Call once to generate all subsets
//         return output;
//     }
// };

int main()
{
    Solution_1 sol;

    print_2D_line(sol.subsets({1,2,3}));
    print_2D_line(sol.subsets({0}));
}