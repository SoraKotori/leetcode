#include "header.h"

// Given an array of integers arr, return the number of subarrays with an odd sum.

// Since the answer can be very large, return it modulo 109 + 7.

// Example 1:
// Input: arr = [1,3,5]
// Output: 4
// Explanation: All subarrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
// All sub-arrays sum are [1,4,9,3,8,5].
// Odd sums are [1,9,3,5] so the answer is 4.

// Example 2:
// Input: arr = [2,4,6]
// Output: 0
// Explanation: All subarrays are [[2],[2,4],[2,4,6],[4],[4,6],[6]]
// All sub-arrays sum are [2,6,12,4,10,6].
// All sub-arrays have even sum and the answer is 0.

// Example 3:
// Input: arr = [1,2,3,4,5,6,7]
// Output: 16

// Constraints:
// 1 <= arr.length <= 105
// 1 <= arr[i] <= 100

// 1 1 4 4 9 9 16
// 0 2 2 6 6 12 12

class Solution_1 {
    void backtrack(vector<int>& arr, int arr_index, int sum, int& number)
    {
        if (sum % 2)
            number = (number + 1) % 1'000'000'000;

        if (arr_index == size(arr))
            return;

        backtrack(arr, arr_index + 1, sum + arr[arr_index], number);
    }
public:
    int numOfSubarrays(vector<int>& arr) {
        int number = 0;
        for (int i = 0; i < size(arr); i++)
            backtrack(arr, i, 0, number);
        return number;
    }
};

class Solution_2 {
public:
    int numOfSubarrays(vector<int>& arr) {
        for (auto& num : arr)
            num %= 2;
        
        vector<int> odds(size(arr));
        vector<int> evens(size(arr));
        (arr.back() ? odds.back() : evens.back()) = 1;

        for (int i = size(arr) - 1; i--;)
            if (arr[i])
            {
                odds[i] = (evens[i + 1] + 1) % 1'000'000'007;
                evens[i] = odds[i + 1];
            }
            else
            {
                odds[i] = odds[i + 1];
                evens[i] = (evens[i + 1] + 1) % 1'000'000'007;
            }

        return accumulate(begin(odds), end(odds), 0, [](auto init, auto value)
        {
            return (init + value) % 1'000'000'007;
        });
    }
};

class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        int prefix = 0;

        int odds = 0;
        int evens = 0;

        int num = 0;
        for (int i = 0; i < size(arr); i++)
        {
            prefix = (prefix + arr[i] % 2) % 2;
            if (arr[i])
            {
                num += odds;
                evens++;
            }
            else
            {

            }
        }

        return num;
    }
};
int main()
{
    Solution sol;

    {
        vector<int> arr = {1,3,5};
        cout << sol.numOfSubarrays(arr) << endl;
    }
    {
        vector<int> arr = {2,4,6};
        cout << sol.numOfSubarrays(arr) << endl;
    }
    {
        vector<int> arr = {1,2,3,4,5,6,7};
        cout << sol.numOfSubarrays(arr) << endl;
    }
}