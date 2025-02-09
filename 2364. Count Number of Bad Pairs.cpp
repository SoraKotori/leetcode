#include "header.h"

class Solution {
public:
    long long countBadPairs(vector<int>& nums) {
        auto n = size(nums);
        auto bad_pairs = n * (n - 1) / 2;

        unordered_map<int, int> map;
        for (int i = 0; i < n; i++)
            bad_pairs -= map[nums[i] - i]++;

        return bad_pairs;
    }
};

class Solution_1 {
public:
    long long countBadPairs(vector<int>& nums) {
        return ranges::fold_left(views::enumerate(nums), 0LL, [map = unordered_map<int, int>{}](auto bad_pair, auto tuple) mutable
        {
            return bad_pair + get<0>(tuple) - map[get<1>(tuple) - get<0>(tuple)]++;
        });
    }
};

class Solution_2 {
public:
    long long countBadPairs(vector<int>& nums) {

        for (auto [index, num] : views::enumerate(nums))
            num -= index;
        ranges::sort(nums);

        auto bad_pairs = size(nums) * (size(nums) - 1) / 2;
        for (auto chunk : nums | views::chunk_by(equal_to{}))
            bad_pairs -= size(chunk) * (size(chunk) - 1) / 2;

        return bad_pairs;
    }
};
int main() {
    Solution_2 sol;
    
    vector<int> nums1 = {4, 1, 3, 3};
    cout << "Output for [4,1,3,3]: " << sol.countBadPairs(nums1) << endl;
    
    vector<int> nums2 = {1, 2, 3, 4, 5};
    cout << "Output for [1,2,3,4,5]: " << sol.countBadPairs(nums2) << endl;
    
    return 0;
}