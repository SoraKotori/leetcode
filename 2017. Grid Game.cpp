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
#include <ranges>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long gridGame(vector<vector<int>>& grid) {
        
        auto sum1 = ranges::fold_left(grid[0], 0LL, plus{});
        auto sum2 = 0LL;
        auto value = numeric_limits<long long>::max();

        for (auto [top, bottom] : ranges::views::zip(grid[0], grid[1])) {
            sum1 -= top;
            value = min(value, max(sum1, sum2));
            sum2 += bottom;
        }

        return value;
    }
};

void testGridGame(vector<vector<int>> grid, long long expected) {
    Solution sol;
    long long result = sol.gridGame(grid);
    if (result == expected) {
        cout << "Test passed." << endl;
    } else {
        cout << "Test failed. Expected " << expected << " but got " << result << "." << endl;
    }
}

int main() {
    vector<vector<int>> grid1 = {{2, 5, 4}, {1, 5, 1}};
    long long expected1 = 4;
    testGridGame(grid1, expected1);

    vector<vector<int>> grid2 = {{20, 3, 20, 17, 2, 12, 15, 17, 4, 15}, {20, 10, 13, 14, 15, 5, 2, 3, 14, 3}};
    long long expected2 = 63;
    testGridGame(grid2, expected2);

    // Add more test cases as needed
    return 0;
}