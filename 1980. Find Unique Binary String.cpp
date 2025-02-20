#include "header.h"

class Solution {
    bool backtrack(string& result, vector<string>& nums, int& index)
    {
        if (size(result) == size(nums[0]))
            return index == size(nums) || result != nums[index++];

        for (char c : {'1', '0'})
        {
            result.push_back(c);
            if (backtrack(result, nums, index))
                return true;
            result.pop_back();
        }
        return false;
    }
public:
    string findDifferentBinaryString(vector<string>&& nums) {
        ranges::sort(nums);
        string result;
        int index = 0;
        backtrack(result, nums, index);
        return result;
    }
};

class Solution_2 {
public:
    string findDifferentBinaryString(vector<string>&& nums) {
        ranges::sort(nums);

        stack<string> stack;
        stack.push("");

        int index = 0;
        while (size(stack))
        {
            auto string = move(stack.top());
            stack.pop();

            if (size(string) == size(nums[0]))
            {
                if (index == size(nums) || nums[index++] != string)
                    return string;
                continue;
            }

            for (char c : {'1', '0'})
            {
                stack.push(string + c);
            }
        }

        return "";
    }
};

class Solution_3 {
public:
    string findDifferentBinaryString(vector<string>&& nums) {
        unordered_set<int> set(size(nums));
        for (auto& num : nums)
            set.insert(stoi(num, nullptr, 2));

        int i = 0;
        for (; i < size(nums) && set.count(i); i++);

        return format("{:0{}b}", i, size(nums));
    }
};

class Solution_4 {
public:
    string findDifferentBinaryString(vector<string>&& nums) {
        int ans = 0;
        for (int i = 0; i < size(nums); i++)
            ans = ans * 2 + (nums[i][i] == '0' ? 1 : 0);
        return format("{:0{}b}", ans, size(nums));
    }
};
int main()
{
    Solution_3 sol;

    cout << sol.findDifferentBinaryString({"01","10"}) << endl;
    cout << sol.findDifferentBinaryString({"00","01"}) << endl;
    cout << sol.findDifferentBinaryString({"111","011","001"}) << endl;
}