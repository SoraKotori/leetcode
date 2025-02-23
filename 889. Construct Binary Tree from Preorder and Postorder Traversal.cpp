#include "header.h"

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution_1 { // 疊代方法
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        vector<TreeNode*> stack = { new TreeNode(preorder[0]) };

        auto first = begin(postorder);
        for (int i = 1; i < size(preorder); i++)
        {
            while (*first == stack.back()->val)
            {
                stack.pop_back();
                first++;
            }

            auto node = new TreeNode(preorder[i]);
            (stack.back()->left ? stack.back()->right
                                : stack.back()->left) = node;
            stack.push_back(node);
        }

        return stack[0];
    }
};

class Solution { // 遞迴方法
public:
    TreeNode* dfs(vector<int>& preorder, vector<int>& postorder, int& pre_index, int& post_index)
    {
        auto node = new TreeNode(preorder[pre_index++]);

        if (node->val != postorder[post_index]) // 如果 new TreeNode 已經是葉子，則不需要再生成左、右子樹
            node->left = dfs(preorder, postorder, pre_index, post_index);

        if (node->val != postorder[post_index]) // 左子樹生成後，檢查被左子樹更新的 post_index，若 node 等於 postorder，則代表需要往上一層，不需要再生成右子樹
            node->right = dfs(preorder, postorder, pre_index, post_index);

        post_index++; // 子樹都生成完畢後 node 勢必等於 postorder，所以要移動到下一個
        return node;
    }

    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        int pre_index = 0;
        int post_index = 0;
        return dfs(preorder, postorder, pre_index, post_index);
    }
};

// 輔助函式：層次遍歷印出樹節點（以空格區隔）
void printLevelOrder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        cout << node->val << " ";
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
    cout << endl;
}

int main() {
    Solution sol;
    
    // 範例 1
    vector<int> preorder1 = {1, 2, 4, 5, 3, 6, 7};
    vector<int> postorder1 = {4, 5, 2, 6, 7, 3, 1};
    TreeNode* tree1 = sol.constructFromPrePost(preorder1, postorder1);
    cout << "範例 1 的層次遍歷結果：";
    printLevelOrder(tree1);
    
    // 範例 2
    vector<int> preorder2 = {1};
    vector<int> postorder2 = {1};
    TreeNode* tree2 = sol.constructFromPrePost(preorder2, postorder2);
    cout << "範例 2 的層次遍歷結果：";
    printLevelOrder(tree2);
    
    // 範例 3
    vector<int> preorder3 = {2,1};
    vector<int> postorder3 = {1,2};
    TreeNode* tree3 = sol.constructFromPrePost(preorder3, postorder3);
    cout << "範例 3 的層次遍歷結果：";
    printLevelOrder(tree3);

    return 0;
}