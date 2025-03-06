#include "header.h"

class Solution_1 {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        auto n2 = size(grid) * size(grid);

        vector<bool> map(n2);
        int a = 0;
        for (const auto& row : grid)
            for (auto val : row)
                if (map[val - 1])
                    a = val;
                else
                    map[val - 1] = true;

        int b = 0;
        for (int i = 0; i < n2; i++)
            if (map[i] == false)
            {
                b = i + 1;
                break;
            }

        return {a, b};
    }
};

class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        long sum = 0;
        long sum_sqrt = 0;

        for (const auto& row : grid)
            for (auto val : row)
            {
                sum += val;
                sum_sqrt += val * val;
            }

        long n2 = size(grid) * size(grid);
        long perfect = n2 * (n2 + 1) / 2;
        long perfect_sqrt = n2 * (n2 + 1) * (2 * n2 + 1) / 6;

        int diff = sum - perfect;
        int diff_sqrt = sum_sqrt - perfect_sqrt;

        return {(diff_sqrt / diff + diff) / 2,
                (diff_sqrt / diff - diff) / 2};
    }
};

int main()
{
    Solution sol;
    {
        vector<vector<int>> grid = {{1,3},{2,2}};
        print_1D(sol.findMissingAndRepeatedValues(grid));
    }
    {
        vector<vector<int>> grid = {{9,1,7},{8,9,2},{3,4,6}};
        print_1D(sol.findMissingAndRepeatedValues(grid));
    }
}