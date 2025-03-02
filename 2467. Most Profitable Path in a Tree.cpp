#include "header.h"

// There is an undirected tree with n nodes labeled from 0 to n - 1, rooted at node 0. You are given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.

// At every node i, there is a gate. You are also given an array of even integers amount, where amount[i] represents:

// the price needed to open the gate at node i, if amount[i] is negative, or,
// the cash reward obtained on opening the gate at node i, otherwise.
// The game goes on as follows:

// Initially, Alice is at node 0 and Bob is at node bob.
// At every second, Alice and Bob each move to an adjacent node. Alice moves towards some leaf node, while Bob moves towards node 0.
// For every node along their path, Alice and Bob either spend money to open the gate at that node, or accept the reward. Note that:
// If the gate is already open, no price will be required, nor will there be any cash reward.
// If Alice and Bob reach the node simultaneously, they share the price/reward for opening the gate there. In other words, if the price to open the gate is c, then both Alice and Bob pay c / 2 each. Similarly, if the reward at the gate is c, both of them receive c / 2 each.
// If Alice reaches a leaf node, she stops moving. Similarly, if Bob reaches node 0, he stops moving. Note that these events are independent of each other.
// Return the maximum net income Alice can have if she travels towards the optimal leaf node.

// Example 1:
// Input: edges = [[0,1],[1,2],[1,3],[3,4]], bob = 3, amount = [-2,4,2,-4,6]
// Output: 6
// Explanation: 
// The above diagram represents the given tree. The game goes as follows:
// - Alice is initially on node 0, Bob on node 3. They open the gates of their respective nodes.
//   Alice's net income is now -2.
// - Both Alice and Bob move to node 1. 
//   Since they reach here simultaneously, they open the gate together and share the reward.
//   Alice's net income becomes -2 + (4 / 2) = 0.
// - Alice moves on to node 3. Since Bob already opened its gate, Alice's income remains unchanged.
//   Bob moves on to node 0, and stops moving.
// - Alice moves on to node 4 and opens the gate there. Her net income becomes 0 + 6 = 6.
// Now, neither Alice nor Bob can make any further moves, and the game ends.
// It is not possible for Alice to get a higher net income.

// Example 2:
// Input: edges = [[0,1]], bob = 1, amount = [-7280,2350]
// Output: -7280
// Explanation: 
// Alice follows the path 0->1 whereas Bob follows the path 1->0.
// Thus, Alice opens the gate at node 0 only. Hence, her net income is -7280. 

// Constraints:
// 2 <= n <= 105
// edges.length == n - 1
// edges[i].length == 2
// 0 <= ai, bi < n
// ai != bi
// edges represents a valid tree.
// 1 <= bob < n
// amount.length == n
// amount[i] is an even integer in the range [-104, 104].

class Solution_1 {
public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {

        vector<vector<int>> adjacents(size(edges) + 1);
        for (const auto& edge : edges)
        {
            adjacents[edge[0]].push_back(edge[1]);
            adjacents[edge[1]].push_back(edge[0]);
        }

        vector<int> stack;
        stack.push_back(bob);

        vector<int> parents(size(edges) + 1);
        parents[bob] = bob;
        
        while (size(stack) && stack.back())
        {
            auto node = stack.back();
            stack.pop_back();

            for (auto adjacent : adjacents[node])
                if (adjacent != parents[node])
                {
                    parents[adjacent] = node;
                    stack.push_back(adjacent);
                }
        }

        int bob_distance = 1;
        for (int node = 0; node != bob; node = parents[node])
            bob_distance++;

        int node = 0;
        for (int bob_half = bob_distance / 2; bob_half--; node = parents[node]);

        if (bob_distance % 2)
        {
            amount[node] /= 2;
            node = parents[node];
        }

        for (int bob_half = bob_distance / 2; bob_half--; node = parents[node])
            amount[node] = 0;

        stack.clear();
        stack.push_back(0);
        fill(begin(parents), end(parents), 0);

        auto max = numeric_limits<int>::min();
        auto income = vector<int>(size(edges) + 1);
        income[0] = amount[0];

        while (size(stack))
        {
            auto node = stack.back();
            stack.pop_back();

            if (size(adjacents[node]) == 1 && node &&
                max < income[node])
                max = income[node];

            for (auto adjacent : adjacents[node])
                if (adjacent != parents[node])
                {
                    stack.push_back(adjacent);
                    income[adjacent] = income[node] + amount[adjacent];
                    parents[adjacent] = node;
                }
        }

        return max;
    }
};

