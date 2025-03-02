#include "header.h"

class Solution_1 {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int str1Length = str1.length();
        int str2Length = str2.length();

        vector<vector<int>> dp(str1Length + 1, vector<int>(str2Length + 1, 0));

        // Initialize the base cases
        // When str2 is empty, the supersequence is str1 itself
        // (length = row index)
        for (int row = 0; row <= str1Length; row++) {
            dp[row][0] = row;
        }
        // When str1 is empty, the supersequence is str2 itself
        // (length = col index)
        for (int col = 0; col <= str2Length; col++) {
            dp[0][col] = col;
        }

        // Fill the DP table
        for (int row = 1; row <= str1Length; row++) {
            for (int col = 1; col <= str2Length; col++) {
                if (str1[row - 1] == str2[col - 1]) {
                    // If characters match,
                    // inherit the length from the diagonal + 1
                    dp[row][col] = dp[row - 1][col - 1] + 1;
                } else {
                    // If characters do not match,
                    // take the minimum length option + 1
                    dp[row][col] = min(dp[row - 1][col], dp[row][col - 1]) + 1;
                }
            }
        }

        string supersequence = "";
        int row = str1Length, col = str2Length;

        while (row > 0 && col > 0) {
            if (str1[row - 1] == str2[col - 1]) {
                // If characters match, take it from diagonal
                supersequence += str1[row - 1];
                row--;
                col--;
            } else if (dp[row - 1][col] < dp[row][col - 1]) {
                // If str1’s character is part of the supersequence, move up
                supersequence += str1[row - 1];
                row--;
            } else {
                // If str2’s character is part of the supersequence, move left
                supersequence += str2[col - 1];
                col--;
            }
        }

        // Append any remaining characters
        // If there are leftover characters in str1
        while (row > 0) {
            supersequence += str1[row - 1];
            row--;
        }
        // If there are leftover characters in str2
        while (col > 0) {
            supersequence += str2[col - 1];
            col--;
        }

        // Reverse the built sequence to get the correct order
        reverse(supersequence.begin(), supersequence.end());
        return supersequence;
    }
};

class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        vector<vector<int>> dp(size(str1) + 1, vector<int>(size(str2) + 1));

        for (int i = 0; i < size(str1); i++)
            for (int j = 0; j < size(str2); j++)
                dp[i + 1][j + 1] = str1[i] == str2[j] ? dp[i][j] + 1
                                                      : max(dp[i][j + 1], dp[i + 1][j]);


        string result;
        int i = size(str1);
        int j = size(str2);
        while (i && j)
        {
            if      (dp[i][j] == dp[i][j - 1])
                result += str2[--j];
            else if (dp[i][j] == dp[i - 1][j])
                result += str1[--i];
            else
            {
                result += str1[--i];
                j--;
            }
        }
        
        while (i) result += str1[--i];
        while (j) result += str2[--j];

        reverse(begin(result), end(result));
        return result;
    }
};

int main()
{
    Solution sol;

    cout << sol.shortestCommonSupersequence("abac", "cab") << endl; // cabac
    cout << sol.shortestCommonSupersequence("aaaaaaaa", "aaaaaaaa") << endl; // aaaaaaaa
    cout << sol.shortestCommonSupersequence("bbabacaa", "cccababab") << endl; // bbcccabacabab
}