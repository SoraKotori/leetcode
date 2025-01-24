#include "header.h"

class Solution1 {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        auto n = size(graph);

        vector<int> ori_point(n, 0);
        vector<int> end_point(n, 0);

        auto ori_it = begin(ori_point);
        for (int i = 0; i < n; i++)
            if (size(graph[i]))
                *ori_it++ = i;
            else
                end_point[i] = true;

        for (decltype(ori_it) before; before != ori_it;)
        {
            before = ori_it;
            ori_it = remove_if(begin(ori_point), ori_it, [&](auto vertex)
            {
                bool b = ranges::all_of(graph[vertex], [&](auto adj)
                {
                    return end_point[adj];
                });

                if (b)
                    end_point[vertex] = true;

                return b;
            });
        }

        ori_it = begin(ori_point);
        for (int i = 0; i < n; i++)
            if (end_point[i])
                *ori_it++ = i;
        ori_point.erase(ori_it, end(ori_point));

        return ori_point;
    }
};

class Solution_Kahn  {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        auto n = size(graph);

        vector<int> out_degree(n, 0);
        vector<vector<int>> adj(n);

        for (int i = 0; i < n; i++)
            for (auto node : graph[i])
            {
                out_degree[i]++;
                adj[node].emplace_back(i);
            }

        queue<int> queue;
        for (int i = 0; i < n; i++)
            if (size(graph[i]) == 0)
                queue.push(i);

        while (!queue.empty())
        {
            auto node = queue.front();
            queue.pop();

            for (auto adj_node : adj[node])
                if (--out_degree[adj_node] == 0)
                    queue.push(adj_node);
        }

        vector<int> ans;
        for (int i = 0; i < n; i++)
            if (out_degree[i] == 0)
                ans.emplace_back(i);

        return ans;
    }
};

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = size(graph);

        vector<int> visited(n, 0);
        vector<int> is_safe(n, 0);
        vector<int> stack(n);
        iota(begin(stack), end(stack), 0);

        while (!stack.empty())
        {
            int index;
            auto node = stack.back();
            while ((index = visited[node]++) < size(graph[node]))
                if (auto adj = graph[node][index]; visited[adj] == 0)
                    node = stack.emplace_back(adj);

            if (index == size(graph[node]))
                if (ranges::all_of(graph[node], [&](auto adj) { return is_safe[adj]; }))
                    is_safe[node] = true;

            stack.pop_back();
        }

        stack.erase(ranges::copy_if(views::iota(0, n), begin(stack), [&](auto node) { return is_safe[node]; }).out, end(stack));
        return stack;
    }
};

int main() {
    Solution solution;

    vector<vector<int>> graph1 = {{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}};
    vector<int> result1 = solution.eventualSafeNodes(graph1);
    cout << "Result 1: ";
    for (int node : result1) {
        cout << node << " ";
    }
    cout << endl;

    vector<vector<int>> graph2 = {{1, 2, 3, 4}, {1, 2}, {3, 4}, {0, 4}, {}};
    vector<int> result2 = solution.eventualSafeNodes(graph2);
    cout << "Result 2: ";
    for (int node : result2) {
        cout << node << " ";
    }
    cout << endl;

    vector<vector<int>> graph3 = {{}, {0, 2, 3, 4}, {3}, {4}, {}};
    vector<int> result3 = solution.eventualSafeNodes(graph3);
    cout << "Result 3: ";
    for (int node : result3) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}