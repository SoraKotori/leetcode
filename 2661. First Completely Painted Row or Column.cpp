#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        int m = size(mat);
        int n = size(mat[0]);

        vector<int> row_count(m, 0);
        vector<int> col_count(n, 0);
        vector<pair<int*, int*>> map(size(arr) + 1);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                map[mat[i][j]] = make_pair(&row_count[i], &col_count[j]);

        for (auto first = begin(arr), last = end(arr); first != last; first++)
        {
            const auto& [row_it, col_it] = map[*first];
            if (++(*row_it) == n || ++(*col_it) == m)
                return distance(begin(arr), first);
        }

        return 0;
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {1, 4, 5, 2, 6, 3};
    vector<vector<int>> mat1 = {{4, 3, 5}, {1, 2, 6}};
    cout << sol.firstCompleteIndex(arr1, mat1) << endl;

    vector<int> arr2 = {6, 2, 3, 1, 4, 5};
    vector<vector<int>> mat2 = {{5, 1}, {2, 4}, {6, 3}};
    cout << sol.firstCompleteIndex(arr2, mat2) << endl;

    return 0;
}