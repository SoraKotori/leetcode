#include "header.h"

class Solution {
public:
    string minWindow(string s, string t) {

        array<int, 'z' + 1> map{};
        for (auto c : t)
            map[c]++;

        size_t min_index = size(s);
        size_t min_size = string::npos;
        int match = size(t);
        int left = 0;

        for (int right = 0; right < size(s);)
        {
            if (map[s[right++]]-- > 0)
                match--;

            for (; match == 0; left++)
                if (map[s[left]]++ == 0)
                {
                    match++;
                    if (min_size > right - left)
                        min_size = right - (min_index = left);
                }
        }

        return s.substr(min_index, min_size);
    }
};

int main()
{
    Solution sol;

    cout << sol.minWindow("ADOBECODEBANC", "ABC") << endl;
    cout << sol.minWindow("a", "a") << endl;
    cout << sol.minWindow("a", "aa") << endl;
}