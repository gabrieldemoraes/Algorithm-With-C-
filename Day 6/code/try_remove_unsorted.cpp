//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 try_remove_unsorted.t.cpp try_remove_unsorted.cpp -o try_remove_unsorted.exe
//cl /Fo.\obj\ /EHsc /O2 try_remove_unsorted.t.cpp try_remove_unsorted.cpp /link /out:try_remove_unsorted.exe

int try_remove_unsorted_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

int main(int argc, char *argv[])
{
    try_remove_unsorted_main(argc, argv, true, false);	
    return 0;
}