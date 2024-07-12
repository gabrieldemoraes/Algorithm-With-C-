//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 binary_search_tree_dfs_iterative.cpp -o binary_search_tree_dfs_iterative.exe
//cl /Fo.\obj\ /EHsc /O2 binary_search_tree_dfs_iterative.cpp /link /out:binary_search_tree_dfs_iterative.exe

#include <vector>
#include <functional>
#include <stack>

#include "binary_search_tree.hpp"

namespace binary_search_tree
{
    //depth-first search
    namespace internal
    {
        template <typename T>
        bool pre_order_traversal_iterative(const bst_node<T>* node, std::function<VisitStatus(const T&)> visit)
        {
            if (node)
            {
                std::stack<bst_node<T>*> s;
                s.push(const_cast<bst_node<T>*>(node));
                while (!s.empty())
                {
                    bst_node<T>* x = s.top();
                    s.pop();
                    if (visit(x->value) == VisitStatus::Stop)
                        return true;
                    if (x->right) s.push(x->right);
                    if (x->left)  s.push(x->left);
                }
            }
            return false;
        }
    }
}

#include <iostream>
#include <string>

int main()
{
    using binary_search_tree::bst;
    using binary_search_tree::VisitStatus;
    using binary_search_tree::internal::pre_order_traversal_recursive;
    using binary_search_tree::internal::pre_order_traversal_iterative;
    
    bst<char> char_bst;
	for (char c : std::string("FBGADCEIH"))
		char_bst.insert(c);
    auto display_value = [](char c) { 
        std::cout << c << ' '; 
        return VisitStatus::Continue; 
    };
	std::cout << "recursive: ";
    pre_order_traversal_recursive<char>(char_bst.get_root(), display_value);
	std::cout << '\n';
    std::cout << "iterative: ";
    pre_order_traversal_iterative<char>(char_bst.get_root(), display_value);
	std::cout << '\n';

    return 0;
}