#include "header.h"

class Solution {
public:
    string removeOccurrences(string s, string part) {
        for (size_t find; (find = s.find(part)) != string::npos; s.erase(find, size(part)));
        return s;
    }
};

vector<int> computeLongestPrefixSuffix(string pattern) {
    // Array to store the longest proper prefix which is also a suffix
    vector<int> lps(pattern.length(), 0);

    // Initialize tracking variables for prefix and current position
    for (int current = 1, prefixLength = 0; current < pattern.length();) {
        // If characters match, extend the prefix length
        if (pattern[current] == pattern[prefixLength]) {
            // Store the length of matching prefix
            lps[current] = ++prefixLength;
            current++;
        }
        // If characters don't match and we're not at the start of the
        // pattern
        else if (prefixLength != 0) {
            // Backtrack to the previous longest prefix-suffix
            prefixLength = lps[prefixLength - 1];
        }
        // If no match and no prefix to backtrack
        else {
            // No prefix-suffix match found
            lps[current] = 0;
            current++;
        }
    }

    // Return the computed longest prefix-suffix array
    return lps;
}

// {
// vector<int> kmp(b.size() + 1),
// idx(a.size() + 1),
// st;
// for (int i = 1, j = 0; i < b.size();)
//     if (b[i] == b[j]) 
//         kmp[++i] = ++j;
//     else {
//         i += j == 0;
//         j = kmp[j];
//     }
// }

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

        vector<int> equal;
        string stack;

        for (int index = 0, prefix_index = 0; index < size(s);)
        {
            stack.push_back(s[index]);
            if (stack.back() == part[prefix_index])
            {
                equal.push_back(prefix_index + 1);
                index++;
            }
            else if (prefix_index)
                prefix_index = prefix[prefix_index - 1];
            else
            {
                equal.push_back(0);
                index++;
            }

            if (size(part) == equal.back())
                for (int i = equal.back(); i ; i--)
                {
                    stack.pop_back();
                    equal.pop_back();
                }
        }

        return stack;
    }
};

int main()
{
    Solution_1 sol;

    string s5 = "cxdwzolfrccawvewcxdcxdwzolfrcccxdwzolfrccawvewkrawvewcxdwzolfrccawvewkrkccxdwzolfrccawvewkrxdwzolfcxdwzolfrccawvewkrrccacxdwzolfrcccxdwzolfrccawvewkrawvewkrwvewkrrwzolfrccxdwzolfrccawvewkrcawvewkrkryscxcxdwzolfrcxdwzolfrccawvewkrccawvewkrdwzolfrccawvewkrotfbdngngvfrj", part5 = "cxdwzolfrccawvewkr";
    string result5 = sol.removeOccurrences(s5, part5);
    cout << "result5: " << result5 << endl;    

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
}