//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include "gale_shapley_stable_matching.hpp"
#include "helpers_and_types.hpp"

#include <cstddef>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <random>

namespace gale_shapley_stable_matching
{
    namespace internal
    {
        static void display(const std::vector<element>& xss, const char* label = nullptr)
        {
            static std::size_t n = 0;
            std::cout << std::setw(5) << (n++ / 2) << " ";
            if (label) std::cout << label << ":";
            std::cout << "[ ";
            for (auto& xs : xss) 
                if (!xs.is_free())
                    std::cout << std::setw(3) << xs.selected << " ";
                else
                    std::cout << "  - ";
            std::cout << "]\n";
        }

        static void display(const std::vector<element>& xss, std::vector<std::string>& chooser, std::vector<std::string>& chosen, const char* label = nullptr)
        {
            static std::size_t n = 0;
            std::cout << std::setw(5) << (n++ / 2) << " ";
            if (label) std::cout << label << ":";
            std::cout << "[ ";
            std::size_t i = 0;
            for (auto& xs : xss)
                std::cout << chooser[i++] << "->" << chosen[xs.selected] << " ";
            std::cout << "]\n";
        }

        static inline std::vector<std::size_t> preference_list(std::size_t n)
        {
            std::vector<std::size_t> xs(n, 0);
            std::iota(xs.begin() + 1, xs.end(), 1);
            return std::move(xs);
        }
        
        static inline std::vector<std::size_t> preference_list_shuffled(std::size_t n)
        {
            static std::default_random_engine rnd(now_since_epoch());
            std::vector<std::size_t> xs{ preference_list(n) };
            std::shuffle(xs.begin(), xs.end(), rnd);
            return std::move(xs);
        }

        static inline element make_element(std::size_t n)
        {
            return element(preference_list(n));
        }

        static inline element make_element_shuffled(std::size_t n)
        {
            return element(preference_list_shuffled(n));
        }
    }
    
    static void test_case_1()
    {
        const std::size_t N = 5;

        std::vector<element> ms
        {
            internal::make_element(N),
            internal::make_element(N),
            internal::make_element(N),
            internal::make_element(N),
            internal::make_element(N)
        };

        std::vector<element> ws
        {
            internal::make_element(N),
            internal::make_element(N),
            internal::make_element(N),
            internal::make_element(N),
            internal::make_element(N)
        };

        find_stable_matching(ms, ws);
        internal::display(ms, "ms"); 
        internal::display(ws, "ws");		
    }

    static void test_case_2()
    {
        const std::size_t N = 5;
        for (std::size_t i = 0; i < 10; ++i)
        {
            std::vector<element> ms
            {
                internal::make_element_shuffled(N),
                internal::make_element_shuffled(N),
                internal::make_element_shuffled(N),
                internal::make_element_shuffled(N),
                internal::make_element_shuffled(N)
            };

            std::vector<element> ws
            {
                internal::make_element_shuffled(N),
                internal::make_element_shuffled(N),
                internal::make_element_shuffled(N),
                internal::make_element_shuffled(N),
                internal::make_element_shuffled(N)
            };

            find_stable_matching(ms, ws);
            internal::display(ms, "ms"); 
            internal::display(ws, "ws");
        }
    }

    static void test_case_3()
    {
        const std::size_t N = 5;

        std::vector<element> ms
        {
            internal::make_element(N),
            internal::make_element(N),
            internal::make_element(N),
            internal::make_element(N),
            internal::make_element(N)
        };

        std::vector<element> ws
        {
            internal::make_element(N),
            internal::make_element(N),
            internal::make_element(N),
            internal::make_element(N),
            internal::make_element(N)
        };

        std::vector<std::string> company_list
        {
            "AMAZON",
            "APPLE",
            "FACEBOOK",
            "GOOGLE",
            "NVIDIA"
        };

        std::vector<std::string> candidate_list
        {
            "ADAM",
            "ANNA",
            "BETH",
            "CARL",
            "DANA"
        };

        find_stable_matching(ms, ws);
        internal::display(ms, company_list, candidate_list); 
        internal::display(ws, candidate_list, company_list);
    }

    static void test_case_4()
    {
        const std::size_t N = 5;
        for (std::size_t i = 0; i < 10; ++i)
        {
            std::vector<element> ms
            {
                internal::make_element_shuffled(N),
                internal::make_element_shuffled(N),
                internal::make_element_shuffled(N),
                internal::make_element_shuffled(N),
                internal::make_element_shuffled(N)
            };

            std::vector<element> ws
            {
                internal::make_element_shuffled(N),
                internal::make_element_shuffled(N),
                internal::make_element_shuffled(N),
                internal::make_element_shuffled(N),
                internal::make_element_shuffled(N)
            };

            std::vector<std::string> company_list
            {
                "AMAZON",
                "APPLE",
                "FACEBOOK",
                "GOOGLE",
                "NVIDIA"
            };

            std::vector<std::string> candidate_list
            {
                "ADAM",
                "ANNA",
                "BETH",
                "CARL",
                "DANA"
            };

            find_stable_matching(ws, ms);
            internal::display(ms, company_list, candidate_list);
            internal::display(ws, candidate_list, company_list);
        }
    }

    static void test_case_5()
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
        internal::display(ms, company_list, candidate_list);
        internal::display(ws, candidate_list, company_list);
    }
    
    static void test_interactive()
    {
        std::cout << "1: find random stable matching\n";
        std::cout << "2: run other samples\n";

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '1':
                {
                    std::size_t n;
                    std::cout << "preference list size: "; std::cin >> n;
                    std::vector<element> ms;
                    std::vector<element> ws;
                    for (size_t i = 0; i < n; ++i)
                    {
                        ms.emplace_back(internal::preference_list_shuffled(n));
                        ws.emplace_back(internal::preference_list_shuffled(n));
                    }
                    find_stable_matching(ws, ms);
                    internal::display(ms, "ms");
                    internal::display(ws, "ws");
                }
                break;
            case '2':
                {
                    test_case_1();
                    test_case_2();
                    test_case_3();
                    test_case_4();
                    test_case_5();
                }
                break;
            default:
                std::cout << "input ignored\n";
                break;
            }
        }
    }
}

int gale_shapley_stable_matching_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using gale_shapley_stable_matching::test_interactive;

    if (run_tests)
    {
        test_interactive();
    }

    return 0;
}