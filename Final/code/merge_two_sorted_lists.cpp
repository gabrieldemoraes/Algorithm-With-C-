//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 merge_two_sorted_lists.cpp -o merge_two_sorted_lists.exe
//cl /Fo.\obj\ /EHsc /O2 merge_two_sorted_lists.cpp /link /out:merge_two_sorted_lists.exe

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

#include <vector>

ListNode* merge_two_lists(ListNode* l1, ListNode* l2) 
{
    if (!l1)
    {
        return l2;
    }
    else if (!l2)
    {
        return l1;
    }

    ListNode* result;
    if (l1->val <= l2->val)
    {
        result = l1;
        l1 = l1->next;
    }
    else
    {
        result = l2;
        l2 = l2->next;
    }

    ListNode* p = result;
    while (l1 && l2)
    {
        if (l1->val <= l2->val)
        {
            p->next = l1;
            l1 = l1->next;
        }
        else
        {
            p->next = l2;
            l2 = l2->next;
        }
        p = p->next;
    }

    if (l1)
    {
        p->next = l1;
    }
    else if (l2)
    {
        p->next = l2;
    }

    return result;
}

#include <iostream>

void display(ListNode* head, const char* label)
{
    std::cout << label << ":\n";
    while (head)
    {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << "nil\n" << std::endl;
}

#include "helpers_and_types.hpp"

void random_suggested_input()
{
   std::size_t N = 5;
   seed_rand(now_since_epoch());
   std::vector<int> values_1 = generate_ordered_distinct_random_ints(N, 1, N * 4);
   std::vector<int> values_2 = generate_ordered_distinct_random_ints(N, 1, N * 4);
   std::cout << values_1.size() << ' ' << values_2.size() << ' ';
   for (int i = 0; i < values_1.size(); ++i) std::cout << values_1[i]  << ' ';
   for (int i = 0; i < values_2.size(); ++i) std::cout << values_2[i]  << ' ';
   std::cout << '\n';
}

//Test cases:
//3 3 1 2 4 1 3 4
//0 0
//0 1 0
//4 3 7 7 9 9 6 8 8
int main()
{
    random_suggested_input();
    
    int N_1, N_2;
    std::cin >> N_1 >> N_2;
    std::vector<int> values_1(N_1, 0);
    std::vector<int> values_2(N_2, 0);
    for (int i = 0; i < N_1; ++i) std::cin >> values_1[i];
    for (int i = 0; i < N_2; ++i) std::cin >> values_2[i];

    std::cout << "\n";

    std::vector<ListNode> nodes_1(values_1.begin(), values_1.end());
    for (int i = 1; i < nodes_1.size(); ++i) nodes_1[i - 1].next = &nodes_1[i];

    std::vector<ListNode> nodes_2(values_2.begin(), values_2.end());
    for (int i = 1; i < nodes_2.size(); ++i) nodes_2[i - 1].next = &nodes_2[i];
    
    display(merge_two_lists(&nodes_1[0], &nodes_2[0]), "merge_two_lists");
    
    return 0;
}