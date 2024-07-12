//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 linear_probing_hashtable.t.cpp linear_probing_hashtable.cpp -o linear_probing_hashtable.exe
//cl /Fo.\obj\ /EHsc /O2 linear_probing_hashtable.t.cpp linear_probing_hashtable.cpp /link /out:linear_probing_hashtable.exe

int linear_probing_hashtable_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

int main(int argc, char *argv[])
{
    linear_probing_hashtable_main(argc, argv, true, false);
    return 0;
}