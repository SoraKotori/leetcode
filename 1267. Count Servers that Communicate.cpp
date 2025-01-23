#include "header.h"

class Solution1 {
public:
    int countServers(vector<vector<int>>& grid) {
        auto m = size(grid);
        auto n = size(grid[0]);

        vector<vector<pair<int, int>>> row(m);
        vector<vector<pair<int, int>>> col(n);

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                {
                    row[i].emplace_back(i, j);
                    col[j].emplace_back(i, j);
                }

        int communicate = 0;
        for (const auto& line : row)
            if (size(line) > 1)
            {
                for (auto [i, j] : line)
                {
                    if (grid[i][j])
                    {
                        communicate++;
                        grid[i][j] = 0;
                    }
                }
            }

        for (const auto& line : col)
            if (size(line) > 1)
            {
                for (auto [i, j] : line)
                {
                    if (grid[i][j])
                    {
                        communicate++;
                        grid[i][j] = 0;
                    }
                }
            }

        return communicate;
    }
};

class Solution2 {
public:
    int countServers(vector<vector<int>>& grid) {
        auto m = size(grid);
        auto n = size(grid[0]);

        int communicate = 0;
        for (int i = 0; i < m; i++)
        {
            int count = 0;
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                    count++;
            if (count < 2)
                continue;

            communicate += count;
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                    grid[i][j] = 2;
        }

        for (int j = 0; j < n; j++)
        {
            int count = 0;
            for (int i = 0; i < m; i++)
                if (grid[i][j])
                    count++;
            if (count < 2)
                continue;

            for (int i = 0; i < m; i++)
                if (grid[i][j] == 1)
                    communicate++;
        }

        return communicate;
    }
};

class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        auto m = size(grid);
        auto n = size(grid[0]);

        vector<int> row_last(m, -1);
        vector<int> col_count(n);

        int communicate = 0;
        for (int i = 0; i < m; i++)
        {
            auto row_count = 0;
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j])
                {
                    row_count++;
                    col_count[j]++;
                    row_last[i] = j;
                }
            }

            if (row_count > 1)
            {
                communicate += row_count;
                row_last[i] = -1;
            }
        }

        for (int i = 0; i < m; i++)
            if (row_last[i] >= 0 && col_count[row_last[i]] > 1)
                communicate++;

        return communicate;
    }
};

int main() {
    Solution solution;
    vector<vector<int>> grid = {
        {0, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {1, 0, 0, 1, 1},
        {0, 0, 1, 1, 0}
    };

    int result = solution.countServers(grid);
    cout << "Number of servers that communicate: " << result << endl;

    return 0;
}