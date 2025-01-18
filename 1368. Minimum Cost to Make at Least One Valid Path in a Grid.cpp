#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <iomanip>
#include <queue>
#include <functional>

using namespace std;

// Function to print the grid_cost
void printGridCost(const vector<vector<int>>& grid_cost) {
    for (const auto& row : grid_cost) {
        for (int cost : row) {
            cout << cost << " ";
        }
        cout << endl;
    }
    cout << "-----------------" << endl;
}

void printGridCost2(const vector<unsigned int>& grid_cost, int m, int n) {
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

int main() {
    Solution_priority_queue solution;
    vector<vector<int>> grid = {
        {3, 4, 3}, {2, 2, 2}, {2, 1, 1}, {4, 3, 2}, {2, 1, 4}, {2, 4, 1}, {3, 3, 3},
        {1, 4, 2}, {2, 2, 1}, {2, 1, 1}, {3, 3, 1}, {4, 1, 4}, {2, 1, 4}, {3, 2, 2},
        {3, 3, 1}, {4, 4, 1}, {1, 2, 2}, {1, 1, 1}, {1, 3, 4}, {1, 2, 1}, {2, 2, 4},
        {2, 1, 3}, {1, 2, 1}, {4, 3, 2}, {3, 3, 4}, {2, 2, 1}, {3, 4, 3}, {4, 2, 3},
        {4, 4, 4}
    };

    int result = solution.minCost(grid);
    cout << "The minimum cost to make at least one valid path is: " << result << endl;

    return 0;
}