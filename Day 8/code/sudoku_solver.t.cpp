//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "sudoku_solver.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>

namespace sudoku_solver
{
    static void test_iterators()
    {
        //std::size_t N = 1, M = 1;
        //std::size_t N = 1, M = 2;
        //std::size_t N = 1, M = 3;
        //std::size_t N = 2, M = 1;
        //std::size_t N = 2, M = 2;
        //std::size_t N = 2, M = 3;
        std::size_t N = 3, M = 3;
        
        grid g(N, M, true);

        std::cout << "rows:\n";
        for (std::size_t i = 0; i < N * M; ++i)
        {
            for (int x : g.row(i))
                std::cout << std::setw(2) << x << " ";
            std::cout << "\n";
        }

        std::cout << "\n";

        std::cout << "columns:\n";
        for (std::size_t i = 0; i < N * M; ++i)
        {
            for (int x : g.column(i))
                std::cout << std::setw(2) << x << " ";
            std::cout << "\n";
        }

        std::cout << "\n";

        std::cout << "regions:\n";
        for (std::size_t i = 0; i < M * M; ++i)
        {
            for (int x : g.region(i))
                std::cout << std::setw(2) << x << " ";
            std::cout << "\n";
        }

        std::cout << "\n";

        std::cout << "grid:\n";
        std::cout << g.to_string();
        
        std::cout << "\n";
        for (std::size_t i = 0; i < N * M; ++i)
            for (std::size_t j = 0; j < N * M; ++j)
                std::cout << "row: " << i << " column: " << j << " value: " << std::setw(2) 
                          << static_cast<int>(g.get_value(i, j)) << " region: " << g.get_region(i, j) << "\n";
    }

    namespace internal
    {
        static void solve_and_display(grid& g)
        {
            std::cout << "init:\n";
            std::cout << g.to_string();
            std::cout << "\n";

            auto start = std::chrono::high_resolution_clock::now();
            //bool solved = solve(g, [](grid& g, std::size_t row, std::size_t column) {
            //	std::cout << "row: " << row << " column: " << column << "\n" << g.to_string() << "\n";
            //}); //solve it and print each state visited
            //or
            bool solved = solve(g); //just solve it!
            auto stop = std::chrono::high_resolution_clock::now();

            std::cout << "solved? " << std::boolalpha << solved;			
            std::cout << "\nresult:\n";
            std::cout << g.to_string();
            std::cerr << "Time elapsed = " << ((stop - start).count() / 1000000.0) << " milliseconds\n";
            std::cout << "\n";
        }
    }

    static void test_solver_1()
    {
        std::size_t N = 3, M = 3;
        grid g(N, M, {
            0, 0, 0, 0, 0, 0, 6, 0, 9,
            1, 0, 0, 0, 0, 4, 0, 0, 0,
            0, 0, 5, 3, 0, 6, 8, 2, 1,
            0, 0, 4, 6, 7, 0, 0, 5, 0,
            0, 0, 7, 0, 0, 0, 9, 0, 0,
            0, 0, 0, 5, 4, 0, 0, 0, 0,
            3, 7, 0, 4, 0, 5, 2, 0, 6,
            0, 0, 0, 0, 0, 0, 5, 1, 0,
            0, 6, 0, 0, 2, 0, 0, 3, 7,
        });
        internal::solve_and_display(g);
    }

    static void test_solver_2()
    {
        std::size_t N = 3, M = 3;
        grid g(N, M, {
            2, 5, 0, 0, 0, 3, 0, 9, 1,
            3, 0, 9, 0, 0, 0, 7, 2, 0,
            0, 0, 1, 0, 0, 6, 3, 0, 0,
            0, 0, 0, 0, 6, 8, 0, 0, 3,
            0, 1, 0, 0, 4, 0, 0, 0, 0,
            6, 0, 3, 0, 0, 0, 0, 5, 0,
            1, 3, 2, 0, 0, 0, 0, 7, 0,
            0, 0, 0, 0, 0, 4, 0, 6, 0,
            7, 6, 4, 0, 1, 0, 0, 0, 0,
        });
        internal::solve_and_display(g);
    }

    static void test_solver_3()
    {
        std::size_t N = 3, M = 3;
        grid g(N, M, {
            5, 8, 6, 0, 7, 0, 0, 0, 0,
            0, 0, 0, 9, 0, 1, 6, 0, 0,
            0, 0, 0, 6, 0, 0, 0, 0, 0,
            0, 0, 7, 0, 0, 0, 0, 0, 0,
            9, 0, 2, 0, 1, 0, 3, 0, 5,
            0, 0, 5, 0, 9, 0, 0, 0, 0,
            0, 9, 0, 0, 4, 0, 0, 0, 8,
            0, 0, 3, 5, 0, 0, 0, 6, 0,
            0, 0, 0, 0, 2, 0, 4, 7, 0,
        });
        internal::solve_and_display(g);
    }

    static void test_solver_4()
    {
        std::size_t N = 3, M = 3;
        grid g(N, M, {
            0, 0, 7, 0, 0, 0, 3, 0, 2,
            2, 0, 0, 0, 0, 5, 0, 1, 0,
            0, 0, 0, 8, 0, 1, 4, 0, 0,
            0, 1, 0, 0, 9, 6, 0, 0, 8,
            7, 6, 0, 0, 0, 0, 0, 4, 9,
            0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 1, 0, 3, 0, 0, 0,
            8, 0, 1, 0, 6, 0, 0, 0, 0,
            0, 0, 0, 7, 0, 0, 0, 6, 3,
        });
        internal::solve_and_display(g);
    }

