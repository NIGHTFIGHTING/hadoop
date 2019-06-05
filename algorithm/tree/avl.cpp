#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    int height;
    TreeNode() {
        value = -1;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

TreeNode* right_rotate(TreeNode*& root);
TreeNode* left_rotate(TreeNode*& root);
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

// 树的高度
int get_height(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return root->height;
}

//  平衡因子
int get_balance_factor(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return get_height(root->left) - get_height(root->right);
}

// 向以tree为根的二分搜索树中插入元素value,递归算法
// 返回插入新节点后二分搜索树的根
TreeNode* insert_tree2(TreeNode** tree, int value) {
    if ((*tree) == nullptr) {
        (*tree) = new TreeNode;
        (*tree)->value = value;
        return (*tree);
    }
    if (value > (*tree)->value) {
        (*tree)->right = insert_tree2(&((*tree)->right), value);
    } else if (value < (*tree)->value) {
        (*tree)->left = insert_tree2(&((*tree)->left), value);
    }
    // 更新height
    (*tree)->height = 1 + max(get_height((*tree)->left), get_height((*tree)->right));
    // 计算平衡因子
    int balance_factor = get_balance_factor(*tree);
    if (abs(balance_factor) > 1) {
        std::cout << "unbalanced: " << balance_factor << std::endl;
    }

    // 平衡维护
    // LL
    if (balance_factor > 1 && get_balance_factor((*tree)->left) >= 0) {
        return right_rotate(*tree);
    }
    // RR
    if (balance_factor < -1 && get_balance_factor((*tree)->right) <= 0) {
        return left_rotate(*tree);
    }
    // LR
    if (balance_factor > 1 && get_balance_factor((*tree)->left) < 0) {
        (*tree)->left = left_rotate((*tree)->left);
        return right_rotate(*tree);
    }
    // RL
    if (balance_factor < -1 && get_balance_factor((*tree)->right) > 0) {
        (*tree)->right = right_rotate((*tree)->right);
        return left_rotate(*tree);
    }

    return (*tree);
}

// 对节点y进行向右旋转操作，返回旋转后新的根节点x
//        y                              x
//       / \                           /   \
//      x   T4     向右旋转 (y)        z     y
//     / \       - - - - - - - ->    / \   / \
//    z   T3                       T1  T2 T3 T4
//   / \
// T1   T2
TreeNode* right_rotate(TreeNode*& y) {
    TreeNode* x = y->left;
    TreeNode* t3 = x->right;

    // 向右旋转过程
    x->right = y;
    y->left = t3;

    // 更新height
    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;

    return x;
}

// 对节点y进行向左旋转操作，返回旋转后新的根节点x
//    y                             x
//  /  \                          /   \
// T1   x      向左旋转 (y)       y     z
//     / \   - - - - - - - ->   / \   / \
//   t2  z                     T1 t2 t3 T4
//      / \
//     t3 T4
TreeNode* left_rotate(TreeNode*& y) {
    TreeNode* x = y->right;
    TreeNode* t2 = x->left;

    // 向左旋转过程
    x->left = y;
    y->right = t2;

    // 更新height
    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;

    return x;
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

// 中序遍历
void in_order(TreeNode*root, vector<int>* arr) {
    if (root == nullptr) {
        return ;
    }
    in_order(root->left, arr);
    arr->push_back(root->value);
    in_order(root->right, arr);
}

// 判断以root为根的树,是否为一颗二分搜索树
bool is_bst(TreeNode* root) {
    vector<int> arr;
    in_order(root, &arr);
    for (int i = 1 ; i < arr.size(); ++i) {
        // cout << "arr[i-1]: " << arr[i-1] << " arr[i]: " << arr[i] << endl;
        if (arr[i-1] > arr[i]) {
            return false;
        }
    }
    return true;
}

// 判断以root为根的二叉树是否是一颗平衡二叉树,递归算法
bool is_balanced(TreeNode* root) {
    if (root == nullptr) {
        return true;
    }
    int balance_factor = get_balance_factor(root);
    if (abs(balance_factor) > 1) {
        return false;
    }
    return get_balance_factor(root->left) && get_balance_factor(root->right); 
}

#if 0
// 对接点y进行向左旋转操作,返回旋转后新的根节点x
//     y                        x
//    / \                      / \
//   T1  x    向右旋转(y)     y   z
//      / \   ------------>  / \  / \
//     T2  z                T1 T2 T3 T4
//        / \
//       T3 T4

TreeNode* left_rotate(TreeNode** root) {
    TreeNode* x = (*root)->right;
    TreeNode* t2 = x->left;

    // 向左旋转过程
    x->left = (*root);
    (*root)->right = t2;

    // 更新height
    (*root)->height = max(get_height((*root)->left), get_height((*root)->right)) + 1;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    return x;
}


// 对接点y进行向右旋转操作,返回旋转后新的根节点x
//     y                        x
//    / \                      / \
//   x   T4  向右旋转(y)      z   y
//  / \      ------------>   / \  / \
// z  T3                    T1 T2 T3 T4
/// \
//T1 T2
TreeNode* right_rotate(TreeNode** root) {
    TreeNode* x = (*root)->left;
    TreeNode* t3 = x->right;

    // 向右旋转过程
    x->right = *root; 
    (*root)->left = t3;

    // 更新height
    (*root)->height = max(get_height((*root)->left), get_height((*root)->right)) + 1;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    return x;
}

#endif
int main() {
    vector<int> arr{3,2,5,6,7,8,1,0,4,9};
    TreeNode* tree = create_tree(arr);
    middle_print(tree);
    std::cout << std::endl;
    std::cout << "contains(100): " << contains(tree, 100) << endl;
    std::cout << "contains(6): " << contains(tree, 6) << endl;
    std::cout << "is_bst(tree): " << is_bst(tree) << endl;
    std::cout << "is_balanced(tree): " << is_balanced(tree) << endl;
    return 0;
}
