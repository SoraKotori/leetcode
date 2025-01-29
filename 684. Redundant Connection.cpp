#include "header.h"

class Solution_Disjoint_Set_Union {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {

        vector<int> parents(size(edges) + 1);
        auto find_root = [&](auto node)
        {
            for (int root; node != (root = parents[node]); node = root);
            return node;
        };

        for (const auto& edge : edges)
        {
            auto node_0 = edge[0];
            auto node_1 = edge[1];
            auto root_0 = find_root(node_0);
            auto root_1 = find_root(node_1);

            if (root_0 == 0 && root_1 == 0)
            {
                parents[node_0] = node_0;
                parents[node_1] = node_0;
            }
            else if (root_0 == 0)      parents[node_0] = root_1;
            else if (root_1 == 0)      parents[node_1] = root_0;
            else if (root_1 != root_0) parents[root_1] = root_0;
            else return edge;
        }

        return {};
    }
};

class Solution {
public:
    int dfs(vector<vector<int>>& adj_list, vector<bool>& visit, vector<int>& parents, int node)
    {
        visit[node] = true;

        for (auto neighbor : adj_list[node])
        {
            if (visit[neighbor] == false)
            {
                parents[neighbor] = node;
                int cycle_start = dfs(adj_list, visit, parents, neighbor);
                if (cycle_start >= 0)
                    return cycle_start;
            }
            else if (parents[node] != neighbor)
            {
                parents[neighbor] = node;
                return neighbor;
            }
        }

        return -1;
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {

        vector<vector<int>> adj_list(size(edges));
        for (const auto& edge : edges)
        {
            adj_list[edge[0] - 1].emplace_back(edge[1] - 1);
            adj_list[edge[1] - 1].emplace_back(edge[0] - 1);
        }

        vector<bool> visit(size(edges));
        vector<int> parents(size(edges));

        int cycle_start = dfs(adj_list, visit, parents, 0);

        vector<bool> cycle_nodes(size(edges));
        for (int node = cycle_start; cycle_start != (node = parents[node]);)
            cycle_nodes[node] = true;
        cycle_nodes[cycle_start] = true;

        for (const auto& edge : edges | views::reverse)
            if (cycle_nodes[edge[0] - 1] && cycle_nodes[edge[1] - 1])
                return edge;

        return {};
    }
};

int main()
{
    Solution solution;

    // Example 1
    vector<vector<int>> edges1 = {{1, 2}, {1, 3}, {2, 3}};
    vector<int> result1 = solution.findRedundantConnection(edges1);
    cout << "Example 1 Output: [" << result1[0] << "," << result1[1] << "]" << endl;

    // Example 2
    vector<vector<int>> edges2 = {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
    vector<int> result2 = solution.findRedundantConnection(edges2);
    cout << "Example 2 Output: [" << result2[0] << "," << result2[1] << "]" << endl;

    return 0;
}