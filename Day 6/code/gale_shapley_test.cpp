//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 gale_shapley_test.cpp -o gale_shapley_test.exe
//cl /Fo.\obj\ /EHsc /O2 gale_shapley_test.cpp /link /out:gale_shapley_test.exe

#include <vector>

#define DBG
#include "gale_shapley_stable_matching.hpp"

namespace gale_shapley_stable_matching
{
    static void test_case_1()
    {
        const std::size_t N = 3;
        
        std::vector<element> ms
        {
            element({ 0 /* top */, 1, 2 }), //queue
            element({ 2, 1, 0 }),
            element({ 0, 2, 1 })
        };

        std::vector<element> ws
        {
            element({ 2, 0, 1 /* top */}), //stack
            element({ 0, 1, 2 }),
            element({ 1, 0, 2 })
        };

        std::vector<std::string> company_list
        {
            "AMAZON",
            "MICROSOFT",
            "NVIDIA"
        };

        std::vector<std::string> candidate_list
        {
            "ADAM",
            "ANNA",
            "CARL"
        };

        find_stable_matching(ms, ws);        
    }

    static void test_case_2()
    {
        const std::size_t N = 3;
        
        std::vector<element> ms
        {
            element({ 2 /* top */, 1, 0 }), //queue
            element({ 2, 1, 0 }),
            element({ 2, 1, 0 })
        };

        std::vector<element> ws
        {
            element({ 2, 1, 0 /* top */}), //stack
            element({ 2, 1, 0 }),
            element({ 2, 1, 0 })
        };
        
        std::vector<std::string> company_list
        {
            "AMAZON",
            "MICROSOFT",
            "NVIDIA"
        };

        std::vector<std::string> candidate_list
        {
            "ADAM",
            "ANNA",
            "CARL"
        };

        find_stable_matching(ms, ws);        
    }

    static void test_case_3()
    {
        const std::size_t N = 3;
        
        std::vector<element> ms
        {
            element({ 2 /* top */, 1, 0 }), //queue
            element({ 1, 0, 2 }),
            element({ 0, 2, 1 })
        };

        std::vector<element> ws
        {
            element({ 2, 1, 0 /* top */}), //stack
            element({ 1, 0, 2 }),
            element({ 0, 2, 1 })
        };

        std::vector<std::string> company_list
        {
            "AMAZON",
            "MICROSOFT",
            "NVIDIA"
        };

        std::vector<std::string> candidate_list
        {
            "ADAM",
            "ANNA",
            "CARL"
        };

        find_stable_matching(ms, ws);        
    }
}

int main()
{
    gale_shapley_stable_matching::test_case_1();
    std::cout << '\n';
    gale_shapley_stable_matching::test_case_2();
    std::cout << '\n';
    gale_shapley_stable_matching::test_case_3();

    return 0;
}