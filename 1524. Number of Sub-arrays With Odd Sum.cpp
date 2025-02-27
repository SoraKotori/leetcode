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
            number = (number + 1) % 1'000'000'007;

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

class Solution_3 {
public:
    int numOfSubarrays(vector<int>& arr) {

        int odds = 0;
        int evens = 0;

        int odd_sum = 0;
        for (int num : arr)
        {
            if (num % 2)
            {
                swap(odds, evens);
                odds = (odds + 1) % 1'000'000'007;
            }
            else
                evens = (evens + 1) % 1'000'000'007;
            odd_sum = (odd_sum + odds) % 1'000'000'007;
        }

        return odd_sum;
    }
};

class Solution_4 {
public:
    int numOfSubarrays(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        int count = 0, prefixSum = 0;
        // evenCount starts as 1 since the initial sum (0) is even
        int oddCount = 0, evenCount = 1;

        for (int num : arr) {
            prefixSum += num;
            // If current prefix sum is even, add the number of odd subarrays
            if (prefixSum % 2 == 0) {
                count += oddCount; // 因為 prefixSum 為偶數，所以要讓找奇數的子陣列來減掉前綴和，才會得到奇數的子陣列
                                   // 若有 oddCount 個奇數子陣列，則每個子陣列減掉前綴和後，總共可以得到 oddCount 個奇數的子陣列
                evenCount++;
            } else {
                // If current prefix sum is odd, add the number of even
                // subarrays
                count += evenCount; // prefixSum 為奇數時，需要找到偶數的子陣列來減掉前綴和，才可以得到奇數的子陣列
                oddCount++;
            }

            count %= MOD;  // To handle large results
        }

        return count;
    }
};

class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        long long oddCount = 0, prefixSum = 0;
        for(int a : arr) {
            prefixSum += a;
            oddCount += prefixSum % 2;
        }
        oddCount += (arr.size() - oddCount) * oddCount; // arr.size() - oddCount 等於 evenCount
                                                        // 偶數的前綴和可以和一個奇數的前綴和相減\差集可以得到一個奇數的子陣列
                                                        // e.g. [1,2,3,4,5,6,7] 和 [1] 可以得到 [2,3,4,5,6,7]
                                                        // e.g. [1,2,3,4,5,6,7] 和 [1,2] 可以得到 [3,4,5,6,7]
                                                        // e.g. [1,2,3,4,5,6,7] 和 [1,2,3,4,5] 可以得到 [6,7]
                                                        // e.g. [1,2,3,4,5,6,7] 和 [1,2,3,4,5,6] 可以得到 [7]
                                                        // e.g. [1,2,3,4] 和 [1] 可以得到 [2,3,4]
                                                        // e.g. [1,2,3,4] 和 [1,2] 可以得到 [3,4]
                                                        // e.g. [1,2,3,4] 和 [1,2,3,4,5] 可以得到 [5]
                                                        // e.g. [1,2,3,4] 和 [1,2,3,4,5,6] 可以得到 [5,6]
                                                        // 總共有 evenCount 的偶數前綴和，和 oddCount 的奇數前綴和
                                                        // 相成獲得總共的奇數的子陣列
        return oddCount % 1'000'000'007;
    }
};

int main()
{
    Solution_4 sol;

    {
        vector<int> arr = {1,3,5}; // 4
        cout << sol.numOfSubarrays(arr) << endl;
    }
    {
        vector<int> arr = {2,4,6}; // 0
        cout << sol.numOfSubarrays(arr) << endl;
    }
    {
        vector<int> arr = {1,2,3,4,5,6,7}; // 16
        cout << sol.numOfSubarrays(arr) << endl;
    }
}