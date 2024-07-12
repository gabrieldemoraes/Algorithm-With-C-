//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 bounded_ring_buffer.t.cpp bounded_ring_buffer.cpp -o bounded_ring_buffer.exe
//cl /Fo.\obj\ /EHsc /O2 bounded_ring_buffer.t.cpp bounded_ring_buffer.cpp /link /out:bounded_ring_buffer.exe

int bounded_ring_buffer_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

int main(int argc, char *argv[])
{
    bounded_ring_buffer_main(argc, argv, true, false);
    return 0;
}