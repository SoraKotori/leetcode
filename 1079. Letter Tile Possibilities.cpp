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
    int gen(string other)
    {
        int total = 0;
        for (auto chunk : other | views::chunk_by(equal_to{}))
        {
            total++;
            auto str = other;
            str.erase(chunk.begin() - other.begin(), 1);
            total += gen(str);
        }

        return total;
    }

public:
    int numTilePossibilities(string tiles) {
        sort(begin(tiles), end(tiles));
        return gen(tiles);
    }
};

class Solution_1 {
public:
    int numTilePossibilities(string tiles) {
        unordered_set<string> sequences;
        vector<bool> used(tiles.length(), false);

        // Generate all possible sequences including empty string
        generateSequences(tiles, "", used, sequences);

        // Subtract 1 to exclude empty string from count
        return sequences.size() - 1;
    }

private:
    void generateSequences(string& tiles, string current, vector<bool>& used,
                            unordered_set<string>& sequences) {
        // Add current sequence to set
        sequences.insert(current);

        // Try adding each unused character to current sequence
        for (int pos = 0; pos < tiles.length(); ++pos) {
            if (!used[pos]) {
                used[pos] = true;
                generateSequences(tiles, current + tiles[pos], used, sequences);
                used[pos] = false;
            }
        }
    }
};

class Solution_2 {
public:
    int numTilePossibilities(string tiles) {
        // Track frequency of each uppercase letter (A-Z)
        int charCount[26] = {0};
        for (char c : tiles) {
            charCount[c - 'A']++;
        }

        // Find all possible sequences using character frequencies
        return findSequences(charCount);
    }

private:
    int findSequences(int charCount[26]) {
        int totalCount = 0;

        // Try using each available character
        for (int pos = 0; pos < 26; pos++) {
            if (charCount[pos] == 0) {
                continue;
            }

            // Add current character and recurse
            totalCount++;
            charCount[pos]--;
            totalCount += findSequences(charCount);
            charCount[pos]++;
        }

        return totalCount;
    }
};

class Solution_3 {
public:
    int numTilePossibilities(string tiles) {
        unordered_set<string> seen;

        // Sort characters to handle duplicates efficiently
        sort(tiles.begin(), tiles.end());

        // Find all unique sequences and their permutations
        return generateSequences(tiles, "", 0, seen) - 1;
    }

private:
    int factorial(int n) {
        if (n <= 1) {
            return 1;
        }

        int result = 1;
        for (int num = 2; num <= n; num++) {
            result *= num;
        }
        return result;
    }

    int countPermutations(string& seq) {
        // Count frequency of each character
        int charCount[26] = {0};
        for (char ch : seq) {
            charCount[ch - 'A']++;
        }

        // Calculate permutations using factorial formula
        int total = factorial(seq.length());
        for (int count : charCount) {
            if (count > 1) {
                total /= factorial(count);
            }
        }
        return total;
    }

    int generateSequences(string& tiles, string current, int pos,
                            unordered_set<string>& seen) {
        if (pos >= tiles.length()) {
            // If new sequence found, count its unique permutations
            if (seen.insert(current).second) {
                return countPermutations(current);
            }
            return 0;
        }

        // Try including and excluding current character
        return generateSequences(tiles, current,              pos + 1, seen) +
               generateSequences(tiles, current + tiles[pos], pos + 1, seen);
    }
};

int main()
{
    Solution sol;

    cout << sol.numTilePossibilities("AAB") << endl;
    cout << sol.numTilePossibilities("AAABBC") << endl;
    cout << sol.numTilePossibilities("V") << endl;
    cout << sol.numTilePossibilities("CDC") << endl;
    
}