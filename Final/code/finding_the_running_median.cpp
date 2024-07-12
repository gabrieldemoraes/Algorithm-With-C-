//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//Problem extract from here: https://www.hackerrank.com/challenges/find-the-running-median/problem
//This file is licensed to you under the MIT license

//g++ -O3 finding_the_running_median.cpp -o finding_the_running_median.exe
//cl /Fo.\obj\ /EHsc /O2 finding_the_running_median.cpp /link /out:finding_the_running_median.exe

#include <vector>
#include <memory>
#include <limits>
#include <iostream>

using namespace std;

static const bool RED = true;
static const bool BLACK = false;

struct int_rbnode
{
    bool is_red;
    std::int32_t value;
    size_t size;
    std::unique_ptr<int_rbnode> left;
    std::unique_ptr<int_rbnode> right;
};

struct llrb
{
    llrb() : root(nullptr), count(0)
    {
    }
    
    void insert(std::int32_t value)
    {
        root = insert_rec(std::move(root), value);
        root->is_red = BLACK;
        ++count;
    }
    
    int_rbnode* top() const
    {
        return root.get();
    }
    
    int_rbnode* kth(size_t index) const
    {
        return kth_rec(root, index);
    }
    
    size_t size() const
    {
        return count;
    }
    
private:
    std::unique_ptr<int_rbnode> insert_rec(std::unique_ptr<int_rbnode> node, std::int32_t value)
    {
        if (nullptr == node)
        {
            std::unique_ptr<int_rbnode> new_node{new int_rbnode};
            new_node->value = value;
            new_node->is_red = RED;
            new_node->size = 1;
            return new_node;
        }
        
        //search insertion point
        auto result = value - node->value;
        if (result > 0)
        {
            //to right
            node->right = insert_rec(std::move(node->right), value);
        }
        else //if (result < 0 || result == 0)
        {
            //to left
            node->left = insert_rec(std::move(node->left), value);
        }
        
        //update size
        node->size = subtree_size(node->right) + subtree_size(node->left) + 1;
        
        //adjust nodes
        //left child black, right child red
        if(!is_red(node->left) && is_red(node->right))
        {
            node = rotate_left(std::move(node));
        }
        //left child red, left grandchild red
        if (is_red(node->left) && is_red(node->left->left))
        {
            node = rotate_right(std::move(node));
        }
        //left child red, right child red
        if (is_red(node->left) && is_red(node->right))
        {
            flip_colors(node);
        }
        
        return node;
    }
    
    static bool is_red(const std::unique_ptr<int_rbnode>& node)
    {
        if (nullptr == node)
            return false;
        return node->is_red;
    };
    
    static size_t subtree_size(const std::unique_ptr<int_rbnode>& node)
    {
        if (nullptr == node)
            return 0;
        return node->size;
    }
    
    static std::unique_ptr<int_rbnode> rotate_left(std::unique_ptr<int_rbnode> node)
    {
        //rotate
        std::unique_ptr<int_rbnode> temp = std::move(node->right);
        node->right = std::move(temp->left);
        temp->left = std::move(node);
        temp->is_red = temp->left->is_red;
        temp->left->is_red = RED;
        //update size
        temp->size = temp->left->size;
        temp->left->size = subtree_size(temp->left->left) + subtree_size(temp->left->right) + 1;
        return temp;
    }
    
    static std::unique_ptr<int_rbnode> rotate_right(std::unique_ptr<int_rbnode> node)
    {
        //rotate
        std::unique_ptr<int_rbnode> temp = std::move(node->left);
        node->left = std::move(temp->right);
        temp->right = std::move(node);
        temp->is_red = temp->right->is_red;
        temp->right->is_red = RED;
        //update size
        temp->size = temp->right->size;
        temp->right->size = subtree_size(temp->right->left) + subtree_size(temp->right->right) + 1;
        return temp;
    }
    
    static void flip_colors(std::unique_ptr<int_rbnode>& node)
    {
        node->left->is_red = BLACK;
        node->right->is_red = BLACK;
        node->is_red = RED;
    }
    
    static int_rbnode* kth_rec(const std::unique_ptr<int_rbnode>& node, size_t index)
    {
        if (nullptr == node)
            return nullptr;
        
        size_t rank = subtree_size(node->left) + 1;
        if (index == rank)
        {
            return node.get();
        }
        else if (index < rank)
        {
            return kth_rec(node->left, index);
        }
        else
        {
            return kth_rec(node->right, index - rank);
        }
    }
    
private:
    std::unique_ptr<int_rbnode> root;
    size_t count;
};

static double compute_median(llrb& t)
{
    size_t index = t.size() / 2;
    auto* node = t.kth(index + 1);
    double median = node->value;
    if (!(t.size() & 0x1))
    {
        node = t.kth(index);
        median = (median + node->value) / 2.0;
    }
    return median;
}

vector<double> running_median(vector<int> a) {
    vector<double> medians;
    llrb t;
    for (int i : a)
    {
        t.insert(i);
        medians.push_back(compute_median(t));
    }
    return medians;
}

//Test cases:
//6 12 4 5 3 8 7           expected output: 12 8 5 4.5 5 6
//10 1 2 3 4 5 6 7 8 9 10  expected output: 1 1.5 2 2.5 3 3.5 4 4.5 5 5.5
int main()
{
    int a_count;
    cin >> a_count;
    
    vector<int> a(a_count);

    for (int a_itr = 0; a_itr < a_count; a_itr++) {
        int a_item;
        cin >> a_item;
        
        a[a_itr] = a_item;
    }

    vector<double> result = running_median(a);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        cout << result[result_itr];

        if (result_itr != result.size() - 1) {
            cout << " ";
        }
    }

    cout << "\n";

    return 0;
}
