#include "header.h"

// Given an integer n, find a sequence that satisfies all of the following:

// The integer 1 occurs once in the sequence.
// Each integer between 2 and n occurs twice in the sequence.
// For every integer i between 2 and n, the distance between the two occurrences of i is exactly i.
// The distance between two numbers on the sequence, a[i] and a[j], is the absolute difference of their indices, |j - i|.

// Return the lexicographically largest sequence. It is guaranteed that under the given constraints, there is always a solution.

// A sequence a is lexicographically larger than a sequence b (of the same length) if in the first position where a and b differ, sequence a has a number greater than the corresponding number in b. For example, [0,1,9,0] is lexicographically larger than [0,1,5,6] because the first position they differ is at the third number, and 9 is greater than 5.

// Example 1:
// Input: n = 3
// Output: [3,1,2,3,2]
// Explanation: [2,3,2,1,3] is also a valid sequence, but [3,1,2,3,2] is the lexicographically largest valid sequence.

// Example 2:
// Input: n = 5
// Output: [5,3,1,4,3,5,2,4,2]

// Constraints:

// 1 <= n <= 20

class Solution {
    vector<int> result;

    bool gen(vector<int> current, deque<int> other, int curr_i)
    {
        if (curr_i == size(current))
        {
            result = current;
            return true;
        }
        else if (current[curr_i])
        {
            if (gen(current, other, curr_i + 1));
                return true;
        }

        for (int i = 0; i < size(other); i++)
        {
            int num = other[i];
            if (num == 1)
            {
                auto new_current = current;
                auto new_other = other;                
                new_current[curr_i] = num;
                new_other.erase(begin(new_other) + i);
                if (gen(new_current, new_other, curr_i + 1));
                    return true;
            }
            else
            {
                int curr_j = curr_i + num;
                if (curr_j >= size(current) || current[curr_j])
                    continue;

                auto new_current = current;
                auto new_other = other;
                new_current[curr_i] = num;
                new_current[curr_j] = num;
                new_other.erase(begin(new_other) + i);
                if (gen(new_current, new_other, curr_i + 1));
                    return true;
            }
        }

        return false;
    }
public:
    vector<int> constructDistancedSequence(int n) {

        deque<int> other(n);
        for (int i = 0; i < n; i++)
            other[i] = n - i;

        gen(vector<int>(n * 2 - 1), other, 0);
        return result;
    }
};

int main()
{
    Solution sol;

    // print_1D(sol.constructDistancedSequence(3));
    print_1D(sol.constructDistancedSequence(5));
    print_1D(sol.constructDistancedSequence(7));
}