#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

struct TrieTree {
    char* str;
    bool end;
    TrieTree* next[26];
    // std::map<char, TrieTree*> next;
    TrieTree() {
        str = nullptr;
        end = false;
        memset(next, 0, sizeof(next));
    }
};

TrieTree* create_trie_node() {
    TrieTree* temp = new TrieTree;
    return temp;
}

TrieTree* root = create_trie_node();

void insert_tree(const char* str) {
    TrieTree* temp = root;
    char* ptr = const_cast<char*>(str);
    while(*str != '\0') {
        // cout << *str - 97 << endl;
        if (temp->next[*str - 97] == nullptr) {
            temp->next[*str - 97] = create_trie_node();
        }
        temp = temp->next[*str - 97];
        str++;
    }
    temp->end = true;
    temp->str = new char(strlen(str) + 1);
    strcpy(temp->str, ptr);
}


void print_trie(TrieTree* root) {
    if (root == nullptr) {
        return ;
    }
    if (root->end) {
        printf("%s\n", root->str);
    }
    for (int i = 0; i < 26; ++i) {
        print_trie(root->next[i]);
    }
}

bool find_trie_tree(TrieTree* root, const char* str) {
    TrieTree* temp = root;
    while(*str != '\0') {
        if (temp->next[*str - 97] != nullptr) {
            temp = temp->next[*str - 97];
            str++;
        } else {
            return false;
        }
    }
    if (temp->end) {
        return true;
    }
    return false;
}

bool is_prefix(TrieTree* root, const char* str) {
    TrieTree* temp = root;
    while(*str != '\0') {
        if (temp->next[*str - 97] != nullptr) {
            temp = temp->next[*str - 97];
            str++;
        } else {
            return false;
        }
    }
    return true;
}

int main() {
    insert_tree("abc");
    insert_tree("abcd");
    print_trie(root);
    std::cout << "find_trie_tree(root, 'abc'): " << find_trie_tree(root, "abc") << std::endl;
    std::cout << "find_trie_tree(root, 'abcd'): " << find_trie_tree(root, "abcd") << std::endl;
    std::cout << "find_trie_tree(root, 'abcde'): " << find_trie_tree(root, "abcde") << std::endl;
    std::cout << "is_prefix(root, 'ab'): " << is_prefix(root, "ab") << std::endl;
    return 0;
}
