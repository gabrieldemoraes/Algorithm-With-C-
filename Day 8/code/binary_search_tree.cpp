//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 binary_search_tree.t.cpp binary_search_tree.cpp -o binary_search_tree.exe
//cl /Fo.\obj\ /EHsc /O2 binary_search_tree.t.cpp binary_search_tree.cpp /link /out:binary_search_tree.exe

int binary_search_tree_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

int main(int argc, char *argv[])
{
    binary_search_tree_main(argc, argv, true, false);
    return 0;
}