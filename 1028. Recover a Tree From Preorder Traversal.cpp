#include "header.h"

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution_2 {
public:
    TreeNode* recoverFromPreorder(string traversal) {
        stack<TreeNode*> stack;

        const char* first = data(traversal);
        auto last = first + size(traversal);

        int val;
        first = from_chars(first, last, val).ptr;
        stack.push(new TreeNode(val));

        while (first != last)
        {
            auto depth = 0;
            while (*first == '-')
            {
                first++;
                depth++;
            }

            first = from_chars(first, last, val).ptr;
            auto node = new TreeNode(val);

            while (size(stack) != depth)
                stack.pop();

            (stack.top()->left ? stack.top()->right
                               : stack.top()->left) = node;
            stack.push(node);
        }

        while (size(stack) != 1)
            stack.pop();
        return stack.top();
    }
};

class Solution {
public:
    TreeNode* recoverFromPreorder(string traversal) {
        vector<TreeNode*> vec;

        const auto* first = data(traversal);
        auto last = first + size(traversal);

        while (first != last)
        {
            int depth = 0;
            for (; *first == '-'; first++, depth++);

            int val;
            first = from_chars(first, last, val).ptr;

            auto node = new TreeNode(val);
            if (depth == size(vec))
                vec.push_back(node);
            else
                vec[depth] = node;

            if (depth)
                (vec[depth - 1]->left ? vec[depth - 1]->right
                                      : vec[depth - 1]->left) = node;
        }
        return vec[0];
    }
};

// 將二元樹用 BFS 形式輸出到 vector<string>
// 包含空節點則輸出 "null"，最後再把尾端多餘的 "null" 移除。
vector<string> bfs(TreeNode* root) {
    vector<string> result;
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        
        if (curr) {
            result.push_back(to_string(curr->val));
            q.push(curr->left);
            q.push(curr->right);
        } else {
            // 若遇到空節點，記錄 "null"
            result.push_back("null");
        }
    }
    // 移除末端多餘的 "null"
    while (!result.empty() && result.back() == "null") {
        result.pop_back();
    }
    return result;
}

int main() {
    // 建立 Solution 物件
    Solution sol;

    // 題目範例輸入
    vector<string> tests = {
        "1-2--3--4-5--6--7",
        "1-2--3---4-5--6---7",
        "1-401--349---90--88"
    };

    // 逐一測試
    for (auto &traversal : tests) {
        TreeNode* root = sol.recoverFromPreorder(traversal);
        vector<string> levelOrderResult = bfs(root);

        cout << "Input: " << traversal << endl;
        cout << "Output: [";
        for (int i = 0; i < (int)levelOrderResult.size(); ++i) {
            cout << levelOrderResult[i];
            if (i < (int)levelOrderResult.size() - 1) {
                cout << ",";
            }
        }
        cout << "]" << endl << endl;
    }

    return 0;
}