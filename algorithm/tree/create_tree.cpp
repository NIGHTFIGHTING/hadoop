#include <iostream>

using namespace std;

struct TreeNode {
    std::string value;
    TreeNode* left;
    TreeNode* right;
    TreeNode() {
        value.clear();
        left = nullptr;
        right = nullptr;
    }
};


TreeNode* create_tree() {
    std::string str;
    cin >> str;
    TreeNode* root = nullptr;
    if (str != "#") {
        root = new TreeNode;
        root->value = str;
        root->left = create_tree();
        root->right = create_tree();
    }
    return root;
}

void pre_order(TreeNode* root) {
    if (root == nullptr) {
        return ; 
    }
    std::cout << root->value << " ";
    pre_order(root->left);
    pre_order(root->right);
}

int main() {
    TreeNode* root = create_tree();
    pre_order(root);
    std::cout << std::endl;
    return 0;
}
