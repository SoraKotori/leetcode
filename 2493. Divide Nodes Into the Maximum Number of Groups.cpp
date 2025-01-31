#include "header.h"

class Solution {
public:
    int magnificentSets(int n, vector<vector<int>> &edges) {

        vector<int> parents(n);
        ranges::iota(parents, 0);
        auto find_root = [&](auto node)
        {
            for (int root; (root = parents[node]) != node; node = root);
            return node;
        };

        vector<vector<int>> adj_list(n);
        for (const auto& edge : edges)
        {
            auto node_0 = edge[0] - 1;
            auto node_1 = edge[1] - 1;
            adj_list[node_0].emplace_back(node_1);
            adj_list[node_1].emplace_back(node_0);

            auto root_0 = find_root(node_0);
            auto root_1 = find_root(node_1);
            parents[root_1] = root_0;
        }

        int max_color = 0;
        queue<int> queue;
        vector<int> colors(n);
        vector<int> groups(n);

        for (auto source = 0; source < n; source++)
        {
            int index = 0;
            ranges::fill(colors, -1);

            for (queue.emplace(source); !queue.empty(); queue.pop())
            {
                auto node = queue.front();
                for (auto adj : adj_list[node])
                {
                    if (auto& color = colors[adj]; color < 0)
                    {
                        color = colors[node] + 1;
                        index = max(index, color);
                        queue.emplace(adj);
                    }
                    else if (color % 2 == colors[node] % 2)
                        return -1;

                    print_1D(colors);
                }
            }

            max_color += index;
        }

        return max_color;
    }
};

int main() {
    Solution solution;

    // Example 1
    int n1 = 6;
    vector<vector<int>> edges1 = {{1, 2}, {1, 4}, {1, 5}, {2, 6}, {2, 3}, {4, 6}};
    int result1 = solution.magnificentSets(n1, edges1);
    cout << "Example 1 Output: " << result1 << endl;

    // Example 2
    int n2 = 3;
    vector<vector<int>> edges2 = {{1, 2}, {2, 3}, {3, 1}};
    int result2 = solution.magnificentSets(n2, edges2);
    cout << "Example 2 Output: " << result2 << endl;

    return 0;
}