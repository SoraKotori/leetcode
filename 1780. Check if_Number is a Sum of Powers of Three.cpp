#include "header.h"

class Solution_1 {
public:
    bool checkPowersOfThree(int n) {
        int power3 = 1;
        for (; power3 < n; power3 *= 3);

        while (n && power3)
        {
            if (n >= power3)
                n -= power3;

            power3 /= 3;
        }

        return n == 0;
    }
};

class Solution {
public:
    bool checkPowersOfThree(int n) {
        for (; n; n /= 3)
            if (n % 3 == 2)
                return false;
        return true;
    }
};

int main()
{
    Solution sol;

    cout << sol.checkPowersOfThree(12) << endl;
    cout << sol.checkPowersOfThree(91) << endl;
    cout << sol.checkPowersOfThree(21) << endl;
}