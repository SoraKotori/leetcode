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

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {

        // cost, vertex
        deque<pair<int, int>> queue{make_pair(0, 0)};

        const auto m = size(grid);
        const auto n = size(grid.front());

        vector<int> grid_cost(m * n, numeric_limits<int>::max());
        grid_cost.front() = 0;

        auto top = queue.front();
        for (auto last_vertex  = m * n - 1;
                  last_vertex != top.second;
             top = queue.front())
        {
            queue.pop_front();

            auto push_adj = [&](auto i, auto j, auto adj_cost)
            {
                auto adj_vertex = i * n + j;
                auto new_cost = top.first + adj_cost;
                if  (new_cost >= grid_cost[adj_vertex])
                    return;
                grid_cost[adj_vertex] = new_cost;

                if (adj_cost)
                    queue.emplace_back(new_cost, adj_vertex);
                else
                    queue.emplace_front(new_cost, adj_vertex);
            };

            auto [i, j] = std::div(top.second, n);
            auto adj_cost = 0;
            for (int move = grid[i][j] - 1, move_end = move + 4; move < move_end; move++)
            {
                switch (move % 4)
                {
                    case 0:
                        if (j + 1 == n) break;
                        push_adj(i, j + 1, adj_cost);
                        break;
                    case 1:
                        if (j - 1 < 0) break;
                        push_adj(i, j - 1, adj_cost);
                        break;
                    case 2:
                        if (i + 1 == m) break;
                        push_adj(i + 1, j, adj_cost);
                        break;
                    case 3:
                        if (i - 1 < 0) break;
                        push_adj(i - 1, j, adj_cost);
                        break;
                }
                adj_cost = 1;
            }
        }
        return top.first;
    }
};

int main() {
    Solution solution;
    vector<vector<int>> grid = {
        {1,1,3}, {3,2,2}, {1,1,4}
    };

    int result = solution.minCost(grid);
    cout << "The minimum cost to make at least one valid path is: " << result << endl;

    return 0;
}