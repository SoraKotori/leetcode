#include "header.h"

// 5 5 2 2 5
// 5 5 2 2|5
// 5 5 2|2 5
// 5 5 2|2|5
// 5 5|2 2 5
// 5 5|2 2|5
// 5 5|2|2 5
// 5 5|2|2|5
// 5|5 2 2 5
// 5|5 2 2 5
// 5|5 2 2|5
// 5|5 2|2 5
// 5|5 2|2|5
// 5|5|2 2 5
// 5|5|2 2|5
// 5|5|2|2 5
// 5|5|2|2|5

class Solution {
    bool CanPartition(int num, int target)
    {
        if (num == target)
            return true;

        for (int div = 10;   num / div && target > num % div; div *= 10)
            if (CanPartition(num / div,   target - num % div))
                return true;
        return false;
    }
public:
    int punishmentNumber(int n) {
        int sum = 0;
        for (int i = 1; i <= n; i++)
            if (int square = i * i; CanPartition(square, i))
                sum += square;
        return sum;
    }
};

int main()
{
    Solution sol;

    cout << sol.punishmentNumber(1) << endl;
    cout << sol.punishmentNumber(10) << endl;
    cout << sol.punishmentNumber(37) << endl;
    cout << sol.punishmentNumber(235) << endl;
}