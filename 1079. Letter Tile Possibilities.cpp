#include "header.h"

// You have n tiles, where each tile has one letter tiles[i] printed on it.

// Return the number of possible non-empty sequences of letters you can make using the letters printed on those tiles.

// Example 1:

// Input: tiles = "AAB"
// Output: 8
// Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".
// Example 2:

// Input: tiles = "AAABBC"
// Output: 188
// Example 3:

// Input: tiles = "V"
// Output: 1

// Constraints:

// 1 <= tiles.length <= 7
// tiles consists of uppercase English letters.

class Solution {
    int tiles_len(string& tiles, int n)
    {
        
    }

public:
    int numTilePossibilities(string tiles) {
        int n = size(tiles);
        int sum = 0;
        for (int i = 1; i < n; i++)
        {

        }
        return sum;
    }
};

int main()
{
    Solution sol;

    cout << sol.numTilePossibilities("AAB") << endl;
    cout << sol.numTilePossibilities("AAABBC") << endl;
    cout << sol.numTilePossibilities("V") << endl;
}