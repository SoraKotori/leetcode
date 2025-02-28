#include "header.h"

class Solution_1 {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(size(text1) + 1, vector<int>(size(text2) + 1));

        for (int i = 0; i < size(text1); i++)
            for (int j = 0; j < size(text2); j++)
                dp[i + 1][j + 1] = text1[i] == text2[j] ?
                    dp[i][j] + 1 : max(dp[i][j + 1], dp[i + 1][j]);
        return dp.back().back();
    }
};

class Solution_2 {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(2, vector<int>(size(text2) + 1));

        for (int i = 0; i < size(text1); i++)
        {
            for (int j = 0; j < size(text2); j++)
                dp[1][j + 1] = text1[i] == text2[j] ?
                    dp[0][j] + 1 : max(dp[0][j + 1], dp[1][j]);
            swap(dp[0], dp[1]);
        }
        return dp[0].back();
    }
};

class Solution_3 {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<int> dp(size(text2) + 1);

        for (char c : text1)
        {
            int prev = 0;
            for (int j = 0; j < size(text2); j++)
            {
                int temp = dp[j + 1];
                dp[j + 1] = c == text2[j] ? prev + 1
                                           : max(dp[j + 1], dp[j]);
                prev = temp;
            }
        }
        return dp.back();
    }
};

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<int> dp(size(text1));
        int longest = 0;

        for (char c : text2)
        {
            int curLength = 0;
            for (int i = 0; i < dp.size(); i++)
                if (curLength < dp[i])
                    curLength = dp[i];
                else if (c == text1[i])
                {
                    dp[i] = curLength + 1;
                    longest = max(longest, curLength + 1);
                }
        }
        return longest;        
    }
};

int main()
{
    Solution sol;

    cout << sol.longestCommonSubsequence("abc", "cab") << endl; // 2
    cout << sol.longestCommonSubsequence("cab", "abc") << endl; // 2
    cout << sol.longestCommonSubsequence("abcde", "ace") << endl; // 3
    cout << sol.longestCommonSubsequence("abc", "abc") << endl; // 3
    cout << sol.longestCommonSubsequence("abc", "def") << endl; // 0
    cout << sol.longestCommonSubsequence("abcba", "abcbcba") << endl; // 5
    cout << sol.longestCommonSubsequence("pmjghexybyrgzczy", "hafcdqbgncrcbihkd") << endl; // 4
    cout << sol.longestCommonSubsequence("bl", "yby") << endl; // 1
}