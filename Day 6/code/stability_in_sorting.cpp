//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 stability_in_sorting.t.cpp stability_in_sorting.cpp -o stability_in_sorting.exe
//cl /Fo.\obj\ /EHsc /O2 stability_in_sorting.t.cpp stability_in_sorting.cpp /link /out:stability_in_sorting.exe

int stability_in_sorting_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

int main(int argc, char *argv[])
{
    stability_in_sorting_main(argc, argv, true, false);	
    return 0;
}