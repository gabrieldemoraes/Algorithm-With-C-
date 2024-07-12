//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 sudoku_solver.t.cpp sudoku_solver.cpp -o sudoku_solver.exe
//cl /Fo.\obj\ /EHsc /O2 sudoku_solver.t.cpp sudoku_solver.cpp /link /out:sudoku_solver.exe

int sudoku_solver_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

int main(int argc, char *argv[])
{
    sudoku_solver_main(argc, argv, true, false);
    return 0;
}