class Solution {
public:
    pair<int, int> dfs(const vector<vector<int>>& adjacents, vector<int>& amount, int bob, int source, int parent, int depth)
    {
        int distance = source == bob ? 0 : size(amount);
        int income = source && size(adjacents[source]) == 1 ? 0 : numeric_limits<int>::min();

        for (auto adjacent : adjacents[source])
            if (adjacent != parent)
            {
                auto [child_income, bob_distance] = dfs(adjacents, amount, bob, adjacent, source, depth + 1);
                income = max(income, child_income);
                distance = min(distance, bob_distance);
            }

        if      (depth <  distance) income += amount[source];
        else if (depth == distance) income += amount[source] / 2;

        return make_pair(income, distance + 1);
    }

    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {

        vector<vector<int>> adjacents(size(amount));
        for (const auto& edge : edges)
        {
            adjacents[edge[0]].push_back(edge[1]);
            adjacents[edge[1]].push_back(edge[0]);
        }

        return dfs(adjacents, amount, bob, 0, 0, 0).first;
    }
};

int main() {
    {
        vector<vector<int>> edges = {{0, 1}, {1, 2}, {1, 3}, {3, 4}};
        int bob = 3;
        vector<int> amount = {-2, 4, 2, -4, 6};
        Solution sol;
        int result = sol.mostProfitablePath(edges, bob, amount);
        cout << "測試案例 1：預期輸出 = 6, 實際輸出 = " << result << endl;
    }
    
    {
        vector<vector<int>> edges = {{0, 1}};
        int bob = 1;
        vector<int> amount = {-7280, 2350};
        Solution sol;
        int result = sol.mostProfitablePath(edges, bob, amount);
        cout << "測試案例 2：預期輸出 = -7280, 實際輸出 = " << result << endl;
    }

    {
        vector<vector<int>> edges = {{0,2},{0,5},{1,3},{1,5},{2,4}};
        int bob = 4;
        vector<int> amount = {5018,8388,6224,3466,3808,3456};
        Solution sol;
        int result = sol.mostProfitablePath(edges, bob, amount);
        cout << "測試案例 3：預期輸出 = 20328, 實際輸出 = " << result << endl;
    }

    {
        vector<vector<int>> edges = {{0,1},{1,2},{2,3}};
        int bob = 3;
        vector<int> amount = {-5644,-6018,1188,-8502};
        Solution sol;
        int result = sol.mostProfitablePath(edges, bob, amount);
        cout << "測試案例 4：預期輸出 = -11662, 實際輸出 = " << result << endl;
    }

    {
        vector<vector<int>> edges = {{0,2},{0,6},{1,3},{1,5},{2,5},{4,6}};
        int bob = 6;
        vector<int> amount = {8838,-6396,-5940,2694,-1366,4616,2966};
        Solution sol;
        int result = sol.mostProfitablePath(edges, bob, amount);
        cout << "測試案例 5：預期輸出 = 7472, 實際輸出 = " << result << endl;
    }

    {
        vector<vector<int>> edges = {{0,2},{1,4},{1,6},{2,4},{3,6},{3,7},{5,7}};
        int bob = 4;
        vector<int> amount = {-6896,-1216,-1208,-1108,1606,-7704,-9212,-8258};
        Solution sol;
        int result = sol.mostProfitablePath(edges, bob, amount);
        cout << "測試案例 6：預期輸出 = -34998, 實際輸出 = " << result << endl;
    }

    return 0;
}