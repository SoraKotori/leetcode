#include "header.h"

// You are given an array of strings words. Each element of words consists of two lowercase English letters.
// Create the longest possible palindrome by selecting some elements from words and concatenating them in any order. Each element can be selected at most once.
// Return the length of the longest palindrome that you can create. If it is impossible to create any palindrome, return 0.
// A palindrome is a string that reads the same forward and backward.

// Example 1:
// Input: words = ["lc","cl","gg"]
// Output: 6
// Explanation: One longest palindrome is "lc" + "gg" + "cl" = "lcggcl", of length 6.
// Note that "clgglc" is another longest palindrome that can be created.

// Example 2:
// Input: words = ["ab","ty","yt","lc","cl","ab"]
// Output: 8
// Explanation: One longest palindrome is "ty" + "lc" + "cl" + "yt" = "tylcclyt", of length 8.
// Note that "lcyttycl" is another longest palindrome that can be created.

// Example 3:
// Input: words = ["cc","ll","xx"]
// Output: 2
// Explanation: One longest palindrome is "cc", of length 2.
// Note that "ll" is another longest palindrome that can be created, and so is "xx".

// Constraints:
// 1 <= words.length <= 105
// words[i].length == 2
// words[i] consists of lowercase English letters.

class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        array<array<pair<int, int>, 26>, 26> diff{};
        array<int, 26> same{};

        int count = 0;
        for (const auto& str : words)
        {
            if (str[0] < str[1])
            {
                auto first = str[0] - 'a';
                auto second = str[1] - 'a';

                auto& pair = diff[first][second];
                if (++pair.first <= pair.second)
                    count += 4;
            }
            else if (str[0] > str[1])
            {
                auto first = str[1] - 'a';
                auto second = str[0] - 'a';

                auto& pair = diff[first][second];
                if (pair.first >= ++pair.second)
                    count += 4;
            }
            else
            {
                auto ch = str[0] - 'a';
                auto cnt = ++same[ch];
            }
        }

        auto one = 0;
        for (auto c : same)
        {
            if (c % 2)
                one = 2;
            if (c > 1)
                count += (c / 2) * 4;
        }

        return count + one;
    }
};

int main()
{
    Solution sol;
    {
        vector<string> words = {"lc","cl","gg"}; // 6
        cout << sol.longestPalindrome(words) << endl;
    }
    {
        vector<string> words = {"ab","ty","yt","lc","cl","ab"}; // 8
        cout << sol.longestPalindrome(words) << endl;
    }
    {
        vector<string> words = {"cc","ll","xx"}; // 2
        cout << sol.longestPalindrome(words) << endl;
    }
    {
        vector<string> words = {"dd","aa","bb","dd","aa","dd","bb","dd","aa","cc","bb","cc","dd","cc"}; // 22
        cout << sol.longestPalindrome(words) << endl;
    }
    {
        vector<string> words = {"em","pe","mp","ee","pp","me","ep","em","em","me"}; // 14
        cout << sol.longestPalindrome(words) << endl;
    }
    {
        vector<string> words = {"nn","nn","hg","gn","nn","hh","gh","nn","nh","nh"}; // 14
        cout << sol.longestPalindrome(words) << endl;
    }
}