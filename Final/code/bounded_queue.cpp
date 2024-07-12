//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 bounded_queue.t.cpp bounded_queue.cpp -o bounded_queue.exe
//cl /Fo.\obj\ /EHsc /O2 bounded_queue.t.cpp bounded_queue.cpp /link /out:bounded_queue.exe

int bounded_queue_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

int main(int argc, char *argv[])
{
    bounded_queue_main(argc, argv, true, false);
    return 0;
}