//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 _demo_bst_rbt.cpp -o _demo_bst_rbt.exe
//cl /Fo.\obj\ /EHsc /O2 _demo_bst_rbt.cpp /link /out:_demo_bst_rbt.exe

#include "helpers_and_types.hpp"

#include <vector>
#include <memory>
#include <iostream>

struct bst_node
{
    int value;
    bst_node* left = nullptr;
    bst_node* right = nullptr;
};

class bst
{
    bst_node* root = nullptr;
    std::vector<bst_node*> nodes;

    bst_node* insert(bst_node* parent, int value)
    {
        if (parent)
        {
            if (value < parent->value)
                parent->left = insert(parent->left, value);
            else //if (value >= parent->value)
                parent->right = insert(parent->right, value);
            return parent;
        }
        nodes.push_back(new bst_node{ value });
        return nodes.back();
    }

public:
    bst() = default;
    bst (const bst&) = delete;
    bst& operator=(const bst&) = delete;
    ~bst() { for (bst_node* node : nodes) delete node; }
    
    void insert(int value)
    {
        root = insert(root, value);
    }

    const bst_node* get_root() const
    {
        return root;
    }
};

static const bool RED = true;
static const bool BLACK = false;

struct rb_node : bst_node
{
    bool color = RED;
};

bool is_red(const rb_node* node) 
{ 
    if (node)
        return node->color;
    return false;
}

class rbt
{
    rb_node* root = nullptr;
    std::vector<rb_node*> nodes;

    rb_node* insert(rb_node* parent, int value)
    {
        if (parent)
        {
            if (value < parent->value)
                parent->left = insert((rb_node*)parent->left, value);
            else //if (value >= parent->value)
                parent->right = insert((rb_node*)parent->right, value);
            
            //balance
            if (is_red((rb_node*)parent->right) && !is_red((rb_node*)parent->left))
                parent = rotate_left(parent);
            if (is_red((rb_node*)parent->left) && is_red((rb_node*)parent->left->left))
                parent = rotate_right(parent);
            if (is_red((rb_node*)parent->left) && is_red((rb_node*)parent->right))
                parent = flip_colors(parent);
            
            return parent;
        }
        rb_node* x = new rb_node;
        x->value = value;
        nodes.push_back(x);
        return nodes.back();
    }

    static rb_node* rotate_left(rb_node* node)
    {
        rb_node* temp = (rb_node*)node->right;
        node->right = temp->left;
        temp->left = node;
        temp->color = node->color;
        node->color = RED;
        return temp;
    }

    static rb_node* rotate_right(rb_node* node)
    {
        rb_node* temp = (rb_node*)node->left;
        node->left = temp->right;
        temp->right = node;
        temp->color = node->color;
        node->color = RED;
        return temp;
    }

    static rb_node* flip_colors(rb_node* node)
    {
        ((rb_node*)node->left)->color = BLACK;
        ((rb_node*)node->right)->color = BLACK;
        node->color = RED;
        return node;
    }

public:
    rbt() = default;
    rbt (const rbt&) = delete;
    rbt& operator=(const rbt&) = delete;
    ~rbt() { for (bst_node* node : nodes) delete node; }
    
    void insert(int value)
    {
        root = insert(root, value);
    }

    const bst_node* get_root() const
    {
        return root;
    }
};

#include <queue>

void bfs(const bst_node* node)
{
    if (node)
    {
        std::queue<const bst_node*> q;
        q.push(node);
        while (!q.empty())
        {
            const bst_node* x = q.front();
            std::cout << x->value << ' ';
            q.pop();
            if (x->left) q.push(x->left);
            if (x->right) q.push(x->right);
        }
    }
}

#include <stack>

void dfs_pre_order(const bst_node* node)
{
    if (node)
    {
        std::stack<const bst_node*> s;
        s.push(node);
        while (!s.empty())
        {
            const bst_node* x = s.top();
            std::cout << x->value << ' ';
            s.pop();
            if (x->right) s.push(x->right);
            if (x->left) s.push(x->left);
        }
    }
}

int main()
{
    bst b;    
    for (int i : generate_random_ints(8, 11, 99))
        b.insert(i);
    bfs(b.get_root());
    std::cout << '\n';
    dfs_pre_order(b.get_root());
    std::cout << '\n';

    rbt r;
    for (int i : generate_random_ints(8, 11, 99))
        r.insert(i);
    bfs(r.get_root());
    std::cout << '\n';
    dfs_pre_order(r.get_root());
    std::cout << '\n';

    return 0;
}