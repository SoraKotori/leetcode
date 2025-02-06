#include "header.h"

class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        unordered_map<int, set<int>> map;

        int n = size(nums);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                map[nums[i] * nums[j]].insert({nums[i], nums[j]});

        int result = 0;
        for (const auto& [product, set] : map)
            for (auto div = size(set) / 2; --div; result += div * 8);

        return result;
    }
};

class Solution_1 {
public:
    int tupleSameProduct(vector<int>& nums) {
        unordered_map<int, int> map;

        int n = size(nums);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                map[nums[i] * nums[j]]++;

        int result = 0;
        for (const auto& [product, count] : map)
            result += count * (count - 1) * 4;

        return result;
    }
};

class Solution_2 {
public:
    int tupleSameProduct(vector<int>& nums) {
        unordered_map<int, int> map;

        int result = 0;
        for (int i = 0, n = size(nums); i < n; i++)
            for (int j = i + 1; j < n; j++)
                result += map[nums[i] * nums[j]]++;

        return result * 8;
    }
};

class Solution_3 {
public:
    int tupleSameProduct(vector<int>& nums) {

        vector<int> products(size(nums) * (size(nums) - 1) / 2);
        auto first = begin(products);

        for (auto i = begin(nums), last = end(nums); i != last; i++)
            for (auto j = i + 1; j != last; j++)
                *first++ = *i * *j;

        ranges::sort(products);

        return ranges::fold_left(products | views::chunk_by(equal_to{}), 0, [](auto init, auto chunk)
        {
            return init + size(chunk) * (size(chunk) - 1) * 4;
        });
    }
};

class Solution_4 {
public:
    int tupleSameProduct(vector<int>& nums) {
        unordered_map<int, int> map;

        int result = 0;
        for (auto [i, num_i] : nums | views::enumerate)
            for (auto num_j  : nums | views::drop(i + 1))
                result += map[num_i * num_j]++;

        return result * 8;
    }
};

int main() {
    Solution_4 solution;

    vector<int> nums1 = {2, 3, 4, 6};
    cout << "Output: " << solution.tupleSameProduct(nums1) << endl; // Expected output: 8

    vector<int> nums2 = {1, 2, 4, 5, 10};
    cout << "Output: " << solution.tupleSameProduct(nums2) << endl; // Expected output: 16

    vector<int> nums3 = {2, 3, 4, 6, 8, 12};
    cout << "Output: " << solution.tupleSameProduct(nums3) << endl; // Expected output: 40

    return 0;
}