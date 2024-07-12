//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 lru-cache.cpp -o lru-cache.exe
//cl /Fo.\obj\ /EHsc /O2 lru-cache.cpp /link /out:lru-cache.exe

#include <unordered_map>
#include <list>
#include <utility>

class lru_cache
{
    using list_t = std::list<int>;
    using table_t = std::unordered_map<int, std::pair<typename list_t::iterator, int>>;

public:
    lru_cache(int capacity) 
        : capacity(capacity) {}
    
    int get(int key)
    {
        auto it = t.find(key);
        if (it == t.end())
            return -1;

        move_to_front(it);
        return it->second.second;;
    }
    
    void put(int key, int value) 
    {
        auto it = t.find(key);
        if (it == t.end())
        {
            if (t.size() == capacity)
            {
                t.erase(q.back());
                q.pop_back();
            }
            q.emplace_front(key);
            t.emplace(key, std::make_pair(q.begin(), value));
        }
        else
        {
            it->second.second = value;
            move_to_front(it);
        }
    }
    
private:    
    void move_to_front(typename table_t::iterator& it) 
    {
        q.erase(it->second.first);
        q.emplace_front(it->first);
        it->second.first = q.begin();
    }
    
private:
    int capacity;
    list_t q;
    table_t t;
};

#include <iostream>

//Test cases:
//2 9 p 1 1 p 2 2 g 1 p 3 3 g 2 p 4 4 g 1 g 3 g 4
//3 14 p 1 1 p 2 2 p 3 3 p 4 4 g 4 g 3 g 2 g 1 p 5 5 g 1 g 2 g 3 g 4 g 5
//2 6 p 2 1 p 2 2 g 2 p 1 1 p 4 1 g 2
//1 6 p 1 1 g 1 p 2 2 p 3 3 g 2 g 3
int main()
{
    int C, N;
	std::cin >> C >> N;
	lru_cache lc(C);
    for (int i = 0; i < N; ++i)
    {
        char a;
        std::cin >> a;
        switch (a)
        {
            case 'p':
            {
                int k, v;
                std::cin >> k >> v;
                lc.put(k, v);
            }
            break;            
            case 'g':
            {
                int k;
                std::cin >> k;
                std::cout << lc.get(k) << ' ';
            }
            break;
        default:
            break;
        }
    }
    std::cout << '\n';
    return 0;
}