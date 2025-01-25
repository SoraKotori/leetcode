#include "header.h"

#include <ranges>
class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        auto n = size(nums);

        vector<int> sort_index(n);
        ranges::iota(sort_index, 0);
        ranges::sort(sort_index, [&](auto i, auto j) { return nums[i] < nums[j]; });

        vector<int> graph(n, 0);       // graph : sort_index
        vector<int> graph_map(n, 0);   // index : graph

        auto graph_index = 0;
        for (int i = 1; i < n; i++)
        {
            if (nums[sort_index[i]] - nums[sort_index[i - 1]] > limit)
                graph[++graph_index] = i;
            graph_map[sort_index[i]] = graph_index;
        }

        vector<int> ans(n);
        ranges::transform(graph_map, begin(ans), [&](auto graph_index) {
            return nums[sort_index[graph[graph_index]++]]; });

        return ans;
    }
};

#include <ranges>
class Solution_2 {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& arr, int limit) {
        auto sorted = arr;
        sort(begin(sorted), end(sorted));
        auto groups = sorted | views::chunk_by([limit](int x, int y) { return y - x <= limit; });
        vector<vector<int>::iterator> group_iters;
        vector<int> group_heads;
        for (auto group : groups) {
            group_iters.push_back(group.begin());
            group_heads.push_back(group.front());
        }
        for (auto& x : arr) {
            auto it = prev(upper_bound(group_heads.begin(), group_heads.end(), x));
            auto& g_it = group_iters[distance(group_heads.begin(), it)];
            x = *g_it++;
        }
        return arr;
    }
};

int main() {
    Solution solution;

    vector<vector<int>> test_cases = {
        {1, 5, 3, 9, 8},
        {1, 7, 6, 18, 2, 1},
        {1, 7, 28, 19, 10}
    };
    vector<int> limits = {2, 3, 3};

    for (int i = 0; i < test_cases.size(); ++i) {
        vector<int> result = solution.lexicographicallySmallestArray(test_cases[i], limits[i]);
        cout << "Result " << i + 1 << ": ";
        for (int num : result) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}