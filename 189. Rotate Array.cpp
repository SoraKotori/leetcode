#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <iomanip>

using namespace std;

void print(const vector<int>& v)
{
    for (auto i : v)
    {
        cout << setw(3) << i << " ";
    }
    cout << endl;
}

template<typename RandomAccessIterator>
auto std_rotate(RandomAccessIterator first,
       RandomAccessIterator middle,
       RandomAccessIterator last)
{
    // 如果要旋轉的區間沒有意義（第一段或第二段長度為 0），直接回傳
    if (first == middle)
        return last;
    if (middle == last)
        return first;

    // n 為整個區間的長度
    auto n = last - first;     // total length
    // k 為左半段的長度（也就是要移動到後面去的大小）
    auto k = middle - first;   // rotate length

    // 如果剛好左右兩段等長，直接 swap 兩段即可
    if (k == n - k) 
    {
        // 兩個區段互換
        std::swap_ranges(first, middle, middle);
        return middle;
    }

    // 計算旋轉後，應該回傳的新起點
    // 例如原先要把 [first, middle) 移到最後，因此新的起點就是原先的 middle
    // 不過此處採用的是另一種計算方式：ret = first + (last - middle)
    // 指的是『將 [middle, last) 放到前面後，該區段的起點』
    auto ret = first + (last - middle);

    // p 用來從左邊開始做移動
    auto p = first;

    // 進入主要旋轉迴圈
    for (;;)
    {
        // 如果左半段長度 k 比右半段 (n - k) 小
        if (k < n - k)
        {
            // 對應程式碼中，如果 k = 1，而且型別是 trivially moveable，
            // 會用較簡單的做法直接搬移一個元素。
            // 這裡略過細節，保留核心概念：
            //
            // 1. 先把左半段 k 個元素換到右半段
            // 2. 更新區間大小 n，然後不斷迴圈
            //
            // 以下為概念示意：
            auto q = p + k;
            // 先把 [p, p + (n-k)) 這一段與 [q, q + (n-k)) 做配對交換
            for (auto i = 0; i < (n - k); ++i)
            {
                std::iter_swap(p, q);
                ++p;
                ++q;
            }

            // 交換完後，左半段已移到後面，更新 n 和 k
            n = n % k;     // 換完之後「未處理」的長度剩多少
            if (n == 0)
                return ret; // 如果沒有剩餘，就結束了

            // 這裡再跟標準程式碼類似，重新 swap(n, k)，更新 k = n - k 等。
            std::swap(n, k);
            k = n - k;
        }
        else
        {
            // 否則，代表右半段比較小，做類似處理，但把右半段搬到前面
            k = n - k; // 先把 k 更新為右半段長度

            // 同理，如果 k = 1，而且型別可直接移動，就做簡化
            // 這裡同樣省略細節，保留核心迴圈示意：
            auto q = p + n;
            // p 先移到右半段要與誰做 swap 的位置
            p = q - k;
            for (auto i = 0; i < (n - k); ++i)
            {
                --p;
                --q;
                std::iter_swap(p, q);
            }

            n = n % k;
            if (n == 0)
                return ret;

            std::swap(n, k);
        }

        print(vector<int>(first, last));
    }
}

class Solution_iterator {
public:
    void rotate(vector<int>& nums, int k) {

        auto first = begin(nums);
        auto last = end(nums);
        auto middle = last - k % size(nums);
        auto next = middle;

        while (first != next)
        {
            iter_swap(first++, next++);
            if (next == last)
                next = middle;
            else if (middle == first)
                     middle = next;
        }
    }
}; 

class Solution2
{
public:
    void rotate(int nums[], int n, int k) 
    {
        if ((n == 0) || (k <= 0) || (k%n == 0))
        {
            return;
        }
        
        k = k%n;
        // Rotation to the right by k steps is equivalent to swapping 
        // the two subarrays nums[0,...,n - k - 1] and nums[n - k,...,n - 1].
        int start = 0;
        int tmp = 0;
        while (k > 0)
        {
            if (n - k >= k)
            {
                // The left subarray with size n - k is longer than 
                // the right subarray with size k. Exchange 
                // nums[n - 2*k,...,n - k - 1] with nums[n - k,...,n - 1].
                for (int i = 0; i < k; i++)
                {
                    tmp = nums[start + n - 2*k + i];
                    nums[start + n - 2*k + i] = nums[start + n - k + i];
                    nums[start + n - k + i] = tmp;
                }
                
                // nums[n - 2*k,...,n - k - 1] are in their correct positions now.
                // Need to rotate the elements of nums[0,...,n - k - 1] to the right 
                // by k%n steps.
                n = n - k;
                k = k%n;
            }
            else
            {
                // The left subarray with size n - k is shorter than 
                // the right subarray with size k. Exchange 
                // nums[0,...,n - k - 1] with nums[n - k,...,2*(n - k) - 1].
                for (int i = 0; i < n - k; i++)
                {
                    tmp = nums[start + i];
                    nums[start + i] = nums[start + n - k + i];
                    nums[start + n - k + i] = tmp;
                }
                
                // nums[n - k,...,2*(n - k) - 1] are in their correct positions now.
                // Need to rotate the elements of nums[n - k,...,n - 1] to the right 
                // by k - (n - k) steps.
                tmp = n - k;
                n = k;
                k -= tmp;
                start += tmp;
            }
        }
    }
};

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        auto first = begin(nums);
        auto last = end(nums);
        auto midden = last - k % size(nums);

        for (size_t lsize, rsize;
            (lsize = distance(first, midden)) &&
            (rsize = distance(midden, last));)
        {
            if (lsize > rsize)
            {
                last = swap_ranges(midden, last, midden - rsize);
                midden -= rsize;
            }
            else
            {
                first = swap_ranges(midden, midden + lsize, first);
                midden += lsize;
            }
        }
    }
};

/*
k = 4
1 2 3 4 5|6 7 8 9
1|6 7 8 9}2 3 4 5
6{1|7 8 9}2 3 4 5

6 7 8 9|1 2 3 4 5

k = 5
1 2 3 4|5 6 7 8 9
5 6 7 8{1 2 3 4|9
5 6 7 8{1 2 3|9}4

5 6 7 8 9|1 2 3 4
*/

int main(int argc, char const *argv[])
{
    Solution s;

    auto iota_view1 = std::ranges::iota_view(1, 10);
    vector<int> vec1(iota_view1.begin(), iota_view1.end());
    s.rotate(vec1, 5);
    print(vec1);

    auto iota_view2 = std::ranges::iota_view(1, 28);
    vector<int> vec2(iota_view2.begin(), iota_view2.end());
    s.rotate(vec2, 11);
    print(vec2);

    return 0;
}
