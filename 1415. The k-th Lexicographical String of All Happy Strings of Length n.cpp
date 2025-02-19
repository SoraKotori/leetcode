#include "header.h"

class Solution {
    array<char, 3> nums = {'a', 'b', 'c'};

    bool backtrack(string& result, int n, int& k)
    {
        if (size(result) == n)
            return --k == 0;

        char back = size(result) ? result.back() : 0;
        for (auto c : nums)
        {
            if (back != c)
            {
                result.push_back(c);
                if (backtrack(result, n, k))
                    return true;
                result.pop_back();
            }
        }

        return false;
    }
public:
    string getHappyString(int n, int k) {
        string result;
        backtrack(result, n, k);
        return result;
    }
};

class Solution_2 {
public:
    string getHappyString(int n, int k) {
        stack<string> stack;
        stack.emplace("");

        while (size(stack))
        {
            auto string = std::move(stack.top());
            stack.pop();

            if (size(string) == n)
            {
                if (--k == 0)
                    return string;
                continue;
            }

            char back = size(string) ? string.back() : 0;
            for (char c = 'c'; c >= 'a'; c--)
                if (c != back)
                    stack.push(string + c);
        }

        return "";
    }
};

class Solution_3 {
public:
    string getHappyString(int n, int k) {
        string result;
        return result;
    }
};

int main()
{
    Solution_2 sol;

    cout << sol.getHappyString(1, 3) << endl;
    cout << sol.getHappyString(1, 4) << endl;
    cout << sol.getHappyString(3, 9) << endl;
}