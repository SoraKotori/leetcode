#include "header.h"

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {

        queue<int> queue;
        vector<int> colors(size(graph));

        for (auto root = begin(colors); (root = find(root, end(colors), 0)) != end(colors);)
        {
            *root = 1;

            for (queue.emplace(distance(begin(colors), root)); !queue.empty(); queue.pop())
            {
                auto node = queue.front();
                for (auto adj : graph[node])
                {
                    if (auto& color = colors[adj]; color == 0)
                    {
                        color = colors[node] == 1 ? 2 : 1;
                        queue.emplace(adj);
                    }
                    else if (color == colors[node])
                        return false;
                }
            }
        }

        return true;
    }
};

int main() {
    Solution solution;

    // Example
    vector<vector<int>> graph = {{1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2}};
    bool result = solution.isBipartite(graph);
    cout << "Output: " << (result ? "true" : "false") << endl;

    return 0;
}