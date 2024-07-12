//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 bloom_filter.t.cpp bloom_filter.cpp -o bloom_filter.exe
//cl /Fo.\obj\ /EHsc /O2 bloom_filter.t.cpp bloom_filter.cpp /link /out:bloom_filter.exe

int bloom_filter_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

int main(int argc, char *argv[])
{
    bloom_filter_main(argc, argv, true, false);
    return 0;
}