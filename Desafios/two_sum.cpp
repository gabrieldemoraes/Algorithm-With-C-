//g++ -O3 two_sum.cpp -o two_sum.exe
#include "two_sum.hpp"
#include<iostream>

int main()
{

    Solution s;

    std::vector<int> v;
    v.push_back(2);
    v.push_back(7);
    v.push_back(11);
    v.push_back(15);

    std::vector<int> r;
    r = s.twoSum(v, 9);

    for(int i = 0; i < r.size(); ++i)

    return 0;
}