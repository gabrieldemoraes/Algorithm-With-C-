//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 gale_shapley_stable_matching.t.cpp gale_shapley_stable_matching.cpp -o gale_shapley_stable_matching.exe
//cl /Fo.\obj\ /EHsc /O2 gale_shapley_stable_matching.t.cpp gale_shapley_stable_matching.cpp /link /out:gale_shapley_stable_matching.exe

int gale_shapley_stable_matching_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

int main(int argc, char *argv[])
{
    gale_shapley_stable_matching_main(argc, argv, true, false);	
    return 0;
}