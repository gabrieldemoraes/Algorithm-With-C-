//g++ -O3 coin_change.cpp -o coin_change.exe

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "coin_change.hpp"

int main()
{
    Solution s;
    std::vector<int> v;
    v.push_back(186);
    v.push_back(419);
    v.push_back(83);
    v.push_back(408);

    int result = s.coinC2hange(v, 6249);

    return 0;

}