//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 _demo_heap_sift.cpp -o _demo_heap_sift.exe
//cl /Fo.\obj\ /EHsc /O2 _demo_heap_sift.cpp /link /out:_demo_heap_sift.exe

#include "helpers_and_types.hpp"

#include <cstddef>
#include <vector>
#include <algorithm>
#include <random>

//sift up (naive) all
void sift_up(std::vector<int>& xs)
{
    std::size_t i = xs.size() - 1; //child
    while (i > 0)
    {
        std::size_t j = (i - 1) / 2; //parent
        if (xs[j] < xs[i]) { std::swap(xs[j], xs[i]); i = j; }
        else break;
    }
}

//sift down (naive) all
void sift_down(std::vector<int>& xs)
{
    std::size_t N = xs.size() - 1;
    std::size_t i = 0; //parent
    while (i < N)
    {
        std::size_t j = (i * 2) + 1; //child
        if (j + 1 <= N && xs[j] < xs[j + 1]) ++j;
        if (j <= N && xs[i] < xs[j]) { std::swap(xs[j], xs[i]); i = j; }
        else break;
    }
}

//sift down one
void sift_down(std::vector<int>& xs, std::size_t i)
{
    const std::size_t N = xs.size();

    if (N < 2 || (N - 2) / 2 < i)
        return;
    
    std::size_t j = 2 * i + 1; //child
    if (j + 1 < N && xs[j] < xs[j + 1]) ++j;

    if (xs[j] < xs[i]) //child < parent
        return;

    int temp = xs[i];
    do
    {
        if ((N - 2) / 2 < i)
            break;
        
        xs[i] = xs[j];
        i = j;
        j = 2 * j + 1;
        if (j + 1 < N && xs[j] < xs[j + 1]) ++j;
    } 
    while (!(xs[j] < temp));
    xs[i] = temp;
}

void heapify(std::vector<int>& xs)
{
    const std::size_t N = xs.size();
    if (N > 1)
    {
        for (std::size_t i = (N - 2) / 2; i != -1; --i)
            sift_down(xs, i);
    }
}

#include <string>
#include <sstream>

std::string to_graphviz_binary_tree(const std::vector<int>& xs)
{
    std::stringstream ss;
    ss << "digraph BINARY_HEAP_TREE {\n";
    const std::size_t N = xs.size();
    ss << "\t//";
    for (std::size_t i = 0; i < N; ++i) ss << xs[i] << ' ';
    ss << '\n';
    for (std::size_t i = 0; i < N; ++i)
    {
        if (2 * i + 1 < N) ss << '\t' << xs[i] << " -> " << xs[2 * i + 1] << ";\n";
        if (2 * i + 2 < N) ss << '\t' << xs[i] << " -> " << xs[2 * i + 2] << ";\n";
    }
    ss << "}\n";
    return ss.str();
}

#include <iostream>

int main()
{
    seed_rand(now_since_epoch());

    std::vector<int> xs;

    for (int k = 0; k < 10; ++k)
    {
        xs.push_back(rand_int(1, 99));
        
        sift_up(xs);

        for (int x : xs)
            std::cout << x << ' ';
        std::cout << '\n';
    }

    std::cout << '\n';

    for (int k = 0; k < 9; ++k)
    {
        std::swap(xs[0], xs[xs.size() - 1]);
        xs.resize(xs.size() - 1);
       
        sift_down(xs);

        for (int x : xs)
            std::cout << x << ' ';
        std::cout << '\n';
    }
    
    std::cout << '\n';

    xs = generate_random_ints(10, 1, 9);
    
    for (auto x : xs)
        std::cout << x << ' ';
    std::cout << '\n';
    
    //auto comp = std::greater<int>(); //min heap
    auto comp = std::less<int>(); //max heap
    std::make_heap(xs.begin(), xs.end(), comp); //heapify
    
    for (auto x : xs)
        std::cout << x << ' ';
    std::cout << '\n';

    //sift up
    xs.push_back(rand_int(11, 19));
    std::push_heap(xs.begin(), xs.end(), comp);

    for (auto x : xs)
        std::cout << x << ' ';
    std::cout << '\n';

    //sift down
    std::pop_heap(xs.begin(), xs.end(), comp);
    xs.pop_back();

    for (auto x : xs)
        std::cout << x << ' ';
    std::cout << '\n';

    std::cout << '\n';

    seed_rand(now_since_epoch());
    xs = generate_ordered_distinct_random_ints(15, 10, 99);
    std::shuffle(xs.begin(), xs.end(), std::default_random_engine(now_since_epoch()));
    for (auto x : xs)
        std::cout << x << ' ';
    std::cout << '\n';

    //make heap
    heapify(xs);

    for (auto x : xs)
        std::cout << x << ' ';
    std::cout << '\n';

    std::cout << to_graphviz_binary_tree(xs) << '\n';

    return 0;
}