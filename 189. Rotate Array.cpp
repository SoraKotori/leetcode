#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ranges>

using namespace std;

void print(vector<int>& v)
{
    for (auto i : v)
    {
        cout << i << " ";
    }
    cout << endl;
}

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        for (auto first = begin(nums); first < end(nums) - k; first += k)
        {
            swap_ranges(first, first + k, end(nums) - k);
            
            print(nums);
        }
    }
};

int main(int argc, char const *argv[])
{
    Solution s;

    auto iota_view = std::ranges::iota_view(1, 27);
    vector<int> vec(iota_view.begin(), iota_view.end());
    print(vec);

    s.rotate(vec, 38);

    return 0;
}
