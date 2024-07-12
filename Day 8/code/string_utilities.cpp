//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 string_utilities.t.cpp string_utilities.cpp -o string_utilities.exe
//cl /Fo.\obj\ /EHsc /O2 string_utilities.t.cpp string_utilities.cpp /link /out:string_utilities.exe

int string_utilities_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

int main(int argc, char *argv[])
{
    string_utilities_main(argc, argv, true, false);	
    return 0;
}