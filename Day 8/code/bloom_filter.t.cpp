//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "bloom_filter.hpp"
#include "helpers_and_types.hpp"

#include <cstddef>
#include <string>
#include <cmath>
#include <iostream>
#include <cstdio>

//custom type 
struct raw_bytes { const char* pointer;  std::size_t size; };

//custom type specialization
namespace bloom_filter
{
    namespace internal
    {
        template<>
        struct bloom_filter_pointer_size<raw_bytes>
        {
            inline static const void* get_pointer(const raw_bytes& value) { return value.pointer; }
            inline static std::size_t get_size(const raw_bytes& value) { return value.size; }
        };
    }
}

namespace bloom_filter
{
    static void test_interactive()
    {
        std::cout << "1: bloom filter of strings\n";
        std::cout << "2: bloom filter of ints\n";
        std::cout << "3: bloom filter of people's name\n";
        std::cout << "4: bloom filter's optimal number of bits and hash functions\n";
        std::cout << "5: bloom filter's false positives test\n";
        std::cout << "6: bloom filter's hash tests\n";
        std::cout << "7: bloom filter's custom type\n";
        
        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '1':
            {
                std::size_t m, n; double fpp;
                std::cout << "bloom filter number of entries: "; std::cin >> m;
                std::cout << "bloom filter expected false positive probability (0.0, 1.0): "; std::cin >> fpp;
                std::cout << "bloom filter number of checks: "; std::cin >> n;
                auto bf = make_bloom_filter<std::string>(m, fpp);
                for (std::string& s : generate_random_strings(m, 8))
                {
                    bf.add(s);
                    std::cout << bf.to_string(s) << "\n";
                }
                std::cout << "\nexists:\n";
                std::size_t count = 0;
                for (std::string& s : generate_random_strings(n, 8))
                {
                    if (bf.exists(s))
                    {
                        std::cout << bf.to_string(s) << "\n";
                        ++count;
                    }
                }
                std::cout << count << " match(es)\n";
            }
            break;
            case '2':
            {
                std::size_t m, n; double fpp;
                std::cout << "bloom filter number of entries: "; std::cin >> m;
                std::cout << "bloom filter expected false positive probability (0.0, 1.0): "; std::cin >> fpp;
                std::cout << "bloom filter number of checks: "; std::cin >> n;
                auto bf = make_bloom_filter<int>(m, fpp);
                for (int i : generate_random_ints(m, 1, 99999))
                {
                    bf.add(i);
                    std::cout << bf.to_string(i) << "\n";
                }
                std::cout << "\nexists:\n";
                std::size_t count = 0;
                for (int i : generate_random_ints(n, 1, 99999999))
                {
                    if (bf.exists(i))
                    {
                        std::cout << bf.to_string(i) << "\n";
                        ++count;
                    }
                }
                std::cout << count << " match(es)\n";
            }
            break;
            case '3':
            {
                std::size_t m, n; double fpp;
                std::cout << "bloom filter number of entries: "; std::cin >> m;
                std::cout << "bloom filter expected false positive probability (0.0, 1.0): "; std::cin >> fpp;
                std::cout << "bloom filter number of checks: "; std::cin >> n;
                auto bf = make_bloom_filter<std::string>(m, fpp);
                std::vector<std::string> boys = load_male_first_names_file();
                std::vector<std::string> girls = load_female_first_names_file();
                std::vector<std::string> surnames = load_surnames_file();
                for (person& p : generate_ordered_random_people(m, boys, girls, surnames))
                {
                    std::string s = p.first_name + " " + p.last_name;
                    bf.add(s);
                    std::cout << bf.to_string(s, 21) << "\n";
                }
                std::cout << "\nexists:\n";
                std::size_t count = 0;
                for (person& p : generate_random_people(m, boys, girls, surnames))
                {
                    std::string s = p.first_name + " " + p.last_name;
                    if (bf.exists(s))
                    {
                        std::cout << bf.to_string(s, 21) << "\n";
                        ++count;
                    }
                }
                std::cout << count << " match(es)\n";
            }
            break;
            case '4':
            {
                std::size_t n; double fpp;
                std::cout << "bloom filter number of entries: "; std::cin >> n;
                std::cout << "bloom filter expected false positive probability (0.0, 1.0): "; std::cin >> fpp;
                std::size_t m = optimal_number_of_bits(n, fpp);
                std::size_t h = optimal_number_of_hash_functions(n, m);
                std::cout << m << " bit(s) and " << h << " hash function(s)\n";
            }
            break;
            case '5':
            {
                const std::size_t N = 1'000'000;
                std::printf("Number of insertions =  %7zd\n", N);
                for (double fpp : { 0.3, 0.1, 0.03, 0.003, 0.0003, 0.00003 })
                {
                    auto bf = make_bloom_filter<std::string>(N, fpp);

                    for (std::size_t i = 0; i < N; ++i)
                        bf.add(std::to_string(i));

                    std::size_t count = 0;
                    for (std::size_t i = N; i < 2 * N; ++i)
                        if (bf.exists(std::to_string(i)))
                            ++count;

                    std::printf("Presence counter = %7zd %8.4f%% [fpp: %8.4f%%]\n", count, 100. * count / static_cast<double>(N), 100. * fpp);
                }
            }
            break;
            case '6':
            {
                const char* s = "abcdefghijklmnopqrstuvwxyz";
                std::size_t n = 26;
                for (int i = 0; i <= n; ++i)
                {
                    //a
                    //85555565F6597889 E6B53A48510E895A (little endian)
                    //897859F665555585 5A890E51483AB5E6 (big endian)
                    std::uint64_t h1, h2;
                    std::tie(h1, h2) = internal::murmur3_128(s, i, 0);
                    std::printf("%s : %016llX%016llX\n", std::string(s, i).c_str(), h1, h2);
                }
                
                auto bf = make_bloom_filter<std::string>(1'000'000, 0.1);
                for (int i = 10; i <= 25; ++i)
                {
                    auto indices = bf.indices(std::to_string(i));
                    std::printf("%d ", i);
                    for (auto index : indices) std::printf("%8lld ", index);
                    std::printf("\n");
                }
            }
            break;
            case '7':
            {
                auto bf = make_bloom_filter<raw_bytes>(10, 0.1);
	            raw_bytes bytes{ "Hello, World!", 13 };
                for (int i = 0; i < 2; ++i)
                {
                    bool added = bf.add(bytes);
                    std::cout << std::string(bytes.pointer) << (added ? " added" : " already exists") << '\n';
                }
            }
            break;
            default:
                std::cout << "input ignored\n";
                break;
            }
        }
    }
}

int bloom_filter_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using bloom_filter::test_interactive;

    if (run_tests)
    {
        test_interactive();
    }

    return 0;
}