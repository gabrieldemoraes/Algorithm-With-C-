//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include "substring_searcher.hpp"
#include "substring_brute_force_searcher.hpp"
#include "substring_kmp_searcher.hpp"
#include "helpers_and_types.hpp"

#include <cstddef>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include "picobench.hpp"

namespace substring_searcher
{
    static std::string generate_pattern(std::size_t length)
    {
        seed_rand(now_since_epoch());
        return to_string(generate_random_chars(length, 'A', 'C'));
    }

    static std::vector<std::string> generate_texts(std::size_t n, std::size_t length)
    {
        std::vector<std::string> texts;
        while (n--) texts.push_back(to_string(generate_random_chars(length, 'A', 'C')));
        return texts;
    }

    static std::string& get_singleton_pattern()
    {
        static std::string pattern = generate_pattern(6);
        return pattern;
    }

    const int MAX_ITER = 1024;

    static std::vector<std::string>& get_singleton_texts()
    {
        static std::vector<std::string> texts = generate_texts(MAX_ITER, 600);
        return texts;
    }

    static void bench_brute_force_ss(picobench::state& s)
    {
        static std::vector<std::string> texts = get_singleton_texts();
        int n = s.iterations(), counter = 0;
        const std::string pattern = get_singleton_pattern();
        const brute_force bf_searcher(pattern);
        s.start_timer();
        while(n--)
        {
            if (std::string::npos != bf_searcher.search(texts[n]))
                ++counter;
        }
        s.stop_timer();
        std::cout << "brute force matches " << pattern << ": " << std::setw(5) << counter 
                  << " of " << std::setw(5) << s.iterations() << '\n';
    }

    static void bench_kmp_ss(picobench::state& s)
    {
        static std::vector<std::string> texts = get_singleton_texts();
        int n = s.iterations(), counter = 0;
        const std::string pattern = get_singleton_pattern();
        const knuth_morris_pratt kmp_searcher(pattern); //not counting the time to build table
        s.start_timer();
        while(n--)
        {
            if (std::string::npos != kmp_searcher.search(texts[n]))
                ++counter;
        }
        s.stop_timer();
        std::cout << "        kmp matches " << pattern << ": " << std::setw(5) << counter 
                  << " of " << std::setw(5) << s.iterations() << '\n';
    }

    static void register_benchmarks()
    {
        std::vector<int> ITERS{ MAX_ITER >> 5, MAX_ITER >> 4, MAX_ITER >> 3, MAX_ITER >> 2, MAX_ITER >> 1, MAX_ITER };
        
        picobench::global_registry::set_bench_suite("substring search");
        picobench::global_registry::new_benchmark("bench_brute_force_ss", bench_brute_force_ss).iterations(ITERS).baseline();
        picobench::global_registry::new_benchmark("        bench_kmp_ss", bench_kmp_ss).iterations(ITERS);
    }

    static void test_interactive()
    {
        std::cout << "1: input pattern, 2: input text, 3: random pattern, 4: random text, 5: init\n";
        std::cout << "?: search pattern in string,     !: display info,   @: kpm online,  EOF: benchmark\n";

        using substring_searcher_type = knuth_morris_pratt; 
        std::unique_ptr<substring_searcher_type> searcher;
        std::string pattern, text;
        std::size_t init = 0;
        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '1':
                {
                    std::cout << "       pattern: "; std::cin >> pattern;
                    searcher.reset(new substring_searcher_type(pattern));
                }
                break;
            case '2':
                {
                    std::cout << "          text: "; std::cin >> text;
                }
                break;
            case '3':
                {
                    std::size_t length;
                    std::cout << "pattern length: "; std::cin >> length;
                    if (length > 0)
                    {
                        pattern = generate_pattern(length);
                        std::cout << "   new pattern: " << pattern << '\n';
                        searcher.reset(new substring_searcher_type(pattern));
                    }
                }
                break;
            case '4':
                {
                    std::size_t length;
                    std::cout << "    text length: "; std::cin >> length;
                    if (length > 0) 
                    {
                        text = generate_texts(1, length)[0];
                        std::cout << "       new text: " << text << '\n';
                    }
                }
                break;
            case '5':
                {
                    std::cout << "          init: "; std::cin >> init;
                }
                break;
            case '?':
                {
                    if (text.size() && pattern.size())
                    {                    
                        auto pos = searcher->search(text, init);
                        std::cout << text << '\n';
                        std::cout << std::string(init, ' ') << '^' << '\n';
                        if (pos == std::string::npos)
                        {
                            std::cout << "not Found " << pattern << '\n';
                        }
                        else
                        {
                            std::cout << std::string(pos, ' ') << pattern << '\n';
                            std::cout << "found at " << pos << '\n';
                        }
                    }
                    else
                    {
                        std::cout << "text or pattern missing\n";
                    }
                }
                break;
            case '!':
                {
                    if (text.size() && pattern.size())
                    {
                        std::cout << "   text: " << text << '\n';
                        std::cout << "pattern: " << pattern << '\n';
                        std::cout << "   init: " << init << '\n';
                    }
                    else
                    {
                        std::cout << "text or pattern missing\n";
                    }
                }
                break;
            case '@':
                {
                    if (pattern.size())
                    {
                        kmp_online online(pattern);
                        while (true)
                        {
                            std::size_t length;
                            std::cout << "   chars length: "; std::cin >> length;
                            if (length)
                                while (length--)
                                {
                                    char ch = rand_char('A', 'C');
                                    std::cout << ch;
                                    std::size_t pos = online.search(ch);
                                    if (pos != std::string::npos)
                                        std::cout << "\nfound at " << pos << '\n';
                                }
                            else
                                break;
                            std::cout << '\n';
                        }
                    }
                    else
                    {
                        std::cout << "pattern missing\n";
                    }
                }
                break;
            default:
                {
                    std::cout << "input ignored\n";
                }
                break;
            }
        }
    }
}

int substring_searcher_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using substring_searcher::test_interactive;
    using substring_searcher::register_benchmarks;

    if (reg_benchmarks)
    {
        register_benchmarks();
    }

    if (run_tests)
    {
        test_interactive();
    }

    return 0;
}