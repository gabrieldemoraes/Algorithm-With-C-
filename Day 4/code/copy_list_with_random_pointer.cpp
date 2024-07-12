//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 copy_list_with_random_pointer.cpp -o copy_list_with_random_pointer.exe
//cl /Fo.\obj\ /EHsc /O2 copy_list_with_random_pointer.cpp /link /out:copy_list_with_random_pointer.exe

#include <vector>
#include <unordered_map>

class Node
{
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) 
        : val(_val), next(nullptr), random(nullptr) {}
};

//hashing
Node* copy_list_with_random_pointer_1(Node* head)
{
    Node* new_head = nullptr;
    if (head)
    {
        std::unordered_map<Node*, Node*> nodes;
        //create
        Node* old_node = head;
        Node* prev = nullptr;
        while (old_node != nullptr)
        {
            Node* new_node = new Node(old_node->val);
            new_node->random = old_node->random;
            if (prev) prev->next = new_node; else new_head = new_node;
            prev = new_node;
            nodes.emplace(old_node, new_node);
            old_node = old_node->next;
        }
        //connect
        for (auto node : nodes)
        {
            if (node.second->random)
                node.second->random = nodes.find(node.first->random)->second;
        }
    }
    return new_head;
}

//linking the pairs of old and new nodes
Node* copy_list_with_random_pointer_2(Node* head)
{
    if (head)
    {
        std::vector<std::pair<Node* /* old */, Node* /* new */>> xs;
        xs.reserve(1000);

        //create
        int i = 0;
        while (head)
        {
            xs.emplace_back(head, new Node(head->val));
            head->val = i++;
            head = head->next;
        }
        //connect random
        for (auto x : xs)
        {
            if (x.first->random)
                x.second->random = xs[x.first->random->val].second;
        }
        //connect next and fix val
        xs[0].first->val = xs[0].second->val;
        for (size_t j = 1, l = xs.size(); j < l; ++j)
        {
            xs[j - 1].second->next = xs[j].second;
            xs[j].first->val = xs[j].second->val;
        }

        return xs[0].second;
    }
    return nullptr;
}

#include <iostream>
#include <iomanip>

void display(Node* head, const char* label)
{
    std::cout << label << ":\n";
    while (head)
    {
        std::cout << '[' << std::hex << &*head << ": " << std::dec << head->val << '(';
        if (head->random)
            std::cout << std::hex << &*head->random;
        else
            std::cout << "nil";
        std::cout << ")] -> ";
        head = head->next;
    }
    std::cout << "nil\n" << std::endl;
}

#include "helpers_and_types.hpp"

void random_suggested_input()
{
   std::size_t N = 5;
   seed_rand(now_since_epoch());
   std::vector<int> values = generate_ordered_distinct_random_ints(N, 1, N * 4);
   N = values.size();
   std::vector<int> randoms = generate_random_ints(N, -1, N - 1);
   std::cout << N << ' ';
   for (int i = 0; i < N; ++i) std::cout << values[i]  << ' ';
   for (int i = 0; i < N; ++i) std::cout << randoms[i] << ' ';
   std::cout << '\n';
}

//Test cases:
//5 7 13 11 10 1 -1 0 4 2 0
//2 1 2 1 1
//3 3 3 3 -1 0 -1
int main()
{
    random_suggested_input();
    
    int N;
	std::cin >> N;
	std::vector<int> values(N, 0);
    std::vector<int> randoms(N, -1); //-1 == nullptr
	for (int i = 0; i < N; ++i) std::cin >> values[i];
    for (int i = 0; i < N; ++i) std::cin >> randoms[i];

    std::cout << "\n";

    std::vector<Node> nodes(values.begin(), values.end());
    for (int i = 1; i < nodes.size(); ++i) nodes[i - 1].next = &nodes[i];
    for (int i = 0; i < nodes.size(); ++i) nodes[i].random = 0 <= randoms[i] ? &nodes[randoms[i]] : nullptr;

    Node* input = &nodes[0];
    display(copy_list_with_random_pointer_1(input), "copy_list_with_random_pointer_1");
    input = &nodes[0];
    display(copy_list_with_random_pointer_2(input), "copy_list_with_random_pointer_2");    

    return 0;
}