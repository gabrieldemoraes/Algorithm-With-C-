//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 unbounded_heap.t.cpp unbounded_heap.cpp -o unbounded_heap.exe
//cl /Fo.\obj\ /EHsc /O2 unbounded_heap.t.cpp unbounded_heap.cpp /link /out:unbounded_heap.exe

int unbounded_heap_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

int main(int argc, char *argv[])
{
    unbounded_heap_main(argc, argv, true, false);
    return 0;
}