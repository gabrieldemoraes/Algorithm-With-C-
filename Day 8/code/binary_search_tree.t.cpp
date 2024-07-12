//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "binary_search_tree.hpp"
#include "helpers_and_types.hpp"

#include <cstddef>
#include <iostream>
#include <iomanip>
#include <algorithm>

namespace binary_search_tree
{
    namespace internal
    {
        template <typename T>
        static void display_recursive(const bst_node<T>* node, int depth = 0)
        {
            if (node)
            {
                for (int i = 0; i < depth - 1; ++i) std::cout << "  ";
                for (int i = std::max(0, depth - 1); i < depth; ++i) std::cout << " |_";
                std::cout << node->value << "\n";
                display_recursive(node->left, depth + 1);
                display_recursive(node->right, depth + 1);
            }
        }
    }

    static bst<int> build_random_int_bst(std::size_t n)
    {
        bst<int> int_bst;
        for (int value : generate_random_ints(n, 1, 99))
            int_bst.insert(value);
        return int_bst;
    }

    static void test_interactive()
    {
        std::cout << "1: build a binary search tree of ints\n";
        std::cout << "2: traversal a binary search tree of ints in level-order\n";
        std::cout << "3: traversal a binary search tree of ints in pre-order\n";
        std::cout << "4: traversal a binary search tree of ints in in-order (sorted order)\n";
        std::cout << "5: traversal a binary search tree of ints in out-order (reverse sorted order)\n";
        std::cout << "6: traversal a binary search tree of ints in post-order\n";
        std::cout << "7: traversal a binary search tree of ints with all\n";
        std::cout << "8: find an int a binary search tree of ints\n";

        auto visit_int = [](int x) { std::cout << x << " "; return VisitStatus::Continue; };

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '1':
                {
                    std::size_t n;
                    std::cout << "bst size: "; std::cin >> n;
                    if (n == 0)
                    {
                        std::cout << "nothing";
                    }
                    else
                    {
                        bst<int> int_bst = build_random_int_bst(n);
                        internal::display_recursive(int_bst.get_root());
                    }
                    std::cout << "\n";
                }
                break;
            case '2':
                {
                    std::size_t n;
                    std::cout << "bst size: "; std::cin >> n;
                    if (n == 0)
                    {
                        std::cout << "nothing";
                    }
                    else
                    {
                        bst<int> int_bst = build_random_int_bst(n);
                        internal::display_recursive(int_bst.get_root());
                        std::cout << "\nlevel-order: ";
                        level_order_traversal<int>(int_bst.get_root(), visit_int);
                    }
                    std::cout << "\n";
                }
                break;
            case '3':
                {
                    std::size_t n;
                    std::cout << "bst size: "; std::cin >> n;
                    if (n == 0)
                    {
                        std::cout << "nothing";
                    }
                    else
                    {
                        bst<int> int_bst = build_random_int_bst(n);
                        internal::display_recursive(int_bst.get_root());
                        std::cout << "\npre-order: ";
                        pre_order_traversal<int>(int_bst.get_root(), visit_int);
                    }
                    std::cout << "\n";
                }
                break;
            case '4':
                {
                    std::size_t n;
                    std::cout << "bst size: "; std::cin >> n;
                    if (n == 0)
                    {
                        std::cout << "nothing";
                    }
                    else
                    {
                        bst<int> int_bst = build_random_int_bst(n);
                        internal::display_recursive(int_bst.get_root());
                        std::cout << "\nin-order: ";
                        in_order_traversal<int>(int_bst.get_root(), visit_int);
                    }
                    std::cout << "\n";
                }
                break;
            case '5':
                {
                    std::size_t n;
                    std::cout << "bst size: "; std::cin >> n;
                    if (n == 0)
                    {
                        std::cout << "nothing";
                    }
                    else
                    {
                        bst<int> int_bst = build_random_int_bst(n);
                        internal::display_recursive(int_bst.get_root());
                        std::cout << "\nout-order: ";
                        out_order_traversal<int>(int_bst.get_root(), visit_int);
                    }
                    std::cout << "\n";
                }
                break;
            case '6':
                {
                    std::size_t n;
                    std::cout << "bst size: "; std::cin >> n;
                    if (n == 0)
                    {
                        std::cout << "nothing";
                    }
                    else
                    {
                        bst<int> int_bst = build_random_int_bst(n);
                        internal::display_recursive(int_bst.get_root());
                        std::cout << "\npost-order: ";
                        post_order_traversal<int>(int_bst.get_root(), visit_int);
                    }
                    std::cout << "\n";
                }
                break;
            case '7':
                {
                    std::size_t n;
                    std::cout << "bst size: "; std::cin >> n;
                    if (n == 0)
                    {
                        std::cout << "nothing";
                    }
                    else
                    {
                        bst<int> int_bst = build_random_int_bst(n);
                        internal::display_recursive(int_bst.get_root());
                        std::cout << "\nlevel-order: "; level_order_traversal<int>(int_bst.get_root(), visit_int);
                        std::cout << "\n  pre-order: ";   pre_order_traversal<int>(int_bst.get_root(), visit_int);
                        std::cout << "\n   in-order: ";    in_order_traversal<int>(int_bst.get_root(), visit_int);
                        std::cout << "\n  out-order: ";   out_order_traversal<int>(int_bst.get_root(), visit_int);
                        std::cout << "\n post-order: ";  post_order_traversal<int>(int_bst.get_root(), visit_int);
                    }
                    std::cout << "\n";
                }
                break;
            case '8':
                {
                    std::size_t n;
                    std::cout << "bst size: "; std::cin >> n;
                    if (n == 0)
                    {
                        std::cout << "nothing";
                    }
                    else
                    {
                        int target, strategy;
                        bool found;
                        bst<int> int_bst = build_random_int_bst(n);
                        internal::display_recursive(int_bst.get_root());
                        std::size_t visit_counter;
                        auto find_target = [&](int x) {
                            ++visit_counter;
                            return target == x ? VisitStatus::Stop : VisitStatus::Continue;
                        };
                        std::cout << "\nstrategies:\n";
                        std::cout << "  1: pre-order  2: post-order\n";
                        std::cout << "  3: in-order   4: out-order\n";
                        std::cout << "  5: level-order (default)\n";
                        while (true)
                        {
                            visit_counter = 0;
                            std::cout << "strategy (0 stop): ";
                            if (!(std::cin >> strategy) || strategy <= 0)
                                break;
                            std::cout << "value to find (0 stop): ";
                            if (!(std::cin >> target) || target <= 0) 
                                break;							
                            if      (strategy == 1)
                                found = pre_order_traversal<int>(int_bst.get_root(), find_target);
                            else if (strategy == 2)
                                found = post_order_traversal<int>(int_bst.get_root(), find_target);
                            else if (strategy == 3)
                                found = in_order_traversal<int>(int_bst.get_root(), find_target);
                            else if (strategy == 4)
                                found = out_order_traversal<int>(int_bst.get_root(), find_target);
                            else
                                found = level_order_traversal<int>(int_bst.get_root(), find_target);
                            std::cout << "# of visited nodes = " << visit_counter << "\n";
                            std::cout << "found? " << std::boolalpha << found << "\n";
                        }
                    }
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

int binary_search_tree_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using binary_search_tree::test_interactive;

    if (run_tests)
    {
        test_interactive();
    }

    return 0;
}