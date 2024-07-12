//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 stack_adapter.t.cpp stack_adapter.cpp -o stack_adapter.exe
//cl /Fo.\obj\ /EHsc /O2 stack_adapter.t.cpp stack_adapter.cpp /link /out:stack_adapter.exe

int stack_adapter_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

int main(int argc, char *argv[])
{
    stack_adapter_main(argc, argv, true, false);	
    return 0;
}