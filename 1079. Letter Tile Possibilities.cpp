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

class Solution_4 {
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

class Solution_5 {
    using array_t = array<int, 26>;
    int backtrack(array_t& array, vector<int>& factorial, int size, int start)
    {
        auto total = factorial[size];
        auto sub_total = 0;
        for (auto i = 0; i < 26; i++)
        {
            auto& count = array[i];
            if (count == 0)
                continue;
            
            total /= factorial[count];

            if (start <= i)
            {
                count--;
                sub_total += backtrack(array, factorial, size - 1, i);
                count++;
            }
        }
        cout << "total:" << total << " sub_total:" << sub_total << endl;
        return total + sub_total;
    }
public:
    int numTilePossibilities(string tiles) {
        array_t array{};
        vector<int> factorial(size(tiles) + 1);

        for (auto c : tiles)
            array[c - 'A']++;

        for (auto i = 1, n = 1; i <= size(tiles); i++)
            factorial[i] = n *= i;
        
        return backtrack(array, factorial, size(tiles), 0);
    }
};

// A2 B1
// A1 B1
// B1
// A1
// A2

// AAB 3! / 2! = 3      AAB ABA BAA
//  AB 2! = 2            AB BA
//   B = 1                B
//  A  = 1                A
// AA   2! / 2! = 1       AA
//  A

class Solution_6 {
    using array_t = array<int, 26>;
    int backtrack(const array_t& array, const vector<int>& factorial, int index, int size, int repeat)
    {
        if (index == array.size())
            return factorial[size] / repeat;

        auto num = backtrack(array, factorial, index + 1, size, repeat); // i = 0
        for (int i = 1; i <= array[index]; i++)
            num += backtrack(array, factorial, index + 1, size + i, repeat * factorial[i]);
        return num; 
    }
public:
    int numTilePossibilities(string tiles) {
        array_t array{};
        vector<int> factorial(size(tiles) + 1);

        for (auto c : tiles)
            array[c - 'A']++;

        for (auto i = 1, n = 1; i <= size(tiles); i++)
            factorial[i] = n *= i;
        
        return backtrack(array, factorial, 0, 0, 1);
    }
};

static int cc = 0;
class Solution {
public:
    int numTilePossibilities(string tiles) {
        int ans = 0;
        
        array<int, 26> freq = {};
        for (char c : tiles)
            freq[c - 'A']++;

        array<int, 8> fac = {1};
        for (int n = 1; n < fac.size(); n++)
            fac[n] = n * fac[n-1];

        auto C = [&](int n, int k) -> int {
            // assert(k <= n);
            return fac[n] / (fac[k] * fac[n - k]);
        };

        vector<array<int, 26>> dp(tiles.size() + 1);
        ranges::fill(ranges::join_view(dp), -1);

        auto dfs = [&](this const auto &self, int pos, int spaces) -> int {
            if (pos >= freq.size())
                return spaces == 0;

            if (dp[spaces][pos] != -1)
                return dp[spaces][pos];

            int res = 0;

            for (int use = 0; use <= min(spaces, freq[pos]); use++)
                res += C(spaces, use) * self(pos + 1, spaces - use);

            cout << cc++ << endl;
            return dp[spaces][pos] = res;
        };

        for (int spaces = 1; spaces <= tiles.size(); spaces++)
            ans += dfs(0, spaces);

        return ans;
    }
};

int main()
{
    Solution sol;

    // cout << sol.numTilePossibilities("AAB") << endl;
    cout << sol.numTilePossibilities("AAABBC") << endl;
    // cout << sol.numTilePossibilities("V") << endl;
    // cout << sol.numTilePossibilities("CDC") << endl;
}