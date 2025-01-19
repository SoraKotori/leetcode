#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <iomanip>
#include <queue>
#include <functional>
#include <queue>
#include <limits>

using namespace std;

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = size(heightMap);
        int n = size(heightMap[0]);

        vector<vector<int>> visited(size(heightMap), vector(size(heightMap[0]), 0));
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> queue{};
        for (int i = m - 1, j = 0; j < n; j++)
        {
            queue.emplace(heightMap[0][j], 0, j);
            queue.emplace(heightMap[i][j], i, j);
            visited[0][j] = true;
            visited[i][j] = true;
        }

        for (int i = 0, j = n - 1; i < m; i++)
        {
            queue.emplace(heightMap[i][0], i, 0);
            queue.emplace(heightMap[i][j], i, j);
            visited[i][0] = true;
            visited[i][j] = true;            
        }

        array<pair<int, int>, 4> dirs = {{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};

        int water = 0;
        int lowest = 0;
        while (!queue.empty())
        {
            auto [height, row, col] = queue.top();
            queue.pop();

            lowest = max(lowest, height);
            for (const auto& dir : dirs)
            {
                int i = row + get<0>(dir);
                int j = col + get<1>(dir);
                if (i < 0 || j < 0 || i == m || j == n || visited[i][j])
                    continue;

                queue.emplace(heightMap[i][j], i, j);
                visited[i][j] = true;

                if (heightMap[i][j] < lowest)
                    water += lowest - heightMap[i][j];
            }
        }
        return water;
    }
};

int main() {
    // vector<vector<int>> height = {{3,3,3,3,3},{3,2,2,2,3},{3,2,1,2,3},{3,2,2,2,3},{3,3,3,3,3}};
    vector<vector<int>> height = {{1,4,3,1,3,2},{3,2,1,3,2,4},{2,3,3,2,3,1}};
    Solution solution;
    cout << "Trapped water: " << solution.trapRainWater(height) << endl;
    return 0;
}
