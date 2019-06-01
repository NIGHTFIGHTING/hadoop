#include <iostream>
#include <vector>

using namespace std;


struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode() {
        value = -1;
        left = nullptr;
        right = nullptr;
    }
};

void insert_tree(TreeNode** tree, int value) {
    if (tree == nullptr) {
        return ;
    }
    if ((*tree) == nullptr) {
        TreeNode* temp = new TreeNode;
        temp->value = value;
        cout << "hhhh" << endl;
        return ;
    }
    while(1) {
        cout << "bbbbbb" << endl;
        if (value > (*tree)->value) {
            if ((*tree)->right == nullptr) {
                (*tree)->right = new TreeNode;
                (*tree)->right->value = value;
                return ;
            }
            tree = &((*tree)->right);
        } else {
            if ((*tree)->left == nullptr) {
                (*tree)->left = new TreeNode;
                (*tree)->left->value = value;
                return ;
            }
            tree = &((*tree)->left);
        }
    }
}

// 向以tree为根的二分搜索树中插入元素value,递归算法
// 返回插入新节点后二分搜索树的根
TreeNode* insert_tree2(TreeNode** tree, int value) {
    if ((*tree) == nullptr) {
        (*tree) = new TreeNode;
        (*tree)->value = value;
    }
    if (value > (*tree)->value) {
        (*tree)->right = insert_tree2(&((*tree)->right), value);
    } else if (value < (*tree)->value) {
        (*tree)->left = insert_tree2(&((*tree)->left), value);
    }
    return (*tree);
}

TreeNode* create_tree(const std::vector<int> arr) {
    TreeNode* root = nullptr;
    for (const auto& ite : arr) {
        //cout << ite << " ";
        //insert_tree(&root, ite);
        insert_tree2(&root, ite);
    }
    return root;
}

// 以tree为根的二分搜索树中是否包含元素value,递归算法
bool contains(TreeNode* tree, int value) {
    if (tree == nullptr) {
        return false;
    }
    if (tree->value == value) {
        return true;
    } else if (tree->value > value) {
        return contains(tree->left, value);
    } else {    // tree->value < value
        return contains(tree->right, value);
    }
}

void middle_print(TreeNode* root) {
    if (!root) {
        return;
    }
    middle_print(root->left);
    std::cout << root->value << " ";
    middle_print(root->right);
}

int main() {
    vector<int> arr{3,2,5,6,7,8,1,0,4,9};
    TreeNode* tree = create_tree(arr);
    middle_print(tree);
    std::cout << std::endl;
    std::cout << "contains(100): " << contains(tree, 100) << endl;
    std::cout << "contains(6): " << contains(tree, 6) << endl;
    return 0;
}
