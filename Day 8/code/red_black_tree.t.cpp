//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "red_black_tree.hpp"
#include "helpers_and_types.hpp"

#include <cstddef>
#include <iostream>
#include <iomanip>
#include <algorithm>

namespace red_black_tree
{
    namespace internal
    {
        template <typename T>
        static void display_recursive(const rb_node<T>* node, int depth = 0)
        {
            if (node)
            {
                for (int i = 0; i < depth - 1; ++i) std::cout << "  ";
                for (int i = std::max(0, depth - 1); i < depth; ++i) std::cout << " |_";
                std::cout << node->value << (node->red() ? " *" : "  ") << "\n";
                display_recursive(node->left, depth + 1);
                display_recursive(node->right, depth + 1);
            }
        }
    }

    static rb<int> build_random_int_rb(std::size_t n)
    {
        rb<int> int_rb;
        for (int value : generate_random_ints(n, 1, 99))
            int_rb.insert(value);
        return int_rb;
    }

    static void test_interactive()
    {
        std::cout << "1: build a binary search tree of ints\n";
        std::cout << "2: traversal a binary search tree of ints in level-order\n";
        std::cout << "3: build a binary search tree of ints (from 1 to 10) and traverse in level-order\n";
        
        auto visit_int = [](int x) { std::cout << x << " "; return VisitStatus::Continue; };

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '1':
            {
                std::size_t n;
                std::cout << "rb size: "; std::cin >> n;
                if (n == 0)
                {
                    std::cout << "nothing";
                }
                else
                {
                    rb<int> int_rb = build_random_int_rb(n);
                    internal::display_recursive(int_rb.get_root());
                }
                std::cout << "\n";
            }
            break;
            case '2':
                {
                    std::size_t n;
                    std::cout << "rb size: "; std::cin >> n;
                    if (n == 0)
                    {
                        std::cout << "nothing";
                    }
                    else
                    {
                        rb<int> int_rb = build_random_int_rb(n);
                        internal::display_recursive(int_rb.get_root());
                        std::cout << "\nlevel-order: ";
                        level_order_traversal<int>(int_rb.get_root(), visit_int);
                    }
                    std::cout << "\n";
                }
                break;
            case '3':
                {
                    rb<int> int_rb;
                    for (int i = 1; i <= 10; ++i)
                        int_rb.insert(i);
                    internal::display_recursive(int_rb.get_root());
                    std::cout << "\nlevel-order: ";
                    level_order_traversal<int>(int_rb.get_root(), visit_int);			
                    std::cout << "\n";
                }
                break;
            default:
                std::cout << "input ignored\n";
                break;
            }
        }
    }
}

int red_black_tree_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using red_black_tree::test_interactive;

    if (run_tests)
    {
        test_interactive();
    }

    return 0;
}