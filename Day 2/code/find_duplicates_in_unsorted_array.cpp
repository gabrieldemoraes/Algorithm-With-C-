//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <unordered_set>
#include <algorithm>

//g++ -O3 find_duplicates_in_unsorted_array.cpp -o find_duplicates_in_unsorted_array.exe
//cl /Fo.\obj\ /EHsc /O2 find_duplicates_in_unsorted_array.cpp /link /out:find_duplicates_in_unsorted_array.exe

//brute force
std::vector<int> find_duplicates_in_unsorted_array_1(std::vector<int>& xs)
{
    const std::size_t N = xs.size();

    std::vector<int> result;

    for (std::size_t i = 0; i < N; ++i)
    {
        for (std::size_t j = i + 1; j < N; ++j)
        {
            if (xs[i] == xs[j])
            {
                result.emplace_back(xs[i]);
                break;
            }
        }
    }

    return result;
}

//sorting
std::vector<int> find_duplicates_in_unsorted_array_2(std::vector<int>& xs)
{
    const std::size_t N = xs.size();

    std::vector<int> result;

    std::sort(xs.begin(), xs.end());

    for (std::size_t i = 1; i < N; ++i)
    {
        if (xs[i - 1] == xs[i])
        {
            result.emplace_back(xs[i]);
            ++i;
        }
    }

    return result;
}

//hashing 
std::vector<int> find_duplicates_in_unsorted_array_3(std::vector<int>& xs)
{
    std::vector<int> result;
    std::unordered_set<int> presence;
    
    for (int x : xs)
    {
        if (presence.find(x) != presence.end())
        {
            result.emplace_back(x);
        }
        else
        {
            presence.emplace(x);
        }
    }

    return result;
}

//bitmapping
std::vector<int> find_duplicates_in_unsorted_array_4(std::vector<int>& xs)
{
    const std::size_t N = xs.size();

    std::vector<int> result;
    std::vector<bool> presence(N + 1, false);

    for (int x : xs)
    {
        if (presence[x])
        {
            result.emplace_back(x);
        }
        else
        {
            presence[x] = true;
        }
    }

    return result;
}

//time and memory greater than 90%
std::vector<int> find_duplicates_in_unsorted_array_5(std::vector<int>& xs)
{
    static int presence[1 + 100000];
    const size_t N = 1 + *std::max_element(xs.begin(), xs.end());
    std::memset(presence, 0, sizeof(presence[0]) * N);

    std::vector<int> result;
    result.reserve(N);
    
    for (int x : xs)
    {
        if (presence[x])
            result.emplace_back(x);
        else
            presence[x] = 1;
    }
    
    return result;
}

//best memory conservative
std::vector<int> find_duplicates_in_unsorted_array_6(std::vector<int>& xs)
{
    size_t i = 0, N = xs.size();
    while (i < N)
    {
        size_t pos = xs[i] - 1;
        if (pos == i)
        {
            xs[i] = -1;
            ++i;
        }
        else if (xs[i] > 0 && xs[pos] > 0)
        {
            xs[i] = xs[pos];
            xs[pos] = -1;
        }
        else
        {
            ++i;
        }
    }
    auto end = std::remove_if(xs.begin(), xs.end(), [](int x){ return x < 0; });
    xs.resize(std::distance(xs.begin(), end));
    return xs;
}

#include <iostream>

void display(std::vector<int> result, const char* label, bool sort = true)
{
    if (sort)
        std::sort(result.begin(), result.end());

    std::cout << label << ":\n";
    for (int x : result)
        std::cout << x << ' ';
    std::cout << '\n' << std::endl;
}

#include "helpers_and_types.hpp"
#include <numeric>
#include <iterator>

void random_suggested_input()
{
    std::size_t N = 50, M = 30;
    std::vector<int> xs(N, 0); std::iota(xs.begin(), xs.end(), 1);
    seed_rand(now_since_epoch());
    std::vector<int> ys = generate_ordered_distinct_random_ints(M, 1, N);
    std::copy(ys.begin(), ys.end(), std::back_inserter(xs));
    std::shuffle(xs.begin(), xs.end(), std::default_random_engine(now_since_epoch()));
    xs.insert(xs.begin(), xs.size());
    display(xs, "suggested input", false);
}

int main()
{
    random_suggested_input();
    
    int N;
    std::cin >> N;
    std::vector<int> input(N, 0);
    for (int i = 0; i < N; ++i)
        std::cin >> input[i];

    std::cout << "\n";
    
    display(find_duplicates_in_unsorted_array_1(input), "find_duplicates_in_unsorted_array_1");
    display(find_duplicates_in_unsorted_array_2(input), "find_duplicates_in_unsorted_array_2");
    display(find_duplicates_in_unsorted_array_3(input), "find_duplicates_in_unsorted_array_3");
    display(find_duplicates_in_unsorted_array_4(input), "find_duplicates_in_unsorted_array_4");
    display(find_duplicates_in_unsorted_array_5(input), "find_duplicates_in_unsorted_array_5");
    display(find_duplicates_in_unsorted_array_6(input), "find_duplicates_in_unsorted_array_6");

    return 0;
}