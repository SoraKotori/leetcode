#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <iomanip>
#include <queue>
#include <functional>
#include <queue>
#include <limits>
#include <deque>

using namespace std;

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

class Solution {
    array<pair<int, int>, 4> dirs = {{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}};
public:
    auto dfs(vector<vector<int>>& grid,
            vector<vector<int>>& costs,
            deque<pair<int, int>>& queue,
            int row,
            int col)
    {
        auto m = size(grid);
        auto n = size(grid[0]);
        auto cost = costs[row][col];

        while (true)
        {
            auto  [dir_row, dir_col] = dirs[grid[row][col] - 1];
            row += dir_row;
            col += dir_col;

            if (row < 0 || col < 0 || row == m || col == n ||
                costs[row][col] <= cost)
                break;

            costs[row][col] = cost;
            queue.emplace_front(row, col);
        }
    }

    int minCost(vector<vector<int>>& grid) {

        auto m = size(grid);
        auto n = size(grid[0]);

        deque<pair<int, int>> queue;
        queue.emplace_back(0, 0);

        vector<vector<int>> costs(m , vector<int>(n, numeric_limits<int>::max()));
        costs[0][0] = 0;

        dfs(grid, costs, queue, 0, 0);

        while (!queue.empty())
        {
            auto [row, col] = queue.front();
            queue.pop_front();

            auto dir_cost = 0;
            for (auto dir = grid[row][col] - 1, end = dir + 4; dir < end; dir++)
            {
                auto [dir_row, dir_col] = dirs[dir % 4];

                auto i = row + dir_row;
                auto j = col + dir_col;
                if (i < 0 || j < 0 || i == m || j == n ||
                    costs[i][j] <= costs[row][col] + dir_cost)
                    continue;
                costs[i][j] = costs[row][col] + dir_cost;
                if (dir_cost)
                    queue.emplace_back(i, j);
                else
                    queue.emplace_front(i, j);

                dir_cost = 1;
            }
        }

        return costs[m - 1][n - 1];
    }
};

int main() {
    // Solution_0_1_BFS solution;
    Solution solution;
    vector<vector<int>> grid = {
        {1,1,3}, {3,2,2}, {1,1,4}
    };

    int result = solution.minCost(grid);
    cout << "The minimum cost to make at least one valid path is: " << result << endl;

    return 0;
}