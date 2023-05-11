#include <iostream>
#include <vector>

using namespace std;


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val): val(val), left(nullptr), right(nullptr) {}
};

// Given two binary trees, write a function to check if they are the same or not.
// Two binary trees are considered the same if they are structurally identical
// and the nodes have the same value.
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p->val != q->val) { return false; }

    bool left_same;
    if (p->left != nullptr && q->left != nullptr) {
        left_same = isSameTree(p->left, q->left);
    } else if (p->left == nullptr && q->left == nullptr) {
        left_same = true;
    } else {
        left_same = false;
    }
    
    bool right_same;
    if (p->right != nullptr && q->right != nullptr) {
        right_same = isSameTree(p->right, q->right);
    } else if (p->right == nullptr && q->right == nullptr) {
        right_same = true;
    } else {
        right_same = false;
    }
    
    return left_same && right_same;
}

bool symmetricHelper(TreeNode* p, TreeNode* q) {
    if (p->val != q->val) { return false; }

    bool left_same;
    if (p->left != nullptr && q->right != nullptr) {
        left_same = symmetricHelper(p->left, q->right);
    } else if (p->left == nullptr && q->right == nullptr) {
        left_same = true;
    } else {
        left_same = false;
    }
    
    bool right_same;
    if (p->right != nullptr && q->left != nullptr) {
        right_same = symmetricHelper(p->right, q->left);
    } else if (p->right == nullptr && q->left == nullptr) {
        right_same = true;
    } else {
        right_same = false;
    }
    
    return left_same && right_same;
}
// Given a binary tree, check whether it is a mirror of itself
// (ie, symmetric around its center).
bool isSymmetric(TreeNode* root) {
    return symmetricHelper(root, root);
}

vector<TreeNode*> levelOrderNodes(TreeNode* root);
// Given a binary tree, implement level order traversal
void levelOrder(TreeNode* root) {
    vector<TreeNode*> nodes = levelOrderNodes(root);
    for (auto node: nodes) {
        cout << node->val << ' ';
    }
}

vector<TreeNode*> levelOrderNodes(TreeNode* root) {
    vector<TreeNode*> nodes;
    nodes.push_back(root);
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->left != nullptr) {
            nodes.push_back(nodes[i]->left);
        }
        if (nodes[i]->right != nullptr) {
            nodes.push_back(nodes[i]->right);
        }
    }
    return nodes;
}


int main() {
    
    TreeNode* root1 = new TreeNode(10);
    root1->left = new TreeNode(5);
    root1->left->left = new TreeNode(2);
    root1->left->left->left = new TreeNode(1);
    root1->left->right = new TreeNode(7);

    root1->right = new TreeNode(15);
    root1->right->left = new TreeNode(12);
    root1->right->right = new TreeNode(17);
    root1->right->right->right = new TreeNode(20);
    
    TreeNode* root2 = new TreeNode(10);
    root2->left = new TreeNode(5);
    root2->left->left = new TreeNode(2);
    root2->left->left->left = new TreeNode(1);
    root2->left->right = new TreeNode(7);

    root2->right = new TreeNode(16);
    root2->right->left = new TreeNode(12);
    root2->right->right = new TreeNode(17);
    root2->right->right->right = new TreeNode(20);

    TreeNode* root3 = new TreeNode(10);
    root3->right = new TreeNode(5);
    root3->right->right = new TreeNode(2);
    root3->right->right->right = new TreeNode(1);
    root3->right->left = new TreeNode(7);

    root3->left = new TreeNode(5);
    root3->left->left = new TreeNode(2);
    root3->left->left->left = new TreeNode(1);
    root3->left->right = new TreeNode(7);

    
    TreeNode* root4 = new TreeNode(10);
    root4->right = new TreeNode(5);
    root4->right->right = new TreeNode(2);
    root4->right->right->right = new TreeNode(1);
    root4->right->left = new TreeNode(7);

    root4->left = new TreeNode(5);
    root4->left->left = new TreeNode(2);
    root4->left->left->left = new TreeNode(1);
    root4->left->right = new TreeNode(8);

    cout << isSameTree(root1, root1) << endl;
    cout << isSameTree(root1, root2) << endl;
    cout << isSymmetric(root3) << endl;
    cout << isSymmetric(root4) << endl;
            
    return 0;
}