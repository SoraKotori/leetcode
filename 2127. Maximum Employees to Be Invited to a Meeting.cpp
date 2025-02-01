#include "header.h"

class Solution {
public:
    int maximumInvitations(vector<int>& favorite) {
        int n = size(favorite);

        vector<int> in_degree(n);
        for(auto node : favorite)
            in_degree[node]++;

        queue<int> queue;
        for (int i = 0; i < n; i++)
            if (in_degree[i] == 0)
                queue.emplace(i);

        vector<int> depth(n, 1);
        for (; !queue.empty(); queue.pop())
        {
            auto node = queue.front();
            auto next = favorite[node];
            
            depth[next] = max(depth[next], depth[node] + 1);
            if (--in_degree[next] == 0)
                queue.emplace(next);
        }

        int two_cycle = 0;
        int max_cycle = 0;
        for (auto node : favorite)
        {
            int cycle = 0;
            for (; in_degree[node]; node = favorite[node])
            {
                in_degree[node] = 0;
                cycle++;
            }

            if (cycle == 2)
                two_cycle += depth[node] + depth[favorite[node]];
            else
                max_cycle = max(max_cycle, cycle);
        }

        return std::max(max_cycle, two_cycle);
    }
};

int main() {
    Solution solution;

    // Example 1
    vector<int> favorite1 = {2, 2, 1, 2};
    int result1 = solution.maximumInvitations(favorite1);
    cout << "Example 1 Output: " << result1 << endl;

    // Example 2
    vector<int> favorite2 = {1, 2, 0};
    int result2 = solution.maximumInvitations(favorite2);
    cout << "Example 2 Output: " << result2 << endl;

    // Example 3
    vector<int> favorite3 = {3, 0, 1, 4, 1};
    int result3 = solution.maximumInvitations(favorite3);
    cout << "Example 3 Output: " << result3 << endl;

    return 0;
}