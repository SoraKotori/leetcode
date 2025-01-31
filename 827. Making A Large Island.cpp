#include "header.h"

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        auto m = size(grid);
        auto n = size(grid[0]);

        vector<int> parents(m * n);
        ranges::iota(parents, 0);

        auto find_root = [&](auto node)
        {
            for (int root; (root = parents[node]) != node; node = root);
            return node;
        };

        vector<int> island_size(m * n, 1);
        array<pair<int, int>, 4> dirs{{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};

        for (int i = 0 ; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                    for (auto [dir_i, dir_j] : dirs)
                    {
                        auto node_i = i + dir_i;
                        auto node_j = j + dir_j;

                        if (node_i < 0 || m <= node_i ||
                            node_j < 0 || n <= node_j || grid[node_i][node_j] == 0)
                            continue;

                        auto root_0 = find_root(i * n + j);
                        auto root_1 = find_root(node_i * n + node_j);
                        if  (root_1 != root_0)
                        {
                            parents[root_1] = root_0;
                            island_size[root_0] += island_size[root_1];
                        }
                    }

        int max_size = 0;
        for (int i = 0 ; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 0)
                {
                    int island = 1;
                    set<int> island_root;

                    for (auto [dir_i, dir_j] : dirs)
                    {
                        auto node_i = i + dir_i;
                        auto node_j = j + dir_j;

                        if (node_i < 0 || m <= node_i ||
                            node_j < 0 || n <= node_j || grid[node_i][node_j] == 0)
                            continue;

                        auto root = find_root(node_i * n + node_j);

                        if (auto [it, inserted] = island_root.emplace(root); inserted)
                            island += island_size[root];
                    }

                    max_size = max(max_size, island);
                }

        return max_size ? max_size : m * n;
    }
};

int main() {
    Solution solution;

    // Additional Test Case
    vector<vector<int>> grid0 = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},
        {1, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},
        {0, 1, 1, 1, 1, 0, 0}
    };
    int result0 = solution.largestIsland(grid0);
    cout << "Additional Test Case Output: " << result0 << endl;

    // Example 1
    vector<vector<int>> grid1 = {{1, 0}, {0, 1}};
    int result1 = solution.largestIsland(grid1);
    cout << "Example 1 Output: " << result1 << endl;

    // Example 2
    vector<vector<int>> grid2 = {{1, 1}, {1, 0}};
    int result2 = solution.largestIsland(grid2);
    cout << "Example 2 Output: " << result2 << endl;

    // Example 3
    vector<vector<int>> grid3 = {{1, 1}, {1, 1}};
    int result3 = solution.largestIsland(grid3);
    cout << "Example 3 Output: " << result3 << endl;

    // Example 4
    vector<vector<int>> grid4 = {{1}};
    int result4 = solution.largestIsland(grid4);
    cout << "Example 4 Output: " << result4 << endl;

    return 0;
}

// int get(int i, int j, vector<vector<int>>& g) {
//   return (min(i, j) < 0 || i >= g.size() || j >= g[0].size()) ? 0 : g[i][j];
// }
// int paint(int i, int j, int clr, vector<vector<int>>& g) {
//   if (get(i, j, g) != 1)
//     return 0;
//   g[i][j] = clr;
//   return 1 + paint(i + 1, j, clr, g) + paint(i - 1, j, clr, g) +
//              paint(i, j + 1, clr, g) + paint(i, j - 1, clr, g);
// }
// int largestIsland(vector<vector<int>>& g, int res = 0) {
//   vector<int> sizes = {0, 0};  // sentinel values; colors start from 2.
//   for (auto i = 0; i < g.size(); ++i)
//     for (auto j = 0; j < g[i].size(); ++j)
//       if (g[i][j] == 1)
// 	    sizes.push_back(paint(i, j, sizes.size(), g));
//   for (auto i = 0; i < g.size(); ++i)
//     for (auto j = 0; j < g[i].size(); ++j)
//       if (g[i][j] == 0) {
//         unordered_set<int> s = { get(i + 1, j, g), get(i - 1, j, g),
//                                  get(i, j + 1, g), get(i, j - 1, g) };
//         res = max(res, accumulate(begin(s), end(s), 1, [&](int sum, int col) {
//           return sum + sizes[col];
//         }));
//       }
//   return res == 0 ? g.size() * g[0].size() : res;
// }