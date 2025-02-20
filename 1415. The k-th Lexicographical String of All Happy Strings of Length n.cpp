#include "header.h"

class Solution {
    bool backtrack(string& result, int n, int& k)
    {
        if (size(result) == n)
            return --k == 0;

        char back = size(result) ? result.back() : 0;
        for (auto c : {'a', 'b', 'c'})
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

// 3 * 2 * 2
// aba
// abc
// aca
// acb
// bab
// bac
// bca
// bcb
// cab
// cac
// cba
// cbc
class Solution_3 {
public:
    string getHappyString(int n, int k) {

        int size = 1 << --n; // size = 2 ^ (n - 1)
        if (size * 3 <= --k) // k is index
            return "";

        string result(1, 'a' + k / size);

        
        // 100
        // 010
        while (size /= 2) // size /= 2 need > 0
        {
            k %= size * 2;
            if (k < size)
                result.push_back('a' + (result.back() == 'a'));
            else
                result.push_back('c' - (result.back() == 'c'));
            // if (k < size)
            //     result.push_back(result.back() == 'a' ? 'b' : 'a');
            // else
            //     result.push_back(result.back() == 'c' ? 'b' : 'c');
        }
        return result;
    }
};

int main()
{
    Solution_3 sol;

    cout << sol.getHappyString(1, 3) << endl; // c
    cout << sol.getHappyString(1, 4) << endl; // ""
    cout << sol.getHappyString(3, 9) << endl; // cab
    cout << sol.getHappyString(10, 100) << endl; // "abacbabacb"
}