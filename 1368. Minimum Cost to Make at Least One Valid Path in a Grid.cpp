#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <iomanip>
#include <queue>

using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {

        auto m = size(grid);
        auto n = size(grid[0]);

        auto cmp = [](const auto& pair1, const auto& pair2)
        {
            return pair1.first > pair2.first;
        };

        // cost, vertex
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> queue(cmp);
        queue.push(make_pair(0, 0));

        vector<unsigned int> grid_cost(m * n, -1);
        grid_cost[0] = 0;

        auto top = queue.top();
        auto exit = m * n - 1;
        while (top.second != exit)
        {
            auto [cost, vertex] = top;

            auto push = [&](auto i, auto j, auto adj_cost)
            {
                if (i < 0 || j < 0 || i == m || j == n)
                    return;

                auto adj_vertex = i * n + j;
                auto new_cost = cost + adj_cost;
                if  (new_cost >= grid_cost[adj_vertex])
                    return;

                queue.push(make_pair(new_cost, adj_vertex));
            };

            auto res = std::div(vertex, n);
            auto i = res.quot;
            auto j = res.rem;

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

            queue.pop();
            top = queue.top();
        }

        return top.first;
    }
};

int main() {
    Solution solution;
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