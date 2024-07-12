//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 separate_chain_hashtable.t.cpp separate_chain_hashtable.cpp -o separate_chain_hashtable.exe
//cl /Fo.\obj\ /EHsc /O2 separate_chain_hashtable.t.cpp separate_chain_hashtable.cpp /link /out:separate_chain_hashtable.exe

int separate_chain_hashtable_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

int main(int argc, char *argv[])
{
    separate_chain_hashtable_main(argc, argv, true, false);
    return 0;
}