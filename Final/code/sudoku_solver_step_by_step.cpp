//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 sudoku_solver_step_by_step.cpp -o sudoku_solver_step_by_step.exe
//cl /Fo.\obj\ /EHsc /O2 sudoku_solver_step_by_step.cpp /link /out:sudoku_solver_step_by_step.exe

#include "sudoku_solver.hpp"

#include <cstddef>
#include <iostream>
#include <iomanip>
#include <chrono>

using sudoku_solver::grid;

static void solve_and_display_step_by_step(grid& g)
{
    std::cout << "init:\n";
    std::cout << g.to_string();
    std::cout << "\n";

    auto start = std::chrono::high_resolution_clock::now();
    bool solved = sudoku_solver::solve(g, [](grid& g, std::size_t row, std::size_t column) {
        std::cout << "row: " << row << " column: " << column << "\n" << g.to_string() << "\n";
    });
    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << "solved? " << std::boolalpha << solved;			
    std::cout << "\nresult:\n";
    std::cout << g.to_string();
    std::cerr << "Time elapsed = " << ((stop - start).count() / 1000000.0) << " milliseconds\n";
    std::cout << "\n";
}

static void solve_mini_1()
{
    std::size_t N = 2, M = 2;
    grid g(N, M, {
        2, 0, 0, 3,
        0, 0, 0, 1,
        1, 0, 0, 0,
        3, 0, 0, 2,
    });
    solve_and_display_step_by_step(g);
}

static void solve_1()
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
    solve_and_display_step_by_step(g);
}

int main()
{
    //solve_mini_1();
    solve_1();
    return 0;
}