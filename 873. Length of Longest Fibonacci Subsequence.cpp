#include "header.h"

class Solution_1 {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        unordered_set<int> set(begin(arr), end(arr));

        int longest = 0;
        for (int i = 0; i < size(arr); i++)
            for (int j = i + 1; j < size(arr); j++)
            {
                int a = arr[i];
                int b = arr[j];
                int length = 2;

                while (set.contains(a + b))
                {
                    swap(a, b);
                    b += a;
                    longest = max(longest, ++length);
                }
            }
        return longest;
    }
};

class Solution_2 {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        unordered_map<int, int> map(size(arr));
        for (int i = 0; i < size(arr); i++)
            map[arr[i]] = i;

        int longest = 0;
        vector<vector<int>> lengths(size(arr), vector<int>(size(arr), 2));
        for (int i = 1; i < size(arr); i++)
            for (int j = i + 1; j < size(arr); j++)
                if (auto find  = map.find(arr[j] - arr[i]);
                         find != map.end() && find->second < i)
                {
                    lengths[i][j] = lengths[find->second][i] + 1;
                    if (longest < lengths[i][j])
                        longest = lengths[i][j];
                }
        return longest;
    }
};

class Solution_3 {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        unordered_map<int, int> map(size(arr));
        vector<vector<int>> lengths(size(arr), vector<int>(size(arr), 2));

        int longest = 0;
        for (int i = 0; i < size(arr); i++)
        {
            map[arr[i]] = i;
            for (int j = 0; j < i; j++)
                if (auto find  = map.find(arr[i] - arr[j]);
                         find != map.end() && find->second < j)
                {
                    lengths[i][j] = lengths[j][find->second] + 1;
                    if (longest < lengths[i][j])
                        longest = lengths[i][j];
                }
        }

        return longest;
    }
};

class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        vector<vector<int>> lengths(size(arr), vector<int>(size(arr), 2));

        int longest = 0;
        for (int i = 0; i < size(arr); i++)
        {
            int left = 0;
            int right = i - 1;
            while (left < right)
            {
                auto comp = arr[left] + arr[right] <=> arr[i];
                if (comp < 0)
                    left++;
                else if (comp > 0)
                    right--;
                else
                {
                    lengths[i][right] = lengths[right][left] + 1;
                    if (longest < lengths[i][right])
                        longest = lengths[i][right];
                    left++;
                    right--;
                }
            }
        }

        return longest;
    }
};

int main()
{
    Solution sol;

    {
        vector<int> vec = {1,2,3,4,5,6,7,8}; // 5
        cout << sol.lenLongestFibSubseq(vec) << endl;
    }
    {
        vector<int> vec = {1,3,7,11,12,14,18}; // 3
        cout << sol.lenLongestFibSubseq(vec) << endl;
    }
    {
        vector<int> vec = {1,3,5}; // 0
        cout << sol.lenLongestFibSubseq(vec) << endl;
    }
    {
        vector<int> vec = {2,4,7,8,9,10,14,15,18,23,32,50}; // 5
        cout << sol.lenLongestFibSubseq(vec) << endl;
    }
}