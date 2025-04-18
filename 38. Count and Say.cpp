#include "header.h"
// The count-and-say sequence is a sequence of digit strings defined by the recursive formula:

// countAndSay(1) = "1"
// countAndSay(n) is the run-length encoding of countAndSay(n - 1).
// Run-length encoding (RLE) is a string compression method that works by replacing consecutive identical characters (repeated 2 or more times) with the concatenation of the character and the number marking the count of the characters (length of the run). For example, to compress the string "3322251" we replace "33" with "23", replace "222" with "32", replace "5" with "15" and replace "1" with "11". Thus the compressed string becomes "23321511".

// Given a positive integer n, return the nth element of the count-and-say sequence.

// Example 1:
// Input: n = 4
// Output: "1211"
// Explanation:
// countAndSay(1) = "1"
// countAndSay(2) = RLE of "1" = "11"
// countAndSay(3) = RLE of "11" = "21"
// countAndSay(4) = RLE of "21" = "1211"

// Example 2:
// Input: n = 1
// Output: "1"
// Explanation:
// This is the base case.

// Constraints:
// 1 <= n <= 30

// Follow up: Could you solve it iteratively?

class Solution {
public:
    string countAndSay(int n) {
        if (n == 1)
            return "1";
        
        string result;

        auto string = countAndSay(n - 1);
        auto prev = string[0];
        int count = 1;
        for (int i = 1; i < size(string); i++)
        {
            if (string[i] == prev)
            {
                count++;
                continue;
            }

            result += to_string(count);
            result += prev;

            prev = string[i];
            count = 1;
        }

        result += to_string(count);
        result += prev;

        return result;
    }
};

int main()
{
    Solution sol;
    cout << sol.countAndSay(1) << endl;
    cout << sol.countAndSay(2) << endl;
    cout << sol.countAndSay(3) << endl;
    cout << sol.countAndSay(4) << endl;
}