    static void test_solver_5()
    {
        std::size_t N = 3, M = 3;
        grid g(N, M, {
            0, 0, 0, 0, 0, 0, 0, 9, 0,
            0, 0, 0, 7, 0, 0, 0, 0, 0,
            2, 4, 8, 1, 0, 0, 0, 0, 0,
            9, 0, 0, 0, 6, 0, 0, 0, 4,
            0, 0, 0, 0, 0, 9, 0, 8, 5,
            0, 0, 1, 0, 0, 8, 0, 0, 2,
            6, 0, 0, 0, 0, 0, 0, 3, 1,
            5, 0, 4, 0, 0, 3, 0, 0, 0,
            0, 0, 0, 2, 0, 0, 0, 0, 0,
        });
        internal::solve_and_display(g);
    }

    static void test_solver_6()
    {
        std::size_t N = 3, M = 3;
        grid g(N, M, {
            0, 0, 0, 0, 0, 0, 0, 3, 2,
            0, 1, 8, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 8, 0, 4, 0, 0, 6,
            0, 0, 0, 1, 4, 0, 0, 0, 0,
            0, 8, 0, 0, 7, 0, 4, 0, 0,
            3, 7, 0, 2, 0, 0, 0, 0, 0,
            0, 0, 1, 0, 0, 0, 0, 0, 0,
            6, 0, 0, 0, 0, 0, 2, 5, 7,
            0, 2, 0, 0, 0, 0, 6, 0, 3,
        });
        internal::solve_and_display(g);
    }

    static void test_solver_7()
    {
        std::size_t N = 3, M = 3;
        grid g(N, M, {
            0, 0, 0, 0, 0, 0, 0, 3, 0,
            0, 6, 2, 0, 0, 4, 0, 0, 8,
            5, 0, 0, 0, 0, 0, 7, 0, 0,
            9, 1, 0, 5, 0, 0, 0, 0, 7,
            0, 5, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 7, 0, 4, 2, 0, 0, 0,
            0, 0, 1, 0, 7, 0, 0, 0, 6,
            0, 0, 0, 9, 0, 6, 8, 0, 0,
            7, 0, 0, 0, 5, 0, 0, 0, 0,
        });
        internal::solve_and_display(g);
    }

    static void test_solver_8()
    {
        std::size_t N = 3, M = 3;
        grid g(N, M, {
            0, 0, 0, 1, 0, 0, 6, 0, 0,
            0, 0, 2, 5, 0, 8, 0, 0, 0,
            0, 5, 0, 7, 0, 0, 2, 1, 0,
            0, 0, 0, 0, 0, 0, 9, 0, 6,
            2, 0, 6, 0, 4, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 3,
            1, 9, 0, 0, 0, 7, 0, 0, 8,
            0, 0, 0, 0, 0, 5, 3, 0, 0,
            0, 0, 4, 0, 0, 0, 0, 9, 0,
        });
        internal::solve_and_display(g);
    }

    static void test_solver_9()
    {
        std::size_t N = 3, M = 3;
        grid g(N, M, {
            5, 3, 0, 0, 7, 0, 0, 0, 0,
            6, 0, 0, 1, 9, 5, 0, 0, 0,
            0, 9, 8, 0, 0, 0, 0, 6, 0,
            8, 0, 0, 0, 6, 0, 0, 0, 3,
            4, 0, 0, 8, 0, 3, 0, 0, 1,
            7, 0, 0, 0, 2, 0, 0, 0, 6,
            0, 6, 0, 0, 0, 0, 2, 8, 0,
            0, 0, 0, 4, 1, 9, 0, 0, 5,
            0, 0, 0, 0, 8, 0, 0, 7, 9,
        });
        internal::solve_and_display(g);
    }

    static void test_interactive()
    {
        std::cout << "1: sudoku config #1     2: sudoku config #2     3: sudoku config #3\n";
        std::cout << "4: sudoku config #4     5: sudoku config #5     6: sudoku config #6\n";
        std::cout << "7: sudoku config #7     8: sudoku config #8     9: sudoku config #9\n";
        std::cout << "0: run iterators\n";

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '0':
                {
                    test_iterators();
                }
                break;
            case '1':			
                {
                    test_solver_1();
                }
                break;
            case '2':
                {
                    test_solver_2();
                }
                break;
            case '3':
                {
                    test_solver_3();
                }
            break;
            case '4':
                {
                    test_solver_4();
                }
            break;
            case '5':
                {
                    test_solver_5();
                }
                break;
            case '6':
                {
                    test_solver_6();
                }
                break;
            case '7':
                {
                    test_solver_7();
                }
                break;
            case '8':
                {
                    test_solver_8();
                }
                break;
            case '9':
                {
                    test_solver_9();
                }
                break;
            default:
                std::cout << "input ignored\n";
                break;
            }
        }
    }
}

int sudoku_solver_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using sudoku_solver::test_interactive;
    
    if (run_tests)
    {
        test_interactive();
    }

    return 0;
}