#include "header.h"

class Solution {
public:
    vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
        vector<int> result(size(nums) - --k);
        deque<int> queue;

        for (int i = 0; i < size(nums); i++)
        {
            while (size(queue) && queue.back() < nums[i])
                queue.pop_back();
            queue.push_back(nums[i]);

            if (i >= k)
                result[i - k] = queue.front();

            if (i >= k && nums[i - k] == queue.front())
                queue.pop_front();
        }

        return result;
    }
};

int main()
{
    Solution sol;

    print_1D(sol.maxSlidingWindow({1,3,-1,-3,5,3,6,7}, 3));
    print_1D(sol.maxSlidingWindow({1}, 1));
}