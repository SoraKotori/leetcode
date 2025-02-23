#include "header.h"

// You are given a 0-indexed string pattern of length n consisting of the characters 'I' meaning increasing and 'D' meaning decreasing.

// A 0-indexed string num of length n + 1 is created using the following conditions:

// num consists of the digits '1' to '9', where each digit is used at most once.
// If pattern[i] == 'I', then num[i] < num[i + 1].
// If pattern[i] == 'D', then num[i] > num[i + 1].
// Return the lexicographically smallest possible string num that meets the conditions.

// Example 1:
// Input: pattern = "IIIDIDDD"
// Output: "123549876"
// Explanation:
// At indices 0, 1, 2, and 4 we must have that num[i] < num[i+1].
// At indices 3, 5, 6, and 7 we must have that num[i] > num[i+1].
// Some possible values of num are "245639871", "135749862", and "123849765".
// It can be proven that "123549876" is the smallest possible num that meets the conditions.
// Note that "123414321" is not possible because the digit '1' is used more than once.

// Example 2:
// Input: pattern = "DDD"
// Output: "4321"
// Explanation:
// Some possible values of num are "9876", "7321", and "8742".
// It can be proven that "4321" is the smallest possible num that meets the conditions.

// Constraints:

// 1 <= pattern.length <= 8
// pattern consists of only the letters 'I' and 'D'.

class Solution_1 {
    string result;
    std::array<bool, 10> array{};

    bool gen(string& pattern, string nums, int pattern_i)
    {   
        if (pattern_i == size(pattern))
        {
            result = nums;
            return true;
        }

        if ('I' == pattern[pattern_i])
        {
            for (char c = nums.back() + 1; c <= '9'; c++)
            {
                if (array[c - '0'] == false)
                {
                    array[c - '0'] = true;
                    nums.push_back(c);
                    if (gen(pattern, nums, pattern_i + 1))
                        return true;
                    nums.pop_back();
                    array[c - '0'] = false;
                }
            }
        }
        else
        {
            for (char c = nums.back() - 1; c >= '1'; c--)
            {
                if (array[c - '0'] == false)
                {
                    array[c - '0'] = true;
                    nums.push_back(c);
                    if (gen(pattern, nums, pattern_i + 1))
                        return true;
                    nums.pop_back();
                    array[c - '0'] = false;
                }                
            }
        }

        return false;
    }
public:
    string smallestNumber(string pattern) {
        
        for (int i = 1; i <= 9; i++)
        {
            array[i] = true;
            if (gen(pattern, to_string(i), 0))
                return result;
            array[i] = false;
        }

        return "";
    }
};

// IDIDIDID
// 132547698
class Solution_2 {
public:
    string smallestNumber(string pattern) {
        auto n = size(pattern);

        vector<char> prefix(size(pattern));
        for (int i = 0, D_count = 0; i < n; i++)
            prefix[i] = pattern[i] == 'D' ? ++D_count : D_count;

        string result(size(pattern) + 1, '0');

        auto small = '1';
        auto pre_D = 0;
        for (int i = 0; i < n; i++)
        {
            if (pattern[i] == 'D')
                continue;

            result[i] = small++;
            for (auto diff = prefix[i] - pre_D, j = 1; j <= diff; j++)
            {
                result[i - j] = small++;
            }

            pre_D = prefix[i];
        }

        for (auto diff = prefix[n - 1] - pre_D, j = 0; j <= diff; j++)
        {
            result[n - j] = small++;
        }

        return result;
    }
};

class Solution {
public:
    string smallestNumber(string pattern) {
        vector<int> prefix(size(pattern));
        string result(size(pattern) + 1, '0');

        for (int n = 0, i = size(pattern); i--;)
            prefix[i] = pattern[i] == 'D' ? ++n : (n = 0);

        auto d_max = 0;
        auto current_max = '1';
        for (int i = 0; i < size(pattern); i++)
        {
            if (pattern[i] == 'I')
            {
                result[i] = current_max++;
                if (d_max)
                {
                    current_max += d_max;
                    d_max = 0;
                }
            }
            else
            {
                result[i] = current_max + prefix[i];
                if (d_max == 0)
                    d_max = prefix[i];
            }
        }
        result.back() = current_max;
        return result;
    }
};

int main()
{
    Solution sol;

    cout << sol.smallestNumber("IIIDIDDD") << endl;
    cout << sol.smallestNumber("DDD") << endl;
    cout << sol.smallestNumber("DDDIII") << endl;
}