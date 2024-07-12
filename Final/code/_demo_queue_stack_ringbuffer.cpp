//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 _demo_queue_stack_ringbuffer.cpp -o _demo_queue_stack_ringbuffer.exe
//cl /Fo.\obj\ /EHsc /O2 _demo_queue_stack_ringbuffer.cpp /link /out:_demo_queue_stack_ringbuffer.exe

#include "helpers_and_types.hpp"

#include <queue>
#include <stack>
#include "bounded_stack.hpp"
#include "bounded_queue.hpp"
#include "bounded_ring_buffer.hpp"
#include <deque>

#include <iostream>

int main()
{
    using bounded_queue::bounded_queue;
    using bounded_stack::bounded_stack;
    using bounded_ring_buffer::bounded_ring_buffer;

    std::queue<int> q;
    std::stack<int> s;
    bounded_queue<int> bq{8};
    bounded_stack<int> bs{8};
    bounded_ring_buffer<int> brb{8};
    std::deque<int> d;

    seed_rand(now_since_epoch());
    auto xs = generate_ordered_distinct_random_ints(10, 10, 99);

    std::cout << "              input: ";
    for(int x : xs) std::cout << x << ' ';
    std::cout << '\n';

    //std::queue
    {
        std::cout << "         std::queue: ";
        for (auto x : xs)
            q.push(x);
        std::cout << q.front() << ' ';
        q.pop();
        std::cout << q.front() << ' ';
        std::cout << '\n';
    }

    //std::stack
    {
        std::cout << "         std::stack: ";
        for (auto x : xs)
            s.push(x);
        std::cout << s.top() << ' ';
        s.pop();
        std::cout << s.top() << ' ';
        std::cout << '\n';
    }

    //bounded_queue
    {
        std::cout << "      bounded_queue: ";
        for (auto x : xs)
            bq.push(x);
        int top;
        //bq.top(top);
        //std::cout << top << ' ';
        bq.pop(top);
        std::cout << top << ' ';
        bq.top(top);
        std::cout << top << ' ';
        std::cout << '\n';
    }

    //bounded_stack
    {
        std::cout << "      bounded_stack: ";
        for (auto x : xs)
            bs.push(x);
        int top;
        //bs.top(top);
        //std::cout << top << ' ';
        bs.pop(top);
        std::cout << top << ' ';
        bs.top(top);
        std::cout << top << ' ';
        std::cout << '\n';
    }

    //bounded_ring_buffer
    {
        std::cout << "bounded_ring_buffer: ";
        for (auto x : xs)
            brb.push(x);
        int top;
        //brb.top(top);
        //std::cout << top << ' ';
        brb.pop(top);
        std::cout << top << ' ';        
        while (!brb.empty())
        {
            brb.pop(top);
            std::cout << top << ' ';
        }        
        std::cout << '\n';

    }

    //deque
    {
        std::cout << "              deque: ";
        for (int i = 0; i < xs.size() / 2; ++i)
            d.push_back(xs[i]);
        for (int i = xs.size() / 2; i < xs.size(); ++i)
            d.push_front(xs[i]);
        int N = d.size() / 2;
        while (N < d.size())
        {
            std::cout << d.front() << ' ';
            d.pop_front();
        }
        while (!d.empty()) 
        {
            std::cout << d.back() << ' ';
            d.pop_back();
        }
        std::cout << '\n';
    }

    return 0;
}

