//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 99people.cpp -o 99people.exe
//cl /Fo.\obj\ /EHsc /O2 99people.cpp /link /out:99people.exe

#include "helpers_and_types.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

int main(int argc, char *argv[])
{
    std::vector<std::string> boys = load_male_first_names_file();
    std::vector<std::string> girls = load_female_first_names_file();
    std::vector<std::string> surnames = load_surnames_file();
    seed_rand(now_since_epoch());
    std::vector<person> people = generate_random_people(99, boys, girls, surnames);
    int count = 0;
    for (auto p : people)
        std::cout << std::setw(2) << (++count) << ":" << to_string(p) << "\n";
    return 0;
}