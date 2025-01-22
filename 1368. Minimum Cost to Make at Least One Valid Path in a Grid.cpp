#include "header.h"

template <typename Container>
void print1D(const Container& container) {
    for (const auto& value : container) {
            cout << setw(3) << value.first;
    }
    cout << "\n-----------------" << endl;
}

void print2D(const vector<unsigned int>& grid_cost, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            cout << grid_cost[i * n + j] << " ";
        cout << endl;
    }
    cout << "-----------------" << endl;
}

void print2D(const vector<vector<int>>& grid_cost) {
    for (auto& sub_cost : grid_cost) {
        for (auto cost : sub_cost)
            cout << cost << " ";
        cout << endl;
    }
    cout << "-----------------" << endl;
}

class Solution {
public:
    virtual int minCost(vector<vector<int>>& grid) = 0;
};

class Solution_priority_queue {
public:
    int minCost(vector<vector<int>>& grid) {

        // cost, vertex
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> queue(greater{});
        queue.push(make_pair(0, 0));

        auto m = size(grid);
        auto n = size(grid[0]);

        vector<unsigned int> grid_cost(m * n, -1);
        grid_cost[0] = 0;

        auto top = queue.top();
        for (auto last_vertex = m * n - 1; top.second != last_vertex; top = queue.top())
        {
            auto [cost, vertex] = top;
            queue.pop();

            auto push = [&](auto i, auto j, auto adj_cost)
            {
                if (i < 0 || j < 0 || i == m || j == n)
                    return;

                auto adj_vertex = i * n + j;
                auto new_cost = cost + adj_cost;
                if  (new_cost >= grid_cost[adj_vertex])
                    return;
                grid_cost[adj_vertex] = new_cost;

                queue.push(make_pair(new_cost, adj_vertex));
            };

            auto [i, j] = std::div(vertex, n);
            for (int move = 1; move <= 4; move++)
            {
                int adj_cost = grid[i][j] == move ? 0 : 1;

                switch (move)
                {
                    case 1:
                        push(i, j + 1, adj_cost);
                        break;
                    case 2:
                        push(i, j - 1, adj_cost);
                        break;
                    case 3:
                        push(i + 1, j, adj_cost);
                        break;
                    case 4:
                        push(i - 1, j, adj_cost);
                        break;
                }
            }
        }

        return top.first;
    }
};

class Solution_0_1_BFS {
public:
    int minCost(vector<vector<int>>& grid) {

        deque<pair<int, int>> queue{make_pair(0, 0)};

        const auto m = size(grid);
        const auto n = size(grid.front());

        vector<int> grid_cost(m * n, numeric_limits<int>::max());
        grid_cost.front() = 0;

        array row_dirs = {0, 0, 1, -1};
        array col_dirs = {1, -1, 0, 0};

        while (!queue.empty())
        {
            auto [row, col] = queue.front();
            queue.pop_front();

            auto adj_cost = 0;
            for (int dir = grid[row][col] - 1, dir_end = dir + 4; dir < dir_end; dir++)
            {
                auto i = row + row_dirs[dir % 4];
                auto j = col + col_dirs[dir % 4];

                if (0 <= i && 0 <= j && i < m && j < n &&
                    grid_cost[i * n + j] > grid_cost[row * n + col] + adj_cost) {
                    grid_cost[i * n + j] = grid_cost[row * n + col] + adj_cost;

                    if (adj_cost)
                        queue.emplace_back(i, j);
                    else
                        queue.emplace_front(i, j);
                }
                adj_cost = 1;
            }
        }

        return grid_cost.back();
    }
};

class Solution_leetcode {
private:
    // Direction vectors: right, left, down, up (matching grid values 1,2,3,4)
    const vector<vector<int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

public:
    int minCost(vector<vector<int>>& grid) {
        int numRows = grid.size(), numCols = grid[0].size(), cost = 0;

        // Track minimum cost to reach each cell
        vector<vector<int>> minCost(numRows, vector<int>(numCols, INT_MAX));

        // Queue for BFS part - stores cells that need cost increment
        queue<pair<int, int>> queue;

        // Start DFS from origin with cost 0
        dfs(grid, 0, 0, minCost, cost, queue);

        // BFS part - process cells level by level with increasing cost
        while (!queue.empty()) {
            cost++;
            int levelSize = queue.size();

            while (levelSize-- > 0) {
                auto [row, col] = queue.front();
                queue.pop();

                // Try all 4 directions for next level
                for (int dir = 0; dir < 4; dir++) {
                    dfs(grid, row + dirs[dir][0], col + dirs[dir][1], minCost,
                        cost, queue);
                }
            }
        }

        return minCost[numRows - 1][numCols - 1];
    }

private:
    // DFS to explore all reachable cells with current cost
    void dfs(vector<vector<int>>& grid, int row, int col,
             vector<vector<int>>& minCost, int cost,
             queue<pair<int, int>>& queue) {
        if (!isUnvisited(minCost, row, col)) return;

        minCost[row][col] = cost;
        queue.push({row, col});

        // Follow the arrow direction without cost increase
        int nextDir = grid[row][col] - 1;
        dfs(grid, row + dirs[nextDir][0], col + dirs[nextDir][1], minCost, cost,
            queue);
    }

    // Check if cell is within bounds and unvisited
    bool isUnvisited(vector<vector<int>>& minCost, int row, int col) {
        return row >= 0 && col >= 0 && row < minCost.size() &&
               col < minCost[0].size() && minCost[row][col] == INT_MAX;
    }
};

class Solution_DFS : public Solution {
    array<pair<int, int>, 4> dirs = {{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}};
public:
    auto dfs(vector<vector<int>>& grid,
             vector<vector<int>>& costs,
             deque<pair<int, int>>& queue,
             int row,
             int col,
             int cost)
    {
        while (0 <= row && row < size(grid) && 
               0 <= col && col < size(grid[0]) &&
               costs[row][col] > cost)
        {
            auto  [dir_row, dir_col] = dirs[grid[row][col] - 1];
            row += dir_row;
            col += dir_col;

            costs[row][col] = cost;
            queue.emplace_back(row, col);
        }
    }

    int minCost(vector<vector<int>>& grid) {

        deque<pair<int, int>> queue;

        vector<vector<int>> costs(size(grid) , vector<int>(size(grid[0]), numeric_limits<int>::max()));

        dfs(grid, costs, queue, 0, 0, 0);

        while (!queue.empty())
        {
            auto [row, col] = queue.front();
            queue.pop_front();

            for (auto dir = grid[row][col] - 1, end = dir + 3; dir < end; dir++)
            {
                auto [dir_row, dir_col] = dirs[dir % 4];
                dfs(grid, costs, queue, row + dir_row, col + dir_col, costs[row][col] + 1);
                print2D(costs);
            }
        }

        return costs.back().back();
    }
};

TEST(Solution_DFS, minCost)
{
    Solution_DFS sol;

    vector<vector<int>> grid1 = {{1,1,3}, {3,2,2}, {1,1,4}};
    EXPECT_EQ(sol.minCost(grid1), 0);

    vector<vector<int>> grid2 = {{2,2,2}, {2,2,2}};
    EXPECT_EQ(sol.minCost(grid2), 3);
}
