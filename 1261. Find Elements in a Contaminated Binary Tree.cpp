#include "header.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class FindElements_1 {
    TreeNode* root_;
    void backtrack(TreeNode* node)
    {
        if (node->left)
        {
            node->left->val = node->val * 2 + 1;
            backtrack(node->left);
        }

        if (node->right)
        {
            node->right->val = node->val * 2 + 2;
            backtrack(node->right);
        }
    }

public:
    FindElements_1(TreeNode* root) {
        root->val = 0;
        backtrack(root);
        root_ = root;
    }
    
    bool find(int target) {
        stack<TreeNode*> stack;
        stack.push(root_);

        while (size(stack))
        {
            auto node = stack.top();
            stack.pop();

            if (node->val == target)
                return true;
            if (node->left)
                stack.push(node->left);
            if (node->right)
                stack.push(node->right);
        }
        return false;
    }
};

class FindElements_2 {
    unordered_set<int> set;
public:
    FindElements_2(TreeNode* root) {
        stack<pair<int, TreeNode*>> stack;

        stack.emplace(0, root);
        while (size(stack))
        {
            auto [val, node] = move(stack.top());
            stack.pop();

            set.insert(val);
            if (node->left)
                stack.emplace(val * 2 + 1, node->left);
            if (node->right)
                stack.emplace(val * 2 + 2, node->right);
        }
    }
    
    bool find(int target) {
        return set.contains(target);
    }
};

class FindElements {
    unordered_set<int> set;
    void dfs(TreeNode* node, int val)
    {
        if (node == nullptr) return;

        set.insert(val);
        dfs(node->left, val * 2 + 1);
        dfs(node->right, val * 2 + 2);
    }
public:
    FindElements(TreeNode* root) {
        dfs(root, 0);
    }
    
    bool find(int target) {
        return set.contains(target);
    }
};

int main() {
    // 範例 1: 輸入:  ["FindElements","find","find"]
    //               [[[-1,null,-1]],[1],[2]]
    // 預期輸出:     [null,false,true]
    {
        // 建立樹狀結構: root(-1), 右子樹(-1), 左子樹為空
        TreeNode* root1 = new TreeNode(-1);
        root1->right = new TreeNode(-1);

        FindElements findElements1(root1);

        // 測試 find(1) 與 find(2)
        cout << boolalpha << "Example1 find(1): " << findElements1.find(1) << endl; // false
        cout << boolalpha << "Example1 find(2): " << findElements1.find(2) << endl; // true
        cout << "------------------------" << endl;
    }

    // 範例 2: 輸入:  ["FindElements","find","find","find"]
    //               [[[-1,-1,-1,-1,-1]],[1],[3],[5]]
    // 預期輸出:     [null,true,true,false]
    {
        // 建立樹狀結構 (滿二元樹高度2，左子樹再延伸兩層):
        //         -1
        //        /  \
        //      -1    -1
        //     / \
        //   -1  -1
        TreeNode* root2 = new TreeNode(-1);
        root2->left = new TreeNode(-1);
        root2->right = new TreeNode(-1);
        root2->left->left = new TreeNode(-1);
        root2->left->right = new TreeNode(-1);

        FindElements findElements2(root2);

        // 測試 find(1), find(3), find(5)
        cout << boolalpha << "Example2 find(1): " << findElements2.find(1) << endl; // true
        cout << boolalpha << "Example2 find(3): " << findElements2.find(3) << endl; // true
        cout << boolalpha << "Example2 find(5): " << findElements2.find(5) << endl; // false
        cout << "------------------------" << endl;
    }

    // 範例 3: 輸入:  ["FindElements","find","find","find","find"]
    //               [[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]
    // 預期輸出:     [null,true,false,false,true]
    {
        // 根據題目描述，此樹的 BFS (層序) 為: [-1, null, -1, -1, null, -1]
        // 實際結構如下：
        //            (root -1)
        //              /    \
        //           null    (-1)
        //                  /   \
        //               (-1)   null
        //               /
        //             (-1)
        TreeNode* root3 = new TreeNode(-1);
        root3->left = nullptr;
        root3->right = new TreeNode(-1);
        root3->right->left = new TreeNode(-1);
        root3->right->right = nullptr;
        root3->right->left->left = new TreeNode(-1);

        FindElements findElements3(root3);

        // 測試 find(2), find(3), find(4), find(5)
        cout << boolalpha << "Example3 find(2): " << findElements3.find(2) << endl; // true
        cout << boolalpha << "Example3 find(3): " << findElements3.find(3) << endl; // false
        cout << boolalpha << "Example3 find(4): " << findElements3.find(4) << endl; // false
        cout << boolalpha << "Example3 find(5): " << findElements3.find(5) << endl; // true
        cout << "------------------------" << endl;
    }

    return 0;
}