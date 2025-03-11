#include "header.h"

// Given a string s consisting only of characters a, b and c.

// Return the number of substrings containing at least one occurrence of all these characters a, b and c.

// Example 1:
// Input: s = "abcabc"
// Output: 10
// Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 

// Example 2:
// Input: s = "aaacb"
// Output: 3
// Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb". 

// Example 3:
// Input: s = "abc"
// Output: 1

// Constraints:
// 3 <= s.length <= 5 x 10^4
// s only consists of a, b or c characters.

class Solution_1 {
public:
    int numberOfSubstrings(string s) {
        int number = 0;

        for (auto left = begin(s); left != end(s); left++)
        {
            array<int, 3> map = {};
            int abc = 0;
            auto right = left;
            while (right != end(s))
            {
                if (map[*right++ - 'a']++ == 0)
                    abc++;

                if (abc == 3)
                {
                    number += distance(right, end(s)) + 1;
                    break;
                }
            }
        }
        return number;
    }
};

class Solution_2 {
public:
    int numberOfSubstrings(string s) {
        int number = 0;

        auto left = begin(s);
        auto right = begin(s);

        array<int, 3> map = {};
        int abc = 0;

        while (right != end(s))
        {
            if (map[*right++ - 'a']++ == 0)
                abc++;

            while (abc == 3)
            {
                number += distance(right, end(s)) + 1;

                if (--map[*left++ - 'a'] == 0)
                    abc--;
            }
        }
        return number;
    }
};

class Solution {
public:
    int numberOfSubstrings(string s) {
        int number = 0;

        array<int, 3> map = {};
        for (int i = 0; i < size(s); i++)
        {
            map[s[i] - 'a'] = i + 1;
            number += min({map[0], map[1], map[2]});
        }

        return number;
    }
};

int main()
{
    Solution sol;

    cout << sol.numberOfSubstrings("abcabc") << endl; // 10
    cout << sol.numberOfSubstrings("aaacb") << endl; // 3
    cout << sol.numberOfSubstrings("acb") << endl; // 1
    cout << sol.numberOfSubstrings("acbbcac") << endl; // 11
}
