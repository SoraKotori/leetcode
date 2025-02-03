#include "header.h"

class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int n = size(nums);

        int longest = 1;
        int increasing = 1;
        int decreasing = 1;
        for (int i = 1; i < n; i++)
        {
            if (nums[i - 1] < nums[i])
            {
                longest = max(longest, ++increasing);
                decreasing = 1;
            }
            else if (nums[i - 1] > nums[i])
            {
                longest = max(longest, ++decreasing);
                increasing = 1;
            }
            else
            {
                increasing = 1;
                decreasing = 1;
            }
        }

        return longest;
    }
};

class Solution_1 {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int maxLength = 0;

        // Find longest strictly increasing subarray
        for (int start = 0; start < nums.size(); start++) {
            int currLength = 1;
            for (int pos = start + 1; pos < nums.size(); pos++) {
                // Extend subarray if next element is larger
                if (nums[pos] > nums[pos - 1]) {
                    currLength++;
                } else {
                    // Break if sequence is not increasing anymore
                    break;
                }
            }
            maxLength = max(maxLength, currLength);
        }

        // Find longest strictly decreasing subarray
        for (int start = 0; start < nums.size(); start++) {
            int currLength = 1;
            for (int pos = start + 1; pos < nums.size(); pos++) {
                // Extend subarray if next element is smaller
                if (nums[pos] < nums[pos - 1]) {
                    currLength++;
                } else {
                    // Break if sequence is not decreasing anymore
                    break;
                }
            }
            maxLength = max(maxLength, currLength);
        }

        return maxLength;  // Return the longer of increasing or decreasing
                           // sequences
    }
};

class Solution_2 {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        // Track current lengths of increasing and decreasing sequences
        int incLength = 1, decLength = 1;
        int maxLength = 1;

        // Iterate through array comparing adjacent elements
        for (int pos = 0; pos < nums.size() - 1; pos++) {
            if (nums[pos + 1] > nums[pos]) {
                // If next element is larger, extend increasing sequence
                incLength++;
                decLength = 1;  // Reset decreasing sequence
            } else if (nums[pos + 1] < nums[pos]) {
                // If next element is smaller, extend decreasing sequence
                decLength++;
                incLength = 1;  // Reset increasing sequence
            } else {
                // If elements are equal, reset both sequences
                incLength = 1;
                decLength = 1;
            }

            // Update max length considering both sequences
            maxLength = max(maxLength, max(incLength, decLength));
        }
        return maxLength;
    }
};

class Solution_4 {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int n = size(nums);

        int longest = 1;
        int increasing = 1;
        int decreasing = 1;
        for (int i = 1; i < n; i++)
        {
            increasing = nums[i - 1] < nums[i] ? increasing + 1 : 1;
            decreasing = nums[i - 1] > nums[i] ? decreasing + 1 : 1;
            longest = max({longest, increasing, decreasing});
        }

        return longest;
    }
};

int main()
{
    Solution_4 sol;

    vector<int> nums1 = {1,4,3,3,2};
    int result1 = sol.longestMonotonicSubarray(nums1);
    cout << "result1: " << result1 << endl;

    vector<int> nums2 = {3,3,3,3};
    int result2 = sol.longestMonotonicSubarray(nums2);
    cout << "result2: " << result2 << endl;

    vector<int> nums3 = {3,2,1};
    int result3 = sol.longestMonotonicSubarray(nums3);
    cout << "result3: " << result3 << endl;
}