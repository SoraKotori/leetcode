#include "header.h"

class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        int diff[2];
        int diff_index = 0;

        for (int i = 0, n = size(s1); i < n; i++)
            if (s1[i] != s2[i])
                if (diff_index < 2)
                    diff[diff_index++] = i;
                else
                    return false;

        if (diff_index == 0) return true;
        if (diff_index == 1) return false;

        return s1[diff[0]] == s2[diff[1]] &&
               s1[diff[1]] == s2[diff[0]];
    }
};

int main() {
    Solution solution;
    
    // Example 1
    string s1 = "bank";
    string s2 = "kanb";
    cout << (solution.areAlmostEqual(s1, s2) ? "true" : "false") << endl; // Output: true

    // Example 2
    s1 = "attack";
    s2 = "defend";
    cout << (solution.areAlmostEqual(s1, s2) ? "true" : "false") << endl; // Output: false

    // Example 3
    s1 = "kelb";
    s2 = "kelb";
    cout << (solution.areAlmostEqual(s1, s2) ? "true" : "false") << endl; // Output: true

    return 0;
}

// You are given two strings s1 and s2 of equal length. A string swap is an operation where you choose two indices in a string (not necessarily different) and swap the characters at these indices.

// Return true if it is possible to make both strings equal by performing at most one string swap on exactly one of the strings. Otherwise, return false.

 

// Example 1:

// Input: s1 = "bank", s2 = "kanb"
// Output: true
// Explanation: For example, swap the first character with the last character of s2 to make "bank".
// Example 2:

// Input: s1 = "attack", s2 = "defend"
// Output: false
// Explanation: It is impossible to make them equal with one string swap.
// Example 3:

// Input: s1 = "kelb", s2 = "kelb"
// Output: true
// Explanation: The two strings are already equal, so no string swap operation is required.
