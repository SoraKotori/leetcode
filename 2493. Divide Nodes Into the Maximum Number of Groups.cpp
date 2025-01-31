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

        deque<int> queue;
        vector<int> colors(n);
        unordered_map<int, int> component_groups;

        for (int source = 0; source < n; source++)
        {
            ranges::fill(colors, 0);

            int color = 1;
            colors[source] = color;

            for (queue.emplace_back(source); !queue.empty(); color++)
                for (auto queue_size = size(queue); queue_size; queue_size--)
                {
                    auto node = queue.front();
                    queue.pop_front();                    

                    for (auto adj : adj_list[node])
                        if (colors[adj] == 0)
                        {
                            colors[adj] = color + 1;
                            queue.emplace_back(adj);
                        }
                        else if (colors[adj] == color)
                            return -1;
                }

            auto& groups = component_groups[find_root(source)];
            groups = max(groups, color - 1);
        }

        return ranges::fold_left(component_groups, 0, [](auto init, const auto& pair)
        {
            return init + pair.second;
        });
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

    // New Test Case
    int n3 = 92;
    vector<vector<int>> edges3 = {{67,29},{13,29},{77,29},{36,29},{82,29},{54,29},{57,29},{53,29},{68,29},{26,29},{21,29},{46,29},{41,29},{45,29},{56,29},{88,29},{2,29},{7,29},{5,29},{16,29},{37,29},{50,29},{79,29},{91,29},{48,29},{87,29},{25,29},{80,29},{71,29},{9,29},{78,29},{33,29},{4,29},{44,29},{72,29},{65,29},{61,29}};
    int result3 = solution.magnificentSets(n3, edges3);
    cout << "New Test Case Output: " << result3 << endl;

    // New Test Case 2
    int n4 = 6;
    vector<vector<int>> edges4 = {{1, 2}, {3, 4}, {5, 6}};
    int result4 = solution.magnificentSets(n4, edges4);
    cout << "New Test Case 2 Output: " << result4 << endl;

    // New Test Case 3
    int n5 = 32;
    vector<vector<int>> edges5 = {{29,12},{29,9},{17,11},{1,9},{31,19},{22,1},{11,1},{3,16},{28,3},{15,30},{28,17},{14,17},{1,7},{20,22},{3,25},{16,19},{13,22},{18,28},{5,13},{3,32},{22,29},{14,25},{20,11},{21,27},{26,9},{20,31},{11,21},{31,11},{30,11},{5,20},{9,3},{12,16},{20,6},{1,28},{3,26},{28,21},{24,28},{11,14},{32,10},{29,13},{7,12},{1,21},{10,25},{24,15},{11,16},{28,22},{15,28},{10,24},{3,27},{27,2}};
    int result5 = solution.magnificentSets(n5, edges5);
    cout << "New Test Case 3 Output: " << result5 << endl;

    // New Test Case 4
    int n6 = 41;
    vector<vector<int>> edges6 = {{1,21},{9,28},{39,11},{31,21},{36,34},{39,27},{27,33},{6,32},{31,17},{38,7},{10,30},{5,4},{2,38},{23,8},{20,24},{4,3},{6,24},{8,34},{23,32},{10,23},{31,12},{5,37},{21,41},{35,6},{37,30},{17,1},{27,5},{1,23},{1,25},{3,35},{33,38},{19,21},{2,3},{22,31},{27,22},{23,25},{23,24}};
    int result6 = solution.magnificentSets(n6, edges6);
    cout << "New Test Case 4 Output: " << result6 << endl;

    return 0;
}