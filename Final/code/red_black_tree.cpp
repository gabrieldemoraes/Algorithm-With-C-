//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 red_black_tree.t.cpp red_black_tree.cpp -o red_black_tree.exe
//cl /Fo.\obj\ /EHsc /O2 red_black_tree.t.cpp red_black_tree.cpp /link /out:red_black_tree.exe

int red_black_tree_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

int main(int argc, char *argv[])
{
    red_black_tree_main(argc, argv, true, false);
    return 0;
}