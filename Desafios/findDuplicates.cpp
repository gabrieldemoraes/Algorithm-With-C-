//g++ -O3 findDuplicates.cpp -o findDuplicates.exe

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "findDuplicates.hpp"

std::vector<int> findDuplicates_V0(std::vector<int>& nums);

int main()
{
    Solution s;
    std::vector<int> v;
    v.push_back(1);
    v.push_back(4);
    v.push_back(1);
    v.push_back(4);
    v.push_back(5);

    std::vector<int> result = s.findDuplicates_V1(v);

    for (int i = 0; i < result.size(); ++i)
    {
        std::cout << result[i] << std::endl;
    }

    return 0;

}