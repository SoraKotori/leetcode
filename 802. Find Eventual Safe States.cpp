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

#include <ranges>
class Solution_iterative_DFS {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = size(graph);
        vector<bool> safe(n, true);
        vector<int> visit(n, 0);
        vector<int> stack;
        
        for (auto root = begin(visit); (root = find(root, end(visit), 0)) != end(visit);)
            for (stack.emplace_back(distance(begin(visit), root)); !stack.empty(); stack.pop_back())
            {
                auto node = stack.back();
                for (int index; (index = visit[node]++) < size(graph[node]);)
                    if (auto neighbor = graph[node][index]; visit[neighbor] == 0) // non-know
                        node = stack.emplace_back(neighbor);
                    else if (visit[neighbor] != size(graph[neighbor]) + 1) // unsafe
                        safe[node] = false;

                if (safe[node])
                    safe[node] = ranges::all_of(graph[node], [&](auto neighbor) { return safe[neighbor]; });
            }

        visit.erase(ranges::copy_if(views::iota(0, n), begin(visit), [&](auto node) { return safe[node]; }).out, end(visit));
        return visit;
    }
};
class Solution {
public:
    bool dfs(int node,vector<int> &visited,vector<int> &pathVisited,vector<int> &checked,vector<vector<int>> &graph)
    {
        visited[node]=1;
        pathVisited[node]=1;

        for(int nei : graph[node])
        {
            if(!visited[nei])
            {
                if(dfs(nei,visited,pathVisited,checked,graph))
                    return true;
            }
            else if(pathVisited[nei]==1)
                return true;
        }

        checked[node]=1;
        pathVisited[node]=0;
        return false;
    }

    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> visited(n,0);
        vector<int> pathVisited(n,0);
        vector<int> checked(n,0);
        vector<int> safe;

        for(int i=0;i<n;i++)
            if(!visited[i])
                dfs(i,visited,pathVisited,checked,graph);

        for(int i=0;i<n;i++)
        {
            if(checked[i]==1)
                safe.push_back(i);
        }

        return safe;
    }
};

int main() {
    Solution_iterative_DFS solution;
    vector<vector<vector<int>>> test_cases = {
        {{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}},
        {{1, 3, 7, 9}, {1, 8}, {7}, {5, 6, 7, 8}, {5, 6, 7, 8}, {8}, {7, 8, 9}, {8}, {9}, {}},
        {{1, 2, 3, 4}, {1, 2}, {3, 4}, {0, 4}, {}},
        {{}, {0, 2, 3, 4}, {3}, {4}, {}},
        {{0}, {2, 3, 4}, {3, 4}, {0, 4}, {}}
    };

    for (int i = 0; i < test_cases.size(); ++i) {
        vector<int> result = solution.eventualSafeNodes(test_cases[i]);
        cout << "Result " << i + 1 << ": ";
        for (int node : result) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}