#include "header.h"
#include <ranges>

class Solution_dfs {
public:
    void dfs (vector<vector<int>>& graph, vector<int>& isReachable, int node)
    {
        for (auto neighbor : graph[node])
            if (isReachable[neighbor] == false)
            {
                isReachable[neighbor] = true;
                dfs(graph, isReachable, neighbor);
            }
    }

    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<vector<int>> graph(numCourses);
        for (const auto& requisite : prerequisites)
            graph[requisite[0]].emplace_back(requisite[1]);

        vector<vector<int>> isReachable(numCourses, vector<int>(numCourses, 0));
        for (int node = 0; node < numCourses; node++)
            dfs(graph, isReachable[node], node);

        vector<bool> ans(size(queries));
        ranges::transform(queries, begin(ans), [&](const auto& querie)
        {
            return isReachable[querie[0]][querie[1]];
        });
        return ans;
    }
};

class Solution_Floyd_Warshall {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {

        vector<vector<bool>> isReachable(numCourses, vector<bool>(numCourses, false));
        for (const auto& requisite : prerequisites)
            isReachable[requisite[0]][requisite[1]] = true;

        for (int k = 0; k < numCourses; k++)
            for (int i = 0; i < numCourses; i++)
                for (int j = 0; j < numCourses; j++)
                    if (isReachable[i][j] == false)
                        isReachable[i][j] = isReachable[i][k] && isReachable[k][j];

        vector<bool> ans(size(queries));
        ranges::transform(queries, begin(ans), [&](const auto& querie)
        {
            return isReachable[querie[0]][querie[1]];
        });
        return ans;
    }
};

class Solution_Kahn {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {

        vector<int> indegree(numCourses, 0);
        vector<vector<int>> graph(numCourses);
        vector<vector<bool>> nodePrerequisites(numCourses, vector<bool>(numCourses, 0));
        for (const auto& requisite : prerequisites)
        {
            indegree[requisite[1]]++;
            graph[requisite[0]].emplace_back(requisite[1]);
            nodePrerequisites[requisite[1]][requisite[0]] = true;
        }

        queue<int> queue;
        for (int i = 0; i < numCourses; i++)
            if (indegree[i] == 0)
                queue.emplace(i);

        while (!queue.empty())
        {
            auto node = queue.front();
            queue.pop();

            for (auto neighbor : graph[node])
            {
                for (int i = 0; i < numCourses; i++)
                    if (nodePrerequisites[neighbor][i] == false)
                        nodePrerequisites[neighbor][i] = nodePrerequisites[node][i];

                if (--indegree[neighbor] == 0)
                    queue.emplace(neighbor);
            }
        }

        vector<bool> ans(size(queries));
        ranges::transform(queries, begin(ans), [&](const auto& querie)
        {
            return nodePrerequisites[querie[1]][querie[0]];
        });
        return ans;
    }
};

int main() {
    int numCourses = 5;
    vector<vector<int>> prerequisites = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
    vector<vector<int>> queries = {{0, 4}, {4, 0}, {1, 3}, {3, 0}};

    Solution_Kahn solution;
    vector<bool> result = solution.checkIfPrerequisite(numCourses, prerequisites, queries);

    for (bool res : result) {
        cout << (res ? "true" : "false") << endl;
    }

    return 0;
}