#include "header.h"

class Solution {
public:
    string removeOccurrences(string s, string part) {
        for (size_t find; (find = s.find(part)) != string::npos; s.erase(find, size(part)));
        return s;
    }
};

class Solution_1 {
public:
    string removeOccurrences(string s, string part)
    {
        vector<int> prefix(size(part));
        for (int index = 1, length = 0; index < size(prefix);)
            if (part[index] == part[length])
                prefix[index++] = ++length;
            else if (length)
                length = prefix[length - 1];
            else
                index++;

        vector<int> match;
        string stack;

        for (char c : s)
        {
            auto length = match.empty() ? 0 : match.back();

            while (length && c != part[length])
                   length = prefix[length - 1];

            match.push_back(c == part[length] ? ++length : 0);
            stack.push_back(c);

            if (length == size(part))
            {
                stack.resize(stack.size() - size(part));
                match.resize(match.size() - size(part));
            }
        }

        return stack;
    }
};

class Solution_2 {
    public:
    string removeOccurrences(string s, string part)
    {
        vector<int> prefix(size(part));
        for (int index = 1, length = 0; index < size(prefix);)
            if (part[index] == part[length])
                prefix[index++] = ++length;
            else if (length)
                length = prefix[length - 1];
            else
                index++;

        vector<int> match(size(s));
        auto begin = std::begin(match);

        for (int first = 0, last = 0; last < size(s); last++)
        {
            auto c = s[last];
            auto length = *begin;

            while (length && c != part[length])
                   length = prefix[length - 1];

            *begin++ = c == part[length] ? ++length : 0;
            s[first++] = c;

            if (length == size(part))
            {
                begin -= size(part);
                first -= size(part);
            }
        }

        return s;
    }
};

int main()
{
    Solution_2 sol;

    string s1 = "daabcbaabcbc", part1 = "abc";
    string result1 = sol.removeOccurrences(s1, part1);
    cout << "result1: " << result1 << endl;

    string s2 = "axxxxyyyyb", part2 = "xy";
    string result2 = sol.removeOccurrences(s2, part2);
    cout << "result2: " << result2 << endl;

    string s3 = "wwwwwwwwwwwwwwwwwwwwwvwwwwswxwwwwsdwxweeohapwwzwuwajrnogb", part3 = "w";
    string result3 = sol.removeOccurrences(s3, part3);
    cout << "result3: " << result3 << endl;

    string s4 = "kpygkivtlqoockpygkivtlqoocssnextkqzjpycbylkaondsskpygkpygkivtlqoocssnextkqzjpkpygkivtlqoocssnextkqzjpycbylkaondsycbylkaondskivtlqoocssnextkqzjpycbylkaondssnextkqzjpycbylkaondshijzgaovndkjiiuwjtcpdpbkrfsi", part4 = "kpygkivtlqoocssnextkqzjpycbylkaonds";
    string result4 = sol.removeOccurrences(s4, part4);
    cout << "result4: " << result4 << endl;
    
    string s5 = "cxdwzolfrccawvewcxdcxdwzolfrcccxdwzolfrccawvewkrawvewcxdwzolfrccawvewkrkccxdwzolfrccawvewkrxdwzolfcxdwzolfrccawvewkrrccacxdwzolfrcccxdwzolfrccawvewkrawvewkrwvewkrrwzolfrccxdwzolfrccawvewkrcawvewkrkryscxcxdwzolfrcxdwzolfrccawvewkrccawvewkrdwzolfrccawvewkrotfbdngngvfrj", part5 = "cxdwzolfrccawvewkr";
    string result5 = sol.removeOccurrences(s5, part5);
    cout << "result5: " << result5 << endl;   
}