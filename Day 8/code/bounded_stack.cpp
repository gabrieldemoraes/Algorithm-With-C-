//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 bounded_stack.t.cpp bounded_stack.cpp -o bounded_stack.exe
//cl /Fo.\obj\ /EHsc /O2 bounded_stack.t.cpp bounded_stack.cpp /link /out:bounded_stack.exe

int bounded_stack_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

int main(int argc, char *argv[])
{
    bounded_stack_main(argc, argv, true, false);
    return 0;
}