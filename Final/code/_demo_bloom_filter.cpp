//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 _demo_bloom_filter.cpp -o _demo_bloom_filter.exe
//cl /Fo.\obj\ /EHsc /O2 _demo_bloom_filter.cpp /link /out:_demo_bloom_filter.exe

#include "helpers_and_types.hpp"

#include "bloom_filter.hpp"

#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <iomanip>

std::string fullname(const person& p)
{
    return p.first_name + ' ' + p.last_name;
}

int main()
{
    seed_rand(now_since_epoch());
    
    std::vector<std::string> boys = load_male_first_names_file();
    std::vector<std::string> girls = load_female_first_names_file();
    std::vector<std::string> surnames = load_surnames_file();
    
    std::vector<person> checklist = generate_random_people(1000, boys, girls, surnames);
    std::set<std::string> checklist_set;
    for (const auto& p : checklist) checklist_set.insert(fullname(p));
    
    std::vector<person> people;
    bloom_filter::bloom_filter<std::string> bf = bloom_filter::make_bloom_filter<std::string>(1'000'000, 0.01);
    int added = 0;
    for (int i = 0; i < 1000; ++i)
    {
        people = generate_random_people(1000, boys, girls, surnames);
        for (const auto& p : people)
        {
            std::string name = fullname(p);
            if (checklist_set.find(name) == checklist_set.end())
            {
                bf.add(name);
                ++added;
            }
        }
    }
    std::cout << added << '\n';

    int count = 0;
    for (const auto& p : people)
        if (bf.exists(fullname(p)))
            ++count;
    std::cout << std::boolalpha << (count == people.size()) << '\n';
    
    count = 0;
    for (const auto& s : checklist_set)
    {
        if (bf.exists(s))
        {
            ++count;
            std::cout << '[' << s << "] ";
        }
    }

    std::vector<std::string> ss = generate_random_strings(250000, 20);
    for (const auto& s : ss)
    {
        if (bf.exists(s))
        {
            ++count;
            std::cout << '[' << s << "] ";
        }
    }
    std::cout << '\n' << count << '\n';

    return 0;
}