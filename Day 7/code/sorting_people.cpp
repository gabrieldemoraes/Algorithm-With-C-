//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 sorting_people.cpp -o sorting_people.exe
//cl /Fo.\obj\ /EHsc /O2 sorting_people.cpp /link /out:sorting_people.exe

#include "helpers_and_types.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[])
{
    std::vector<std::string> boys = load_male_first_names_file();
    std::vector<std::string> girls = load_female_first_names_file();
    std::vector<std::string> surnames = load_surnames_file();
    seed_rand(now_since_epoch());
    std::vector<person> people = generate_random_people(99, boys, girls, surnames);

    std::sort(people.begin(), people.end()); //sort by first_name

    std::cout << "Sorted by first_name:\n";
    int count = 0;
    for (auto p : people)
        std::cout << std::setw(2) << (++count) << ':' << to_string(p) << '\n';
    std::cout << '\n';

    auto fn_it = std::adjacent_find(people.begin(), people.end(),
        [](const person& p1, const person& p2) {
            return p1.first_name == p2.first_name;
        });
    if (fn_it != people.end())
        std::cout << fn_it->first_name << '\n';
    else
        std::cout << "first name not repeated\n";

    std::sort(people.begin(), people.end(), 
        [](const person& p1, const person& p2) {
            return p1.last_name < p2.last_name;
        }); //sort by last_name

    std::cout << "\nSorted by last_name:\n";
    count = 0;
    for (auto p : people)
        std::cout << std::setw(2) << (++count) << ':' << to_string(p) << '\n';
    std::cout << '\n';

    auto ln_it = std::adjacent_find(people.begin(), people.end(), 
        [](const person& p1, const person& p2) {
            return p1.last_name == p2.last_name;
        });
    if (ln_it != people.end())
        std::cout << ln_it->last_name << '\n';
    else
        std::cout << "last name not repeated\n";

    std::cout << '\n';

    std::sort(people.begin(), people.end()); //sort by first_name again
    
    fn_it = people.begin() - 1;
    do
    {
        ++fn_it;
        fn_it = std::adjacent_find(fn_it, people.end(),
        [](const person& p1, const person& p2) {
            return p1.first_name == p2.first_name;
        });
        if (fn_it != people.end())
            std::cout << fn_it->first_name << ' ';
    }
    while (fn_it != people.end());
    std::cout << '\n';

    return 0;
}