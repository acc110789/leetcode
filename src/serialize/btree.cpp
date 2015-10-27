// Copyright (C) 2015 Leslie Zhai <xiangzhai83@gmail.com>

#include <iostream>
#include <string>
#include <vector>

struct node 
{
    int val;
    node *left;
    node *right;
};

class btree 
{
public:
    explicit btree() {}
    ~btree() { destroy_tree(root); }

    void insert(int key) 
    {
        if (root) {
            insert(key, root);
        } else {
            root = new node;
            root->val = key;
            root->left = nullptr;
            root->right = nullptr;
        }
    }

    void reverse(node *leaf = nullptr) 
    {
        if (leaf) {
            node *tmp = leaf->left;
            leaf->left = leaf->right;
            leaf->right = tmp;
            if (leaf->left) reverse(leaf->left);
            if (leaf->right) reverse(leaf->right);
        } else {
            reverse(root);
        }
    }

    node *search(int key) { return search(key, root); }

    node *root = nullptr;

private:
    // 左小右大
    void insert(int key, node *leaf) 
    {
        if (key < leaf->val) {
            if (leaf->left) {
                insert(key, leaf->left);
            } else {
                leaf->left = new node;
                leaf->left->val = key;
                leaf->left->left = nullptr;
                leaf->left->right = nullptr;
            }
        } else if (key >= leaf->val) {
            if (leaf->right) {
                insert(key, leaf->right);
            } else {
                leaf->right = new node;
                leaf->right->val = key;
                leaf->right->left = nullptr;
                leaf->right->right = nullptr;
            }
        }
    }

    node *search(int key, node *leaf) 
    {
        if (leaf) {
            if (key == leaf->val)
                return leaf;
            if (key < leaf->val)
                return search(key, leaf->left);
            else
                return search(key, leaf->right);
        }
        return nullptr;
    }

    void destroy_tree(node *leaf) 
    {
        if (leaf) {
            destroy_tree(leaf->left);
            destroy_tree(leaf->right);
            delete leaf;
            leaf = nullptr;
        }
    }
};

// 分层遍历
std::string serialize(node *root) 
{
    std::string encode = "[";
    unsigned int cur = 0;
    unsigned int last = 1;
    std::vector<node*> vec;
    vec.push_back(root);
    while (cur < vec.size()) {
        last = vec.size();
        while (cur < last) {
            if (vec[cur]) {
                encode += std::to_string(vec[cur]->val) + ",";
                if (vec[cur]->left)
                    vec.push_back(vec[cur]->left);
                else if (vec[cur]->left == nullptr && vec[cur]->right)
                    encode += "null,";
                if (vec[cur]->right)
                    vec.push_back(vec[cur]->right);
                else if (vec[cur]->right == nullptr && vec[cur]->left)
                    encode += "null,";
            }
            cur++;
        }
    }
    return encode.substr(0, encode.size() - 1) + "]";
}

int main(int argc, char *argv[]) 
{
    btree *tree = new btree;
    tree->insert(10);
    tree->insert(6);
    tree->insert(5);
    tree->insert(8);
    tree->insert(14);
    tree->insert(11);
    tree->insert(18);
    std::cout << serialize(tree->root) << std::endl;
    tree->reverse();
    std::cout << serialize(tree->root) << std::endl;
    delete tree;
    tree = nullptr;
    return 0;
}
