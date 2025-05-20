#include "header.h"

// Given a list of dominoes, dominoes[i] = [a, b] is equivalent to dominoes[j] = [c, d] if and only if either (a == c and b == d), or (a == d and b == c) - that is, one domino can be rotated to be equal to another domino.

// Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length, and dominoes[i] is equivalent to dominoes[j].

// Example 1:
// Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
// Output: 1

// Example 2:
// Input: dominoes = [[1,2],[1,2],[1,1],[1,2],[2,2]]
// Output: 3

// Constraints:
// 1 <= dominoes.length <= 4 * 10^4
// dominoes[i].length == 2
// 1 <= dominoes[i][j] <= 9

class Solution {
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        array<int, 154> map{};

        auto count = 0;
        for (const auto& vec : dominoes)
            if (vec[0] < vec[1])
                count += map[vec[0] + (vec[1] << 4)]++;
            else
                count += map[(vec[0] << 4) + vec[1]]++;

        return count;
    }
};

#include <print>

int main()
{
    Solution sol;
    {
        vector<vector<int>> dominoes{{1,2},{2,1},{3,4},{5,6}};
        println("{}", sol.numEquivDominoPairs(dominoes));
    }
    {
        vector<vector<int>> dominoes{{1,2},{1,2},{1,1},{1,2},{2,2}};
        println("{}", sol.numEquivDominoPairs(dominoes));
    }
    {
        vector<vector<int>> dominoes{{2,1},{5,4},{3,7},{6,2},{4,4},{1,8},{9,6},{5,3},{7,4},{1,9},{1,1},{6,6},{9,6},{1,3},{9,7},{4,7},{5,1},{6,5},{1,6},{6,1},{1,8},{7,2},{2,4},{1,6},{3,1},{3,9},{3,7},{9,1},{1,9},{8,9}};
        println("{}", sol.numEquivDominoPairs(dominoes));
    }
}