#include "header.h"

// Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.
// You must do it in place.

// Example 1:
// Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
// Output: [[1,0,1],[0,0,0],[1,0,1]]

// Example 2:
// Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
// Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]

// Constraints:
// m == matrix.length
// n == matrix[0].length
// 1 <= m, n <= 200
// -2^31 <= matrix[i][j] <= 2^31 - 1

// Follow up:
// A straightforward solution using O(mn) space is probably a bad idea.
// A simple improvement uses O(m + n) space, but still not the best solution.
// Could you devise a constant space solution?

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        vector<int> rows(size(matrix));
        vector<int> cols(size(matrix[0]));

        for (int i = 0; i < size(matrix); i++)
            for (int j = 0; j < size(matrix[0]); j++)
                if (matrix[i][j] == 0)
                {
                    rows[i] = true;
                    cols[j] = true;
                }

        for (int i = 0; i < size(matrix); i++)
            if (rows[i])
                for (int j = 0; j < size(matrix[0]); j++)
                    matrix[i][j] = 0;

        for (int j = 0; j < size(matrix[0]); j++)
            if (cols[j])
                for (int i = 0; i < size(matrix); i++)
                    matrix[i][j] = 0;
    }
};

int main()
{
    Solution sol;
    {
        vector<vector<int>> matrix = {{1,1,1},{1,0,1},{1,1,1}};
        sol.setZeroes(matrix);
        print_2D_line(matrix);
    }
    {
        vector<vector<int>> matrix = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
        sol.setZeroes(matrix);
        print_2D_line(matrix);
    }    
}
