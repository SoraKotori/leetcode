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
    bool backtrack(vector<int>& result, vector<int>& used, int index)
    {
        if (index == size(result))
            return true;

        if (result[index])
            return backtrack(result, used, index + 1);

        for (int number = size(used) - 1; number; number--)
        {
            if (used[number])
                continue;

            used[number] = true;
            result[index] = number;
            if (number == 1)
            {
                if (backtrack(result, used, index + 1)) return true;
            }
            else
            {
                int second = index + number;
                if (second < size(result) && result[second] == 0)
                {
                    result[second] = number;
                    if (backtrack(result, used, index + 1)) return true;
                    result[second] = 0;
                }
            }
            result[index] = 0;
            used[number] = false;
        }

        return false;
    }
public:
    vector<int> constructDistancedSequence(int n) {

        vector<int> used(n + 1);
        vector<int> result(n * 2 - 1);

        backtrack(result, used, 0);
        return result;
    }
};

class Solution_2 {
public:
    vector<int> constructDistancedSequence(int targetNumber) {
        // Initialize the result sequence with size 2*n - 1 filled with 0s
        vector<int> resultSequence(targetNumber * 2 - 1, 0);

        // Keep track of which numbers are already placed in the sequence
        vector<bool> isNumberUsed(targetNumber + 1, false);

        // Start recursive backtracking to construct the sequence
        findLexicographicallyLargestSequence(0, resultSequence, isNumberUsed,
                                                targetNumber);

        return resultSequence;
    }

private:
    // Recursive function to generate the desired sequence
    bool findLexicographicallyLargestSequence(int currentIndex,
                                                vector<int>& resultSequence,
                                                vector<bool>& isNumberUsed,
                                                int targetNumber) {
        // If we have filled all positions, return true indicating success
        if (currentIndex == resultSequence.size()) {
            return true;
        }

        // If the current position is already filled, move to the next index
        if (resultSequence[currentIndex] != 0) {
            return findLexicographicallyLargestSequence(
                currentIndex + 1, resultSequence, isNumberUsed, targetNumber);
        }

        // Attempt to place numbers from targetNumber to 1 for a
        // lexicographically largest result
        for (int numberToPlace = targetNumber; numberToPlace >= 1;
                numberToPlace--) {
            if (isNumberUsed[numberToPlace]) continue;

            isNumberUsed[numberToPlace] = true;
            resultSequence[currentIndex] = numberToPlace;

            // If placing number 1, move to the next index directly
            if (numberToPlace == 1) {
                if (findLexicographicallyLargestSequence(
                        currentIndex + 1, resultSequence, isNumberUsed,
                        targetNumber)) {
                    return true;
                }
            }
            // Place larger numbers at two positions if valid
            else if (currentIndex + numberToPlace < resultSequence.size() &&
                        resultSequence[currentIndex + numberToPlace] == 0) {
                resultSequence[currentIndex + numberToPlace] = numberToPlace;

                if (findLexicographicallyLargestSequence(
                        currentIndex + 1, resultSequence, isNumberUsed,
                        targetNumber)) {
                    return true;
                }

                // Undo the placement for backtracking
                resultSequence[currentIndex + numberToPlace] = 0;
            }

            // Undo current placement and mark the number as unused
            resultSequence[currentIndex] = 0;
            isNumberUsed[numberToPlace] = false;
        }

        return false;
    }
};

int main()
{
    Solution sol;

    print_1D(sol.constructDistancedSequence(3));
    print_1D(sol.constructDistancedSequence(5));
    print_1D(sol.constructDistancedSequence(7));
    print_1D(sol.constructDistancedSequence(9));
    print_1D(sol.constructDistancedSequence(11));
    print_1D(sol.constructDistancedSequence(17));
    print_1D(sol.constructDistancedSequence(19));
}