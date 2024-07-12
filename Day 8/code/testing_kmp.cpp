//g++ -O3 testing_kmp.cpp -o testing_kmp.exe


#include "substring_kmp_searcher.hpp"

using namespace substring_searcher;
int main()
{
    const knuth_morris_pratt kmp_searcher("ABABAC");

    kmp_searcher.search("AABABCAAABABAC");
}