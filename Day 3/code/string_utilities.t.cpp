//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include "string_utilities.hpp"

#include <cstddef>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>

namespace string_utilities
{
    namespace internal
    {
        static std::string read_string_line(bool ignore = true)
        {
            char input[64];
            if (ignore) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.getline(input, sizeof(input));
            std::size_t size = std::cin.gcount();
            return std::move(std::string(input, input + size - 1));
        }

        template<typename Container>
        static void display(const Container& xs, const char* label = nullptr)
        {
            static std::size_t n = 0;
            std::cout << std::setw(5) << (n++ / 2) << " ";
            if (label) std::cout << label << ":[ ";
            for (auto x : xs) std::cout << x << " ";
            std::cout << "]\n";
        }
    }

    static void test_case_1()
    {
        auto is_space = [](int ch) { return std::isspace(ch); };
        {
            std::vector<char> xs{ ' ', ' ', ' ', ' ', 'a', 'b', 'c' };
            internal::display(xs, " before strip left");
            string_utilities::vector_support::strip_left_if(xs, is_space);
            internal::display(xs, "  after strip left");
        }
        {
            std::vector<char> xs{ ' ', 'a', 'b', 'c' };
            internal::display(xs, " before strip left");
            string_utilities::vector_support::strip_left_if(xs, is_space);
            internal::display(xs, "  after strip left");
        }
        {
            std::vector<char> xs{ 'a', 'b', 'c' };
            internal::display(xs, " before strip left");
            string_utilities::vector_support::strip_left_if(xs, is_space);
            internal::display(xs, "  after strip left");
        }
        {
            std::vector<char> xs{ 'a', 'b', 'c', ' ', ' ', ' ', ' ' };
            internal::display(xs, "before strip right");
            string_utilities::vector_support::strip_right_if(xs, is_space);
            internal::display(xs, " after strip right");
        }
        {
            std::vector<char> xs{ 'a', 'b', 'c', ' ' };
            internal::display(xs, "before strip right");
            string_utilities::vector_support::strip_right_if(xs, is_space);
            internal::display(xs, " after strip right");
        }
        {
            std::vector<char> xs{ 'a', 'b', 'c' };
            internal::display(xs, "before strip right");
            string_utilities::vector_support::strip_right_if(xs, is_space);
            internal::display(xs, " after strip right");
        }
        {
            std::vector<char> xs{ ' ', ' ', ' ', ' ', 'a', 'b', 'c', ' ', ' ', ' ', ' ' };
            internal::display(xs, "      before strip");
            string_utilities::vector_support::strip(xs);
            internal::display(xs, "       after strip");
        }
        {
            std::vector<char> xs{ ' ', 'a', 'b', 'c', ' ' };
            internal::display(xs, "      before strip");
            string_utilities::vector_support::strip(xs);
            internal::display(xs, "       after strip");
        }
        {
            std::vector<char> xs{ 'a', 'b', 'c' };
            internal::display(xs, "      before strip");
            string_utilities::vector_support::strip(xs);
            internal::display(xs, "       after strip");
        }
        {
            std::vector<char> xs{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
            internal::display(xs, "      before strip");
            string_utilities::vector_support::strip(xs);
            internal::display(xs, "       after strip");
        }
    }
    
    static void test_case_2()
    {
        auto is_zero = [](int i) { return i == 0; };
        {
            std::vector<int> xs{ 0, 0, 0, 1, 2, 3, 0, 0, 0, 0 };
            internal::display(xs, "      before strip");
            auto last = string_utilities::iterator_support::strip_if(xs.begin(), xs.end(), is_zero);
            auto n = std::distance(xs.begin(), last);
            xs.resize(std::distance(xs.begin(), last));
            internal::display(xs, "       after strip");
        }
        {
            std::vector<int> xs{ 0, 0, 0, 1, 2, 0, 0, 3, 4, 0 };
            internal::display(xs, "      before strip");
            auto last = string_utilities::iterator_support::strip_if(xs.begin(), xs.end(), is_zero);
            auto n = std::distance(xs.begin(), last);
            xs.resize(std::distance(xs.begin(), last));
            internal::display(xs, "       after strip");
        }
        {
            std::vector<int> xs{ 1, 2, 3, 0, 0, 0, 0 };
            internal::display(xs, "      before strip");
            auto last = string_utilities::iterator_support::strip_if(xs.begin(), xs.end(), is_zero);
            auto n = std::distance(xs.begin(), last);
            xs.resize(std::distance(xs.begin(), last));
            internal::display(xs, "       after strip");
        }
        {
            std::vector<int> xs{ 1, 2, 3 };
            internal::display(xs, "      before strip");
            auto last = string_utilities::iterator_support::strip_if(xs.begin(), xs.end(), is_zero);
            auto n = std::distance(xs.begin(), last);
            xs.resize(std::distance(xs.begin(), last));
            internal::display(xs, "       after strip");
        }
        {
            std::vector<int> xs{ 0, 1, 2, 3 };
            internal::display(xs, "      before strip");
            auto last = string_utilities::iterator_support::strip_if(xs.begin(), xs.end(), is_zero);
            xs.resize(std::distance(xs.begin(), last));
            internal::display(xs, "       after strip");
        }
        {
            std::vector<int> xs{ 0, 0, 0, 0, 0 };
            internal::display(xs, "      before strip");
            auto last = string_utilities::iterator_support::strip_if(xs.begin(), xs.end(), is_zero);
            xs.resize(std::distance(xs.begin(), last));
            internal::display(xs, "       after strip");
        }
        {
            std::vector<int> xs{ 0, 0, 0, 1, 2, 3, 0, 0, 0, 0 };
            internal::display(xs, " before strip left");
            std::vector<int> ys;
            auto last = string_utilities::iterator_support::strip_left_if(xs.begin(), xs.end(), std::back_inserter(ys), is_zero);
            internal::display(ys, "  after strip left");
        }
        {
            std::vector<int> xs{ 0, 0, 0, 1, 2, 0, 0, 3, 4, 0 };
            internal::display(xs, " before strip left");
            std::vector<int> ys;
            auto last = string_utilities::iterator_support::strip_left_if(xs.begin(), xs.end(), std::back_inserter(ys), is_zero);
            internal::display(ys, "  after strip left");
        }
        {
            std::vector<int> xs{ 1, 2, 3, 0, 0, 0, 0 };
            internal::display(xs, " before strip left");
            std::vector<int> ys;
            auto last = string_utilities::iterator_support::strip_left_if(xs.begin(), xs.end(), std::back_inserter(ys), is_zero);
            internal::display(ys, "  after strip left");
        }
        {
            std::vector<int> xs{ 1, 2, 3 };
            internal::display(xs, " before strip left");
            std::vector<int> ys;
            auto last = string_utilities::iterator_support::strip_left_if(xs.begin(), xs.end(), std::back_inserter(ys), is_zero);
            internal::display(ys, "  after strip left");
        }
        {
            std::vector<int> xs{ 0, 1, 2, 3 };
            internal::display(xs, " before strip left");
            std::vector<int> ys;
            auto last = string_utilities::iterator_support::strip_left_if(xs.begin(), xs.end(), std::back_inserter(ys), is_zero);
            internal::display(ys, "  after strip left");
        }
        {
            std::vector<int> xs{ 0, 0, 0, 0, 0 };
            internal::display(xs, " before strip left");
            std::vector<int> ys;
            auto last = string_utilities::iterator_support::strip_left_if(xs.begin(), xs.end(), std::back_inserter(ys), is_zero);
            internal::display(ys, "  after strip left");
        }
        {
            std::vector<int> xs;
            internal::display(xs, " before strip left");
            std::vector<int> ys;
            auto last = string_utilities::iterator_support::strip_left_if(xs.begin(), xs.end(), std::back_inserter(ys), is_zero);
            internal::display(ys, "  after strip left");
        }
        {
            std::vector<int> xs{ 0, 0, 0, 1, 2, 3, 0, 0, 0, 0 };
            internal::display(xs, "before strip right");
            std::vector<int> ys;
            auto last = string_utilities::iterator_support::strip_right_if(xs.begin(), xs.end(), std::back_inserter(ys), is_zero);
            internal::display(ys, " after strip right");
        }
        {
            std::vector<int> xs{ 0, 0, 0, 1, 2, 0, 0, 3, 4, 0 };
            internal::display(xs, "before strip right");
            std::vector<int> ys;
            auto last = string_utilities::iterator_support::strip_right_if(xs.begin(), xs.end(), std::back_inserter(ys), is_zero);
            internal::display(ys, " after strip right");
        }
        {
            std::vector<int> xs{ 1, 2, 3, 0, 0, 0, 0 };
            internal::display(xs, "before strip right");
            std::vector<int> ys;
            auto last = string_utilities::iterator_support::strip_right_if(xs.begin(), xs.end(), std::back_inserter(ys), is_zero);
            internal::display(ys, " after strip right");
        }
        {
            std::vector<int> xs{ 1, 2, 3 };
            internal::display(xs, "before strip right");
            std::vector<int> ys;
            auto last = string_utilities::iterator_support::strip_right_if(xs.begin(), xs.end(), std::back_inserter(ys), is_zero);
            internal::display(ys, " after strip right");
        }
        {
            std::vector<int> xs{ 0, 1, 2, 3 };
            internal::display(xs, "before strip right");
            std::vector<int> ys;
            auto last = string_utilities::iterator_support::strip_right_if(xs.begin(), xs.end(), std::back_inserter(ys), is_zero);
            internal::display(ys, " after strip right");
        }
        {
            std::vector<int> xs{ 0, 0, 0, 0, 0 };
            internal::display(xs, "before strip right");
            std::vector<int> ys;
            auto last = string_utilities::iterator_support::strip_right_if(xs.begin(), xs.end(), std::back_inserter(ys), is_zero);
            internal::display(ys, " after strip right");
        }
        {
            std::vector<int> xs;
            internal::display(xs, "before strip right");
            std::vector<int> ys;
            auto last = string_utilities::iterator_support::strip_right_if(xs.begin(), xs.end(), std::back_inserter(ys), is_zero);
            internal::display(ys, " after strip right");
        }
    }

    static void test_interactive()
    {
        std::cout << "1: strip string left, 2: strip string right,  3: strip string\n";
        std::cout << "4: contains pattern,  5: starts with pattern, 6: ends with pattern\n";
        std::cout << "7: run other samples\n";

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
                case '1':
                {
                    std::cout << "enter string? "; std::string s = internal::read_string_line();
                    std::cout << "before strip left:[" << s << "],";
                    std::cout << " after strip left:[" << strip_left(s) << "]\n";
                }
                break;
            case '2':
                {
                    std::cout << "enter string? "; std::string s = internal::read_string_line();
                    std::cout << "before strip right:[" << s << "],";
                    std::cout << " after strip right:[" << strip_right(s) << "]\n";
                }
                break;
            case '3':
                {
                    std::cout << "enter string? "; std::string s = internal::read_string_line();
                    std::cout << "before strip:[" << s << "],";
                    std::cout << " after strip:[" << strip(s) << "]\n";
                }
                break;
            case '4':
                {
                    std::cout << "enter string  source? "; std::string source  = internal::read_string_line();
                    std::cout << "enter string pattern? "; std::string pattern = internal::read_string_line(false);
                    std::cout << "does " << (contains(source, pattern) ? "" : "not ") << "contain pattern\n";
                }
                break;
            case '5':
                {
                    std::cout << "enter string  source? "; std::string source = internal::read_string_line();
                    std::cout << "enter string pattern? "; std::string pattern = internal::read_string_line(false);
                    std::cout << "does " << (starts_with(source, pattern) ? "" : "not ") << "start with pattern\n";
                }
                break;
            case '6':
                {
                    std::cout << "enter string  source? "; std::string source = internal::read_string_line();
                    std::cout << "enter string pattern? "; std::string pattern = internal::read_string_line(false);
                    std::cout << "does " << (ends_with(source, pattern) ? "" : "not ") << "end with pattern\n";
                }
                break;
            case '7':
                {
                    test_case_1();
                    test_case_2();
                }
                break;
            default:
                std::cout << "input ignored\n";
                break;
            }
        }
    }
}

int string_utilities_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using string_utilities::test_interactive;

    if (run_tests)
    {
        test_interactive();
    }

    return 0;
}