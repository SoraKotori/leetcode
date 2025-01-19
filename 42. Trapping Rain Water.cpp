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
    int trap(vector<int>& height) {
        int water = 0;
        int first_max = 0;
        int last_max = 0;
        for (auto first = begin(height),
                  last  = end(height) - 1;
            first != last;)
        {
            if (*first < *last)
            {
                if (first_max <= *first)
                    first_max  = *first;
                else
                    water += first_max - *first;
                first++;
            }
            else
            {
                if (last_max <= *last)
                    last_max  = *last;
                else
                    water += last_max - *last;
                last--;
            }
        }
        return water;
    }
};

int main() {
    vector<int> height = {4, 2, 3};
    Solution solution;
    cout << "Trapped water: " << solution.trap(height) << endl;
    return 0;
}
